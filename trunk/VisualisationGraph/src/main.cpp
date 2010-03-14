/**
  * @author Estebe Anthony
  */
  
#include "model/Model.h"
#include "controller/ControllerModel.h"
#include "view/Console.h"
#include "view/MainFrame.h"
#include <QtGui>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	AbstractModel *myModel = new Model();

	MainFrame *f = new MainFrame(myModel);
	if(argc > 1){
		if(argv[1][0] == '-' && argv[1][1] == 'a')
			f->addAlgo(argv[2]);
		else
			f->importGraph(argv[1]);
	}
	f->show();

//	Console *c = new Console(NULL);
//	myModel->addObserver(c);

	dynamic_cast<Model*> (myModel)->showGraph();
	return app.exec();
}
