#ifndef DATA_H_
#define DATA_H_
#include <iostream>
#include <list>

using namespace std;

class Data {
	public:
		Data(){}
		Data(int nb, list<pair<int, int>*> *listPair);
		virtual ~Data();
		string toString();

	private:
		int zeroMove;
		list<pair<int, int>*> *pos;
};

#endif /* DATA_H_ */
