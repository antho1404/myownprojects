#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_
#include "Pattern.h"
#include "Permutation.h"

class BruteForce {
	public:
		BruteForce(){}
		BruteForce(Permutation *permut, Pattern *pattern, bool allValues);
		virtual ~BruteForce();

	private:
		void boucle(int rang, int ind);		//permet de générer toutes les possibilités en récursif
		bool patternValidator(int *indiceTab);		//permet de savoir si le pattern est valid
		Permutation *permut;		//permutation courante
		Pattern *patternCourant;	//pattern courant
		int *tabIndice;				//tableau contenant les indice ou l'on insert le pattern
		int *indexTmp;
		bool *used;					//tableau des valeurs utilisé
		bool valueFind;
};

#endif /* BRUTEFORCE_H_ */
