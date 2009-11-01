#include "BruteForce.h"

/**
 * Constructor
 */
BruteForce::BruteForce(Permutation *permut, Pattern *pattern, bool allValues) {
	double time = (double)clock();
	BruteForce::permut = permut;
	patternCourant = pattern;
	tabIndice = new int[pattern->getSize()];
	indexTmp = new int[pattern->getSize()];
	used = new bool[pattern->getSize()];
	valueFind = allValues;
	boucle(0,-1);
	cout << "\ttemps BruteForce : " << (double)(clock() - time)/1000000 << endl;

}

/**
 * Destructor
 */
BruteForce::~BruteForce() {
	delete[] tabIndice;
	delete[] indexTmp;
	delete[] used;
}

/**
 * Methods
 */

//permet de générer toutes les possibilités en récursif
void BruteForce::boucle(int rang, int ind){
	if (!valueFind){
		if (rang < patternCourant->getSize()){
			for (int i=ind+1; i<permut->getSize()-patternCourant->getSize()+rang+1; i++){
				tabIndice[rang] = i;
				boucle(rang+1, i);		//appel récursif
			}
		}
		else {
			if (patternValidator(tabIndice)){	//si le pattern est valid
				patternCourant->addPattern(tabIndice, rang);		//sauvegarde
				valueFind = true;
			}
		}
	}
}

//permet de savoir si le pattern est valid
bool BruteForce::patternValidator(int *indiceTab){
	for (int i=0; i<patternCourant->getSize(); i++)
		used[i] = false;
	int i = 0;
	int tmp, ind;
	while (i < patternCourant->getSize()){
		tmp = 0;
		ind = 0;
		for (int j=0; j<patternCourant->getSize(); j++){
			if (tmp < permut->getValue(indiceTab[j]) && !used[j]){
				tmp = permut->getValue(indiceTab[j]);
				ind  = j;
			}
		}
		indexTmp[ind] = i;
		used[ind] = true;
		if (indexTmp[ind] != patternCourant->getIndex(ind))
			return false;
		i++;
	}
	return true;
}
