#ifndef GROUPPERMUTATION_H_
#define GROUPPERMUTATION_H_
#include "Permutation.h"

#define nbPermut 3;		//nombre de permutation

class GroupPermutation {
	public:
		GroupPermutation(){}
		GroupPermutation(int *perm1, int *perm2, int *perm3, int size);
		virtual ~GroupPermutation();
		bool equalDistance(int *mediane);	//retourne vrai si la m�diane est �quidistante
		int getSize();		//retourne la taille des permutations
		int getDist(int permut, int a, int b);	//retourne la distance � la permutation permut entre a et b
		int getTotalDist(int *mediane, int permut);	//retourne la distance entre la m�diane et la permutation permut
		int getMaxSize();
		int squareDist(int *mediane);	//retourne la somme des carr�s des distances
		int* getPermutation(int ind);	//retourne la permutation � l'indice ind

	private:
		Permutation **tabPermut;		//tableau contenant les permutation
		int size;						//taille des permutations
};

#endif /* GROUPPERMUTATION_H_ */
