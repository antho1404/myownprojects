#include "Result.h"

/**
 * Constructor
 */

Result:: Result(GroupPermutation *gp){
	perfectMedian = false;
	permutations = gp;
	listBestPermut = new std::list<int*>();
	mediane = new int[gp->getSize()];
	distOpt = (gp->getSize()*(gp->getSize()-1))/2;
}

/**
 * Destructor
 */

Result::~Result(){
	clearList();
	delete listBestPermut;
	delete[] mediane;
}

/**
 * Mehods
 */

//remet � zero la liste de sauvegarde des medianes
void Result::clearList(){
	for (std::list<int*>::iterator it = listBestPermut->begin(); it!=listBestPermut->end(); it++)
		delete[] (*it);
	listBestPermut->clear();
}

//sauvegarde une mediane
void Result::addPermut(int* permut){
	tmpMedian = new int[permutations->getSize()];
	for (int i=0; i<permutations->getSize(); i++){
		tmpMedian[i] = permut[i];
	}
	listBestPermut->push_back(tmpMedian);
}

//modifit la distance
void Result::setDist(float d){
	distOpt = d;
}

//retourne la distance de la mediane
int Result::getDist(){
	return distOpt;
}
