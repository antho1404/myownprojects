#ifndef PERMUTATION_H_
#define PERMUTATION_H_
#include "Result.h"

class Permutation : public Result{
	public :
		Permutation(){}
		Permutation(int *permut, int permutSize);
		virtual ~Permutation();
		int getSize();	//retourne la taille de la permutation
		virtual int getLeftCodeVal(int ind);	//retourne le code gauche a l'indice ind
		virtual int getRightCodeVal(int ind);	//retourne le code droit a l'indice ind
		virtual int getIndex(int ind);	//retourne l'index a l'indice ind
		int getValue(int ind);	//retourne la valeur de la permutation a l'indice ind

	private :
		int permutSize;		//taille de la permutation
		int *permutation;	//tableau contenant la permutation
};

#endif /* PERMUTATION_H_ */
