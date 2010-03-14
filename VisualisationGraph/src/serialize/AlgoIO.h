/**
  * @author Estebe Anthony
  */
  
#ifndef ALGOIO_H
#define ALGOIO_H

#include "Algo.h"

class AlgoIO {
public:
	virtual ~AlgoIO() {}
	virtual string saveAlgo(string title, string src, bool fromFile) = 0;
	virtual Algo* importAlgo(string algo) = 0;
	virtual void closeAlgo(Algo *a) = 0;
	virtual string deleteAlgo(string name) = 0;
	virtual list<string> *findAll() = 0;
};

#endif // ALGOIO_H
