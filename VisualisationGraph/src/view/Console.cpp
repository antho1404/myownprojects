/**
  * @author Estebe Anthony
  */
  
#include "Console.h"
#include <iostream>

using namespace std;

Console::Console(ControllerModel* ctrl) {
	this->ctrl = ctrl;
}

Console::~Console() {
}

void Console::update(unsigned int size, list<string*>* summit, list<int*>* edges) {
	cout << size << "\nSummit" << endl;
	for (list<string*>::iterator it = summit->begin(); it != summit->end(); it++)
		cout << (*it)[_NUMBER] << " -> " << (*it)[_TAG] << "  _"
				<< (*it)[_STATE] << endl;
	cout << "Edges" << endl;
	for (list<int*>::iterator it = edges->begin(); it != edges->end(); it++) {
		cout << "(" << (*it)[_SOURCE_NODE] << "," << (*it)[_DEST_NODE] << "):"
				<< (*it)[_VALUE] << " __ " << (*it)[_EDGE_STATE] << "\t";
	}
	cout << endl;
}
