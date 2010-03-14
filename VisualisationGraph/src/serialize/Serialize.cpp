/**
  * @author Estebe Anthony
  */
  
#include "Serialize.h"
#include "GraphXml.h"
#include "AlgoLoader.h"

Serialize *Serialize::instance = NULL;

Serialize::Serialize() {
	objGraph = NULL;
	objAlgo = NULL;
}

Serialize::~Serialize() {
	delete objAlgo;
	delete objGraph;
}

Serialize* Serialize::getInstance() {
	if (NULL == instance)
		instance = new Serialize();
	return instance;
}

void Serialize::kill() {
	if (NULL != instance) {
		delete instance;
		instance = NULL;
	}
}

AlgoIO* Serialize::algo() {
	if(objAlgo == NULL)
		objAlgo = new AlgoLoader();
	return objAlgo;
}

GraphIO* Serialize::graph() {
	if(objGraph == NULL)
		objGraph = new GraphXML();
	return objGraph;
}
