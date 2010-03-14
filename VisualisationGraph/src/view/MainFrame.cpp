/**
  * @author Estebe Anthony
  */
  
#include "MainFrame.h"
#include <QFileDialog>
#include <QtGui/QSplitter>
#include <QInputDialog>
#include <QSettings>

MainFrame::MainFrame(AbstractModel *m) {
	ctrl = new ControllerModel(m);

	menu = new MenuBar(this);
	toolBar = new ToolsBar(this);
	status = new StatusBar();
	graphWidget = new GraphWidget(this, ctrl);
	configG = new ConfigGraph(this);
	centralWidget = new QWidget(this);

	QHBoxLayout *l = new QHBoxLayout(this);
	l->addWidget(graphWidget);

	centralWidget->setLayout(l);
	addDockWidget(Qt::RightDockWidgetArea, configG);
	this->setMenuBar(menu);
	this->addToolBar(toolBar);
	this->setCentralWidget(centralWidget);
	this->setStatusBar(status);

	m->addObserver(graphWidget);

	resize(settings.value("window/size", QSize(800, 600)).toSize());
	showFullScreen(settings.value("window/fullScreen", false).toBool());
	toolBar->setVisible(settings.value("window/toolBar", true).toBool());
	configG->setVisible(settings.value("window/toolBox", true).toBool());
	statusBar()->setVisible(settings.value("window/statusBar", true).toBool());
	move(settings.value("window/position", QPoint(200, 200)).toPoint());

	connect(ctrl, SIGNAL(finished()), this, SLOT(stopAlgo()));
	this->resize(width(), height()+1);
	this->resize(width(), height()-1);
}

void MainFrame::resizeEvent(QResizeEvent *event){
	Q_UNUSED(event);
	graphWidget->resize();
}

void MainFrame::closeEvent(QCloseEvent *event){
	settings.beginGroup("window");
	settings.setValue("size", size());
	settings.setValue("position", pos());
	settings.setValue("fullScreen", isFullScreen());
	settings.setValue("toolBar", toolBar->isVisible());
	settings.setValue("toolBox", configG->isVisible());
//	settings.setValue("toolBarPosition", toolBar->
	settings.setValue("statusBar", statusBar()->isVisible());
	settings.endGroup();
	settings.beginGroup("Algo");
	settings.setValue("algorithm", toolBar->getAlgoIndex());
	settings.setValue("speed", configG->getAlgoSpeed());
	settings.setValue("interact", configG->getInteraction());
	settings.setValue("animated", configG->getAnimated());
	settings.setValue("values", configG->getValueVisible());
	settings.endGroup();
	event->accept();
}

/*
 * SLOTS
 */

void MainFrame::runAlgo() {
	if (ctrl->isRunning())
		ctrl->terminate();
	configG->setEnableRunButton(false);
	ctrl->setAlgo(toolBar->getAlgo());
	ctrl->start();
}

void MainFrame::stopAlgo() {
	if (ctrl->isRunning())
		ctrl->terminate();
	configG->setEnableRunButton(true);
}

void MainFrame::importGraphFromFile() {
	QString file = QFileDialog::getOpenFileName(this, "Ouvrir un fichier",
			QString(), "Graphe (*.graph *.xml)");
	if(file != ""){
		if (ctrl->isRunning())
			ctrl->terminate();
		ctrl->importGraph(file.toStdString(), true);
	}
}

void MainFrame::importGraph() {
	list<string> *graphs = ctrl->getGraphList();
	QStringList graphList;
	for(list<string>::iterator it = graphs->begin(); it != graphs->end(); it++)
		graphList.push_back(QString::fromStdString(*it));
	delete graphs;
	QString g = QInputDialog::getItem(this, QString("Choix du graphe"), QString("Liste des graphes disponnibles"), graphList, 0, false);
	if(g != ""){
		if (ctrl->isRunning())
			ctrl->terminate();
		ctrl->importGraph(g.toStdString(), false);
	}
}

void MainFrame::importGraph(string src) {
	ctrl->importGraph(src, true);
}

void MainFrame::newGraph() {
	if (ctrl->isRunning())
		ctrl->terminate();
	ctrl->newGraph();
}

void MainFrame::generateGraph() {
	if (ctrl->isRunning())
		ctrl->terminate();
	ctrl->generateGraph();
}

void MainFrame::exportGraph() {
	QString file = QFileDialog::getSaveFileName(this, "Sauvegarder le graphe",
			QString(), "Graphe (*.graph *.xml)");
	if(file != "")
		ctrl->exportGraph(file.toStdString());
}

void MainFrame::toolsVisible(bool b){
	toolBar->setVisible(b);
	if(b) this->resize(width(), height()-1);
	else this->resize(width(), height()+1);
}

void MainFrame::stateVisible(bool b){
	statusBar()->setVisible(b);
	if(b) this->resize(width(), height()-1);
	else this->resize(width(), height()+1);
}

void MainFrame::showSmallWindow(bool b){
	configG->setVisible(!b);
	if(b) this->resize(width()-1, height());
	else this->resize(width()+1, height());
}

void MainFrame::showFullScreen(bool b){
	if(b)dynamic_cast<QMainWindow*>(this)->showFullScreen();
	else showNormal();
}

void MainFrame::annimateGraph(bool b){
	graphWidget->setAnnimated(b);
}

void MainFrame::showValues(bool b){
	graphWidget->showEdgesValues(b);
}

void MainFrame::changeAlgoSpeed(int speed){
	ctrl->changeAlgoSpeed(speed);
}

void MainFrame::changeAlgoInteraction(int flag){
	ctrl->changeAlgoInteraction(flag);
}

list<string> *MainFrame::getAlgoList(){
	return ctrl->getAlgoList();
}

void MainFrame::addAlgo(){
	QString name = QInputDialog::getText(this, "Nom de l'algorithme", "Nom de l'algorithme");
	if(name != ""){
#if defined(WIN32) || defined(WIN64)
                QString file = QFileDialog::getOpenFileName(this, "Choisir un algorithme",
                   QString(), "DLL (*.dll)");
#else
		QString file = QFileDialog::getOpenFileName(this, "Choisir un algorithme",
				"model/Algorithm", "CPP (*.cpp)");
#endif
		string result = ctrl->addAlgorithm(name.toStdString(), file.toStdString());
		if(result == "")
			toolBar->updateAlgo();
		else
			QMessageBox::critical(this, "Erreur", QString().fromStdString(result));
	}
}

void MainFrame::addAlgo(string src){
	QString name = QInputDialog::getText(this, "Nom de l'algorithme", "Nom de l'algorithme");
	if(name != ""){
		string result = ctrl->addAlgorithm(name.toStdString(), src);
		if(result == "")
			toolBar->updateAlgo();
		else
			QMessageBox::critical(this, "Erreur", QString().fromStdString(result));
	}
}

void MainFrame::removeAlgo(){
	list<string> *algos = ctrl->getAlgoList();
	QStringList algoList;
	for(list<string>::iterator it = algos->begin(); it != algos->end(); it++)
		algoList.push_back(QString::fromStdString(*it));
	delete algos;
	bool ok = false;
	QString algo = QInputDialog::getItem(this, "Suppression d'algorithmes", QString::fromUtf8("Algorithme Ã  supprimer"), algoList, 0, false, &ok);
	if(ok){
		int rep = QMessageBox::question(this, "Supression d'algorithme", QString::fromUtf8("Etes vous sÃ»r de vouloir supprimer\nl'algorithme ")+algo, QMessageBox::Yes | QMessageBox::No);
		if (rep == QMessageBox::Yes){
			string result = ctrl->removeAlgorithm(algo.toStdString());
			if(result == "")
				toolBar->updateAlgo();
			else
				QMessageBox::critical(this, "Erreur", QString().fromStdString(result));
		}
	}
}
