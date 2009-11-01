#include "Data.h"
#include <sstream>

Data::Data(int nb, list<pair<int, int>*> *listPair) {
	Data::zeroMove = nb;
	pair<int, int>* p;
	pos = new list<pair<int, int>*>();
	for(list<pair<int, int>*>::iterator it=listPair->begin(); it!=listPair->end(); it++){
		p = new pair<int, int>;
		p->first = (*it)->first;
		p->second = (*it)->second;
		pos->push_back(p);
	}
//	cin.get();
}

Data::~Data() {
	for (list<pair<int, int>*>::iterator it=pos->begin(); it!=pos->end(); it++){
		delete *it;
	}
	delete pos;
}

string Data::toString(){
	string str;
	stringstream out;
	out << zeroMove;
	str += out.str();
	str += "  ";
	for (list<pair<int, int>*>::iterator it=pos->begin(); it!=pos->end(); it++){
		out << "(";
		out << (*it)->first;
		out << ",";
		out << (*it)->second;
		out << ")";
	}
	out << "#";
	return out.str();
}
