#include "Result.h"
#include <iostream>
/**
 * Constructeur
 */

Result::Result(GroupePermutation *g){
    group = g;
    listBestPermut = new list<int*>();
    median = new int[group->getDim()];

    int ind = group->bestPermutation();
    dist = group->getPermutation(ind)->getDist();		//distance de la meilleur permutation de l'ensemble
    for (int i=0; i<group->getDim(); i++)
        median[i] = group->getPermutation(ind)->permut[i];	//initialisation de la médiane à la meilleur permutation de l'ensemble
    addPermut(median);
}

/**
 * Destructeur
 */

Result::~Result(){
	delete[] median;
	clearList();
	delete listBestPermut;
}

/**
 * Methodes
 */

void Result::changeMedian(int *tab){
	for (int i=0; i< group->getDim(); i++)		//sauvegarde de la médiane
		median[i] = tab[i];
}

void Result::addPermut(int* permut){
	tmpMedian = new int[group->getDim()];
	for (int i=0; i<group->getDim(); i++)
		tmpMedian[i] = permut[i];
	listBestPermut->push_back(tmpMedian);
}

void Result::clearList(){
	for (list<int*>::iterator it = listBestPermut->begin(); it!=listBestPermut->end(); it++)
		delete[] (*it);
	listBestPermut->clear();
}

void Result::setDist(int d){
	dist = d;
}

int Result::getDist(){
	return dist;
}

void Result::show(){
	cerr << "[";
	for (int i=0; i<group->getDim(); i++)
		cerr << median[i] << " ";
	cerr << "]             d = " << dist << endl;
}
