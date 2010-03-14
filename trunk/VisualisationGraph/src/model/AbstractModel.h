/**
  * @author Estebe Anthony
  */
  
#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include <list>
#include "../observer/Observable.h"
#include "./Graph.h"

using namespace std;

class AbstractModel: virtual public Observable {
public:
	AbstractModel();
	virtual ~AbstractModel();

	virtual void createNewGraph() = 0;
	virtual void createGraph() = 0;
	virtual void setNodeSelected(int node) = 0;
	virtual void addNode(string tag, int state) = 0;
	virtual void addEdge(int nodeA, int nodeB, int value, int state) = 0;
	virtual void exportGraph(string dir) = 0;
	virtual void importGraph(string name, bool file) = 0;
	virtual string addAlgorithm(string name, string src) = 0;
	virtual string removeAlgorithm(string name) = 0;
	virtual void runAlgo(string name) = 0;
	virtual void changeAlgoSpeed(unsigned long speed) = 0;
	virtual void changeAlgoInteraction(int flag) = 0;
	virtual list<string> *getAlgoList() = 0;
	virtual list<string> *getGraphList() = 0;

	void addObserver(Observer* obs);
	void removeObserver();
	void notifyObserver(Graph* g);

private:
	list<Observer*> *observer;
};

#endif /* ABSTRACTMODEL_H_ */
