/**
  * @author Estebe Anthony
  */
  
#ifndef TEST_H
#define TEST_H
#include "../Algo.h"

class Test : public Algo {
public :
	Test() ;
	virtual ~Test();
	void run(Graph *g);
	void setAlgoUtils(AlgoUtils *au);
private :
	AlgoUtils *au;
};

#endif

