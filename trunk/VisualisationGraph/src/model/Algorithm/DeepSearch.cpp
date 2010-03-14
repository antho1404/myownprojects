/**
  * @author Estebe Anthony
  */
  
#include "DeepSearch.h"
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

DeepSearch::DeepSearch(){
	desc = new list<int>();
}

DeepSearch::~DeepSearch() {
	delete desc;
}

void DeepSearch::search(int node) {
	int n;
	list<int>* succ = g->successors(node);
	list<int>* ok = new list<int> ();
	for (list<int>::iterator it = succ->begin(); it != succ->end(); it++)
		if (g->getState(*it) == _NON_MARQUE)
			ok->push_back(*it);
	while (!ok->empty()) {
		for (list<int>::iterator it = ok->begin(); it != ok->end(); it++) {
			if (g->getState(*it) == _MARQUE) {
				ok->remove(*it);
				it--;
			}
		}
		if (!ok->empty()) {
			n = au->chooseNode(g, ok);
			desc->push_back(n);
			g->setState(n, _MARQUE);
			g->setEdgeState(node, n, _ON_EDGE);
			search(n);
			g->setEdgeState(node, n, _VISITED);
			au->_sleep(1);
			au->notify(g);
			ok->remove(n);
		}
	}
	delete succ;
	delete ok;
}

void DeepSearch::run(Graph *g) {
	this->g = g;
	desc->clear();
	list<int> *nodes = new list<int>();
	for (int i = 0; i < g->getOrder(); i++){
		g->setState(i, _NON_MARQUE);
		nodes->push_back(i);
	}
	int node = au->chooseNode(g, nodes);
	delete nodes;
	desc->push_back(node);
	g->setState(node, _MARQUE);
	search(node);
} 

void DeepSearch::setAlgoUtils(AlgoUtils *au){
	this->au = au;
}

extern "C" Algo* create() {
	return new DeepSearch();
}

extern "C" void destroy(Algo* a) {
	delete a;
}

