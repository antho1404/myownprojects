/**
  * @author Estebe Anthony
  */
  
#include <iostream>
#include <sstream>
#include "GraphMatrix.h"

using namespace std;

GraphMatrix::GraphMatrix(int order) :
	Graph(order) {
	matrix = new int*[order];
	summits = new Summit*[order];
	stateEdge = new int*[order];
	for (int i = 0; i < order; i++) {
		summits[i] = new Summit(i);
		matrix[i] = new int[order];
		stateEdge[i] = new int[order];
	}
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++) {
			matrix[i][j] = _NO_VALUE;
			stateEdge[i][j] = _NOT_VISITED;
		}
}

GraphMatrix::GraphMatrix(int order, string name) :
	Graph(order, name) {
	matrix = new int*[order];
	summits = new Summit*[order];
	stateEdge = new int*[order];
	for (int i = 0; i < order; i++) {
		summits[i] = new Summit(i);
		matrix[i] = new int[order];
		stateEdge[i] = new int[order];
	}
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++) {
			matrix[i][j] = _NO_VALUE;
			stateEdge[i][j] = _NOT_VISITED;
		}
}

GraphMatrix::~GraphMatrix() {
	for (int i = 0; i < getOrder(); i++) {
		delete[] matrix[i];
		delete summits[i];
		delete[] stateEdge[i];
	}
	delete[] matrix;
	delete[] summits;
	delete[] stateEdge;
}

void GraphMatrix::addEdge(int nodeA, int nodeB) {
	if (nodeA < getOrder() && nodeB < getOrder() && nodeA >= 0 && nodeB >= 0)
		if(!isSuccessor(nodeB, nodeA))
			matrix[nodeA][nodeB] = _DEFAULT_VALUE;
		else
			cerr << "Adding edge : edge already exist\n";
	else
		cerr << "Adding edge : summit doesn't exists\n";
}

void GraphMatrix::removeEdge(int nodeA, int nodeB) {
	if (nodeA < getOrder() && nodeB < getOrder() && nodeA >= 0 && nodeB >= 0)
		matrix[nodeA][nodeB] = _NO_VALUE;
	else
		cerr << "Removing edge : summit doesn't exists\n";
}

int GraphMatrix::addNode() {
	int num = getOrder();
	int ** matrixtmp = new int*[num + 1];
	Summit** summitTmp = new Summit*[num + 1];
	int ** stateTmp = new int*[num + 1];
	for (int i = 0; i < num + 1; i++) {
		matrixtmp[i] = new int[num + 1];
		summitTmp[i] = (i < num) ? summits[i] : new Summit(i);
		stateTmp[i] = new int[num + 1];
		for (int j = 0; j < num + 1; j++) {
			if (j < getOrder() && i < num) {
				matrixtmp[i][j] = matrix[i][j];
				stateTmp[i][j] = stateEdge[i][j];
			} else {
				matrixtmp[i][j] = _NO_VALUE;
				stateTmp[i][j] = _NOT_VISITED;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		delete[] matrix[i];
		delete[] stateEdge[i];
	}
	delete[] matrix;
	delete[] summits;
	delete[] stateEdge;
	matrix = matrixtmp;
	summits = summitTmp;
	stateEdge = stateTmp;
	summits[num]->setState(0);
	setOrder(num + 1);
	return num;
}

void GraphMatrix::removeNode(int node) {
	if (node < getOrder() && node >= 0) {
		int ** matrixtmp = new int*[getOrder() - 1];
		Summit** summitTmp = new Summit*[getOrder() - 1];
		int ** stateTmp = new int*[getOrder() - 1];
		int indi = 0;
		int indj = 0;
		for (int i = 0; i < getOrder(); i++) {
			if (i != node) {
				matrixtmp[indi] = new int[getOrder() - 1];
				summitTmp[indi] = summits[i];
				stateTmp[indi] = new int[getOrder() - 1];
				indj = 0;
				for (int j = 0; j < getOrder(); j++) {
					if (j != node) {
						matrixtmp[indi][indj] = matrix[i][j];
						stateTmp[indi][indj] = stateEdge[i][j];
						indj++;
					}
				}
				indi++;
			} else
				delete summits[i];
		}
		for (int i = 0; i < getOrder(); i++) {
			delete[] matrix[i];
			delete[] stateEdge[i];
		}
		delete[] matrix;
		delete[] summits;
		delete[] stateEdge;
		matrix = matrixtmp;
		summits = summitTmp;
		stateEdge = stateTmp;
		setOrder(getOrder() - 1);
	} else
		cerr << "Removing summit : summit doesn't exist\n";
}

bool GraphMatrix::isSuccessor(int nodeA, int nodeB) {
	return matrix[nodeB][nodeA] >= 0;
}

list<int>* GraphMatrix::successors(int node) {
	list<int> *succ = new list<int> ();
	for (int i = 0; i < getOrder(); i++)
		if (isSuccessor(i, node))
			succ->push_back(i);
	return succ;
}
//
//int GraphMatrix::numberSuccessors(int node){
//	list<int> *tmp = successors(node);
//	int nb = tmp->size();
//	delete tmp;
//	return nb;
//}
//
//bool GraphMatrix::isPredecessor(int nodeA, int nodeB){
//        return matrix[nodeB][nodeA];	//TODO
//}
//
list<int>* GraphMatrix::predecessors(int node) {
	list<int> *pred = new list<int> ();
	for (int i = 0; i < getOrder(); i++)
		if (isPredecessor(i, node))
			pred->push_back(i);
	return pred;
}
//
//int GraphMatrix::numberPredecessors(int node){
//	list<int> *tmp = predecessors(node);
//	int nb = tmp->size();
//	delete tmp;
//	return nb;
//}
//
//bool GraphMatrix::isNeighbor(int nodeA, int nodeB){
//	return isSuccessor(nodeA, nodeB) || isPredecessor(nodeA, nodeB);
//}
//
//list<int>* GraphMatrix::neighbors(int node){
//	list<int> *neighbors = successors(node);
//	list<int> *tmp = predecessors(node);
//	for(list<int>::iterator it = tmp->begin(); it != tmp->end(); it++)	//append predecessors to successors
//		neighbors->push_back(*it);
//	delete tmp;
//	return neighbors;
//}
//
//int GraphMatrix::numberNeighbors(int node){
//	return numberPredecessors(node) + numberSuccessors(node);
//}
//
//
//bool GraphMatrix::isSymmetric(int nodeA, int nodeB){
//	if(nodeA < getOrder() && nodeB < getOrder() && nodeA >= 0 && nodeB >= 0)
//		return matrix[nodeA][nodeB] && matrix[nodeB][nodeA];
//	else{
//		cerr << "Symmetric : edge doesn't exist\n";
//		return false;
//	}
//}
//
//list<int>** GraphMatrix::getEdges(){
//	int s = getOrder();
//	list<int>** edges = new list<int>*[s];
//	for(int i=0; i<s; i++){
//		edges[i] = new list<int>();
//		for(int j=0; j<s; j++)
//			if(matrix[i][j])
//				edges[i]->push_back(j);
//	}
//	return edges;
//}
//
list<string*>* GraphMatrix::getSummits() {
	list<string*>* sum = new list<string*> ();
	string *tmp;
	for (int i = 0; i < getOrder(); i++) {
		tmp = new string[3];
		ostringstream num, stateStr;
		num << summits[i]->getNumber();
		stateStr << summits[i]->getState();
		tmp[_NUMBER] = num.str();
		tmp[_TAG] = summits[i]->getTag();
		tmp[_STATE] = stateStr.str();
		sum->push_back(tmp);
	}
	return sum;
}

void GraphMatrix::setState(int node, int state) {
	summits[node]->setState(state);
}

int GraphMatrix::getState(int node) {
	return summits[node]->getState();
}

void GraphMatrix::setTag(int node, string tag) {
	summits[node]->setTag(tag);
}

string GraphMatrix::getTag(int node) {
	return summits[node]->getTag();
}

int GraphMatrix::getEdgeValue(int nodeA, int nodeB) {
	return matrix[nodeA][nodeB];
}

void GraphMatrix::setEdgeValue(int nodeA, int nodeB, int value) {
	if (value >= 0)
		matrix[nodeA][nodeB] = value;
	else
		cerr << "setEdgeValue : value < 0" << endl;
}

int GraphMatrix::getEdgeState(int nodeA, int nodeB) {
	return stateEdge[nodeA][nodeB];
}

void GraphMatrix::setEdgeState(int nodeA, int nodeB, int state) {
	stateEdge[nodeA][nodeB] = state;
}

