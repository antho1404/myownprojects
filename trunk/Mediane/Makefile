compil = g++
flag = -c -Wall -g -fno-inline 	#pour le debugger
#flag = -c -Wall -O3 		#pour la vitesse

main : Result.o Permutation.o GroupPermutation.o Heuristique.o BruteForce.o main.o
	$(compil) Result.o Permutation.o GroupPermutation.o Heuristique.o BruteForce.o main.o -o main

Permutation.o : Permutation.cpp Permutation.h
	$(compil) $(flag) Permutation.cpp
	
Heuristique.o : Result.cpp Result.h Heuristique.cpp Heuristique.h
	$(compil) $(flag) Heuristique.cpp
	
BruteForce.o : Result.cpp Result.h BruteForce.cpp BruteForce.h
	$(compil) $(flag) BruteForce.cpp
		
GroupPermutation.o : GroupPermutation.cpp GroupPermutation.h
	$(compil) $(flag) GroupPermutation.cpp
	
Result.o : Result.cpp Result.h
	$(compil) $(flag) Result.cpp

main.o : main.cpp
	$(compil) $(flag) main.cpp
	
