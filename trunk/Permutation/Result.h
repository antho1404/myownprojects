#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED
#include "GroupePermutation.h"

using namespace std;

class Result {
    public :
        Result(){}
        Result(GroupePermutation *g);
        virtual ~Result();

        void changeMedian(int *tab);
        void addPermut(int* permut);
        void clearList();
        void setDist(int d);
        int getDist();
        void show();
        int *median;		//meilleur médiane trouvée à l'aide des différent algorithmes

    protected :
        int dist;			//distance de la médiane
//        int *median;		//meilleur médiane trouvée à l'aide des différent algorithmes
        GroupePermutation *group;	//ensemble des permutations

    private :
    	list<int*> *listBestPermut;	//liste des meilleures permutations
    	int *tmpMedian;		//tableau temporaire permettant la copie d'une médiane dans la liste
};

#endif // RESULT_H_INCLUDED
