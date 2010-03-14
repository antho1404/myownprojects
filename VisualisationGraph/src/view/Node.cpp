/**
  * @author Estebe Anthony
  */
  
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QInputDialog>

#if defined(WIN32) || defined(WIN64)
#include <time.h>
#endif

#include "Edge.h"
#include "Node.h"
#include "GraphWidget.h"
#include "MainFrame.h"

static Node *selectedNode;
static double _time;

Node::Node(GraphWidget *graphWidget, string number, string tag, string state) {
	selectedNode = NULL;
	graph = graphWidget;
	this->number = number;
	this->tag = tag;
	this->state = atoi(state.c_str());
	this->color1 = new QColor[6];
	color1[0] = Qt::cyan;
	color1[1] = Qt::blue;
	color1[2] = Qt::red;
	color1[3] = Qt::gray;
	color1[4] = Qt::magenta;
	color1[5] = Qt::green;
	this->color2 = new QColor[6];
	color2[0] = Qt::darkCyan;
	color2[1] = Qt::darkBlue;
	color2[2] = Qt::darkRed;
	color2[3] = Qt::darkGray;
	color2[4] = Qt::darkMagenta;
	color2[5] = Qt::darkGreen;
	setToolTip(QString().fromStdString(tag));
	setFlag( ItemIsMovable);
#if defined(WIN32) || defined(WIN64)
        setFlag(ItemSendsGeometryChanges);
#endif
	setCacheMode( DeviceCoordinateCache);
	setZValue(1);
	force = settings.value("node/force", .2).toDouble();
}

void Node::addEdge(Edge *edge) {
	edgeList << edge;
	edge->adjust();
}

QList<Edge *> Node::edges() const {
	return edgeList;
}

void Node::calculateForces() {
	if (!scene() || scene()->mouseGrabberItem() == this) {
		newPos = pos();
		return;
	}

	// Sum up all forces pushing this item away
	qreal xvel = 0;
	qreal yvel = 0;
	foreach (QGraphicsItem *item, scene()->items()) {
		Node *node = qgraphicsitem_cast<Node *>(item);
		if (!node)
		continue;

		QLineF line(mapFromItem(node, 0, 0), QPointF(0, 0));
		qreal dx = line.dx();
		qreal dy = line.dy();
		double l = force * (dx * dx + dy * dy);
		if (l > 0) {
			xvel += (dx * 150.0) / l;
			yvel += (dy * 150.0) / l;
		}
	}

	// Now subtract all forces pulling items together
	double weight = (edgeList.size() + 1) * 10;
	foreach (Edge *edge, edgeList) {
		QPointF pos;
		if (edge->sourceNode() == this)
		pos = mapFromItem(edge->destNode(), 0, 0);
		else
		pos = mapFromItem(edge->sourceNode(), 0, 0);
		xvel += pos.x() / weight;
		yvel += pos.y() / weight;
	}

	if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
		xvel = yvel = 0;

	QRectF sceneRect = scene()->sceneRect();
	newPos = pos() + QPointF(xvel, yvel);
	newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right()
			- 10));
	newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom()
			- 10));
}

bool Node::advance() {
	if (newPos == pos())
		return false;
	setPos(newPos);
	return true;
}

QRectF Node::boundingRect() const {
	qreal adjust = 2;
	return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const {
	QPainterPath path;
	path.addEllipse(-10, -10, 20, 20);
	return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *) {
//	painter->setPen(Qt::NoPen);
//	painter->setBrush(Qt::darkGray);
//	painter->drawEllipse(-7, -7, 20, 20);

	QRadialGradient gradient(-3, -3, 10);
	QColor colorPrim, colorSec;

	if (state == -1) {
		setCursor(Qt::OpenHandCursor);
		colorPrim = QColor(Qt::yellow);
		colorSec = QColor(Qt::darkYellow);
	} else {
		setCursor(Qt::ArrowCursor);
		colorPrim = color1[state];
		colorSec = color2[state];
	}

	if (option->state & QStyle::State_Sunken) {
		gradient.setCenter(3, 3);
		gradient.setFocalPoint(3, 3);
		gradient.setColorAt(1, colorPrim.light(120));
		gradient.setColorAt(0, colorSec.light(120));
	} else {
		gradient.setColorAt(0, colorPrim);
		gradient.setColorAt(1, colorSec);
	}
	painter->setBrush(gradient);
	painter->setPen(QPen(Qt::black, 0));
	painter->drawEllipse(-10, -10, 20, 20);
	if (getNumber() >= 10)
		painter->drawText(-8, 4, QString().fromStdString(tag));
	else
		painter->drawText(-4, 4, QString().fromStdString(tag));
}

QPointF Node::getPos() {
	return newPos;
}

int Node::getNumber() {
	return atoi(number.c_str());
}

string Node::getTag() {
	return tag;
}

int Node::getState() {
	return state;
}

void Node::setNumber(string n) {
	this->number = n;
}

void Node::setTag(string tag) {
	this->tag = tag;
	setToolTip(QString().fromStdString(tag));
}

void Node::setState(string state) {
	this->state = atoi(state.c_str());
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
	switch (change) {
	case ItemPositionHasChanged:
		foreach (Edge *edge, edgeList)
		edge->adjust();
		graph->itemMoved();
		break;
	default:
		break;
	};
	return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if (state == -1) {
		graph->validNode(atoi(number.c_str()));
	} else {
		if(event->button() == Qt::RightButton){
			int state = QInputDialog::getInt(NULL, "Etat du noeud", "Etat", 0, 0);
			this->state = state;
			update();
			QString tag = QInputDialog::getText(NULL, "Tag du noeud", "tag");
			if(tag.size() > 0)
				this->tag = tag.toStdString();
		}
		else{
                        if ((selectedNode != NULL) && ((time(NULL) - _time) <= 1.5)) {
				bool ok = false;
				int val = QInputDialog::getInt(NULL, QString("Valeur de l'arc"), QString("valeur : "), 1, 0, 99999, 1, &ok);
				if(ok){
					int state = QInputDialog::getInt(NULL, "Etat de l'arc", QString().fromUtf8("0 : Pas visité\n1 : Visité\n2 : Dessus"), 0, 0, 2, 1, &ok);
					if(ok)
						graph->ctrl->addEdge(selectedNode->getNumber(), this->getNumber(), val, state);
				}
				selectedNode = NULL;
			} else {
				selectedNode = this;
				_time = time(NULL);
			}
		}
		update();
		QGraphicsItem::mousePressEvent(event);
	}
}
