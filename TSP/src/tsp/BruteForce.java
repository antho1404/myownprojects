package tsp;

	/**
	 * Classe permettant de g�n�rer tous les parcours possibles entre toutes les 
	 * villes si ceux ci sont inf�rieurs � un parcours d�ja trouv�
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class BruteForce extends MethodesResolution{

	private double limite;
	private int[] circuit;
	private int[] circuitMin;
	private boolean [] utilise;


	/**
	 * Constructor
	 * @param g : graphe des villes
	 */
	public BruteForce(Graphe g){
		super(g);
		double deb=System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}

	/**
	 * Methods
	 */
	
	//execution du brute force
	private void run() {

		super.dist = 0;
		this.limite = -1 ;
		this.circuit = new int[super.g.getDim()];
		this.circuitMin=new int[super.g.getDim()];
		this.utilise = new boolean[super.g.getDim()];
		for(int i=0;i<super.g.getDim();i++){
			this.circuit[i] = 0;
			this.utilise[i] = false;
		}
		this.utilise[0] = true;

		recherche(1, 0);

		for(int i=0; i<super.g.getDim(); i++)
			super.parcoursMin.add(this.circuitMin[i]);
		super.parcoursMin.add(0);
		for (int i=0; i<super.parcoursMin.size()-1;i++)
			super.dist += super.g.calculDist(this.parcoursMin.get(i),this.parcoursMin.get(i+1));
	}

	//m�thode r�cursive permettant de chercher le parcours
	private void recherche(int rang, double dist) {
		double d = 0;
		// pas fini
		if (rang < super.g.getDim()) {
			for (int i=0; i<super.g.getDim(); i++) {
				if(!this.utilise[i]){
					d = dist + super.g.calculDist(this.circuit[rang-1],i);
					this.circuit[rang] = i;
					this.utilise[i] = true;
					recherche(rang+1, d);
					this.utilise[i] = false;
				}
			}
		}
		// fini
		else {
//			affiche2();
			d = dist + super.g.calculDist(this.circuit[rang-1], 0);
			if (d < this.limite || this.limite == -1){
				this.limite = d;
				for (int i=0; i< this.circuit.length; i++)
					this.circuitMin[i] = this.circuit[i];
			}
		}
	}
}