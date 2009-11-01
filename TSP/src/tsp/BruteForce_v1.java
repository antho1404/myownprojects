
package tsp;

import java.util.ArrayList;

		/**
		 * Classe permettant de g�n�rer tous les parcours possibles entre toutes les 
		 * villes contenues dans le graphe g et en r�cup�rant la meilleur
		 * @author Dejean Quentin, Estebe Anthony
		 */

public class BruteForce_v1 extends MethodesResolution{

	/**
	 * Constructor
	 * @param g : graphe des villes
	 */
	public BruteForce_v1(Graphe g){
		super(g);
		double deb=System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}
	
	/**
	 * Methods
	 */
	
	//Execution du brute force
	private void run(){
		ArrayList<Integer> parcours = new ArrayList<Integer>();
		ArrayList<Integer> sommets = new ArrayList<Integer>();
		
		//initialisation de la liste contenant les sommets
		for (int i=1; i<super.g.getDim();i++) {
			sommets.add(i);
		}
		cheminMin(parcours,sommets,super.g.getDim());
	}
	
	//recherche du chemin le plus cours
	private void cheminMin (ArrayList<Integer> parcours, ArrayList<Integer> sommets,  int n){
		
		//condition d'arret
		if (sommets.size()>=1){
			if (n != super.g.getDim()){
				for (int ind=0; ind<sommets.size(); ind++) {
					ArrayList<Integer> cpSommets = new ArrayList<Integer>();
					ArrayList<Integer> cpParcours = new ArrayList<Integer>();
					cpParcours = super.copieListe(parcours);
					cpSommets = super.copieListe(sommets);
					cpParcours.add(cpSommets.get(ind));
					cpSommets.remove(ind);

					//appel r�cursif avec les copies avec ajout du sommet dans le parcours
					cheminMin(cpParcours, cpSommets, n-1);
				}
			}else{
				ArrayList<Integer> cpSommets = new ArrayList<Integer>();
				ArrayList<Integer> cpParcours = new ArrayList<Integer>();
				cpParcours = super.copieListe(parcours);
				cpSommets = super.copieListe(sommets);
				//cpParcours.add(0);
				
				//appel r�cursif avec les copies
				cheminMin(cpParcours, cpSommets, n-1);
			}
		}
		else {
			System.out.println(parcours);
			double dist = super.g.calculDist(0, parcours.get(parcours.size()-1))+calculParcours(parcours);
			if (dist<super.dist || super.dist == -1){
				super.dist = dist;
				super.parcoursMin = super.copieListe(parcours);
				super.parcoursMin.add(0);
			}
		}
	}
	
	//retourne la distance entre tous les points du parcours
	private double calculParcours (ArrayList<Integer> list){
		double val = 0;
		for (int i=0; i<list.size()-1; i++){
			val += super.g.calculDist(list.get(i), list.get(i+1));
		}
		return val;
	}
}