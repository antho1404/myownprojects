#ifndef HEURISTIQUE_H_
#define HEURISTIQUE_H_
#include <list>
#include <iostream>
#include "Permutation.h"
#include "Pattern.h"

typedef std::list<int> liste;

class Heuristique {
	public:
		Heuristique(){}
		Heuristique(Permutation *permut, Pattern *pattern, bool allValues);
		virtual ~Heuristique();

	private :
		void fillList();	//remplis � chaques indices les occurences possibles
		bool test(const int& value);
		void cleanList();	//supprime les occurences irr�alisables
		void addPatternPositions(int rang, int val);	//sauvegarde les insertions possibles
		bool patternValidator(int *indiceTab);			//verifit si le pattern s'insert bien

		Permutation *permut;	//permutation courrante
		Pattern *pattern;		//pattern courant
		liste **tabList;		//tableau contenant les occurence possibles
		int *indiceTab;			//tableau contenant les emplacements possibles
		int *indexTmp;			//tableau contenant les index aux emplacements possibles
		bool *used;				//tableau contenant les utilisation des diff�rentes valeurs pour la validation du pattern
		bool valueFind;
};

#endif /* HEURISTIQUE_H_ */
