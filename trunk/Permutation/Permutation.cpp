#include "Permutation.h"

/**
 * Constructeur
 */

Permutation::Permutation(int *p, int taille){
    size = taille;
	permut = new int[size];
	indiceTab = new int[size];
	for (int i=0; i<size; i++){
		permut[i] = p[i];
		indiceTab[permut[i] - 1] = i;
	}
	dist = 0;
}

/**
 * Destructeur
 */

Permutation::~Permutation() {
    delete[] permut;
    delete[] indiceTab;
}

/**
 * Methodes
 */

int Permutation::getIndiceOfValue(int value){
	return indiceTab[value];
}

int Permutation::permutationSize(){
    return size;
}

int Permutation::getDist(){
    return dist;
}

void Permutation::setDist(int d){
    dist = d;
}
