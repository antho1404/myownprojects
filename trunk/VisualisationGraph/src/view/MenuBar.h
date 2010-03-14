/**
  * @author Estebe Anthony
  */
  
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include "MainFrame.h"

class MenuBar: public QMenuBar {

public:
	MenuBar(MainFrame *parent);
	QMenu* fileMenu();
	QMenu* algoMenu();
	QMenu* showMenu();

private:
	MainFrame *parent;
	QMenu *menu;
	QAction *action;
};

#endif // MENUBAR_H
