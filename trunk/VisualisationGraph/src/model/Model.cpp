/**
  * @author Estebe Anthony
  */
  
#include "Model.h"
#include "Graph/GraphMatrix.h"
#include "../serialize/Serialize.h"

using namespace std;

Model::Model() :
	AbstractModel() {
	g = new GraphMatrix(0, "Unknow");
	algoSpeed = 1;
	algoInteraction = _USER;
	algoUtils = new AlgoUtils();
}

Model::~Model() {
	delete g;
	delete algo;
	Serialize::kill();
}

void Model::showGraph() {
	notifyObserver(g);
}

void Model::createNewGraph() {
	notifyObserver(NULL);
	g = new GraphMatrix(0);
	notifyObserver(g);
}

void Model::createGraph() {
	notifyObserver(NULL);
	int size = -1;
	while (size <= 0)
		size = rand() % 20;
	int c = rand() % (size * size);
	g = new GraphMatrix(size, "Unknow");
	int nodeA, nodeB;
	for (int i = 0; i < c; i++){
		nodeA = rand() % size;
		nodeB = rand() % size;
		if(!g->isNeighbor(nodeA, nodeB))
			g->addEdge(nodeA, nodeB);
	}
	notifyObserver(g);
}

void Model::setNodeSelected(int node) {
	algoUtils->setNodeSelected(node);
}

void Model::addNode(string tag, int state) {
	int n = g->addNode();
	g->setState(n, state);
	g->setTag(n, tag);
	notifyObserver(g);
}

void Model::addEdge(int nodeA, int nodeB, int value, int state) {
	g->addEdge(nodeA, nodeB);
	g->setEdgeValue(nodeA, nodeB, value);
	g->setEdgeState(nodeA, nodeB, state);
	notifyObserver(g);
}

void Model::exportGraph(string dir) {
	Serialize::getInstance()->graph()->exportGraph(g, dir);
}

void Model::importGraph(string name, bool file) {
	notifyObserver(NULL);
	g = Serialize::getInstance()->graph()->importGraph(name, file);
	notifyObserver(g);
}

string Model::addAlgorithm(string name, string src){
	return Serialize::getInstance()->algo()->saveAlgo(name, src, true);
}

string Model::removeAlgorithm(string name){
	return Serialize::getInstance()->algo()->deleteAlgo(name);
}

void Model::runAlgo(string algoName) {
	algoUtils->setModel(this);
	algoUtils->changeFlagInteraction(algoInteraction);
	algoUtils->changeSpeed(algoSpeed);
	algoUtils->initAlgo(g);
	algo = Serialize::getInstance()->algo()->importAlgo(algoName);
	if(algo != NULL){
		algo->setAlgoUtils(algoUtils);
		algo->run(g);
		notifyObserver(g);
		Serialize::getInstance()->algo()->closeAlgo(algo);
	}
}

void Model::changeAlgoSpeed(unsigned long speed){
	algoSpeed = speed;
	algoUtils->changeSpeed(algoSpeed);
}

void Model::changeAlgoInteraction(int flag){
	algoInteraction = flag;
	algoUtils->changeFlagInteraction(algoInteraction);
}

list<string> *Model::getAlgoList(){
	return Serialize::getInstance()->algo()->findAll();
}

list<string> *Model::getGraphList(){
	return Serialize::getInstance()->graph()->findAll();
}
