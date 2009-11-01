import com.music.controller.AbstractController;
import com.music.controller.Controller;
import com.music.model.Library;
import com.music.model.Model;
import com.music.view.IHM;


public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Model model = new Library();
		AbstractController ctrl = new Controller(model);
		IHM view = new IHM(ctrl);
		model.addObserver(view);
	}

}

/**
 * FENETRE AVEC QT JAMBI
 */
//import com.trolltech.qt.gui.*;
//
//public class Main extends QMainWindow{
//
//    private QMenu fileMenu;
//    private QMenu helpMenu;
//
//    private QAction exitAct;
//    private QAction aboutAct;
//    private QAction aboutQtJambiAct;
//
//    public static void main(String[] args) {
//        QApplication.initialize(args);
//
//        Main testmain = new Main(null);
//        testmain.show();
//
//        QApplication.exec();
//    }
//
//    public Main(QWidget parent){
//        super(parent);
//        createActions();
//        createMenus();
//    }
//
//    private void createActions()
//    {
//        exitAct = new QAction(tr("E&xit"), this);
//        exitAct.setShortcut(tr("Ctrl+Q"));
//        exitAct.setStatusTip(tr("Exit the application"));
//        exitAct.triggered.connect(this, "close()");
//
//        aboutAct = new QAction(tr("&About"), this);
//        aboutAct.setStatusTip(tr("Show the application's About box"));
//        aboutAct.triggered.connect(this, "about()");
//
//        aboutQtJambiAct = new QAction(tr("About &Qt Jambi"), this);
//        aboutQtJambiAct.setStatusTip(tr("Show the Qt Jambi's About box"));
//        aboutQtJambiAct.triggered.connect(QApplication.instance(), "aboutQtJambi()");
//    }
//
//    private void createMenus()
//    {
//        fileMenu = menuBar().addMenu(tr("&File"));
//        fileMenu.addAction(exitAct);
//
//        helpMenu = menuBar().addMenu(tr("&Help"));
//        helpMenu.addAction(aboutAct);
//        helpMenu.addAction(aboutQtJambiAct);
//    }
//
//    protected void about() {
//        QMessageBox.information(this, "Info", "It's your turn now :-)");
//    }
//}
