/**
  * @author Estebe Anthony
  */
  
#ifndef NUMEROTATION_COMPATIBLE_H
#define NUMEROTATION_COMPATIBLE_H

#include "../Algo.h"

class Numerotation_compatible : public Algo{
public:
	Numerotation_compatible();
	~Numerotation_compatible();
	void run(Graph *g);
	void setAlgoUtils(AlgoUtils *au);

private:
	list<int>* getSources();
	bool contain(list<int> *liste, int node);
	list<int> *nodes;
	AlgoUtils *au;
	Graph *g;
};

#endif // NUMEROTATION_COMPATIBLE_H
