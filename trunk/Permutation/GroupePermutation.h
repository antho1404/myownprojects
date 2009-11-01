#ifndef GROUPEPERMUTATION_H_
#define GROUPEPERMUTATION_H_
#include "Permutation.h"
#include <iostream>
#include <list>

using namespace std;

class GroupePermutation {
	public:
		GroupePermutation(){}
		GroupePermutation(int *perm1, int *perm2, int *perm3, int taillePermutation);
		virtual ~GroupePermutation();

        int calculDistance(int *pi, int params);	//retourne la distance d'une permutation
        int getDim();								//retourne la taille d'une permutation
        int getPermutationValue(int i);				//retourne la valeur d'une permutation à un indice donné
        int bestPermutation();						//retourne la permutation qui à la meilleure distance
        int getDistance(int a, int b);				//retourne la distance entre 2 valeurs
        Permutation* getPermutation(int i);			//retourne la permutation contenue dans la liste des permutation
        pair<int, int>* getConstraint(int i, int ind);	//retourne la contrainte demandée du tableau de listes.
        int getSizeOfConstraintsList(int ind);		//retourne la taille de la liste spécifiée du tableau.
        void show();

	private :
        void constraintCalcul();		//fonction calculant l'ensemble des contraintes de nos permutations initiales.
        Permutation **tabPermutation;	//tableau contenant les nb permutations
        int **matriceDist;				//matrice contenant les distances en tre chaques nombre
        list<pair<int, int>*> **tabConstraints;	//tableau de listes de contraintes;
};

#endif /* PERMUTATION_H_ */
