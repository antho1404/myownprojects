/**
  * @author Estebe Anthony
  */
  
#ifndef NODE_H
#define NODE_H

#include <string>
#include <QGraphicsItem>
#include <QList>

using namespace std;

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

using namespace std;

class Node: public QGraphicsItem {

public:
	Node(GraphWidget *graphWidget, string number, string tag, string state);
	void addEdge(Edge *edge);
	QList<Edge *> edges() const;

	enum {
		Type = UserType + 1
	};
	int type() const {
		return Type;
	}

	void calculateForces();
	bool advance();
	QPainterPath shape() const;
	QPointF getPos();

	int getNumber();
	string getTag();
	int getState();
	void setNumber(string n);
	void setTag(string tag);
	void setState(string state);

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			QWidget *widget);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	QColor *color1;
	QColor *color2;
	QList<Edge *> edgeList;
	QPointF newPos;
	double force;
	string number;
	string tag;
	int state;
	GraphWidget *graph;
};

#endif
