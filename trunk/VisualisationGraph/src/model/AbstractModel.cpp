/**
  * @author Estebe Anthony
  */
  
#include <iostream>
#include "AbstractModel.h"

AbstractModel::AbstractModel() {
	observer = new list<Observer*> ;
}

AbstractModel::~AbstractModel() {
	delete observer;
}

void AbstractModel::addObserver(Observer * obs) {
	observer->push_back(obs);
}

void AbstractModel::removeObserver() {
	for (list<Observer*>::iterator it = observer->begin(); it
			!= observer->end(); it++)
		delete (*it);
	observer->clear();
}

void AbstractModel::notifyObserver(Graph* g) {
	int order = (g != NULL) ? g->getOrder() : 0;
	list<string*>* summit = (g != NULL) ? g->getSummits()
			: new list<string*> ();
	list<int*>* edges = (g != NULL) ? g->getEdges() : new list<int*> ();

	for (list<Observer*>::iterator it = observer->begin(); it
			!= observer->end(); it++)
		(*it)->update(order, summit, edges);

	for (list<int*>::iterator it = edges->begin(); it != edges->end(); it++)
		delete[] *it;
	for (list<string*>::iterator it = summit->begin(); it != summit->end(); it++)
		delete[] *it;
	delete summit;
	delete edges;
}

