#ifndef RESULT_H_
#define RESULT_H_
#include "GroupPermutation.h"
#include <list>
#include <iostream>

class Result{

	public:
		Result(){}
		Result(GroupPermutation *gp);
		~Result();
		int getDist();	//retourne la distance de la mediane
		bool perfectMedian;		//vrai si la médiane est équidistante, faux sinon
		int *mediane;

	protected:
		void clearList();		//remet à zero la liste de sauvegarde des medianes
		void addPermut(int* permut);	//sauvegarde une mediane
		void setDist(float d);			//modifit la distance
		GroupPermutation *permutations;	//contient l'ensemble de spermutations des départ
//		int *mediane;	//meilleure médiane
		float distOpt;			//distance de la mediane

	private:
		std::list<int*> *listBestPermut;	//liste de sauvegarde des médianes
		int *tmpMedian;		//mediane temporaire

};

#endif /* RESULT_H_ */
