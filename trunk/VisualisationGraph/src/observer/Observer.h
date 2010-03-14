/**
  * @author Estebe Anthony
  */
  
#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <list>
#include <string>

using namespace std;

class Observer {
public:
	virtual ~Observer() {}
	virtual void update(unsigned int size, list<string*>* summit, list<int*>* edges) = 0;
};

#endif /* OBSERVER_H_ */
