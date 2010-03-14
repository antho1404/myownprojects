/**
  * @author Estebe Anthony
  */
  
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QResizeEvent>
#include <QSettings>

#include "GraphWidget.h"
#include "../model/AbstractModel.h"
#include "../controller/ControllerModel.h"
#include "StatusBar.h"
#include "ToolsBar.h"
#include "MenuBar.h"
#include "ConfigGraph.h"

class MenuBar;
class GraphWidget;
class StatusBar;
class ConfigGraph;

class MainFrame: public QMainWindow {

Q_OBJECT

public:
	MainFrame(AbstractModel *m);

private:
	ControllerModel *ctrl;
	GraphWidget *graphWidget;
	StatusBar *status;
	ToolsBar *toolBar;
	MenuBar *menu;
	ConfigGraph *configG;
	QWidget *centralWidget;
	QComboBox *algoInteract;
	QSpinBox *speed;
	QSlider *algoSpeed;

protected:
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *);

public slots:
	void runAlgo();
	void stopAlgo();
	void importGraphFromFile();
	void importGraph();
	void importGraph(string src);
	void newGraph();
	void generateGraph();
	void exportGraph();
	void toolsVisible(bool b);
	void stateVisible(bool b);
	void showSmallWindow(bool b);
	void showFullScreen(bool b);
	void annimateGraph(bool b);
	void showValues(bool b);
	void changeAlgoSpeed(int speed);
	void changeAlgoInteraction(int flag);
	list<string> *getAlgoList();
	void addAlgo();
	void addAlgo(string src);
	void removeAlgo();
};

static QSettings settings("graph-visualisation", "Visualisation Graphe");

#endif //MAINFRAME_H
