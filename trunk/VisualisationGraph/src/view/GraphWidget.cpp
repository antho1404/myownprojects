/**
  * @author Estebe Anthony
  */
  
#include "GraphWidget.h"
#include "Edge.h"
#include "Node.h"

#include <QInputDialog>
#include <QGraphicsScene>
#include <math.h>

GraphWidget::GraphWidget(MainFrame *parent, ControllerModel *ctrl) {
	this->parent = parent;
	timerId = 0;
	this->ctrl = ctrl;
	nodesList = new vector<Node*> ();
	edgeList = new list<Edge*> ();
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	setResizeAnchor(AnchorViewCenter);
	setMinimumSize(250, 250);
	annimated = true;
	edgeValue = true;
}

GraphWidget::~GraphWidget() {
}

void GraphWidget::itemMoved() {
	if (!timerId)
		timerId = startTimer(1000 / 30);
}

Node* GraphWidget::createNode(int size, string num, string tag, string state) {
	int i = nodesList->size();
	int coeff = 150;
	Node *n = new Node(this, num, tag, state);
	n->setPos(coeff * cos((2 * (i + 1) * M_PI) / size), coeff * sin((2
			* (i + 1) * M_PI) / size));
	nodesList->push_back(n);
	getScene()->addItem(n);
	return n;
}

Node* GraphWidget::createNode(string num, string tag, string state, int x, int y) {
	Node *n = new Node(this, num, tag, state);
	n->setPos(x, y);
	nodesList->push_back(n);
	getScene()->addItem(n);
	return n;
}

Edge* GraphWidget::createEdge(Node *source, Node *dest, int value, int state) {
	list<Edge *>::iterator it = edgeList->begin();
	bool find = false;
	while (it != edgeList->end() && !find) {
		if (dest->getNumber() == (*it)->destNode()->getNumber()
				&& source->getNumber() == (*it)->sourceNode()->getNumber()) {
			find = true;
			(*it)->setState(state);
			(*it)->setValue(value);
		}
		it++;
	}
	if (!find) {
		Edge *edge = new Edge(source, dest, value);
		edge->setState(0);
		edgeList->push_back(edge);
		getScene()->addItem(edge);
		return edge;
	} else
		return NULL;
}

QGraphicsScene* GraphWidget::getScene() {
	return scene();
}

void GraphWidget::update(unsigned int size, list<string*>* summit, list<int*>* edges) {
	QGraphicsScene *scene = getScene();
	if (size == 0) {
		nodesList->clear();
		edgeList->clear();
		scene->items().clear();
		scene->clear();
	}
	//Update nodes
	Node *nFind = NULL;
	for (list<string*>::iterator it = summit->begin(); it != summit->end(); it++) {
		nFind = NULL;
		foreach(QGraphicsItem *item, scene->items()) //search if the node of summit is ever in the scene
			if(Node *node = qgraphicsitem_cast<Node *>(item))
				if(node->getNumber() == atoi(((*it)[_NUMBER]).c_str())) //the node of summit is in the scene
					nFind = node;
		if (nFind != NULL) { //if the node exist
			nFind->setTag((*it)[_TAG]);
			nFind->setState((*it)[_STATE]);
			nFind->update(-10, -10, 20, 20);
		} else  //create a node
			createNode(size, (*it)[_NUMBER], (*it)[_TAG], (*it)[_STATE]);
	}
	//update edges
	if (edgeList->size() == 0 || edgeList->size() != size)
		for (list<int*>::iterator it = edges->begin(); it != edges->end(); it++)
			createEdge(nodesList->at((*it)[_SOURCE_NODE]), nodesList->at(
					(*it)[_DEST_NODE]), (*it)[_VALUE], (*it)[_EDGE_STATE]);
	showEdgesValues(edgeValue);
}

void GraphWidget::timerEvent(QTimerEvent *event) {
	Q_UNUSED(event);
	if(annimated){
		QList<Node *> nodes;
		foreach (QGraphicsItem *item, scene()->items()) {
			if (Node *node = qgraphicsitem_cast<Node *>(item))
			nodes << node;
		}

		foreach (Node *node, nodes)
		node->calculateForces();

		bool itemsMoved = false;
		foreach (Node *node, nodes)
		if (node->advance())
		itemsMoved = true;

		if (!itemsMoved) {
			killTimer(timerId);
			timerId = 0;
		}
	}
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect) {
	Q_UNUSED(rect);

	// Shadow
	QRectF sceneRect = this->sceneRect();
	QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5,
			sceneRect.height());
	QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(),
			sceneRect.width(), 5);
	if (rightShadow.intersects(rect) || rightShadow.contains(rect))
		painter->fillRect(rightShadow, Qt::darkGray);
	if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
		painter->fillRect(bottomShadow, Qt::darkGray);

	// Fill
	QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
	gradient.setColorAt(0, Qt::white);
	gradient.setColorAt(1, Qt::lightGray);
	painter->fillRect(rect.intersect(sceneRect), gradient);
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(sceneRect);
}

void GraphWidget::validNode(int node) {
	ctrl->setNodeSelected(node);
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	bool ok = false;
	QString tag = QInputDialog::getText(NULL, QString("Tag du noeud"), QString("tag : "));
	if(!tag.isEmpty()){
		int state = QInputDialog::getInt(NULL, "Etat du noeud", QString().fromUtf8("Etat : "), 0, 0, 10, 1, &ok);
		if(ok)
			ctrl->addNode(tag.toStdString(), state);
	}
}

void GraphWidget::resize(){
	scene()->setSceneRect(-width()/2, -height()/2, width()-2, height()-2);
}

void GraphWidget::setAnnimated(bool b){
	annimated = b;
}

void GraphWidget::showEdgesValues(bool b){
	edgeValue = b;
	for(list<Edge*>::iterator it = edgeList->begin(); it != edgeList->end(); it++){
		(*it)->showValue(b);
		(*it)->adjust();
	}
}
