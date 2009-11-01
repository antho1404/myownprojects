#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "GroupePermutation.h"
#include "BruteForce.h"
#include "BruteForce2.h"
#include "Echange.h"
#include "Heuristique.h"


void permutationGen(int rang);
void selectPermutation(int rang, int ind, int nbPermut);
void selectPermutationAlea();
int factorielle(int a);
void algorythme(int *p1, int *p2, int *p3);
void mix(int *tab, int alea, int size);

ofstream file("Result/Result14.log", ios::out);
int permutSize = 14;
int cpt = 0;
int **tabPermutation;
int *tabIndic;
bool *valUsed;
int *v1, *v2, *v3;

void mix(int *tab, int alea, int size){
	int tmp, rdm;
	for (int i=0; i<size; i++){
		rdm = (int)((double)rand() / ((double)RAND_MAX + 1) * size);
		tmp = tab[i];
		tab[i] = tab[rdm];
		tab[rdm] = tmp;
	}
}

int calcDistKT(int *pi1, int *pi2){
	int d = 0;
	int ind1, ind2;
	for (int i=0; i<permutSize-1; i++){
		for (int j=i+1; j<permutSize; j++){
			for (int a=0; a<permutSize; a++){
				if (pi2[a] == pi1[i]) ind1 = a;
				if (pi2[a] == pi1[j]) ind2 = a;
			}
			if (ind1 > ind2)d++;
		}
	}
	return d;
}

int pg(int d01,int d02,int d12){
	int d = d01;
	if (d02 > d) d = d02;
	if (d12 > d) d = d12;
	return d;
}

int main(int argc, char **argv) {
	permutSize = atoi(argv[1]);
	int nbTest = atoi(argv[2]);
	int precision = atoi(argv[3]);
	bool alea = atoi(argv[4]);


	int* p[3];
	int seed = time(NULL);
	srand(seed);

	float time;
	float moyBFopt = 0;

	int *p1 = new int[permutSize];
	int *p2 = new int[permutSize];
	int *p3 = new int[permutSize];
	for (int i=0; i<permutSize; i++)
		p1[i] = p2 [i] = p3[i] = i+1;

	for (int a=0; a<nbTest; a++){
		Heuristique::newList();

		mix(p1,1,permutSize);
		mix(p2,1,permutSize);
		mix(p3,1,permutSize);

//		p1 = bla;
//		p2 = b;
//		p3 = c;

		p[0] = p1;
		p[1] = p2;
		p[2] = p3;

		if(true || a==10){
//			cerr << "nouvelles données\n";
//			cerr << "[";
//			for (int i=0; i<permutSize; i++)
//				cerr << p1[i] << " ";
//			cerr << "]\n[";
//			for (int i=0; i<permutSize; i++)
//				cerr << p2[i] << " ";
//			cerr << "]\n[";
//			for (int i=0; i<permutSize; i++)
//				cerr << p3[i] << " ";
//			cerr << "]\n";
//			cin.get();
//			if(a%100 == 0)
//				cerr << a << endl;
			GroupePermutation *gp = new GroupePermutation(p[0],p[1],p[2],permutSize);

		//	int pbla[] = {2,4,3,1};
		//	int pba2[] = {3,2,4,1};
		//	cerr << gp->calculDistance(pbla,-1) << "    " << gp->calculDistance(pba2,-1) << endl;
			Heuristique *bf2 = new Heuristique(gp,precision,alea);
			time = clock();
			BruteForce *bf = new BruteForce(gp);
			moyBFopt += (clock()-time)/1000000;
			if (bf->getDist() != bf2->getDist()){
				cpt++;
				bf->show();
				bf2->show();
			}
			bf->show();
			bf2->show();
			delete bf;
			delete gp;
		}
//		if (!Heuristique::empty()){
//			if(Heuristique::size() > 1){
//				file << "[";
//				for (int i=0; i<permutSize; i++)
//					file << p1[i] << " ";
//				file << "]\n[";
//				for (int i=0; i<permutSize; i++)
//					file << p2[i] << " ";
//				file << "]\n[";
//				for (int i=0; i<permutSize; i++)
//					file << p3[i] << " ";
//				file << "]\n";
//				file << Heuristique::affList();
//				file << endl;
//			}
//		}
		Heuristique::destrList();
	}
	
	cerr << "BF : " <<moyBFopt/nbTest<< endl;
//	delete[] p1;
//	delete[] p2;
//	delete[] p3;
}
