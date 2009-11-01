#ifndef BRUTEFORCE2_H_
#define BRUTEFORCE2_H_
#include "Result.h"
#include <iostream>
#include <list>

using namespace std;

class BruteForce2 : public Result{
	public:
		BruteForce2(){}
		BruteForce2(GroupePermutation *gp);
		virtual ~BruteForce2();

	private:
		void gen(int n, int k);
		int combinations(int p, int n);
		int fact(int val);
		int rank(int x);
		int calcDistKT(int *pi1, int *pi2);
		int pg(int d01,int d02,int d12);
		bool constraintVerified(int i);
		int *currentPermutation;
		int *id;
		bool *valUsed;
};

#endif /* BRUTEFORCE2_H_ */
