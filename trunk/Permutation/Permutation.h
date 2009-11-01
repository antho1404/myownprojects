#ifndef PERMUTATION_H_
#define PERMUTATION_H_

class Permutation {

	public:
		Permutation(){}
		Permutation(int *p, int taille);
		virtual ~Permutation();
		int getIndiceOfValue(int value);
		int permutationSize();			//retourne la taille de la permutation
		int getDist();					//retourne la distance de la permutation
		void setDist(int d);			//définit la distance de la permutation fournie par d
		int *permut;					//tableau contenant les valeur de la permutation

    private:
        int size;						//taille de la permutation
		int dist;						//distance de la permutation
		int *indiceTab;					//tableau d'indice des valeurs de la permutation
};

#endif /* PERMUTATION */
