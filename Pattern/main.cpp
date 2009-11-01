#include <iostream>
#include "Pattern.h"
#include "Permutation.h"
#include "Heuristique.h"
#include "BruteForce.h"
#include "Result.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));
	int rdm, tmp;
	float time, moy;
	Pattern *patt;
	Permutation *permut;
	int *tmpPermut;
	int *tmpPattern;
	BruteForce *bf;
	Heuristique *h;

//	int pe[] = {3,1,4,2,5};
//	int pa[] = {2,4,1};
//	permut = new Permutation(pe, 5);
//	patt = new Pattern(pa,3);
//	h = new Heuristique(permut, patt, true);

	for (int permutSize = 29; permutSize < 30; permutSize++){
		//cout << "\ntaille permut : " << permutSize << endl;
		tmpPermut = new int[permutSize];
		for (int j=0; j<permutSize; j++)
			tmpPermut[j] = j+1;
		for (int i=0; i<permutSize; i++){
			rdm = (int)((double)rand() / ((double)RAND_MAX + 1) * permutSize);
			tmp = tmpPermut[i];
			tmpPermut[i] = tmpPermut[rdm];
			tmpPermut[rdm] = tmp;
		}
		permut = new Permutation(tmpPermut, permutSize);

		for (int pattSize = 3; pattSize<permutSize-2; pattSize++){
//			cout << "taille pattern : " << pattSize << endl;
			time = clock();
			for(int nbfois = 0; nbfois<5000; nbfois++){
				tmpPattern = new int[pattSize];
				for (int j=0; j<pattSize; j++)
					tmpPattern[j] = j+1;
				for (int i=0; i<pattSize; i++){
					rdm = (int)((double)rand() / ((double)RAND_MAX + 1) * pattSize);
					tmp = tmpPattern[i];
					tmpPattern[i] = tmpPattern[rdm];
					tmpPattern[rdm] = tmp;
				}
				patt = new Pattern(tmpPattern, pattSize);
	//			bf = new BruteForce(permut, patt, true);
	//			patt->show();
				patt->cleanPatterns();
				//time = clock();
//				sleep(1);
				h = new Heuristique(permut, patt, true);
				//moy += (clock()-time);
	//			patt->show();
//				delete bf;
				delete h;

				delete patt;
				delete[] tmpPattern;
			}
			cerr << "temp : " << ((clock()-time)/1000000)/5000<< endl;
		}
		delete permut;
		delete[] tmpPermut;
	}
}

