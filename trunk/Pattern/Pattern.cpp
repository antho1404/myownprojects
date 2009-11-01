#include <iostream>
#include "Pattern.h"

using namespace std;

/**
 * Constructeur
 */

Pattern::Pattern(int *patt, int pattSize) : Result(patt, pattSize){
	pattern = new int[pattSize];
	Pattern::pattSize = pattSize;
	for (int i=0; i<pattSize; i++){
		pattern[i] = patt[i];
	}
}

/**
 * Destructeur
 */

Pattern::~Pattern() {
	delete[] pattern;
}

/**
 * Methodes
 */

//retourne la taille du pattern
int Pattern::getSize(){
	return pattSize;
}

//retourne le code gauche a l'indice ind
int Pattern::getLeftCodeVal(int ind){
	return Result::leftCode[ind];
}

//retourne le code droit a l'indice ind
int Pattern::getRightCodeVal(int ind){
	return Result::rightCode[ind];
}

//retourne l'index a l'indice ind
int Pattern::getIndex(int ind){
	return Result::indexTab[ind];
}
