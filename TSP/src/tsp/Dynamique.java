package tsp;

	/**
	 * Classe permettant la g�n�ration du parcours minimum grace � la programmation dynamique
	 * qui est une m�thode exacte, et avec un temp d'execution plus rapide que d'autres m�thodes
	 * exactes tels que le BackTrack ou le BruteForce et avec un temp toujours iddentique en 
	 * fonction du nombre de points.
	 * @author Dejean Quentin, Estebe Anthony
	 */

import java.util.Iterator;
import java.util.TreeMap;
import java.util.TreeSet;


public class Dynamique extends MethodesResolution{

	private TreeSet<Integer> colonne;					//notre colonne courante
	private int[] tabSet;								//notre tableau permettant l'initialisation des colonnes
	private TreeMap<TreeSet<Integer>, double[]> map;	//notre tableau contenant tout les sous ensemble de sommets contenant 0
														//et la distance vers les autres sommets de cet ensemble	

	/**
	 *  Constructor
	 *  @param g : graphe des villes
	 */
	public Dynamique (Graphe g){
		super(g);
		double deb=System.currentTimeMillis();
		run();
		super.time = System.currentTimeMillis()-deb;
	}

	//initialisation de la map
	private void run(){
		this.map = new TreeMap<TreeSet<Integer>, double[]>(new IntSetComparator());	
		this.tabSet = new int[super.g.getDim()];
		
		//premi�re colonne
		this.colonne = new TreeSet<Integer>();
		this.colonne.add(0);
		this.map.put(this.colonne,initValSet());
		
		for (int i=0; i<Math.pow(2,(super.g.getDim()-1))-1; i++){
			this.colonne = new TreeSet<Integer>();
			this.tabSet[this.tabSet.length-1]++;
			
			testInitSet(this.tabSet.length-1);		
			
			//cr�ation du set � l'aide du tableau
			for (int j=this.tabSet.length-1; j>=0; j--)
				this.colonne.add(tabSet[j]);
			
			
			this.map.put(this.colonne, initValSet());		//ajout de la nouvelle colonne dans la map
			this.colonne = new TreeSet<Integer>();			//cr�ation d'une nouvelle colonne
		}
		
		Iterator<TreeSet<Integer>> it = this.map.keySet().iterator();
		TreeSet<Integer> obj = null;
		//parcours de la map jusqu'� la derni�re colonne
		while(it.hasNext())
			obj = it.next();
		this.colonne = obj;
		super.dist = chercheMeilleur(0);	//trouve la meilleur distance totale
		trouveParcours(this.colonne, 0);	//retrouve le parcours
		super.parcoursMin.add(0,0);
	}
	
	//fonction r�cursive permettant de tester l'ajout de nouvelles valeurs dans la colonne
	private void testInitSet(int i){
		if (this.tabSet[i] == super.g.getDim()){
			this.tabSet[i-1]++;
			testInitSet(i-1);
			this.tabSet[i] = this.tabSet[i-1]+1;
			testInitSet(i);
		}
	}
	
	//retourne toute les valeurs d'une colonne
	private double[] initValSet() {
		double[] valSet = new double[super.g.getDim()];
		if (this.colonne.size() == 1)		//premi�re colonne
			for (int i=0; i< super.g.getDim(); i++)
				valSet[i] = super.g.calculDist(i, 0);
		else{
			for (int i=0; i<super.g.getDim(); i++){
				if (!this.colonne.contains(i))
					valSet[i] = chercheMeilleur(i);
				else valSet[i] = 0;
			}
		}
		return valSet;
	}

	//retourne la distance la plus petite de tous les set de taille (m-1)
	private double chercheMeilleur(int a) {
		double best = -1, tmp = 0;
		TreeSet<Integer> subset = new TreeSet<Integer>();
		subset.addAll(this.colonne);
		for(int e : this.colonne){
			if (e!=0){
				subset.remove(e);				//subset = set - {e}
				tmp = this.map.get(subset)[e] + super.g.calculDist(e, a);
				if (tmp < best || best == -1)
					best = tmp;
				subset.add(e);
			}
		}
		return best;
	}
	
	//permet de trouver le parcours une fois la map g�n�r�e
	private void trouveParcours (TreeSet<Integer> set, int params){
		double best = -1;	//meilleur distance de tous les subSet
		double tmp;	
		int elem = 0;
		TreeSet<Integer> bestSet = null;
		TreeSet<Integer> subSet = new TreeSet<Integer>();
		subSet.addAll(set);
		for (int e : set){
			if (e != 0){
				subSet.remove(e);	//subset - {e}
				tmp = this.map.get(subSet)[e] + super.g.calculDist(e, params);
				if (tmp < best || best == -1){
					best = tmp;
					bestSet = new TreeSet<Integer>();
					bestSet.addAll(subSet);
					elem = e;
				}
				subSet.add(e);
			}
		}
		super.parcoursMin.add(elem);	//ajout du sommet au parcours
		if (bestSet != null)
			trouveParcours(bestSet, elem);	//appel r�cursif pour trouver le sommet suivant
	}
}