#ifndef ECHANGE_H_
#define ECHANGE_H_
#include "Result.h"

class Echange : public Result{

	public:
		Echange(){}
		Echange (GroupePermutation *g);
		virtual ~Echange();

	private :
		void calcul();
		void leftRotation(int iFirst, int iLast);
		void rightRotation(int iFirst, int iLast);
		int test(int iFirst, int iLast);
		bool constraintLeftVerified(int iBegin, int iLast);
		bool constraintRightVerified(int iBegin, int iLast);
		int *currentMedian;
		int defaultValue;
};

#endif /* ECHANGE_H_ */
