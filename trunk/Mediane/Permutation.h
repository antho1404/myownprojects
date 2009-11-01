#ifndef PERMUTATION_H_
#define PERMUTATION_H_

class Permutation {
	public:
		Permutation(){}
		Permutation(int *perm, int size);
		virtual ~Permutation();
		int calculTotalDist(int *mediane);	//retourne la distance entre la permutation et la mediane
		int getDist(int a, int b);	//retourne la distance de a vers b
		int* getPermut();		//retourne la permutation
		int distPermut();

	private:
		int *permut;		//permutation
		int **matDist;		//matrice contenant les distance entre chaques points de la permutation
		int permutSize;		//taille de la permutation
};

#endif /* PERMUTATION_H_ */
