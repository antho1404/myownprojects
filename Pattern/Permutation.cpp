#include "Permutation.h"
#include <iostream>

/**
 * Constructeur
 */

Permutation::Permutation(int *permut, int permutSize) : Result(permut, permutSize) {
	permutation = new int[permutSize];
	Permutation::permutSize = permutSize;
	for (int i=0; i<permutSize; i++){
		permutation[i] = permut[i];
	}
}

/**
 * Destructeur
 */

Permutation::~Permutation() {
	delete[] permutation;
}

/**
 * Methodes
 */

//retourne la taille de la permutation
int Permutation::getSize(){
	return permutSize;
}

//retourne le code gauche a l'indice ind
int Permutation::getLeftCodeVal(int ind){
	return Result::leftCode[ind];
}

//retourne le code droit a l'indice ind
int Permutation::getRightCodeVal(int ind){
	return Result::rightCode[ind];
}

//retourne l'index a l'indice ind
int Permutation::getIndex(int ind){
	return Result::indexTab[ind];
}

//retourne la valeur de la permutation a l'indice ind
int Permutation::getValue(int ind){
	return permutation[ind];
}
