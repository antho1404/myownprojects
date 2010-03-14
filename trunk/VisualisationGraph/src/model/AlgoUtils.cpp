/**
  * @author Estebe Anthony
  */

#include "AlgoUtils.h"
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

AlgoUtils::AlgoUtils(){
	this->model = NULL;
	this->name = "Algo";
	this->selectedNode = -1;
	this->sleepTime = 1;
	this->flagInteraction = _USER;
}

AlgoUtils::AlgoUtils(AbstractModel *model) {
	this->model = model;
	this->name = "Algo";
	this->selectedNode = -1;
	this->sleepTime = 1;
	this->flagInteraction = _USER;
}

AlgoUtils::AlgoUtils(AbstractModel *model, string name) {
	this->model = model;
	this->name = name;
	this->selectedNode = -1;
	this->sleepTime = 1;
	this->flagInteraction = _USER;
}

void AlgoUtils::changeFlagInteraction(int flag){
	flagInteraction = flag;
}

void AlgoUtils::changeSpeed(unsigned long time){
	sleepTime = time;
}

void AlgoUtils::setName(string name) {
	this->name = name;
}

void AlgoUtils::setModel(AbstractModel *model){
	this->model = model;
}

string AlgoUtils::getName() {
	return this->name;
}

void AlgoUtils::_sleep(unsigned long time){
#if defined(WIN32) || defined(WIN64)
        Sleep(time);
#else
        sleep(time);
#endif
}

void AlgoUtils::initAlgo(Graph *g){
	for(int i=0; i<g->getOrder(); i++)
		g->setState(i, 0);
	list<int*> *edges = g->getEdges();
	for(list<int*>::iterator it=edges->begin(); it != edges->end(); it++){
		g->setEdgeState((*it)[_SOURCE_NODE], (*it)[_DEST_NODE], 0);
	}
}

int AlgoUtils::chooseNode(Graph *g, list<int>* nodes) {
	int result = *nodes->begin();
	int *tmpState = new int[nodes->size()];
	int i = 0;
	//Change states of nodes that permit to see which are selectable
	for (list<int>::iterator it = nodes->begin(); it != nodes->end(); it++) {
		tmpState[i] = g->getState(*it);
		g->setState(*it, _CHOICE_STATE);
		i++;
	}
	model->notifyObserver(g); //show the graph to the screen
	switch (flagInteraction) {
	case _FIFO: { //first value of the list nodes
		result = *nodes->begin();
		_sleep(sleepTime);
		break;
	}
	case _LIFO: { //last value of the list nodes
		list<int>::iterator it = nodes->end();
		it--;
		result = *it;
		_sleep(sleepTime);
		break;
	}
	case _RDM: { //random value into the list nodes
		int rdm = rand() % (nodes->size());
		list<int>::iterator it = nodes->begin();
		while (it != nodes->end() && rdm != 0) {
			it++;
			rdm--;
		}
		result = *it;
		_sleep(sleepTime);
		break;
	}
	case _USER: { //value given by the user selected into the list nodes
		while (selectedNode == -1) {
			_sleep(0.01);
		}
		result = selectedNode;
		selectedNode = -1;
		break;
	}
	default:
		break;
	}
	i = 0;
	//Rollback of the states not modified
	for (list<int>::iterator it = nodes->begin(); it != nodes->end(); it++) {
		g->setState(*it, tmpState[i]);
		i++;
	}
	delete[] tmpState;
	return result;
}

void AlgoUtils::setNodeSelected(int node) {
	selectedNode = node;
}

void AlgoUtils::notify(Graph *g){
	model->notifyObserver(g);
}
