/**
  * @author Estebe Anthony
  */

#ifndef ALGO_H_
#define ALGO_H_

#include "AlgoUtils.h"

class Algo {
public:

	/**
	 * @fn virtual void run() = 0
	 * @brief Abstract method that permit to run an algorithm
	 */
	virtual void run(Graph *g) = 0;

	/**
	  * @fn virtual void setAlgoUtils(AlgoUtils *au) = 0
	  * @brief Assign an algoUtils object that permit to use functions of algorithm
	  * @param the algoUtils we want to assign
	  */
	virtual void setAlgoUtils(AlgoUtils *au) = 0;
};

typedef Algo* create_t();
typedef void destroy_t(Algo*);

#endif /* ALGO_H_ */
