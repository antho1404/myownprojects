#ifndef HEURISTIQUE_H_
#define HEURISTIQUE_H_
#include "Result.h"

class Heuristique : public Result{
	public:
		Heuristique(){}
		Heuristique(GroupPermutation *gp, int precision);
		virtual ~Heuristique();

	private:
		void search(int rang, int *tmp);
		void swap(int *tab, int a, int b);
		int dmin;
		int *med;
};

#endif /* HEURISTIQUE_H_ */
