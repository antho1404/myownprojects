#include "GroupPermutation.h"

/**
 * Constructor
 */
GroupPermutation::GroupPermutation(int *perm1, int *perm2, int *perm3, int size) {
	GroupPermutation::size = size;
	tabPermut = new Permutation*[3];
	tabPermut[0] = new Permutation(perm1, size);
	tabPermut[1] = new Permutation(perm2, size);
	tabPermut[2] = new Permutation(perm3, size);
}

/**
 * Destructor
 */
GroupPermutation::~GroupPermutation() {
	for (int i=0; i<3; i++){
		delete tabPermut[i];
	}
	delete[] tabPermut;
}

/**
 * Methods
 */

//retourne vrai si la m�diane est �quidistante
bool GroupPermutation::equalDistance(int *mediane){
	int i=1;
	int d = tabPermut[0]->calculTotalDist(mediane);
	while (i<3){
		if(d != tabPermut[i]->calculTotalDist(mediane)){
			return false;
		}
		i++;
	}
	return true;
}

//retourne la taille des permutations
int GroupPermutation::getSize(){
	return size;
}

//retourne la distance � la permutation permut entre a et b
int GroupPermutation::getDist(int permut, int val1, int val2){
	return tabPermut[permut]->getDist(val1,val2);
}

int GroupPermutation::getMaxSize(){
	int max = tabPermut[0]->distPermut();
	int d = 0;
	for (int i=1; i<3; i++){
		d = tabPermut[i]->distPermut();
		if(d > max)
			max = d;
	}
	return max;
}

//retourne la distance entre la m�diane et la permutation permut
int GroupPermutation::getTotalDist(int *mediane, int permut){
	return tabPermut[permut]->calculTotalDist(mediane);
}

//retourne la somme des carr�s des distances
int GroupPermutation::squareDist(int *mediane){
	int distance = 0, tmp = 0;
	for (int i=0; i<3; i++){
		tmp = getTotalDist(mediane, i);
		distance += tmp*tmp;
	}
	return distance;
}

//retourne la permutation � l'indice ind
int* GroupPermutation::getPermutation(int ind){
	return tabPermut[ind]->getPermut();
}
