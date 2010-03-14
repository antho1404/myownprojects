/**
  * @author Estebe Anthony
  */
  
#ifndef DEEPSEARCH_H_
#define DEEPSEARCH_H_

#include "../Algo.h"

#define _NON_MARQUE 0
#define _MARQUE 1

class DeepSearch: public Algo {
public:
	DeepSearch();
	virtual ~DeepSearch();
	void run(Graph *g);
	void setAlgoUtils(AlgoUtils *au);

protected:

private:
	void search(int node);

	Graph *g;
	AlgoUtils *au;
	list<int> *desc;
};

#endif /* DEEPSEARCH_H_ */
