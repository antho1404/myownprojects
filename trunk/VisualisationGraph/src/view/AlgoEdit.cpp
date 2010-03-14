/**
  * @author Estebe Anthony
  */
  
#include "AlgoEdit.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

AlgoEdit::AlgoEdit(QString name, int val){
	this->id = val;
	this->name = name;
	QString title = name + ((val == SOURCE) ? ".cpp" : ((val == HEADER) ? ".h" : ""));
	setWindowTitle(title);
	resize(width()*.7, height()+100);

	setUtf8(true);
	setMarginLineNumbers(1, true);
	setMarginWidth(1, 30);
	lexerCPP = new QsciLexerCPP();
	api = new QsciAPIs(lexerCPP);
	api->load("ressources/completion.txt");
	api->prepare();
	lexerCPP->setAPIs(api);
	setAutoCompletionSource(QsciScintilla::AcsAPIs);
	setAutoCompletionThreshold(1);
	setLexer(lexerCPP);
	setFolding(QsciScintilla::BoxedTreeFoldStyle, 2);

	fillAlgo();

	show();
}

void AlgoEdit::fillAlgo(){
	string fileDir = "";
	if(id == SOURCE)
		fileDir += "ressources/source";
	else if(id == HEADER)
		fileDir += "ressources/header";
	string buff = "";
	ifstream _filein(fileDir.c_str(), ios::in);
	if(_filein){
		string line;
		while(getline(_filein, line))
			buff += QString().fromStdString(line).replace("NouvelAlgo", name).toStdString() + "\n";
		_filein.close();
	}
	else
		cerr << "Error while fill the algo" << endl;
	setText(QString().fromUtf8(buff.c_str()));
}
