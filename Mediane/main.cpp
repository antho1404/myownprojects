#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "GroupPermutation.h"
#include "BruteForce.h"
#include "Heuristique.h"
#include <iostream>

using namespace std;

int *p1,*p2,*p3;
int permutSize = 6;
ofstream file("Pour 9", ios::out);

void mix(int *tab, int alea, int size){
	int tmp, rdm;
	for (int i=0; i<size; i++){
		rdm = (int)((double)rand() / ((double)RAND_MAX + 1) * size);
		tmp = tab[i];
		tab[i] = tab[rdm];
		tab[rdm] = tmp;
	}
}

int main(int argc, char **argv) {
//	int p1[] = {4,3,1,2,5};		//OK
//	int p2[] = {5,1,3,2,4};
//	int p3[] = {4,3,2,5,1};

//
//	int p1[] = {3,6,4,5,2,8,7,1};	//OK
//	int p2[] = {7,3,1,5,2,6,8,4};
//	int p3[] = {1,3,5,2,6,4,7,8};

//	int p1[] = {3,1,2,4,5,6};	//une branche
//	int p2[] = {2,5,1,3,4,6};
//	int p3[] = {2,4,1,6,5,3};

//	int p1[] = {1,3,4,5,2};	//plusieurs branches
//	int p2[] = {4,5,3,2,1};
//	int p3[] = {3,2,5,1,4};

	GroupPermutation *gp;
	BruteForce *bf;
	Heuristique *h;
//	Heuristique *halea;
//	Heuristique2 *h2;

//	gp = new GroupPermutation(p1, p2, p3, permutSize);
//	bf = new BruteForce(gp);
//	cerr << bf->getDist() << endl;
//	bf->show();
//	h = new Heuristique(gp, 100);
//	h->show();
//	cerr << h->getDist() << endl;
////	h2 = new Heuristique2(gp);
////	h2->show();
//
//	delete h;delete bf;delete gp;

//	srand(time(NULL));
	int cptBFOk=0;
	int cptHOk=0;
	int cptEgal = 0;
	int cptnEgal = 0;
	int cpt2 = 0;
	int cpt3 = 0, cpt4=0, cpt5=0, cpt6=0;
	p1 = new int[permutSize];
	p2 = new int[permutSize];
	p3 = new int[permutSize];

//	double time = (float)clock();

	for (int i=0; i<permutSize; i++)
		p1[i] = p2[i] = p3[i] = i+1;
	for (int nb=0; nb<5000; nb++){
		mix(p1, rand(), permutSize);
		mix(p2, rand(), permutSize);
		mix(p3, rand(), permutSize);
		gp = new GroupPermutation(p1,p2,p3,permutSize);
		bf = new BruteForce(gp);
		h = new Heuristique(gp, 10);
//		halea = new Heuristique(gp,true);
		if (bf->perfectMedian){
//			bf->show();
//			cerr << bf->getDist() << endl;
//			h->show();
//			cerr << h->getDist() << endl;
//			halea->show();
//			cerr << halea->getDist() << endl;
//			cin.get();
//			for (int b=0; b<3; b++){
//				for (int a=0; a<permutSize; a++)
//					cerr << gp->getPermutation(b)[a] << " ";
//				cerr << endl;
//			}
//			cin.get();

			cptBFOk++;
			if (h->perfectMedian){
				cptHOk++;

				if (h->getDist() == bf->getDist()){
					cptEgal++;
				}
				else {
					if (h->getDist()+2 == bf->getDist())
						cpt2++;
					if (h->getDist()+3 == bf->getDist())
						cpt3++;
					if (h->getDist()+4 == bf->getDist())
						cpt4++;
					if (h->getDist()+5 == bf->getDist())
						cpt5++;
					if (h->getDist()+6 == bf->getDist())
						cpt6++;
//					cin.get();
					cptnEgal++;
				}

			}
			else {
			}
		}
		delete bf;
		delete h;
		delete gp;
	}
	delete[] p1;
	delete[] p2;
	delete[] p3;

	//cerr << (float)(clock() - time)/1000000;

	file << "Brute force parfaite : " <<cptBFOk << "\n";
	file << "Heuristique parfaite : " <<cptHOk << "\n";
	file << "meme dist : " <<cptEgal << "\n";
	file << "dist diff : " <<cptnEgal << "\n";
	file << "d + 2 : " << cpt2 << endl;
	file << "d + 3 : " << cpt3 << endl;
	file << "d + 4 : " << cpt4 << endl;
	file << "d + 5 : " << cpt5 << endl;
//	cout << "d + 6 : " << cpt6 << endl;*/
}

