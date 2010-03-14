/**
  * @author Estebe Anthony
  */
  
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>
#include <QMessageBox>
#include <vector>
#include "../controller/ControllerModel.h"
#include "../observer/Observer.h"

class MainFrame;
class Node;
class Edge;

class GraphWidget: public QGraphicsView, virtual public Observer {
Q_OBJECT

public:
	GraphWidget(MainFrame *parent, ControllerModel *ctrl);
	~GraphWidget();

	void itemMoved();

	Node* createNode(int size, string num, string tag, string state);
	Node* createNode(string num, string tag, string state, int x, int y);
	Edge* createEdge(Node *source, Node *dest, int value, int state);

	QGraphicsScene* getScene();
	void update(unsigned int size, list<string*>* summit, list<int*>* edges);
	ControllerModel *ctrl;
	void resize();
	void setAnnimated(bool b);
	void showEdgesValues(bool b);

protected:
	void timerEvent(QTimerEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseDoubleClickEvent(QMouseEvent *event);


public slots:
	void validNode(int node);

private:
	bool annimated;
	bool edgeValue;
	MainFrame *parent;
	int order;
	vector<Node*> *nodesList;
	list<Edge*> *edgeList;
	int timerId;
};

#endif
