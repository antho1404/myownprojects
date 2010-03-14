/**
  * @author Estebe Anthony
  */
  
#include "MenuBar.h"

MenuBar::MenuBar(MainFrame *parent) {
	this->parent = parent;
	this->addMenu(fileMenu());
	this->addMenu(algoMenu());
	this->addMenu(showMenu());
}

QMenu* MenuBar::fileMenu() {
	menu = new QMenu(QString::fromUtf8("&Fichier"), this);

	action = new QAction(QString::fromUtf8("&Nouveau graphe"), menu);
	action->setStatusTip(QString::fromUtf8("Permet de créer un nouveau graphe"));
	action->setShortcut(QKeySequence("Ctrl+N"));
	action->setIcon(QIcon("picture/new.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(newGraph()));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("&Générer un graphe"), menu);
	action->setStatusTip(QString::fromUtf8("Permet de générer un nouveau graphe"));
	action->setShortcut(QKeySequence("Ctrl+G"));
	action->setIcon(QIcon("picture/generate.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(generateGraph()));
	menu->addAction(action);

	menu->addSeparator();

	action = new QAction(QString::fromUtf8("&Ouvrir un graphe"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'ouvrir un graphe de la librairie de graphes"));
	action->setShortcut(QKeySequence("Ctrl+O"));
	action->setIcon(QIcon("picture/import.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(importGraph()));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("Ouvrir un graphe depuis un fichier"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'ouvrir un graphe �  partir d'un fichier sauvegardé"));
	action->setShortcut(QKeySequence("Ctrl+Shift+O"));
	action->setIcon(QIcon("picture/open.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(importGraphFromFile()));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("&Sauvegarder le graphe"), menu);
	action->setStatusTip(QString::fromUtf8("Permet de sauvegarder le graphe courant"));
	action->setShortcut(QKeySequence("Ctrl+S"));
	action->setIcon(QIcon("picture/save.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(exportGraph()));
	menu->addAction(action);

	menu->addSeparator();

	action = new QAction(QString::fromUtf8("&Quitter"), menu);
	action->setStatusTip(QString::fromUtf8("Permet de quitter le logiciel"));
	action->setShortcut(QKeySequence("Ctrl+Q"));
	action->setIcon(QIcon("picture/quit.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(close()));
	menu->addAction(action);

	return menu;
}

QMenu* MenuBar::algoMenu() {
	menu = new QMenu(QString::fromUtf8("&Algorithme"), this);

	action = new QAction(QString::fromUtf8("&Lance l'algorithme"), menu);
	action->setStatusTip(QString::fromUtf8("Lance l'algorithme choisi sur le graphe courant"));
	action->setShortcut(QKeySequence("Ctrl+L"));
	action->setIcon(QIcon("picture/run.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(runAlgo()));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("&Ajouter un algorithme"), menu);
	action->setStatusTip(QString::fromUtf8("Ajoute un nouvel algorithme"));
	action->setIcon(QIcon("picture/addAlgo.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(addAlgo()));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("&Supprimer un algorithme"), menu);
	action->setStatusTip(QString::fromUtf8("Supprime un algorithme contenu dans la librairie d'algorithmes"));
	action->setIcon(QIcon("picture/delAlgo.png"));
	connect(action, SIGNAL(triggered()), parent, SLOT(removeAlgo()));
	menu->addAction(action);

	return menu;
}

QMenu* MenuBar::showMenu() {
	menu = new QMenu(QString::fromUtf8("&Affichage"), this);

	action = new QAction(QString::fromUtf8("Affiche/Cache la barre d'&outils"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'afficher ou de cacher la barre d'outils"));
	action->setCheckable(true);
	action->setChecked(settings.value("window/toolBar", true).toBool());
	connect(action, SIGNAL(triggered(bool)), parent, SLOT(toolsVisible(bool)));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("&Affiche/Cache la barre d'&état"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'afficher ou de cacher la barre d'état"));
	action->setCheckable(true);
	action->setChecked(settings.value("window/statusBar", true).toBool());
	connect(action, SIGNAL(triggered(bool)), parent, SLOT(stateVisible(bool)));
	menu->addAction(action);

	action = new QAction(QString::fromUtf8("Affichage &Réduit"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'afficher le logiciel avec une interface réduite"));
	action->setCheckable(true);
	action->setChecked(!settings.value("window/toolBox", true).toBool());
	action->setShortcut(QKeySequence("Ctrl+Shift+M"));
	connect(action, SIGNAL(triggered(bool)), parent, SLOT(showSmallWindow(bool)));
	menu->addAction(action);

	menu->addSeparator();

	action = new QAction(QString::fromUtf8("Affichage Plein Ecran"), menu);
	action->setStatusTip(QString::fromUtf8("Permet d'afficher le logiciel en plein écran"));
	action->setCheckable(true);
	action->setChecked(settings.value("window/fullScreen", false).toBool());
	action->setShortcut(QKeySequence("F11"));
	connect(action, SIGNAL(triggered(bool)), parent, SLOT(showFullScreen(bool)));
	menu->addAction(action);

	return menu;
}
