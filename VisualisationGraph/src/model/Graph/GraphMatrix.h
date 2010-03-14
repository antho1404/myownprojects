/**
  * @author Estebe Anthony
  */
  
#ifndef GRAPHMATRIX_H_
#define GRAPHMATRIX_H_

#include "../Graph.h"

#define _NO_VALUE -1
#define _DEFAULT_VALUE 1

class GraphMatrix: public Graph {
public:
	GraphMatrix(int size);
	GraphMatrix(int size, string name);
	virtual ~GraphMatrix();

	/**
	 * Virtual methods from Graph class
	 * @see Graph Class
	 */
	virtual void addEdge(int nodeA, int nodeB);
	virtual void removeEdge(int nodeA, int nodeB);
	virtual int addNode();
	virtual void removeNode(int node);
	virtual bool isSuccessor(int nodeA, int nodeB);
	virtual list<int>* successors(int node);
	virtual list<int>* predecessors(int node);
	virtual list<string*>* getSummits();
	virtual void setState(int node, int state);
	virtual int getState(int node);
	virtual void setTag(int node, string tag);
	virtual string getTag(int node);
	virtual int getEdgeValue(int nodeA, int nodeB);
	virtual void setEdgeValue(int nodeA, int nodeB, int value);
	virtual int getEdgeState(int nodeA, int nodeB);
	virtual void setEdgeState(int nodeA, int nodeB, int state);

	//        End of virtual methods from Graph class

	void showGraph() {
		for (int i = 0; i < getOrder(); i++) {
			for (int j = 0; j < getOrder(); j++)
				cerr << matrix[i][j] << " ";
			cerr << endl;
		}
	}
	;

private:
	int ** matrix; //matrix that represent the graph
	Summit** summits; //summit of the graph
	int **stateEdge; //state of the edges
};

#endif /* GRAPHMATRIX_H_ */
