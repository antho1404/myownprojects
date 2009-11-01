#ifndef BRUTEFORCE_H_INCLUDED
#define BRUTEFORCE_H_INCLUDED
#include "Result.h"

using namespace std;

class BruteForce : public Result {
    public:
        BruteForce(){}
        BruteForce(GroupePermutation *g);
         ~BruteForce();

    private:
        void search(int rang, int distance);	//calcul de l'ensemble des permutation possibles
        bool constraintVerified(int i);
        int *currentPermutation;	//permutation qui prend toutes les possibilités
        bool *valUsed;				//tableau de booléen permettant de savoir si une valeur à déja étée prise
};

#endif // BRUTEFORCE_H_INCLUDED
