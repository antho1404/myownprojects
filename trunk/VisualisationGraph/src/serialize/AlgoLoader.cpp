/**
  * @author Estebe Anthony
  */
  
#include "AlgoLoader.h"
#include <iostream>
#include <fstream>
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using namespace std;

AlgoLoader::AlgoLoader(){
        directory = "./Algorithm/";
#if defined(WIN32) || defined (WIN64)
        ext = ".dll";
        fileDirectory = "./Algorithm/AlgorithmListWin";
#else
        ext = ".so";
        fileDirectory = "./Algorithm/AlgorithmListLin";
#endif
}

string AlgoLoader::saveAlgo(string title, string src, bool fromFile){
	if(!fromFile)
		src= createFile(title, src);

        string cmd_compil;
        string cmd_rm;
#if defined (WIN32) || defined(WIN64)
        cmd_compil = "copy \"" + src + "\" \"" + directory + "\"";
        cmd_rm = "rm " + src;
#else
        cmd_compil = "g++ -fPIC -shared -o " + directory + "lib_" + replace(title, " ", "_") + ext + " " + src;
        cmd_rm = "rm -f " + src;
#endif
	int res = system(cmd_compil.c_str());
	if(res == 0){
		if(!fromFile)
			res = system(cmd_rm.c_str());
		ofstream _file(fileDirectory.c_str(), ios::out | ios::app);
		if(_file){
                        _file << title << "\t:\tlib_" << replace(title, " ", "_") << ext << "\n";
			_file.close();
			return "";
		}
		else
			return "Error while adding the algorithm : \n" + title;
	}
	else
		return "Adding algorithm impossible : \n" + cmd_compil;
}

Algo* AlgoLoader::importAlgo(string algo){
	string lib = directory + getAlgoFile(algo);
	Algo *_algo = NULL;

	//Loading of the library

#if defined(WIN32) || defined(WIN64)
        WCHAR loutre[255];
        for(unsigned int i=0; i<lib.length(); i++)
            loutre[i] = (WCHAR)lib.at(i);
        library = LoadLibrary(loutre);
#else
        library = dlopen(lib.c_str(), RTLD_LAZY);
#endif
	//test if the library is loaded
	if(library == NULL){
		cerr << "Error while loading the library : ";
		showError();
		return NULL;
	}
	//Loading of the creator

	create_t *creator =
#if defined(WIN32) || defined(WIN64)
	(create_t*) GetProcAddress(library, "create");
#else
	(create_t*) dlsym(library, "create");
#endif
	//test if the function is loaded
	if(creator == NULL){
		cerr << "Error while loading the library : ";
		showError();
		closeAlgo(_algo);
		return NULL;
	}

	//create the object
	_algo = creator();

	return _algo;
}

void AlgoLoader::closeAlgo(Algo *a){
	//Loading of the destructor
	if(a != NULL){
                destroy_t *destructor =
#if defined(WIN32) || defined(WIN64)
		(destroy_t*) GetProcAddress(library, "destroy");
#else
		(destroy_t*) dlsym(library, "destroy");
#endif
		if(destructor == NULL){
			cerr << "Error while destruction of the algorithm : ";
			showError();
		}
		//destroy the algorithm
		destructor(a);
	}

	// Fermeture de la librairie
#if defined(WIN32) || defined(WIN64)
	FreeLibrary(library);
#else
	dlclose(library);
#endif
}

string AlgoLoader::deleteAlgo(string name){
#if defined(WIN32) || defined(WIN64)
	string cmd_remove = "rm " + directory + getAlgoFile(name);
#else
	string cmd_remove = "rm -f " + directory + getAlgoFile(name);
#endif
	int res = system(cmd_remove.c_str());
	if(res == 0){
		string buff = "";
		ifstream _filein(fileDirectory.c_str(), ios::in);
		if(_filein){
			string line;
			while(getline(_filein, line)){
				if(getAlgoName(line) != name)
					buff += line + "\n";
			}
			_filein.close();
		}
		else
			cerr << "Error while loading of the list of algorithms" << endl;
		ofstream _fileout(fileDirectory.c_str());
		_fileout << buff;
		_fileout.close();
	}
	else return "Error while removing algorithm :\n " + cmd_remove;
	return "";
}

list<string>* AlgoLoader::findAll(){
	list<string> *algos = new list<string>();
	ifstream _file(fileDirectory.c_str(), ios::in);
	if(_file){
		string line;
		while(getline(_file, line))
			algos->push_back(getAlgoName(line));
		_file.close();
	}
	else
		cerr << "Error while loading of the list of algorithms" << endl;
	return algos;
}

void AlgoLoader::showError(){
	cerr <<
#if defined(WIN32) || defined(WIN64)
	GetLastError();
#else
	dlerror()
#endif
	 << endl;
}

string AlgoLoader::getAlgoName(string line){
	string result;
	unsigned int i = 0;
	while(i < line.size() && line.at(i) != '\t' && line.at(i) != ':'){
		result.push_back(line.at(i));
		i++;
	}
	return result;
}

string AlgoLoader::getAlgoFile(string algoName){
	string result = "";
	ifstream _file(fileDirectory.c_str(), ios::in);
	if(_file){
		string line;
		bool find = false;
		while(getline(_file, line) && !find){
			if(algoName == getAlgoName(line)){
				unsigned int i = 0;
				while(i < line.length() && line.at(i) != ':')
					i++;
				i++;
				while((i < line.length() && line.at(i) == ' ') || (i < line.length() && line.at(i) == '\t'))
					i++;
				while(i < line.length() && line.at(i) != '\n'){
					result.push_back(line.at(i));
					i++;
				}
			}
		}
		_file.close();
	}
	else
		cerr << "Error while loading of the list of algorithms" << endl;
	return result;
}

string AlgoLoader::replace(string str, const string from, const string to){
	size_t lookHere = 0;
	size_t foundHere;
	while((foundHere = str.find(from, lookHere)) != string::npos) {
		str.replace(foundHere, from.size(), to);
		lookHere = foundHere + to.size();
	}
	return str;
}

string AlgoLoader::createFile(string title, string src){
	string fileDir = directory+title+".cpp";
	ofstream _file(fileDirectory.c_str());
	if(_file){
		_file << src;
		_file.close();
	}
	return fileDir;
}
