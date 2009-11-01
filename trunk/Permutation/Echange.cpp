#include "Echange.h"

Echange::Echange(GroupePermutation *g) : Result(g){
	currentMedian = new int[Result::group->getDim()];
	int d = 0;
	for (int nb=0; nb<2; nb++){
		defaultValue = -1;		//on priorise les mouvements gauche
		for (int permut = 0; permut<3; permut++){
			for (int i=0; i<Result::group->getDim(); i++)
				currentMedian[i] = Result::group->getPermutation(permut)->permut[i];
			calcul();
			d = Result::group->calculDistance(currentMedian, -1);
			if (d < Result::getDist()){
				Result::changeMedian(currentMedian);
				Result::setDist(d);
			}
		}
		defaultValue = +2;		//on priorise les mouvement droits
	}
}

Echange::~Echange() {
	delete[] currentMedian;
}

void Echange::calcul(){
	int testResult = 0;
	int n = Result::group->getDim();
	bool morePossibility = true;
	bool change = false;
	int repass = 1;
	while (morePossibility || repass < 2){
		change = false;
		for (int i=0; i<n-1; i++){
			for (int j=i+1; j<n; j++){
				testResult = test(i, j);
				if (testResult == -1){		//si le left améliore
					leftRotation(i, j);
					change = true;
				}
				else if (testResult == 1){		//si le right améliore
					rightRotation(i, j);
					change = true;
				}
			}
		}
		if (!change){
			morePossibility = false;
			repass++;
		}
	}
}

void Echange::leftRotation(int iFirst, int iLast){
	int tmp = currentMedian[iLast];
	for (int i=iLast; i>iFirst; i--)
		currentMedian[i] = currentMedian[i-1];
	currentMedian[iFirst] = tmp;
}

void Echange::rightRotation(int iFirst, int iLast){
	int tmp = currentMedian[iFirst];
	for (int i=iFirst; i<iLast; i++)
		currentMedian[i] = currentMedian[i+1];
	currentMedian[iLast] = tmp;
}

int Echange::test(int iFirst, int iLast){
	int dLInit = 0;
	int dRInit = 0;
	int dL = 0;
	int dR = 0;
	for (int i=iFirst; i<=iLast-1; i++){
		dLInit += group->getDistance(currentMedian[i], currentMedian[iLast]);
		dL += group->getDistance(currentMedian[iLast], currentMedian[i]);
	}
	for (int i=iFirst+1; i<=iLast; i++){
		dRInit += group->getDistance(currentMedian[iFirst], currentMedian[i]);
		dR += group->getDistance(currentMedian[i], currentMedian[iFirst]);
	}
	if (dR < dRInit || dL < dLInit){
		if (dR == dL)			//si les deux rotations sont égales
			return defaultValue;
		else if (dR < dL)
//			if (constraintRightVerified(iFirst, iLast))
				return 1;			//si le meilleur parcours est la rotation droite
//			else return 0;
		else
			//if(constraintLeftVerified(iFirst, iLast))
				return -1;			//si le meilleur parcours est la rotation gauche
//			else return 0;
	}
	return 0;
}

bool Echange::constraintLeftVerified(int iBegin, int iLast){
	int i = iBegin;
	pair<int, int> *constraints;
	while(i < iLast){
		for (int ind=0; ind<group->getSizeOfConstraintsList(currentMedian[iLast]-1); ind++){
			constraints = group->getConstraint(currentMedian[iLast]-1, ind);
			if (constraints->second == currentMedian[iLast] && constraints->first == currentMedian[i])
				return false;
		}
		i++;
	}
	return true;
}

bool Echange::constraintRightVerified(int iBegin, int iLast){
	int i = iLast;
	pair<int, int> *constraints;
	while(i > iBegin){
		for (int ind=0; ind<group->getSizeOfConstraintsList(currentMedian[iBegin]-1); ind++){
			constraints = group->getConstraint(currentMedian[iBegin]-1, ind);
			if (constraints->first == currentMedian[iBegin] && constraints->second == currentMedian[i])
				return false;
		}
		i--;
	}
	return true;
}
