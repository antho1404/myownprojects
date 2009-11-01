compil = g++
flag = -c -Wall -g -fno-inline 	#pour le debugger
#flag = -c -Wall -O3 		#pour la vitesse

main : BruteForce.o BruteForce2.o GroupePermutation.o Permutation.o Result.o Echange.o Heuristique.o Data.o main.o
	$(compil) BruteForce.o BruteForce2.o GroupePermutation.o Permutation.o Result.o Echange.o Heuristique.o Data.o main.o -o main

Data.o : Data.cpp Data.h
	$(compil) $(flag) Data.cpp

Permutation.o : Permutation.cpp Permutation.h
	$(compil) $(flag) Permutation.cpp

GroupePermutation.o : GroupePermutation.cpp GroupePermutation.h
	$(compil) $(flag) GroupePermutation.cpp

Result.o : Result.cpp Result.h
	$(compil) $(flag) Result.cpp

Echange.o : Result.cpp Result.h Echange.cpp Echange.h
	$(compil) $(flag) Echange.cpp
	
Heuristique.o : Result.cpp Result.h Heuristique.cpp Heuristique.h
	$(compil) $(flag) Heuristique.cpp

BruteForce.o : Result.cpp Result.h BruteForce.cpp BruteForce.h
	$(compil) $(flag) BruteForce.cpp
	
BruteForce2.o : Result.cpp Result.h BruteForce2.cpp BruteForce2.h
	$(compil) $(flag) BruteForce2.cpp

main.o : main.cpp
	$(compil) $(flag) main.cpp
