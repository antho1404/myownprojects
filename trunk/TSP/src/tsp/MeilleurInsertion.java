package tsp;

import java.util.ArrayList;

	/**
	 * Classe permettant de g�n�rer un parcours en inserant au mieu un sommet
	 * dans les un parcours minimal optimal
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class MeilleurInsertion extends MethodesResolution{
	
	private double distMin;	//distance minimum du parcours
	private int sommet;	//meilleur sommet � inserer
	private int indice;		//meilleur emplacement du sommet 
	
	/**
	 * Constructor
	 * @param g : graphe contenant les villes
	 */
	
	public MeilleurInsertion(Graphe g){
		super(g);
		this.distMin = -1;
		this.sommet = -1;
		this.indice = -1;
		double deb = System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}

	/**
	 * Methods
	 */
	
	//execution de la meilleur insertion
	private void run(){
		ArrayList<Integer> sommetRest = new ArrayList<Integer>();
		ArrayList<Integer> cpRest = new ArrayList<Integer>();
		ArrayList<Integer> parcours = new ArrayList<Integer>();
		
		//initialisation d'un parcours minimum optimal
		for (int i=0; i<3;i++){
			parcours.add(i);
		}
		parcours.add(0);
		
		//initialisation des sommets restants
		for (int i=3;i<super.g.getDim();i++)
			sommetRest.add(i);
		
		//boucle sur tous les sommets
		while (!sommetRest.isEmpty()){
			cpRest = super.copieListe(sommetRest);
			this.distMin = -1;
			
			//boucle sur tous les sommets copi�s
			while (!cpRest.isEmpty()){
				
				//boucle sur le parcours
				for (int j=0;j<parcours.size()-1;j++){
					parcours.add(j+1, cpRest.get(0));
					
					//test si l'insertion ne d�grade pas le parcours
					if (calcParcours(parcours)<this.distMin || this.distMin == -1){
						this.distMin = calcParcours(parcours);
						this.indice = j;
						this.sommet = cpRest.get(0);
					}
					parcours.remove(j+1);
				}
				cpRest.remove(0);
			}
			
			//ajout de la valeur dans le parcours
			parcours.add(this.indice+1, this.sommet);
			suppVal(this.sommet, sommetRest);
		}
		super.parcoursMin = parcours;
		super.dist = this.distMin;
	}

	//supprime une valeur val dans une liste
	private ArrayList<Integer> suppVal (int val, ArrayList<Integer> list){
		for (int i=0; i<list.size();i++){
			if (list.get(i)==val){
				list.remove(i);
			}
		}
		return list;
	}
	
	//retourne la distance entre tous les sommet d'une liste
	private double calcParcours(ArrayList<Integer> parcours){
		double dist = 0;
		for(int i=0;i<parcours.size()-1;i++)
			dist+=super.g.calculDist(parcours.get(i), parcours.get(i+1));
		return dist;
	}
}
