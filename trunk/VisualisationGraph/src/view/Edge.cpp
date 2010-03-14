/**
  * @author Estebe Anthony
  */
  
#include <QPainter>
#include <math.h>
#include <sstream>
#include "Edge.h"
#include "Node.h"

Edge::Edge(Node *sourceNode, Node *destNode, int value) {
	valueVisible = true;
	arrowSize = 10;
	this->value = value;
	setAcceptedMouseButtons(0);
	source = sourceNode;
	dest = destNode;
	source->addEdge(this);
	dest->addEdge(this);
	setToolTip(QString().fromStdString(sourceNode->getTag()) + " -> "
			+ QString().fromStdString(destNode->getTag()));
	adjust();
}

Edge::~Edge() {
}

Node *Edge::sourceNode() const {
	return source;
}

void Edge::setSourceNode(Node *node) {
	source = node;
	setToolTip(QString().fromStdString(node->getTag()) + " -> "
			+ QString().fromStdString(dest->getTag()));
	adjust();
}

Node *Edge::destNode() const {
	return dest;
}

void Edge::setDestNode(Node *node) {
	dest = node;
	setToolTip(QString().fromStdString(source->getTag()) + " -> "
			+ QString().fromStdString(node->getTag()));
	adjust();
}

void Edge::setValue(int value) {
	this->value = value;
}

void Edge::setState(int state) {
	this->state = state;
}

void Edge::showValue(bool show) {
	valueVisible = show;
}

void Edge::adjust() {
	if (!source || !dest)
		return;

	QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
	qreal length = line.length();

	prepareGeometryChange();

	if (length > qreal(20.)) {
		QPointF
				edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
		sourcePoint = line.p1() + edgeOffset;
		destPoint = line.p2() - edgeOffset;
	} else {
		sourcePoint = destPoint = line.p1();
	}
}

QRectF Edge::boundingRect() const {
	if (!source || !dest)
		return QRectF();

	qreal penWidth = 1;
	qreal extra = (penWidth + arrowSize) / 2.0;

	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
			destPoint.y() - sourcePoint.y())).normalized().adjusted(-extra,
			-extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
	if (!source || !dest)
		return;
	// Draw the line
	switch (state) {
	case _not_colored:
		painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
		painter->setBrush(Qt::black);
		break;
	case _colored:
		painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
		painter->setBrush(Qt::red);
		break;
	case _over:
		painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
		painter->setBrush(Qt::red);
		break;
	}

	if(sourcePoint != destPoint){
		QLineF line(sourcePoint, destPoint);
		if (qFuzzyCompare(line.length(), qreal(0.)))
			return;

		painter->drawLine(line);
//	painter->drawArc(sourcePoint.x(), sourcePoint.y(), (destPoint.x()-sourcePoint.y()), (destPoint.y()-sourcePoint.y()), 10, 360);
		//Write the value of the edge
		if (valueVisible) {
			ostringstream val;
			val << value;
			painter->drawText(line.x1() + line.dx() / 2, line.y1() + line.dy() / 2,
					QString().fromStdString(val.str()));
		}

		// Draw the arrows
		double angle = acos(line.dx() / line.length());
		if (line.dy() >= 0)
			angle = (2 * M_PI) - angle;

		QPointF destArrowP1 = destPoint + QPointF(
				sin(angle - M_PI / 3) * arrowSize, cos(angle - M_PI / 3)
						* arrowSize);
		QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3)
				* arrowSize, cos(angle - M_PI + M_PI / 3) * arrowSize);

		painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
	}
	else{
		painter->setBrush(Qt::NoBrush);
		painter->drawEllipse(sourcePoint.x(), sourcePoint.y(), 20, 20);
		if (valueVisible) {
			ostringstream val;
			val << value;
			painter->drawText(sourcePoint.x()+20, sourcePoint.y()+20,
					QString().fromStdString(val.str()));
		}
	}
}
