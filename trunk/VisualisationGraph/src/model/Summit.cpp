/**
  * @author Estebe Anthony
  */
  
#include "Summit.h"
#include <sstream>

Summit::Summit(int number) {
	this->number = number;
	ostringstream out;
	out << number;
	this->tag = out.str();
	this->state = 0;
}

Summit::Summit(int number, string tag) {
	this->number = number;
	this->tag = tag;
	this->state = 0;
}

Summit::~Summit() {
}

int Summit::getNumber() {
	return number;
}

string Summit::getTag() {
	return tag;
}

void Summit::setTag(string tag) {
	this->tag = tag;
}

int Summit::getState() {
	return this->state;
}

void Summit::setState(int state) {
	this->state = state;
}
