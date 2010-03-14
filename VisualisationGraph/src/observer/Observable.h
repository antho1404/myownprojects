/**
  * @author Estebe Anthony
  */
  
#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "Observer.h"
#include "../model/Graph.h"

class Observable {
public:

	virtual ~Observable() {}
	virtual void addObserver(Observer *obs) = 0;
	virtual void removeObserver() = 0;
	virtual void notifyObserver(Graph* g) = 0;
};

#endif /* OBSERVABLE_H_ */
