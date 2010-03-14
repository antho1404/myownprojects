/**
  * @author Estebe Anthony
  */
  
#ifndef CONTROLLERMODEL_H_
#define CONTROLLERMODEL_H_

#include <QThread>
#include "../model/AbstractModel.h"

class ControllerModel: public QThread {

public:
	ControllerModel(AbstractModel *m);
	virtual ~ControllerModel();

	void setNodeSelected(int node);
	void addNode(string tag, int state);
	void addEdge(int nodeA, int nodeB, int value, int state);
	void importGraph(string name, bool file);
	void newGraph();
	void generateGraph();
	void exportGraph(string dir);
	string addAlgorithm(string name, string src);
	string removeAlgorithm(string name);
	void setAlgo(string algo);
	void run();
	void changeAlgoSpeed(int speed);
	void changeAlgoInteraction(int flag);
	list<string> *getAlgoList();
	list<string> *getGraphList();

private:
	string algo;
	AbstractModel *model;
};

#endif /* CONTROLLERMODEL_H_ */
