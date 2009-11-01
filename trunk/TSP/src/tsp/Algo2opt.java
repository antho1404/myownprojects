package tsp;

import java.util.ArrayList;

	/**
	 * Classe permettant de g�n�rer un nouveau parcours � partir d'un d�ja cr�er
	 * en cassant les boucle de ce parcours
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class Algo2opt extends MethodesResolution{
	
	private PlusProcheVoisin ppv;				//algorithme du plus proche voisin

	/**
	 * Constructor
	 * @param g : graphe contenant les villes
	 */
	
	public Algo2opt(Graphe g){
		super(g);
		double deb = System.currentTimeMillis();
		run();
		super.time = (System.currentTimeMillis()-deb);
	}
	
	/**
	 * Methods
	 */
	
	//Execution du 2opt
	private void run(){
		this.ppv = new PlusProcheVoisin(g);
		boolean change = true;
		
		//boucle sur les modifs du parcours
		while (change){
			change = false;	
			//boucle sur les villes
			for (int i=0; i<super.g.getDim()-1;i++){
				
				//boucles sur les villes suivantes
				for (int j=i+2; j<super.g.getDim();j++){
					if (test(i,j)){

						//modification du parcours
						echange(i,j);
						change = true;
					}
				}
			}	
		}
		super.parcoursMin = this.ppv.parcoursMin;
		super.dist = calcParcours(super.parcoursMin);
	}
	
	//Test si l'interversion des 2 sommet ne d�graderas pas le parcours
	private boolean test (int i, int j){
		boolean bool = false;
		
		// retourne vrai si d(i,i+1)+d(j,j+1) > d(i,j)+d(i+1,j+1)
		  if((super.g.calculDist(this.ppv.parcoursMin.get(i+1), this.ppv.parcoursMin.get(i))
		 + super.g.calculDist(this.ppv.parcoursMin.get(j+1), this.ppv.parcoursMin.get(j)))
			>
		   (super.g.calculDist(this.ppv.parcoursMin.get(i+1), this.ppv.parcoursMin.get(j+1))
			+ super.g.calculDist(this.ppv.parcoursMin.get(j), this.ppv.parcoursMin.get(i))))
		{
			bool = true;
		}
		return bool;
	}
	
	//changement des deux villes du parcours
	private void echange (int i, int j){
		int tmp = this.ppv.parcoursMin.get(i+1);
		this.ppv.parcoursMin.set(i+1, this.ppv.parcoursMin.get(j));
		this.ppv.parcoursMin.set(j, tmp);
	}
	
	//retourne la distance du parcours
	private double calcParcours(ArrayList<Integer> list){
		double dist = 0;
		for(int i=0;i<list.size()-1;i++)
			dist+=super.g.calculDist(list.get(i), list.get(i+1));
		return dist;
	}
}
