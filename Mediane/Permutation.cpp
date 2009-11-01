#include "Permutation.h"

/**
 * Constructor
 */

Permutation::Permutation(int *perm, int size) {
	permutSize = size;
	permut = new int[size];
	for (int i=0; i<size; i++)
		permut[i] = perm[i];
	matDist = new int*[size];
	int ind1 = 0;
	int ind2 = 0;
	int cpt;
	int ind;
	//initialisation de la matrice de distances
	for (int i=0; i<size; i++){
		matDist[i] = new int[size];
		for (int j=0; j<size; j++){
			if (i!=j){
				cpt = 0;
				ind = 0;
				while (ind < size && cpt < 2){
					if (permut[ind] == i+1){
						ind1 = ind;
						cpt++;
					}
					if (permut[ind] == j+1){
						ind2 = ind;
						cpt++;
					}
					ind++;
				}
				if (ind1 > ind2) matDist[i][j] = 1;		//pas dans le meme ordre
				else matDist[i][j] = 0;					//meme ordre
			}
			else matDist[i][j] = 0;						//valeurs impossible à atteindre
		}
	}
}

/**
 * Destructor
 */

Permutation::~Permutation() {
	for (int i=0; i<permutSize; i++)
		delete[] matDist[i];
	delete[] matDist;
	delete[] permut;
}

/**
 * Methods
 */

//retourne la distance entre la permutation et la mediane
int Permutation::calculTotalDist(int *mediane){
	int d = 0;
	for (int i=0; i<permutSize-1; i++)
		for (int j=i+1; j<permutSize; j++)
			d += getDist(mediane[i],mediane[j]);
	return d;
}

int Permutation::distPermut(){
	int d = 0;
	for (int i=0; i<permutSize-1; i++)
		for (int j=i+1; j<permutSize; j++)
			d += getDist(i+1,j+1);
	return d;
}

//retourne la distance de a vers b
int Permutation::getDist(int a, int b){
	return matDist[a-1][b-1];
}

//retourne la permutation
int* Permutation::getPermut(){
	return permut;
}
