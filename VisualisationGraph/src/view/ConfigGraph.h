/**
  * @author Estebe Anthony
  */
  
#ifndef CONFIGGRAPH_H
#define CONFIGGRAPH_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include "MainFrame.h"
#include <QDockWidget>

class ConfigGraph: public QDockWidget {

public:
	ConfigGraph(MainFrame *f);
	int getAlgoSpeed();
	int getInteraction();
	bool getAnimated();
	bool getValueVisible();
	void setEnableRunButton(bool b);

private:
	void init();
	MainFrame *parent;
	QCheckBox *showValue, *movable;
	QComboBox *algoInteract;
	QSlider *algoSpeed;
	QSpinBox *speed;
	QPushButton *run;
};

#endif // CONFIGGRAPH_H
