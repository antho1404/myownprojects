#include "BruteForce.h"
#include "Heuristique.h"

/**
 * Constructeur
 */

BruteForce::BruteForce(GroupPermutation *g) : Result(g) {
    valUsed = new bool[permutations->getSize()];
    currentPermut = new int[permutations->getSize()];
	for (int i=0; i<permutations->getSize(); i++)
		valUsed[i] = false;
	Heuristique *h = new Heuristique(g, 4);
	if (h->perfectMedian){
		distOpt = h->getDist();
		perfectMedian = true;
	}
	delete h;
    search(0, 0, 0, 0);
}

/**
 * Destructeur
 */

BruteForce::~BruteForce(){
    delete[] valUsed;
    delete[] currentPermut;
}

/**
 * Methodes
 */

//Methode récursive permettant de générer toutes les permutations possible et de sauvegarder la meilleure
void BruteForce::search(int rang, int dist1, int dist2, int dist3){
	int d1, d2, d3, ind, i;
	bool isAccepted;
	if (rang < permutations->getSize()) {						//condition d'arret
		for (i=0; i < permutations->getSize(); i++){		//parcours sur les valeurs possibles
			if(!valUsed[i]){				//valeurs non utilisée
				d1 = dist1;
				d2 = dist2;
				d3 = dist3;
				ind = 0;
				isAccepted = true;
				while (ind < rang && isAccepted){
					if ((d1 >= distOpt) || (d2 >= distOpt) || (d3 >= distOpt))
						isAccepted = false;
					else{
						d1 += permutations->getDist(0, currentPermut[ind], i+1);
						d2 += permutations->getDist(1, currentPermut[ind], i+1);
						d3 += permutations->getDist(2, currentPermut[ind], i+1);
						ind++;
					}
				}
				if(isAccepted){
					currentPermut[rang] = i+1;		//ajout de la valeur à l'indice rang
					valUsed[i] = true;
					search(rang+1, d1, d2, d3);					//appel récursif au rang suivant
					valUsed[i] = false;
				}
			}
		}
	}
	else {
		if (permutations->equalDistance(currentPermut) && dist1 <= distOpt){
			if (!perfectMedian)
				perfectMedian = true;
			if (dist1 < distOpt){
				for (i = 0; i < i; i++)
					mediane[i] = currentPermut[i];
				clearList();
				setDist(dist1);
			}
			addPermut(currentPermut);
		}
	}
}
