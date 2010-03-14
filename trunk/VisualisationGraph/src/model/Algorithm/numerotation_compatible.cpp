/**
  * @author Estebe Anthony
  */
  
#include "numerotation_compatible.h"
#if defined(WIN32) || defined(WIN64)
#include <windows.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
	break;
	}
	return true;
}
#endif

Numerotation_compatible::Numerotation_compatible(){
	nodes = new list<int>();
}

Numerotation_compatible::~Numerotation_compatible(){
	delete nodes;
}

void Numerotation_compatible::run(Graph *g){
	this->g = g;
	int i = 0;
	for(int i=0; i<g->getOrder(); i++){
		nodes->push_back(i);
	}
	list<int> *source = getSources();
	int s;
	while(nodes->size() > 0 && source->size() > 0){
		s = au->chooseNode(g, source);
		i++;
		ostringstream tag;
		tag << i;
		g->setTag(s, tag.str());
		g->setState(s, 1);
		nodes->remove(s);
		delete source;
		source = getSources();
	}
}

void Numerotation_compatible::setAlgoUtils(AlgoUtils *au){
	this->au = au;
}

list<int>* Numerotation_compatible::getSources(){
	list<int> *src = new list<int>();
	list<int> *pred;
	int cpt;
	for(list<int>::iterator it = nodes->begin(); it != nodes->end(); it++){
		cpt = 0;
		pred = g->predecessors(*it);
		for(list<int>::iterator it2 = pred->begin(); it2 != pred->end(); it2++){
			if(contain(nodes, *it2)){
				cpt++;
			}
		}
		delete pred;
		if(cpt == 0)
			src->push_back(*it);
	}
	return src;
}

bool Numerotation_compatible::contain(list<int> *liste, int node){
	for(list<int>::iterator it = liste->begin(); it != liste->end(); it++)
		if(*it == node)
			return true;
	return false;
}

extern "C" Algo* create() {
	return new Numerotation_compatible();
}

extern "C" void destroy(Algo* a) {
	delete a;
}
