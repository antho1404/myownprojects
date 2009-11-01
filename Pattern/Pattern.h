#ifndef PATTERN_H_
#define PATTERN_H_
#include "Result.h"

class Pattern : public Result{
	public:
		Pattern(){}
		Pattern(int *patt, int pattSize);
		virtual ~Pattern();
		int getSize();	//retourne la taille du pattern
		virtual int getLeftCodeVal(int ind);	//retourne le code gauche a l'indice ind
		virtual int getRightCodeVal(int ind);	//retourne le code droit a l'indice ind
		virtual int getIndex(int ind);	//retourne l'index a l'indice ind

	private :
		int *pattern;	//tableau contenant le pattern
		int pattSize;	//taille du pattern
};

#endif /* PATTERN_H_ */
