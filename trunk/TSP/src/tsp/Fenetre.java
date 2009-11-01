package tsp;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

@SuppressWarnings("serial")
public class Fenetre extends JFrame implements ActionListener{
	
	public Graphe graphe;					//Graphe contenant les villes
	public MethodesResolution choix;		//Choix de l'algo de recherche
	public JInternalFrame graphique;		//Fenetre interne contenant le graphique
	public JSlider slider;					//slider permettant de selectionner le nombre de villes
	public JSpinner spinnerV;				//spinner permettant de selectionner le nombre de villes
	public JTextField textResult1, textResult2;		//cases de saisie permettant l'affichage de la distance et du temp
	public JComboBox dimEchelle;			//dimention de l'echelle
	public JTextField echelle;				//taille de l'echelle
	public JCheckBoxMenuItem carte;

	private JInternalFrame ville, algo, resultat;		//Fenetres internes contenant la gestion de villes, des algo et des r�sultats
	private JDesktopPane desktop;			//panneau contenant les fenetres internes
	private JButton boutonVille, quitter, save;			//bouton permettant de g�n�rer des nouvelles ville, quitter le programme et sauvegarder
	private JLabel labelVille, labelAlgo, labelResult1, labelResult2;	//Labels permettant l'explication des boutons et autres
	private JMenuBar barre;				//barre de menu
	private JMenu fichier, aide;				//menu de la barre de menu
	private JMenuItem aPropos, saveVille, openVille, quit;	//sous menu contenus dans la barre de menu
	private JButton[] tabButton;		//tableau de boutons contenant les diff�rent algo
	private String[] tabString = {"BruteForce", "BackTrack", "Dynamique", "PlusProcheVoisin", "Algo2opt", "Meilleur Insertion"};
	private JCheckBox mem;		//permet de choisir le type d'optimisation
	
	
	/**
	 * Constructor
	 */
	
	public Fenetre (){
		super.setSize(800, 640);	//taille de la fenetre
		super.setTitle("Voyageur de Commerce");	//titre
		super.setDefaultCloseOperation(EXIT_ON_CLOSE);	//op�ration de fermeture
		super.setResizable(false);	//non redimentionnable
		super.setIconImage(Toolkit.getDefaultToolkit().getImage("img/logo.gif"));	//ajout logo

		//position en millieu d'�cran
		int xScreen = Toolkit.getDefaultToolkit().getScreenSize().width;
		int yScreen = Toolkit.getDefaultToolkit().getScreenSize().height;
		super.setLocation((xScreen-800)/2, (yScreen-600)/2);
		
		this.graphe = new Graphe(20);	//cr�ation d'un nouveau graphe
		this.choix = null;	//initialisation du choix de l'algorythme
		
		//Initialisation du fond
		this.desktop = new JDesktopPane();
		this.desktop.setBackground(Color.orange);
		super.setContentPane(this.desktop);
				
		//cr�ation du bouton pour sauvegarder les points et le graphe
		this.save = new JButton("Sauvegarder");
		this.save.setActionCommand("Sauvegarder");
		this.save.setFont(new Font(Font.SERIF,1,20));
		this.save.addActionListener(this);
		this.save.setSize(150, 30);
		this.save.setLocation(470, 550);
		this.save.setVisible(true);
		this.desktop.add(this.save);
						
		//cr�ation du bouton pour quitter l'application
		this.quitter = new JButton("Quitter");
		this.quitter.setActionCommand("Quitter");
		this.quitter.setFont(new Font(Font.SERIF,1,20));
		this.quitter.addActionListener(this);
		this.quitter.setSize(150, 30);
		this.quitter.setLocation(630, 550);
		this.quitter.setVisible(true);
		this.desktop.add(this.quitter);
		
		this.echelle = new JTextField("1");
		this.echelle.setSize(40, 20);
		this.echelle.setLocation(285, 540);
		this.echelle.setVisible(true);
		this.dimEchelle = new JComboBox();
		this.dimEchelle.addItem("km");	//choix de la combobox
		this.dimEchelle.addItem("m");
		this.dimEchelle.addItem("cm");
		this.dimEchelle.addItem("mm");
		this.dimEchelle.setSize(60,20);
		this.dimEchelle.setLocation(325, 540);
		this.dimEchelle.setVisible(true);
		JLabel fleche = new JLabel();
		fleche.setFont(new Font(Font.SERIF, 1, 15));
		fleche.setText("----------------------------------------------------->");
		//fleche d'unit� d'echelle
		fleche.setSize(500,20);
		fleche.setLocation(285, 521);
		fleche.setVisible(true);
		JLabel footer = new JLabel("Développé par DEJEAN Quentin et ESTEBE Anthony");
		footer.setSize(400, 20);
		footer.setLocation(5, 570);
		footer.setVisible(true);
		this.desktop.add(footer);
		this.desktop.add(fleche);
		this.desktop.add(this.dimEchelle);
		this.desktop.add(this.echelle);
		
		//initialisation de la barre de menu
		initMenu();
		
		//initialisation des fenetre internes
		initVille();
		initAlgo();
		initGraphique();
		initResultat();
		
		//affichage de la fenetre correctement initialis�e
		super.setVisible(true);
	}
	
	/**
	 * Methods
	 */
	
	private void initMenu(){
		//Initialisation de la barre de menu
		this.barre = new JMenuBar();
		//cr�ation des menus
		this.fichier = new JMenu("Fichier");
		this.aide = new JMenu("?");
		//cr�ation des sous menus
		this.aPropos = new JMenuItem("A Propos");
		this.saveVille = new JMenuItem("Sauvegarder");
		this.openVille = new JMenuItem("Ouvrir");
		this.carte = new JCheckBoxMenuItem("Ajout Carte");
		this.quit = new JMenuItem("Quitter");
		//cr�ation des commandes d'action
		this.aPropos.setActionCommand("A Propos");
		this.saveVille.setActionCommand("Sauvegarder");
		this.openVille.setActionCommand("Ouvrir");
		this.carte.setActionCommand("carte");
		this.quit.setActionCommand("Quitter");
		//ajout d'accelerateur
		this.quit.setAccelerator(KeyStroke.getKeyStroke("alt F4"));
		this.openVille.setAccelerator(KeyStroke.getKeyStroke("ctrl O"));
		this.saveVille.setAccelerator(KeyStroke.getKeyStroke("ctrl S"));
		//ajout d'�couteurs
		this.aPropos.addActionListener(this);
		this.saveVille.addActionListener(this);
		this.openVille.addActionListener(this);
		this.carte.addActionListener(this);
		this.quit.addActionListener(this);
		//ajout des menus a la barre
		this.fichier.add(this.saveVille);
		this.fichier.add(this.openVille);
		this.fichier.add(this.carte);
		this.fichier.addSeparator();
		this.fichier.add(this.quit);
		this.aide.add(this.aPropos);
		this.barre.add(this.fichier);
		this.barre.add(this.aide);
		super.setJMenuBar(this.barre);
	}
	
	private void initVille() {
		// initialisation de la fenetre interne Ville
		this.ville = new JInternalFrame("Ville",false,false,false,false);
		this.ville.setSize(265, 150);
		this.ville.setLocation(10, 20);
		this.ville.setBackground(Color.gray);
		this.ville.setBorder(BorderFactory.createEtchedBorder());
		
		this.labelVille = new JLabel("Nombre de villes : ");
		this.slider = new JSlider(0,500,20);	//cr�ation d'un slider de 0 � 500
		this.slider.setMajorTickSpacing(100);	
		this.slider.setMinorTickSpacing(50);
		this.slider.setPaintTicks(true);
		this.slider.setPaintLabels(true);
		this.spinnerV = new JSpinner();
		this.spinnerV.setPreferredSize(new Dimension(60, 20));
		JSpinner.NumberEditor spinnerEditor = new JSpinner.NumberEditor(this.spinnerV);
		this.spinnerV.setEditor(spinnerEditor);	//permet la configuration du spinner
		spinnerEditor.getModel().setMinimum(3);
		spinnerEditor.getModel().setMaximum(500);
		spinnerEditor.getModel().setValue(20);
		this.slider.addChangeListener(new ChangeListener(){	//ajout d'un �couteur et d�finition interne
			public void stateChanged(ChangeEvent arg0) {
				spinnerV.setValue(slider.getValue());
			}
		});
		this.slider.setBackground(Color.gray);
		
		this.boutonVille = new JButton("Generer");	//cration du bouton pour g�n�rer les villes
		this.boutonVille.addActionListener(this);	//ajout de l'�couteur
				
		this.ville.getContentPane().setLayout(new FlowLayout());	//cr�ation d'un flowlayout
		//ajout des composants
		this.ville.getContentPane().add(this.labelVille);
		this.ville.getContentPane().add(this.spinnerV);
		this.ville.getContentPane().add(this.slider);
		this.ville.getContentPane().add(this.boutonVille);
	
		this.ville.setVisible(true);
		this.desktop.add(this.ville);
	}
	
	private void initAlgo() {
		Dimension dim = new Dimension(115,25);	
		this.tabButton = new JButton[6];
		this.labelAlgo = new JLabel("Selectionnez l'algorithme de votre choix :");

		// initialisation de la fenetre interne Algorithme
		this.algo = new JInternalFrame("Algorithme",false,false,false,false);
		this.algo.setSize(265,220);
		this.algo.setLocation(10,187);
		this.algo.setBackground(Color.gray);
		this.algo.setBorder(BorderFactory.createEtchedBorder());
		
		this.algo.getContentPane().setLayout(new FlowLayout());
		this.algo.getContentPane().add(this.labelAlgo);

		JPanel exact, aprox;	//cr�ation de 2 panneau contenant les diff�rents boutons
		//de methodes exactes ou aproximatives
		exact = new JPanel();
		aprox = new JPanel();
		exact.setBackground(Color.gray);
		aprox.setBackground(Color.gray);
		exact.setPreferredSize(new Dimension(125, 140));
		aprox.setPreferredSize(new Dimension(125, 140));
		exact.setBorder(BorderFactory.createTitledBorder("Exactes  "));
		aprox.setBorder(BorderFactory.createTitledBorder("Approch�es"));
				
		//initialisation des boutons
		for (int i=0; i<this.tabButton.length; i++){
			this.tabButton[i] = new JButton(this.tabString[i]);	//ajout titre
			this.tabButton[i].setPreferredSize(dim);
			this.tabButton[i].addActionListener(this);	//ajout �couteurs
			this.tabButton[i].setFont(new Font(Font.SERIF, 0, 12));
			//r�partition
			if (i<3)exact.add(this.tabButton[i]);
			else aprox.add(this.tabButton[i]);
		}
		
		this.mem = new JCheckBox("Prioriser la vitesse");
		this.mem.setBackground(Color.gray);
		this.mem.addActionListener(new ActionListener(){	//ajout d'un �couteur interne
			public void actionPerformed(ActionEvent arg0) {
				graphe.setPlaceMemoire(mem.isSelected());
			}
		});
		this.mem.setVisible(true);

		//ajout des composants
		this.algo.getContentPane().add(exact);
		this.algo.getContentPane().add(aprox);
		this.algo.getContentPane().add(mem);
		this.algo.setVisible(true);
		this.desktop.add(this.algo);
	}

	private void initGraphique() {
		// initialisation de la fenetre interne Graphique
		this.graphique = new JInternalFrame("Graphique",false,false,false,false);
		this.graphique.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
		this.graphique.setSize(485,507);
		this.graphique.setLocation(285,20);
		this.graphique.setBorder(BorderFactory.createEtchedBorder());
		
		//dessin de la grille
		this.graphique.setContentPane(new Dessin(this));
				
		this.graphique.setVisible(true);
		this.desktop.add(this.graphique);
	}

	private void initResultat() {
		// initialisation de la fenetre interne R�sultat
		this.resultat = new JInternalFrame("Resultat",false,false,false,false);
		this.resultat.setSize(265,100);
		this.resultat.setLocation(10,426);
		this.resultat.setBackground(Color.gray);
		this.resultat.setBorder(BorderFactory.createEtchedBorder());
		
		//cr�ation des labels et des zones de saisie
		this.labelResult1 = new JLabel("Distance du parcours : ");
		this.textResult1 = new JTextField(7);
		this.textResult1.setEditable(false);	//impossible � �diter
		this.labelResult2 = new JLabel("       Temp d'execution : ");
		this.textResult2 = new JTextField(7);
		this.textResult2.setEditable(false);	//impossible � �diter
		//ajout des composant
		this.resultat.getContentPane().setLayout(new FlowLayout());
		this.resultat.getContentPane().add(this.labelResult1);
		this.resultat.getContentPane().add(this.textResult1);
		this.resultat.getContentPane().add(this.labelResult2);
		this.resultat.getContentPane().add(this.textResult2);
		
		this.resultat.setVisible(true);
		this.desktop.add(this.resultat);
	}

	public void actionPerformed(ActionEvent e) {
		String evt = e.getActionCommand();
		if (evt == "Generer"){	//g�n�rer les villes
			this.choix = null;		//initialisation du choix de l'algo
			this.mem.setSelected(false);	//optimisation r�initialis�
			//cr�ation d'un nouveau graphe
		    this.graphe = new Graphe(Integer.parseInt(spinnerV.getValue().toString()));
		    //ajout du dessin
			this.graphique.setContentPane(new Dessin(this));
		    repaint();
		}	
		if (evt == "Quitter"){	//quitter le programme
			System.exit(0);		//fermeture du programme
		}
		if (evt == "Sauvegarder" || evt == "Ouvrir"){	//sauvegarder / ouvrir
			Fichier xml = new Fichier();
			if (evt == "Sauvegarder")	//sauvegarder
				try{
					xml.save(this.choix);	//sauvegarde 
				}catch (NullPointerException e1){}
			if (evt == "Ouvrir"){	//ouvrir
				try{
					xml.load();	//ouverture
					this.spinnerV.setValue(Graphe.listeVille.size());
					repaint();
				}catch (NullPointerException e1){}
			}
		}
		if (evt == "A Propos"){	//a propos
			//fenetre contenant le "a propos"
			JOptionPane.showMessageDialog(null,
				      "    TSP - Travelling Salesman Problem :\n" +
				      "		  Probl�me du Voyageur de Commerce  \n\n" +
				      "But : \n" +
				      " Trouver le plus court chemin en passant \n" +
				      "       par toutes les villes disponnibles. \n\n" + 
				      "D�velopp� par :\n" +
				      "          DEJEAN Quentin \n" +
				      "          ESTEBE Anthony \n",
				      "A propos",
				      JOptionPane.INFORMATION_MESSAGE, 
				      new ImageIcon("img/logo.png"));
  
		}
		//pression d'un bouton lancant un algorithme
		if (evt == "BruteForce" || evt == "BackTrack" || evt == "PlusProcheVoisin" || evt == "Algo2opt" 
			|| evt == "Meilleur Insertion" || evt == "Dynamique"){
			AlgoThread algo = new AlgoThread(evt, this);	//cr�ation d'un algo
			algo.run();
//			algo.start();	//execution de l'algo
			this.graphique.setContentPane(new Dessin(this));	//nouveau dessin
		}
		if (evt == "carte"){
			Dessin bla = new Dessin(this);
			bla.setCarte(true);
			this.graphique.setContentPane(bla);
		}
	}
}