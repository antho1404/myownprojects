#include "Heuristique.h"
#include <math.h>
#include <stdlib.h>


Heuristique::Heuristique(GroupPermutation *gp, int precision) : Result(gp) {
	dmin = -1;
	int *deb = new int[permutations->getSize()];
	int rdm;
	med = new int[permutations->getSize()];
	for (int i=0; i<gp->getSize(); i++)
		deb[i] = gp->getPermutation(0)[i];
	for (int i=0; i<precision; i++){
		for (int i=0; i<permutations->getSize(); i++){
			rdm = (int)((double)rand() / ((double)RAND_MAX + 1) * permutations->getSize());
			swap(deb, i, rdm);
		}
		search(0, deb);
	}
	delete[] deb;
}

Heuristique::~Heuristique() {
	delete[] med;
}

void Heuristique::search(int rang, int *permut){
	bool change = true;
	int d, dnext;
	while (change){
		change = false;
		for (int i=0; i<permutations->getSize()-1; i++){
			d = permutations->squareDist(permut);
			swap(permut, i, i+1);
			dnext = permutations->squareDist(permut);
            if (permutations->equalDistance(permut) && (dnext < dmin || dmin == -1)){
            		change = true;
					perfectMedian = true;
					dmin = dnext;
					setDist(sqrt(dmin/3));
					for (int ind=0; ind<permutations->getSize(); ind++)
						mediane[ind] = med[ind] = permut[ind];
					search(rang+1, med);
				swap(permut, i, i+1);
			}
            else if (dnext > d)
				swap(permut, i, i+1);
			else change = true;
		}
        if (!perfectMedian && rang == 0){
			for (int i=0; i<permutations->getSize(); i++)
				mediane[i] = permut[i];
			setDist(sqrt(permutations->squareDist(permut)/3));
		}
	}
}

void Heuristique::swap(int *tab, int a, int b){
	int tmp = tab[a];
	tab[a] = tab[b] ;
	tab[b] = tmp;
}
