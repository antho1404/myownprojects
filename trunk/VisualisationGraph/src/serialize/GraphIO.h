/**
  * @author Estebe Anthony
  */
  
#ifndef GRAPHIO_H
#define GRAPHIO_H

#include "Graph.h"

class GraphIO {
public:
	virtual ~GraphIO() {}
	virtual void exportGraph(Graph *g, string dir) = 0;
	virtual Graph* importGraph(string graph, bool file) = 0;
	virtual list<string> *findAll() = 0;
};

#endif // GRAPHIO_H
