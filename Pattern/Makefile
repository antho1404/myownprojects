compil = g++
flag = -c -Wall -g -fno-inline 	#pour le debugger
#flag = -c -Wall -O3 		#pour la vitesse

main : Result.o Pattern.o Permutation.o Heuristique.o BruteForce.o main.o
	$(compil) Result.o Pattern.o Permutation.o Heuristique.o BruteForce.o main.o -o main

Result.o : Result.cpp Result.h
	$(compil) $(flag) Result.cpp
	
Permutation.o : Result.cpp Result.h Permutation.cpp Permutation.h
	$(compil) $(flag) Permutation.cpp

Pattern.o : Result.cpp Result.h Pattern.cpp Pattern.h
	$(compil) $(flag) Pattern.cpp
	
Heuristique.o : Heuristique.cpp Heuristique.h
	$(compil) $(flag) Heuristique.cpp

BruteForce.o : BruteForce.cpp BruteForce.h
	$(compil) $(flag) BruteForce.cpp

main.o : main.cpp
	$(compil) $(flag) main.cpp
