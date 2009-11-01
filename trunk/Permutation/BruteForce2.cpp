#include "BruteForce2.h"
#include "Echange.h"

BruteForce2::BruteForce2(GroupePermutation *gp) : Result(gp){

	Result *algo = new Echange(gp);
    Result::setDist(algo->getDist());
    for (int i=0; i<group->getDim(); i++)
    	changeMedian(algo->median);
	delete algo;

	currentPermutation = new int[gp->getDim()];
	valUsed = new bool[gp->getDim()];
	id = new int[gp->getDim()];
	int *identity = new int[gp->getDim()];
	int cpt = gp->getDim();
	for (int i=0; i<gp->getDim(); i++){
		id[i] = cpt;
		identity[i] = i+1;
		cpt--;
		valUsed[i] = false;
		currentPermutation[i] = 0;
	}


	int d01 = calcDistKT(gp->getPermutation(0)->permut, gp->getPermutation(1)->permut);
	int d02 = calcDistKT(gp->getPermutation(0)->permut, gp->getPermutation(2)->permut);
	int d12 = calcDistKT(gp->getPermutation(1)->permut, gp->getPermutation(2)->permut);
	int inv0 = calcDistKT(identity, gp->getPermutation(0)->permut);
	int inv1 = calcDistKT(identity, gp->getPermutation(1)->permut);
	int inv2 = calcDistKT(identity, gp->getPermutation(2)->permut);

	delete[] identity;

	float max, min;
	if(pg(d01,d02,d12) == d01){
		max = (float)(inv0 + inv1 + inv2 + d12 + d02)/3;
		min = (float)(inv0 + inv1 + inv2 - d12 - d02)/3;
	}
	else if(pg(d01,d02,d12) == d02){
		max = (float)(inv0 + inv1 + inv2 + d12 + d01)/3;
		min = (float)(inv0 + inv1 + inv2 - d12 - d01)/3;
	}
	else if(pg(d01,d02,d12) == d12){
		max = (float)(inv0 + inv1 + inv2 + d01 + d02)/3;
		min = (float)(inv0 + inv1 + inv2 - d01 - d02)/3;
	}

//	cerr << min << "       " << max << endl;
//	group->show();
	if (min-((int)min) > 0)
		min = (int)min + 1;
	for (int i = (int)min; i <= (int)max; i++)
		gen(gp->getDim(),i);
}

BruteForce2::~BruteForce2() {
	delete[] currentPermutation;
	delete[] id;
	delete[] valUsed;
}

void BruteForce2::gen(int n, int k){
	int lim = combinations(2,(n-1))+n;
	int rnk;
	if (n != 0 || k != 0){
		for (int i=group->getDim(); i>0; i--){
			if(!valUsed[i-1]){
				rnk = rank(i);
				if(n-rnk <= k && k <= lim-rnk && constraintVerified(i)){
					currentPermutation[n-1] = i;
					valUsed[i-1] = true;
					gen(n-1, k-n+rnk);
					valUsed[i-1] = false;
				}
			}
		}
	}
	else {
		int d = Result::group->calculDistance(currentPermutation, -1);		//calcul de sa distance
		if (d <= Result::dist){
			if (d < Result::dist){		//si la distance est meilleure...
				Result::clearList();	// .. on supprime l'ancienne liste
				Result::setDist(d);		// et on réinitialise la distance de référence.
				Result::changeMedian(currentPermutation);
			}
			Result::addPermut(currentPermutation);	// On ajoute la nouvelle permutation à la liste.
//			for (int i=0; i<group->getDim(); i++)
//				cerr << currentPermutation[i] << " ";
//			cerr << "     " << d << endl;
		}
	}
}

int BruteForce2::combinations(int p, int n){
	return (fact(n)/(fact(p)*(fact(n-p))));
}

int BruteForce2::fact(int val){
	int result = 1;
	for (int i=1; i< val+1; i++)
		result= result*i;
	return result;
}

int BruteForce2::rank(int x){
	int rnk = 1;
	for (int i=group->getDim(); i>0; i--)
		if(!valUsed[i-1] && i < x)
			rnk++;
	return rnk;
}

int BruteForce2::calcDistKT(int *pi1, int *pi2){
	int d = 0;
	int ind1, ind2;
	for (int i=0; i<group->getDim()-1; i++){
		for (int j=i+1; j<group->getDim(); j++){
			for (int a=0; a<group->getDim(); a++){
				if (pi2[a] == pi1[i]) ind1 = a;
				if (pi2[a] == pi1[j]) ind2 = a;
			}
			if (ind1 > ind2)d++;
		}
	}
	return d;
}

int BruteForce2::pg(int d01,int d02,int d12){
	int d = d01;
	if (d02 > d) d = d02;
	if (d12 > d) d = d12;
	return d;
}

bool BruteForce2::constraintVerified(int i){
	bool result = true;
	pair<int, int> *constraint;
	for (int ind=0; ind<group->getSizeOfConstraintsList(i-1); ind++){
		constraint = group->getConstraint(i-1, ind);

//		for (int ind=0; ind<group->getDim(); ind++)
//			cerr <<ind+1 << " ";
//		cerr << endl;
//		for (int ind=0; ind<group->getDim(); ind++)
//			cerr <<valUsed[ind] << " ";
//		cerr << "  --  params : " << i << "  --  const : [" <<constraint->first << " " << constraint->second << "]  --  result : ";

		if(constraint->second == i){
			if(valUsed[constraint->first-1]){
				result = false;
//				cerr << "bla";
			}
		}
		else
		if(constraint->first == i){
			if(!valUsed[constraint->second-1]){
				result = false;
//				cerr << "bla2";
			}
		}
//		cerr << result << endl;
	}
//	cerr << endl << endl;
	return result;
}
