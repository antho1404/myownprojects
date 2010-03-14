/**
  * @author Estebe Anthony
  */
  
#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "GraphIO.h"
#include "AlgoIO.h"
#include <iostream>

class Serialize {
public:
	static Serialize* getInstance();
	static void kill();
	GraphIO* graph();
	AlgoIO* algo();

private:
	Serialize();
	~Serialize();
	static Serialize *instance;
	GraphIO *objGraph;
	AlgoIO *objAlgo;
};

#endif // SERIALIZE_H
