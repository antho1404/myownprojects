/**
  * @author Estebe Anthony
  */
  
#ifndef ALGOLOADER_H
#define ALGOLOADER_H

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

#include <string>
#include "AlgoIO.h"

class AlgoLoader : public AlgoIO {
public:
    AlgoLoader();
	virtual string saveAlgo(string title, string src, bool fromFile);
	virtual Algo* importAlgo(string algo);
	virtual void closeAlgo(Algo *a);
	virtual string deleteAlgo(string name);
	virtual list<string>* findAll();

private:
	void showError();
	string getAlgoName(string line);
	string getAlgoFile(string algoName);
	string replace(string str, const string from, const string to);
	string createFile(string title, string src);
	string directory;
	string fileDirectory;
	string ext;
#if defined(WIN32) || defined(WIN64)
        HINSTANCE library;
#else
	void* library;
#endif
};

#endif // ALGOLOADER_H
