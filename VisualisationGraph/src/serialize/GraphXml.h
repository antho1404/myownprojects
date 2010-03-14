/**
  * @author Estebe Anthony
  */
  
#ifndef GRAPHXML_H
#define GRAPHXML_H

#include <string>
#include "GraphIO.h"

using namespace std;

class GraphXML: virtual public GraphIO {
public:
	GraphXML();
	virtual void exportGraph(Graph *g, string dir);
	virtual Graph* importGraph(string graph, bool file);
	virtual list<string>* findAll();

private:
	bool endWith(string word, string ending);
	string ext;
	string directory;
};

#endif // GRAPHXML_H
