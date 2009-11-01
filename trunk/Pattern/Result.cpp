#include "Result.h"

/**
 * Constructeur
 */

Result::Result(int *tab, int size) {
	Result::size = size;
	listPattern = new list<int*>();
	indexTab = new int[size];
	leftCode = new int[size];
	rightCode = new int[size];
	bool *used = new bool[size];
	for (int i=0; i<size; i++)
		used[i] = false;


	for (int j=0; j<size; j++){
		int max = 0;
		int tmp = 0;
		for (int i=0; i<size; i++){
			if (!used[i] && tab[i] > tmp){
				tmp = tab[i];
				max = i;
			}
		}
		indexTab[max] = j;
		used[max] = true;
	}

	int valInf;
	for (int i=0; i<size-1; i++){
		valInf = 0;
		for (int j=i+1; j<size; j++){
			if (tab[i] > tab[j])
				valInf++;
		}
		rightCode[i] = valInf;
	}
	rightCode[size-1] = 0;

	int valSupp;
	for (int i=size-1; i>0; i--){
		valSupp = 0;
		for (int j=i-1; j>=0; j--){
			if (tab[i] < tab[j])
				valSupp++;
		}
		leftCode[i] = valSupp;
	}
	leftCode[0] = 0;
	delete[] used;
}

/**
 * Destructeur
 */

Result::~Result() {
	for (list<int*>::iterator it=listPattern->begin(); it != listPattern->end(); it++)
		delete[] (*it);
	listPattern->clear();
	delete listPattern;
	delete[] indexTab;
	delete[] leftCode;
	delete[] rightCode;
}

/**
 * Methodes
 */

//affiche les résultats
void Result::show(){
	cout << "Resultats ou le pattern peut etre insere : \n";
	for (list<int*>::iterator it = listPattern->begin(); it != listPattern->end(); it++){
		for (int i=0; i<size;
		i++)
			cout << (*it)[i] << " ";
		cout << endl;
	}
}

//retourne le nombre de pattern sauvegardés
int Result::getNbPattern(){
	return listPattern->size();
}

//sauvegarde un pattern
void Result::addPattern(int *patt, int size){
	int *tmp = new int[size];
	for (int i=0; i<size; i++)
		tmp[i] = patt[i];
	listPattern->push_back(tmp);
}

//supprime tous les patterns sauvegardés
void Result::cleanPatterns(){
	for (list<int*>::iterator it=listPattern->begin(); it != listPattern->end(); it++)
		delete[] (*it);
	listPattern->clear();
}
