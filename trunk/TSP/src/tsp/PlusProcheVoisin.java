package tsp;

	/**
	 * Classe premettant de g�nerer la recherche gloutonne du plus proche voisin
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class PlusProcheVoisin extends MethodesResolution{
	
	
	private boolean villeParcourus[];	//tableau des villes parcourus

	/**
	 * Constructor
	 * @param g : Graphe contenant les villes
	 */
	
	public PlusProcheVoisin(Graphe g){
		super(g);
		super.dist = 0;		
		this.villeParcourus = new boolean[super.g.getDim()];
		double deb = System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}
	
	/**
	 * Methods
	 */
	
	//Execution du plus proche voisin
	private void run(){
		int sommetSuiv = 0;
		int tmp = 0;
		
		for (int i=0; i<this.villeParcourus.length; i++){
			super.parcoursMin.add(sommetSuiv);
			tmp = sommetSuiv;
			sommetSuiv = ppv(sommetSuiv);
			super.dist += super.g.calculDist(tmp, sommetSuiv);
		}
		super.parcoursMin.add(0);
	}
	
	//retourne le plus proche voisin d'un point
	private int ppv(int sommet){
	    double distMin = -1;
	    int indiceMin = 0;
	    for(int i=1;i<super.g.getDim();++i){
	    	if(i!=sommet && this.villeParcourus[i]==false){
	    		if(super.g.calculDist(sommet,i)<distMin || distMin == -1){
	    			distMin=super.g.calculDist(sommet,i);
	    			indiceMin=i;
	    		}
	    	}
	    }
	    this.villeParcourus[indiceMin]=true;
	    return indiceMin;
	}
}