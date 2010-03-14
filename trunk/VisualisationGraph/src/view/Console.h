/**
  * @author Estebe Anthony
  */
  
#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../observer/Observer.h"
#include "../controller/ControllerModel.h"
#include <list>

using namespace std;

class Console: virtual public Observer {
public:
	Console(ControllerModel* ctrl);
	virtual ~Console();
	void update(unsigned int size, list<string*>* summit, list<int*>* edges);
private:
	ControllerModel *ctrl;
};

#endif /* CONSOLE_H_ */
