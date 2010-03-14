/**
  * @author Estebe Anthony
  */
  
#include "ConfigGraph.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ConfigGraph::ConfigGraph(MainFrame *f){	
	parent = f;
	init();
	algoSpeed->setValue(settings.value("algo/speed", 1).toInt());
	algoInteract->setCurrentIndex(settings.value("algo/interact", 3).toInt());
	movable->setChecked(settings.value("algo/animated", true).toBool());
	showValue->setChecked(settings.value("algo/values", true).toBool());
	f->showValues(showValue->isChecked());
	f->annimateGraph(movable->isChecked());
	f->changeAlgoInteraction(algoInteract->currentIndex());
	f->changeAlgoSpeed(algoSpeed->value());
}

void ConfigGraph::init(){
	showValue = new QCheckBox(QString("Afficher les valeurs des arcs"), this);
	showValue->setChecked(true);
	movable = new QCheckBox(QString("Annimer le graphe"), this);
	movable->setChecked(true);
	algoInteract = new QComboBox(this);
	algoInteract->addItem(QString("Fifo"));
	algoInteract->addItem(QString("Lifo"));
	algoInteract->addItem(QString().fromUtf8("Aléatoire"));
	algoInteract->addItem(QString("Utilisateur"));
	algoInteract->setCurrentIndex(3);
	algoSpeed = new QSlider(Qt::Horizontal, this);
	algoSpeed->setValue(1);
	algoSpeed->setTickPosition(QSlider::TicksBelow);
	algoSpeed->setMinimum(0);
	algoSpeed->setMaximum(60);
	speed = new QSpinBox(this);
	speed->setMaximum(60);
	speed->setMinimum(0);
	speed->setValue(algoSpeed->value());
	run = new QPushButton(QIcon("picture/run.png"), QString("Lancer l'algorithme"), this);

	QVBoxLayout *layoutConfig = new QVBoxLayout(this);
	layoutConfig->addWidget(showValue);
	layoutConfig->addWidget(movable);
	QHBoxLayout *l3 = new QHBoxLayout(this);
	l3->addWidget(new QLabel(QString("Type d'interaction"), this));
	l3->addWidget(algoInteract);
	layoutConfig->addLayout(l3);
	QHBoxLayout *l4 = new QHBoxLayout(this);
	l4->addWidget(new QLabel(QString().fromUtf8("Vitesse de l'algorithme"), this));
	l4->addWidget(speed);
	layoutConfig->addLayout(l4);
	layoutConfig->addWidget(algoSpeed);
	layoutConfig->addWidget(run);
	QWidget *w = new QWidget(this);
	w->setLayout(layoutConfig);
	this->setWidget(w);

	connect(run, SIGNAL(clicked()), parent, SLOT(runAlgo()));
	connect(movable, SIGNAL(clicked(bool)), parent, SLOT(annimateGraph(bool)));
	connect(showValue, SIGNAL(clicked(bool)), parent, SLOT(showValues(bool)));
	connect(algoInteract, SIGNAL(currentIndexChanged(int)), parent, SLOT(changeAlgoInteraction(int)));
	connect(algoSpeed, SIGNAL(valueChanged(int)), parent, SLOT(changeAlgoSpeed(int)));
	connect(algoSpeed, SIGNAL(sliderMoved(int)), speed, SLOT(setValue(int)));
	connect(algoSpeed, SIGNAL(valueChanged(int)), speed, SLOT(setValue(int)));
	connect(speed, SIGNAL(valueChanged(int)), algoSpeed, SLOT(setValue(int)));
}

int ConfigGraph::getAlgoSpeed(){
	return algoSpeed->value();
}

int ConfigGraph::getInteraction(){
	return algoInteract->currentIndex();
}

bool ConfigGraph::getAnimated(){
	return movable->isChecked();
}

bool ConfigGraph::getValueVisible(){
	return showValue->isChecked();
}

void ConfigGraph::setEnableRunButton(bool b){
	run->setEnabled(b);
}
