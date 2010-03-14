/**
  * @author Estebe Anthony
  */
  
#include "test.h"

Test::Test(){

}

Test::~Test() {

}

void Test::run(Graph *g) {
	au->initAlgo(g);
	list<int> *n = new list<int>();
	for(int i=0; i<g->getOrder(); i++)
		n->push_back(i);
	int a = au->chooseNode(g, n);
	delete n;
	n = g->successors(a);
	for(list<int>::iterator it = n->begin(); it != n->end(); it++){
		g->setState(*it, g->getState(*it)+1);
		au->_sleep(1);
		au->notify(g);
	}
}

void Test::setAlgoUtils(AlgoUtils *au) {
	this->au = au;
}

extern "C" Algo* create(){
	return new Test;
}

extern "C" void destroy(Algo *a){
	delete a;
}
