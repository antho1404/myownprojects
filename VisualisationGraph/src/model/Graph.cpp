/**
  * @author Estebe Anthony
  */
  
#include "Graph.h"

Graph::Graph(int order) {
	this->order = order;
	this->state = new int[order];
	this->tags = new string[order];
	for (int i = 0; i < order; i++) {
		state[i] = 0;
		tags[i] = "";
	}
}

Graph::Graph(int order, string name) {
	this->order = order;
	this->name = name;
	this->state = new int[order];
	this->tags = new string[order];
	for (int i = 0; i < order; i++) {
		state[i] = 0;
	}
}

Graph::~Graph() {
	delete[] state;
	delete[] tags;
}

int Graph::getOrder() {
	return order;
}

void Graph::setOrder(int order) {
	this->order = order;
}

list<int>* Graph::successors(int node) {
	list<int>* succ = new list<int> ();
	for (int i = 0; i < order; i++) {
		if (isSuccessor(i, node))
			succ->push_back(i);
	}
	return succ;
}

int Graph::numberSuccessors(int node) {
	list<int>* s = successors(node);
	int size = s->size();
	delete s;
	return size;
}

bool Graph::isPredecessor(int nodeA, int nodeB) {
	return isSuccessor(nodeB, nodeA);
}

list<int>* Graph::predecessors(int node) {
	list<int>* pred = new list<int> ();
	for (int i = 0; i < order; i++) {
		if (isPredecessor(i, node))
			pred->push_back(i);
	}
	return pred;
}

int Graph::numberPredecessors(int node) {
	list<int>* p = predecessors(node);
	int size = p->size();
	delete p;
	return size;
}

bool Graph::isNeighbor(int nodeA, int nodeB) {
	return isSuccessor(nodeB, nodeA) || isSuccessor(nodeA, nodeB);
}

list<int>* Graph::neighbors(int node) {
	list<int>* neig = new list<int> ();
	for (int i = 0; i < order; i++) {
		if (isNeighbor(i, node))
			neig->push_back(i);
	}
	return neig;
}

int Graph::numberNeighbors(int node) {
	list<int>* n = neighbors(node);
	int size = n->size();
	delete n;
	return size;
}

bool Graph::isSymmetric(int nodeA, int nodeB) {
	return isSuccessor(nodeA, nodeB) && isSuccessor(nodeB, nodeA);
}

list<int*>* Graph::getEdges() {
	int n = getOrder();
	list<int*>* edges = new list<int*> ();
	int j;
	int *tmp;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (isSuccessor(i, j)) {
				tmp = new int[4];
				tmp[_SOURCE_NODE] = j;
				tmp[_DEST_NODE] = i;
				tmp[_VALUE] = getEdgeValue(j, i);
				tmp[_EDGE_STATE] = getEdgeState(j, i);
				edges->push_back(tmp);
			}
		}
	}
	return edges;
}

list<string*>* Graph::getSummits() {
	list<string*>* sum = new list<string*> ();
	string *tmp;
	for (int i = 0; i < getOrder(); i++) {
		tmp = new string[3];
		ostringstream num, state;
		num << i;
		state << this->state[i];
		tmp[_NUMBER] = num.str();
		tmp[_TAG] = this->tags[i].c_str();
		tmp[_STATE] = state.str();
		sum->push_back(tmp);
	}
	return sum;
}

void Graph::setState(int node, int state) {
	this->state[node] = state;
}

int Graph::getState(int node) {
	return state[node];
}

void Graph::setTag(int node, string tag) {
	this->tags[node].assign(tag, 0, tag.length());
}

void Graph::setTag(int node, int tag) {
	ostringstream num;
	num << tag;
	setTag(node, num.str());
}

string Graph::getTag(int node) {
	return tags[node];
}

int Graph::getTagInt(int node) {
	return atoi(tags[node].c_str());
}

string Graph::getName() {
	return name;
}

void Graph::setName(string name){
	this->name = name;
}
