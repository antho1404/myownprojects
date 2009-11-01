package tsp;

import java.util.ArrayList;

	/**
	 * Classe permettant de g�n�rer tous les parcours possibles entre toutes les 
	 * villes si ceux ci sont inf�rieurs � un parcours d�ja trouv�
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class BackTrack_v1 extends MethodesResolution{

	/**Constructor
	 * @param g : graphe des villes
	 */
	public BackTrack_v1(Graphe g){
		super(g);
		double deb = System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}
	
	/**
	 * Methods
	 */
	
	//execution du backtrack
	private void run(){
		ArrayList<Integer> parcours = new ArrayList<Integer>();
		ArrayList<Integer> sommets = new ArrayList<Integer>();
		
		//initialisation de la liste des sommets
		for (int i=1; i<super.g.getDim();i++) {
			sommets.add(i);
		}

		//g�n�ration d'un parcours initial
		Algo2opt algo = new Algo2opt(super.g);
		super.parcoursMin = algo.parcoursMin;
		super.dist = algo.dist;

		cheminMin(parcours,sommets,super.g.getDim(), 0);
	}
	
	//recherche du chemin le plus court
	private void cheminMin (ArrayList<Integer> parcours, ArrayList<Integer> sommets,  int n, double dist){
		
		//condition d'arret
		if (sommets.size()>=1){
			if (n != super.g.getDim()){
				
				//test si le parcours n'est pas sup�rieur au parcours total
				if (dist<super.dist){
					for (int ind=0; ind<sommets.size(); ind++) {
						double dist2 = dist + super.g.calculDist(parcours.get(parcours.size()-1), sommets.get(ind));
						ArrayList<Integer> sommets2 = new ArrayList<Integer>();
						ArrayList<Integer> parcours2 = new ArrayList<Integer>();
						parcours2 = super.copieListe(parcours);
						sommets2 = super.copieListe(sommets);
						parcours2.add(sommets2.get(ind));
						sommets2.remove(ind);
					
						//appel r�cursif avec les copies avec ajout du sommet dans le parcours
						cheminMin(parcours2, sommets2, n-1,dist2);
					}
				}
			}else{
				ArrayList<Integer> sommets2 = new ArrayList<Integer>();
				ArrayList<Integer> parcours2 = new ArrayList<Integer>();
				parcours2 = super.copieListe(parcours);
				sommets2 = super.copieListe(sommets);
				parcours2.add(0);
				
				//appel r�cursif avec les copies
				cheminMin(parcours2, sommets2, n-1, dist);
			}
		}
		else {
			double dist2 = super.g.calculDist(0, parcours.get(parcours.size()-1))+dist;
			if (dist2<super.dist || super.dist == -1){
				super.dist = dist2;
				super.parcoursMin = super.copieListe(parcours);
				super.parcoursMin.add(0);
			}
		}
	}
}
