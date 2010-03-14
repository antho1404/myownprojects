/**
  * @author Estebe Anthony
  */
  
#ifndef TOOLSBAR_H
#define TOOLSBAR_H

#include <QtGui/QToolBar>
#include <QComboBox>
#include <QPushButton>

using namespace std;

class MainFrame;

class ToolsBar : public QToolBar
{
public:
	ToolsBar(MainFrame * f);
	string getAlgo();
	int getAlgoIndex();
	void updateAlgo();

private:
	MainFrame * parent;
	QComboBox *cbAlgo;
};

#endif // TOOLSBAR_H
