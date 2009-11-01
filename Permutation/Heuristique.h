#ifndef HEURISTIQUE_H_
#define HEURISTIQUE_H_
#include "Result.h"
#include <list>
#include <iostream>
#include <fstream>
#include "Data.h"

using namespace std;

class Heuristique : public Result{

	public:
		Heuristique(){}
		Heuristique (GroupePermutation *g, int precision, bool alea);
		virtual ~Heuristique();

		static string affList();
		static void newList();
		static int size();
		static bool empty();
		static void destrList();

	private :
		void calcul(int rang, int *permut, int dist, int compt);
		void leftRotation(int *permut, int iFirst, int iLast);
		void rightRotation(int *permut, int iFirst, int iLast);
		int test(int *permut, int iFirst, int iLast);
		void recupMedianEqual(int *median, list<int*> *listTmp);
		int *tmp;
		int precision;
		int defaultValue;
		bool alea;
		list<pair<int, int>*> *listInd;

		static list<list<Data*>*> *listData;
};

#endif /* ECHANGE_H_ */
