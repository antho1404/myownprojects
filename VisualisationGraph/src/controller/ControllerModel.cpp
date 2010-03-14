/**
  * @author Estebe Anthony
  */
  
#include "ControllerModel.h"

ControllerModel::ControllerModel(AbstractModel* m) {
	this->model = m;
}

ControllerModel::~ControllerModel() {
	delete model;
}

void ControllerModel::setNodeSelected(int node) {
	model->setNodeSelected(node);
}

void ControllerModel::addNode(string tag, int state) {
	model->addNode(tag, state);
}

void ControllerModel::addEdge(int nodeA, int nodeB, int value, int state) {
	model->addEdge(nodeA, nodeB, value, state);
}

void ControllerModel::importGraph(string name, bool file) {
	model->importGraph(name, file);
}

void ControllerModel::newGraph() {
	model->createNewGraph();
}

void ControllerModel::generateGraph() {
	model->createGraph();
}

void ControllerModel::exportGraph(string dir) {
	model->exportGraph(dir);
}

string ControllerModel::addAlgorithm(string name, string src){
	return model->addAlgorithm(name, src);
}

string ControllerModel::removeAlgorithm(string name){
	return model->removeAlgorithm(name);
}

void ControllerModel::setAlgo(string algo){
	this->algo = algo;
}

void ControllerModel::run() {
	model->runAlgo(algo);
}

void ControllerModel::changeAlgoSpeed(int speed){
	model->changeAlgoSpeed(speed);
}

void ControllerModel::changeAlgoInteraction(int flag){
	model->changeAlgoInteraction(flag);
}

list<string> *ControllerModel::getAlgoList(){
	return model->getAlgoList();
}

list<string> *ControllerModel::getGraphList(){
	return model->getGraphList();
}
