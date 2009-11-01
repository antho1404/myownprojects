package tsp;

	/**
	 * Classe permettant de g�n�rer tous les parcours possibles entre toutes les 
	 * villes si ceux ci sont inf�rieurs � un parcours d�ja trouv�
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class BackTrack extends MethodesResolution{

	private double limite;
	private int[] circuit;
	private int[] circuitMin;
	private boolean [] utilise;


	/**Constructor
	 * @param g : graphe des villes
	 */
	public BackTrack(Graphe g){
		super(g);
		double deb=System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}

	/**
	 * Methods
	 */
	
	//execution du backtrack
	private void run() {
		MethodesResolution algo = new Algo2opt(super.g);

		super.dist = 0;
		this.limite = 0 ;
		this.circuit = new int[super.g.getDim()];
		this.circuitMin=new int[super.g.getDim()];
		this.utilise = new boolean[g.getDim()];
		for(int i=0;i<super.g.getDim();i++){
			this.circuit[i] = 0;
			this.utilise[i] = false;
			this.circuitMin[i] = algo.parcoursMin.get(i);
		}

		this.limite = algo.dist;
		this.utilise[0] = true;

		recherche(1, 0);

		for(int i=0; i<super.g.getDim(); i++)
			super.parcoursMin.add(this.circuitMin[i]);
		super.parcoursMin.add(0);
		for (int i=0; i<super.parcoursMin.size()-1;i++)
			super.dist += super.g.calculDist(this.parcoursMin.get(i),this.parcoursMin.get(i+1));
	}

	private void recherche(int rang, double dist) {
		double d = 0;
		// pas fini
		if (rang < super.g.getDim()) {
			for (int i=0; i<super.g.getDim(); i++) {
				if(!this.utilise[i]){
					d = dist + super.g.calculDist(this.circuit[rang-1],i);
					if (d < this.limite) {
						this.circuit[rang] = i;
						this.utilise[i] = true;
						recherche(rang+1, d);
						this.utilise[i] = false;
					}
				}
			}
		}
		// fini
		else {
			d = dist + super.g.calculDist(this.circuit[rang-1], 0);
			if (d < this.limite){
				this.limite = d;
				for (int i=0; i< this.circuit.length; i++)
					this.circuitMin[i] = this.circuit[i];
			}
		}
	}
}
