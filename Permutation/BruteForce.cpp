#include "BruteForce.h"
#include "Echange.h"

/**
 * Constructeur
 */

BruteForce::BruteForce(GroupePermutation *g) : Result(g) {

    Result *algo = new Echange(group);
    Result::setDist(algo->getDist());
    for (int i=0; i<g->getDim(); i++)
    	changeMedian(algo->median);
	Result::setDist(algo->getDist());
	delete algo;

	currentPermutation = new int[g->getDim()];

    valUsed = new bool[group->getDim()];
	for (int i=0; i<group->getDim(); i++){
		valUsed[i] = false;
		currentPermutation[i] = 0;
	}
    search(0, 0);
}

/**
 * Destructeur
 */
BruteForce::~BruteForce(){
    delete[] currentPermutation;
    delete[] valUsed;
}


/**
 * Methodes
 */

//Methode récursive permettant de générer toutes les permutations possible et de sauvegarder la meilleure
void BruteForce::search(int rang, int distance){

	int d = 0;
	if (rang < group->getDim()) {						//condition d'arret
		for (int i=0; i < group->getDim(); i++) {		//parcours sur les valeurs possibles
			if(!valUsed[i]){				//valeurs non utilisée
				if (constraintVerified(i)){  // Si toutes les contraintes sont vérifiées
					d = distance;
					for (int ind = 0; ind < rang; ind++){
						d += Result::group->getDistance(currentPermutation[ind], i+1);
					}
					if (d <= Result::dist){
						currentPermutation[rang] = i+1;		//ajout de la valeur à l'indice rang
						valUsed[i]=true;
						search(rang+1, d);				//appel récursif au rang suivant
						valUsed[i] = false;
					}
				}
			}
		}
	}
	else {											//permutation générée
		d = Result::group->calculDistance(currentPermutation, -1);		//calcul de sa distance
		if (d <= Result::dist){
			if (d < Result::dist){		//si la distance est meilleure...
				Result::clearList();	// .. on supprime l'ancienne liste
				Result::setDist(d);		// et on réinitialise la distance de référence.
				Result::changeMedian(currentPermutation);
			}
			Result::addPermut(currentPermutation);	// On ajoute la nouvelle permutation à la liste.
		}
	}
}


// Fonction utilisée pour vérifier si toutes les contraintes sont respectées dans la permutation courante.
bool BruteForce::constraintVerified(int i){
	pair<int, int> *constraints;
	bool boolean=true;
	for (int ind=0; ind<group->getSizeOfConstraintsList(i); ind++){
		constraints = group->getConstraint(i, ind);
		if (constraints->first == i+1)	// Si l'indice envoyé est retrouvé en première valeur dans une paire
			if (valUsed[constraints->second-1])	 // Si la seconde valeur a déjà été rentrée dans la permutation.
				boolean = false;	// alors la contrainte n'est pas respectée.

		if (constraints->second == i+1) //Si l'indice envoyé est retrouvé en seconde valeur dans une paire
			if (!valUsed[constraints->first-1])	// Si première valeur n'a pas encore été utilisée dans la permutation
				boolean = false; // Alors la contrainte n'est pas respectée.
	}
	return boolean;
}


