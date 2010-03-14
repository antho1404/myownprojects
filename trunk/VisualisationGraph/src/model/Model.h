/**
  * @author Estebe Anthony
  */
  
#ifndef MODEL_H_
#define MODEL_H_

#include "AbstractModel.h"
#include "Algo.h"
#include "AlgoUtils.h"

class Model: public AbstractModel {
public:
	Model();
	virtual ~Model();
	void showGraph();

	virtual void createNewGraph();
	virtual void createGraph();
	virtual void setNodeSelected(int node);
	virtual void addNode(string tag, int state);
	virtual void addEdge(int nodeA, int nodeB, int value, int state);
	virtual void exportGraph(string dir);
	virtual void importGraph(string name, bool file);
	virtual string addAlgorithm(string name, string src);
	virtual string removeAlgorithm(string name);
	virtual void changeAlgoSpeed(unsigned long speed);
	virtual void changeAlgoInteraction(int flag);
	virtual list<string> *getAlgoList();
	virtual list<string> *getGraphList();

	virtual void runAlgo(string algoName);

private:
	Graph *g;
	Algo *algo;
	AlgoUtils *algoUtils;
	unsigned long algoSpeed;
	int algoInteraction;
};

#endif /* MODEL_H_ */
