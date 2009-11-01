#include "Heuristique.h"

using namespace std;

/**
 * Constructeur
 */

Heuristique::Heuristique(Permutation *permut, Pattern *pattern, bool allValues) {
	double time = clock();
	Heuristique::permut = permut;
	Heuristique::pattern = pattern;
	tabList = new liste*[permut->getSize()];
	indiceTab = new int[pattern->getSize()];
	indexTmp = new int[pattern->getSize()];
	used = new bool[pattern->getSize()];
	valueFind = allValues;
	for (int i=0; i<permut->getSize(); i++)
		tabList[i] = new liste();

	fillList();
	cleanList();
//	for (int i=0; i<permut->getSize(); i++){
//		for (liste::iterator it = tabList[i]->begin(); it != tabList[i]->end(); it++)
//			cerr << *it << " ";
//		cerr << endl;
//	}
	addPatternPositions(0, 0);
//	cout << "\ttemps Heuristique : " << (double)(clock() - time)/1000000 << endl;
}

/**
 * Destructeur
 */

Heuristique::~Heuristique() {
	for (int i=0; i<permut->getSize(); i++){
		tabList[i]->clear();
		delete tabList[i];
	}
	delete[] tabList;
	delete[] indiceTab;
	delete[] used;
	delete[] indexTmp;
}

/**
 * Methodes
 */

//remplis � chaques indices les occurences possibles
void Heuristique::fillList(){
	for (int i=0; i<permut->getSize(); i++)
		for (int j=0; j<pattern->getSize(); j++)
			//si les codes gauche et droits du pattern sont inferieur � ceux de la permutation
			if (pattern->getLeftCodeVal(j) <= permut->getLeftCodeVal(i) && pattern->getRightCodeVal(j) <= permut->getRightCodeVal(i))
				 tabList[i]->push_back(j);		//ajout de la valeur possible
}

//supprime les occurences irr�alisables
void Heuristique::cleanList(){
	int compt = -1;
	unsigned int val;
	bool b = false;
	//dans le sens normal
	for (int i=0; i<permut->getSize(); i++){
		b = false;
		if (!tabList[i]->empty()){
			for (liste::iterator it=tabList[i]->begin(); it!=tabList[i]->end(); it++){
				if(compt+1 < *it)	//si la valeur est impossible
					it = tabList[i]->erase(it);			//suppression
				else if (compt+1 == *it){
					b = true;
					val = compt+1;
				}
			}
			if (b)
				compt = val;
		}
	}
	//dans le sens inverse
//	compt = pattern->getSize();
//	for (int i=permut->getSize()-1; i>=0; i--){
//		b = false;
//		if (!tabList[i]->empty()){
//			for (liste::iterator it = tabList[i]->begin(); it!=tabList[i]->end(); it++){
//				if(compt-1 < *it){				//si la valeur est impossible
////					it = tabList[i]->erase(it);			//suppression
//					it = tabList[i]->begin();
//				}
//				else if (compt-1 == *it){
//					b = true;
//					val = compt-1;
//				}
//			}
//			if (b)
//				compt = val;
//		}
//	}
}

//sauvegarde les insertions possibles
void Heuristique::addPatternPositions(int rang, int val){
	if(!valueFind){
		if (val < pattern->getSize()){ //condition d'arret de la r�cursivit�
			for (int i=rang; i<permut->getSize(); i++){	//parcours de la permutation
				for (liste::iterator it = tabList[i]->begin(); it != tabList[i]->end(); it++){
					//parcours de la liste contenant les insertions possible a l'indice i
					if (*it == val){	//si la valeur est contenue dans la liste
						indiceTab[val] = i;
						addPatternPositions(i+1, val+1);
					}
				}
			}
		}
		else{
			if (patternValidator(indiceTab)){	//si le pattern convient
				pattern->addPattern(indiceTab, pattern->getSize());	//ajout des indices ou le pattern peut s'inserer
				valueFind = true;
			}
		}
	}
}

//verifit si le pattern s'insert bien
bool Heuristique::patternValidator(int *indiceTab){
	for (int i=0; i<pattern->getSize(); i++)
		used[i] = false;
	int i = 0;
	int tmp, ind;
	while (i < pattern->getSize()){
		tmp = 0;
		ind = 0;
		for (int j=0; j<pattern->getSize(); j++){
			if (tmp < permut->getValue(indiceTab[j]) && !used[j]){
				tmp = permut->getValue(indiceTab[j]);
				ind  = j;
			}
		}
		indexTmp[ind] = i;
		used[ind] = true;
		if (indexTmp[ind] != pattern->getIndex(ind))
			return false;
		i++;
	}
	return true;
}
