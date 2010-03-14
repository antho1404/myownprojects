/**
  * @author Estebe Anthony
  */
  
#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

#define _not_colored 0	//when the edge was not visited
#define _colored 1		//when the edge was visited
#define _over 2			//when we are over the edge
class Node;

class Edge: public QGraphicsItem {
public:
	Edge(Node *sourceNode, Node *destNode, int value);
	~Edge();
	Node *sourceNode() const;
	void setSourceNode(Node *node);
	Node *destNode() const;
	void setDestNode(Node *node);
	void setValue(int value);
	void setState(int state);
	void showValue(bool show);
	void adjust();

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			QWidget *widget);

private:
	Node *source, *dest;
	int value;
	int state;
	bool valueVisible;
	QPointF sourcePoint;
	QPointF destPoint;
	qreal arrowSize;
};

#endif
