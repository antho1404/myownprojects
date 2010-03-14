/**
  * @author Estebe Anthony
  */
  
#ifndef ALGOEDIT_H
#define ALGOEDIT_H

#define SOURCE 1
#define HEADER 0

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qsciapis.h>

class MainFrame;
class AlgoEdit : public QsciScintilla {

public:
	AlgoEdit(QString name, int val);

private:
	void fillAlgo();
	int id;
	QString name;
	QsciScintilla *sci;
	QsciLexerCPP *lexerCPP;
	QsciAPIs *api;
};

#endif // ALGOEDIT_H
