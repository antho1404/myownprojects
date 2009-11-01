#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "Heuristique.h"

using namespace std;

//STATIC
list<list<Data*>*> * Heuristique::listData;

string Heuristique::affList(){
	stringstream file;
	int i=0;
	if (file){
		for (list<list<Data*>*>::iterator it = Heuristique::listData->begin(); it!=Heuristique::listData->end(); it++){
			file << "rang " << i << " : ";
			i++;
			for (list<Data*>::iterator it2 = (*it)->begin(); it2!=(*it)->end(); it2++)
				file << (*it2)->toString() << " ";
			file << endl;
		}
	}
	return file.str();
}

void Heuristique::newList(){
	Heuristique::listData = new list<list<Data*>*>();
}
int Heuristique::size(){return Heuristique::listData->size();}
bool Heuristique::empty(){
	return Heuristique::listData->empty();
}
void Heuristique::destrList(){
	for (list<list<Data*>*>::iterator it = Heuristique::listData->begin(); it!=Heuristique::listData->end(); it++){
		for (list<Data*>::iterator it2 = (*it)->begin(); it2!=(*it)->end(); it2++){
			delete *it2;
		}
		(*it)->clear();
		delete *it;
	}
	Heuristique::listData->clear();
	delete Heuristique::listData;
}
//FIN STATIC

Heuristique::Heuristique(GroupePermutation *g, int precision, bool alea) : Result(g){
	Heuristique::precision = precision;
	Heuristique::alea = alea;
	int *currentMedian = new int[Result::group->getDim()];
//	for (int nb=0; nb<2; nb++){
		defaultValue = -1;		//on priorise les mouvements gauche
		for (int permut = 0; permut<3; permut++){
			for (int i=0; i<Result::group->getDim(); i++)
				currentMedian[i] = Result::group->getPermutation(permut)->permut[i];
			calcul(0, currentMedian, group->calculDistance(currentMedian, -1), 0);
		}
//		defaultValue = +2;		//on priorise les mouvement droits
//	}
//	for (int i=0; i<g->getDim(); i++)cerr << currentMedian[i] << " "; cerr << "    " << group->calculDistance(currentMedian, -1) << endl;
	delete[] currentMedian;
}

Heuristique::~Heuristique() {
}

void Heuristique::calcul(int rang, int *permut, int dist, int compt){
	int testResult = 0;
	int n = Result::group->getDim();
	bool morePossibility = true;
	bool change = false;
	int repass = 1;
	while (morePossibility || repass < 2){
		change = false;
		for (int i=0; i<n-1; i++){
			for (int j=i+1; j<n; j++){
				testResult = test(permut, i, j);
				if (testResult == -1){		//si le left améliore
					leftRotation(permut, i, j);
					change = true;
				}
				else if (testResult == 1){		//si le right améliore
					rightRotation(permut, i, j);
					change = true;
				}
			}
		}
		if (!change){
			morePossibility = false;
			repass++;
		}
	}
	int d = group->calculDistance(permut, -1);
	if (d < Result::getDist()){
		Result::changeMedian(permut);
		Result::setDist(d);
	}
	/*
//	if(d < dist || (cpt < precision && d == dist)){
//		if(d < dist)
//			cpt = 0;
//		else
//			cpt++;
	listInd = new list<pair<int, int>*>();
	list<int*> *listMed = new list<int*>();
	recupMedianEqual(permut, listMed);

	/////////REMPLISSAGE DATA ////////////////
	if((int)Heuristique::listData->size() == rang){
		Heuristique::listData->push_back(new list<Data*>);
	}
	list<list<Data*>*>::iterator it = Heuristique::listData->begin();
	for (int i=0; i<rang; i++)
		it++;
	if(d < dist)
		(*it)->push_back(new Data(listMed->size(), listInd));
	else (*it)->push_back(new Data(0, new list<pair<int, int>*>));
	for(list<pair<int, int>*>::iterator it=listInd->begin(); it!=listInd->end(); it++)
		delete *it;
	delete listInd;
	///////////////////////////////////////////:
	if(d < dist){
		if(!listMed->empty()){
			if(alea){
				int rdm = rand()%listMed->size();
				list<int*>::iterator it = listMed->begin();
				for (int i=0; i<rdm; i++)
					it++;
				if(d < dist)
					calcul(rang+1,*it,d,cpt);
				else
					calcul(rang,*it,d,cpt);
			}
			else{
				for (list<int*>::iterator it = listMed->begin(); it!=listMed->end(); it++){
//					if(d < dist)
						calcul(rang+1,*it,d,cpt);
//					else
//						calcul(rang,*it,d,cpt);
				}
			}
			for (list<int*>::iterator it = listMed->begin(); it!=listMed->end(); it++)
				delete[] *it;
			delete listMed;
		}
	}*/
}

void Heuristique::leftRotation(int *permut, int iFirst, int iLast){
	int tmp = permut[iLast];
	for (int i=iLast; i>iFirst; i--)
		permut[i] = permut[i-1];
	permut[iFirst] = tmp;
}

void Heuristique::rightRotation(int *permut, int iFirst, int iLast){
	int tmp = permut[iFirst];
	for (int i=iFirst; i<iLast; i++)
		permut[i] = permut[i+1];
	permut[iLast] = tmp;
}

int Heuristique::test(int *permut, int iFirst, int iLast){
	int dLInit = 0;
	int dRInit = 0;
	int dL = 0;
	int dR = 0;
	for (int i=iFirst; i<iLast; i++){
		dLInit += group->getDistance(permut[i], permut[iLast]);
		dL += group->getDistance(permut[iLast], permut[i]);
	}
	for (int i=iFirst+1; i<=iLast; i++){
		dRInit += group->getDistance(permut[iFirst], permut[i]);
		dR += group->getDistance(permut[i], permut[iFirst]);
	}
	if (dR < dRInit || dL < dLInit){
		if (dR == dL)			//si les deux rotations sont égales
			return defaultValue;
		else if (dR < dL)
				return 1;			//si le meilleur parcours est la rotation droite
		else
			return -1;			//si le meilleur parcours est la rotation gauche
	}
	return 0;
}

void Heuristique::recupMedianEqual(int *median, list<int*> *listTmp){
//	cerr << "----median----" << endl;
//	for (int a=0; a<group->getDim(); a++)cerr << median[a] << " "; cerr <<  "     " << group->calculDistance(median, -1) << endl;
	int t, sum;
	pair<int, int> *p;
	for(int i=0; i<group->getDim()-2; i++){
		t = 0;
		sum = 0;
		for (int j=i+1; j<group->getDim(); j++){
			t++;
			sum += group->getDistance(median[i], median[j]);
			if(t % 2 == 0 && 3*(t/2) == sum){
				rightRotation(median, i,j);
				tmp = new int[group->getDim()];
				for(int a=0; a<group->getDim(); a++)
					tmp[a] = median[a];
				p = new pair<int, int>;
				p->first = i;
				p->second = j;
				listInd->push_back(p);
				listTmp->push_back(tmp);
//				for (int a=0; a<group->getDim(); a++)cerr << median[a] << " "; cerr <<  "     " << group->calculDistance(median, -1) << endl;
				leftRotation(median, i, j);
			}
		}
	}
	for(int i=group->getDim()-1; i>=2; i--){
		t = 0;
		sum = 0;
		for (int j=i-1; j>=0; j--){
			t++;
			sum += group->getDistance(median[j], median[i]);
			if(t % 2 == 0 && 3*(t/2) == sum){
				leftRotation(median, j, i);
				tmp = new int[group->getDim()];
				for(int a=0; a<group->getDim(); a++)
					tmp[a] = median[a];
				p = new pair<int, int>;
				p->first = i;
				p->second = j;
				listInd->push_back(p);
				listTmp->push_back(tmp);
//				for (int a=0; a<group->getDim(); a++)cerr << median[a] << " "; cerr << "     " << group->calculDistance(median, -1) << endl;
				rightRotation(median, j, i);
			}
		}
	}
}
