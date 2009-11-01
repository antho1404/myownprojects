package tsp;

	/**
	 * Permet d'executer les algo de recherche
	 * @author Dejean Quentin, Estebe Anthony
	 */
public class AlgoThread extends Thread{

	private String s;		//algo choisi
	private Fenetre fen;	//fenetre sur laquel on travaille
	
	/**
	 * Constructor
	 * @param algo : algo choisi
	 * @param fen  : fenetre sur laquelle on travaille
	 */
	public AlgoThread (String algo, Fenetre fen){
		this.s = algo;
		this.fen = fen;
	}
	
	//m�thode permettant de lancer les diff�rentes m�thodes
	public void run() {
		if (this.s == "BruteForce"){
			this.fen.choix = new BruteForce(this.fen.graphe);
		}
		if (this.s == "BackTrack"){
			this.fen.choix = new BackTrack(this.fen.graphe);
		}
		if (this.s == "Dynamique"){
			this.fen.choix = new Dynamique(this.fen.graphe);
		}
		if (this.s == "PlusProcheVoisin"){
			this.fen.choix = new PlusProcheVoisin(this.fen.graphe);
		}
		if (this.s == "Algo2opt"){
			this.fen.choix = new Algo2opt(this.fen.graphe);
		}
		if (this.s == "Meilleur Insertion"){
			this.fen.choix = new MeilleurInsertion(this.fen.graphe);
		}
	}
}
