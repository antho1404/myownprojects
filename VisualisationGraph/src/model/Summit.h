/**
  * @author Estebe Anthony
  */
  
#ifndef SUMMIT_H_
#define SUMMIT_H_

#include <iostream>

using namespace std;

class Summit {
public:
	Summit(int number);
	Summit(int number, string tag);

	virtual ~Summit();

	int getNumber();
	string getTag();
	void setTag(string tag);
	int getState();
	void setState(int state);

private:
	int number;
	string tag;
	int state;
};

#endif /* SUMMIT_H_ */
