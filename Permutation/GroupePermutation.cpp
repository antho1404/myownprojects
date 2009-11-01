#include "GroupePermutation.h"
#include <stdlib.h>

#define nbPermut 3

using namespace std;

/**
 * Constructeur
 */

GroupePermutation::GroupePermutation(int *perm1, int *perm2, int *perm3, int permutationSize){
    tabPermutation = new Permutation*[nbPermut]; //On crée un tableau qui va contenir nos 3 permutations initiales.
    tabPermutation[0] = new Permutation(perm1, permutationSize);
    tabPermutation[1] = new Permutation(perm2, permutationSize);
    tabPermutation[2] = new Permutation(perm3, permutationSize);

	matriceDist = new int*[permutationSize];	//matrice de distance qui va contenir l'ensemble des distances entre chaque point de la permutation.
	for (int i=0; i<permutationSize; i++)
		matriceDist[i] = new int[permutationSize];
	for (int i=0; i<permutationSize; i++)
		for (int j=0; j<permutationSize; j++){
			matriceDist[i][j] = 0;
			if (i != j)
				for (int k=0; k<nbPermut; k++)	//Pour chaque permutation, on regarde si les paires sont placées dans le bon ordre.
					if (tabPermutation[k]->getIndiceOfValue(i) > tabPermutation[k]->getIndiceOfValue(j))
						matriceDist[i][j] += 1; //Si ce n'est pas le cas, on incrémente la distance de 1 à la case spécifiée.
		}
	for (int i=0; i<nbPermut; i++)
		tabPermutation[i]->setDist(calculDistance(tabPermutation[i]->permut, i));

	tabConstraints= new list<pair<int, int>*>*[permutationSize];		//tableau rassemblant les listes de contraintes de nos permutations initiales.
	for (int i=0; i<permutationSize; i++){
		tabConstraints[i]= new list<pair<int, int>*>();
	}

	constraintCalcul();
}

/**
 * Destructeur
 */

GroupePermutation::~GroupePermutation() {
    for (int i=0; i < getDim(); i++){
    	for (list<pair<int, int>*>::iterator it = tabConstraints[i]->begin(); it!=tabConstraints[i]->end(); it++)
    		delete (*it);
		tabConstraints[i]->clear();
		delete tabConstraints[i];
    	delete[] matriceDist[i];
    }
    delete[] tabConstraints;
    for (int i=0; i < nbPermut; i++)
        delete tabPermutation[i];
    delete[] matriceDist;
    delete[] tabPermutation;
}

/**
 * Methodes
 */

//retourne la distance de Kendall-Tau d'une permutation par rapport a l'ensemble des permutations
int GroupePermutation::calculDistance(int *pi, int params){
    int dist = 0;
	for (int i=0; i < getDim()-1; i++)		//parcours des valeurs d'une permutation
		for (int j=i+1; j < getDim(); j++)	//parcours des valeurs suivante de la permutation
			dist = dist + matriceDist[pi[i]-1][pi[j]-1];
    return dist;
}

//retourne la taille d'une permutation
int GroupePermutation::getDim(){
    return tabPermutation[0]->permutationSize();
}

//retourne la valeur d'une permutation à un indice donné
int GroupePermutation::getPermutationValue(int i){
    return tabPermutation[0]->permut[i];
}

//retourne la permutation qui à la meilleure distance
int GroupePermutation::bestPermutation(){
    int dist = tabPermutation[0]->getDist();
    int d = 0;
    int ind = 0;
    for (int i=1; i<nbPermut; i++){		//parcours de l'ensemble des permutations
        d = tabPermutation[i]->getDist();
        if (d < dist){				//test de la distance de cette permutation
            dist = d;
            ind = i;
        }
    }
    return ind;
}

//retourne la distance entre 2 valeurs
int GroupePermutation::getDistance(int a, int b){
	return matriceDist[a-1][b-1];
}

//retourne la permutation contenue dans la liste des permutation
Permutation* GroupePermutation::getPermutation(int i){
    return tabPermutation[i];
}

//Calcule l'ensemble des contraintes de nos permutations initiales.
void GroupePermutation::constraintCalcul(){
	for (int i=0; i< getDim()-1; i++){
		for (int j=i+1; j<getDim(); j++){
			if (getDistance(i+1, j+1) == 0){	//Si, dans notre matrice de distances, nos 3 permutations ont une paire en commun...
				pair<int, int> *pair1 = new pair<int, int>;
				pair<int, int> *pair2 = new pair<int, int>;
				pair1->first = i+1;
				pair1->second = j+1;
				pair2->first = i+1;
				pair2->second = j+1;
				tabConstraints[i]->push_back(pair1);	//..On l'ajoute à notre tableau de listes de contraintes.
				tabConstraints[j]->push_back(pair2);
			}
			else if(getDistance(i+1, j+1) == 3){ //de même si la distance est égale à 3 dans la matrice.
				pair<int, int> *pair1 = new pair<int, int>;
				pair<int, int> *pair2 = new pair<int, int>;
				pair1->first = j+1;
				pair1->second = i+1;
				pair2->first = j+1;
				pair2->second = i+1;
				tabConstraints[i]->push_back(pair1);
				tabConstraints[j]->push_back(pair2);
			}
		}
	}

}

//Retourne la contrainte i à un indice donné dans la liste demandée du tableau de contraintes.
pair<int, int>* GroupePermutation::getConstraint(int i, int ind){
	list<pair<int, int>*>::iterator it = tabConstraints[i]->begin();
	while (it!= tabConstraints[i]->end() && ind !=0){
		it++;
		ind--;
	}
	return (*it);
}

//Retourne la taille de la liste demandée dans le tableau de contraintes.
int GroupePermutation::getSizeOfConstraintsList(int ind){
	return tabConstraints[ind]->size();
}

void GroupePermutation::show(){
	for (int i=0; i<getDim(); i++){
		for (list<pair<int, int>*>::iterator it = tabConstraints[i]->begin(); it != tabConstraints[i]->end(); it++)
			cerr << "["<<(*it)->first<<" "<<(*it)->second<<"]  ";
		cerr << endl;
	}
}
