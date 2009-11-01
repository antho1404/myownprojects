#ifndef BRUTEFORCE_H_INCLUDED
#define BRUTEFORCE_H_INCLUDED
#include "GroupPermutation.h"
#include "Result.h"

class BruteForce : public Result {
    public:
        BruteForce(){};
        BruteForce(GroupPermutation *g);
         ~BruteForce();

    private:
        void search(int rang, int dist1, int dist2, int dist3);	//calcul de l'ensemble des permutation possibles
        int *currentPermut;
        bool *valUsed;				//tableau de booléen permettant de savoir si une valeur à déja étée prise
};

#endif // BRUTEFORCE_H_INCLUDED
