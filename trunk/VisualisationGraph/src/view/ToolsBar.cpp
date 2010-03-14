/**
  * @author Estebe Anthony
  */
  
#include "ToolsBar.h"
#include <QAction>
#include <QLabel>
#include <list>
#include <string>
#include "MainFrame.h"

ToolsBar::ToolsBar(MainFrame * f){
	this->parent = f;

	QAction *a;
	a = new QAction(QIcon("picture/new.png"), "Nouveau graphe", this);
	connect(a, SIGNAL(triggered()), parent, SLOT(newGraph()));
	addAction(a);

	a = new QAction(QIcon("picture/generate.png"), QString().fromUtf8("Générer un graphe"), this);
	connect(a, SIGNAL(triggered()), parent, SLOT(generateGraph()));
	addAction(a);

	addSeparator();

	a = new QAction(QIcon("picture/import.png"), "Importer un graphe", this);
	connect(a, SIGNAL(triggered()), parent, SLOT(importGraph()));
	addAction(a);

	a = new QAction(QIcon("picture/open.png"), "Ouvrir un graphe", this);
	connect(a, SIGNAL(triggered()), parent, SLOT(importGraphFromFile()));
	addAction(a);

	a = new QAction(QIcon("picture/save.png"), "Sauvegarder un graphe", this);
	connect(a, SIGNAL(triggered()), parent, SLOT(exportGraph()));
	addAction(a);

	addSeparator();

	addWidget(new QLabel("Algorithmes : "));

	cbAlgo = new QComboBox(this);
	updateAlgo();
	cbAlgo->setCurrentIndex(settings.value("Algo/algorithm", 0).toInt());
	addWidget(cbAlgo);
}

string ToolsBar::getAlgo(){
	return cbAlgo->currentText().toStdString();
}

int ToolsBar::getAlgoIndex(){
	return cbAlgo->currentIndex();
}

void ToolsBar::updateAlgo(){
	cbAlgo->clear();
	list<string> *algos = parent->getAlgoList();
	for(list<string>::iterator it = algos->begin(); it != algos->end(); it++)
		cbAlgo->addItem(QString().fromStdString(*it));
	delete algos;
	cbAlgo->adjustSize();
}
