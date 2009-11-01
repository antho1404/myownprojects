#ifndef RESULT_H_
#define RESULT_H_
#include <list>
#include <iostream>

using namespace std;

class Result {
	public :
		Result(){}
		Result(int *tab, int taille);
		virtual ~Result();
		void show();	//affiche les r�sultats
		int getNbPattern();		//retourne le nombre de pattern sauvegard�s
		void addPattern(int *patt, int size);	//sauvegarde un pattern
		void cleanPatterns();	//supprime tous les patterns sauvegard�s

	protected :
		virtual int getLeftCodeVal(int ind) = 0;	// retourne le code gauche de la permutation � l'indice ind
		virtual int getRightCodeVal(int ind) = 0;	//retourne le code droit de la permutation � l'indice ind
		virtual int getIndex(int ind) = 0;			//retourne l'index de la permutation � l'indice ind
		int *indexTab;	//tableau d'index
		int *leftCode;	//tableau contenant les codes gauche
		int *rightCode;	//tablea contenant les codes droits

	private :
		list<int*> *listPattern;	//liste de sauvegarde des patterns
		int size;		//taille du pattern
};

#endif /* RESULT_H_ */
