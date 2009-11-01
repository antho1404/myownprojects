package tsp;

import java.awt.Graphics;
import java.util.ArrayList;

	/**
	 * Classe d'algorithme g�n�ral qui permet de d�finir des m�thodes et des donn�es 
	 * communes � tous les algorythmes de recherche
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class MethodesResolution {

	protected Graphe g;							//graphe contenant les villes
	public double dist;							//distance du parcours
	public ArrayList<Integer> parcoursMin;		//parcours minimum trouv�
	public double time;							//temps d'execution de l'algorithme de recherche
	
	/**
	 * Constructor
	 * @param g : graphe contenant les villes
	 */
	public MethodesResolution(Graphe g){
		this.g = g;
		this.dist = -1;
		this.parcoursMin = new ArrayList<Integer>();
		this.time = 0;
	}
	
	/**
	 * Methods
	 */
	
	//retourne la copie d'une liste dans un nouvel espace m�moire
	protected ArrayList<Integer> copieListe (ArrayList<Integer> list){
		ArrayList<Integer> copie = new ArrayList<Integer>();
		for (int ind : list){
			copie.add(ind);
		}
		return copie;
	}
	
	//m�thode permettant l'affichage console du parcours, de la distance et du temp d'execution de celui ci
	protected void affiche(){
		System.out.println(this.getClass().getName()+"   => "+parcoursMin);
		System.out.println(this.getClass().getName()+"   => "+"dist : "+dist);
		System.out.println(this.getClass().getName()+"   => "+"temp : "+(time/1000)+" s");
		System.out.println();
	}
	
	//dessine le parcours sur un graphique
	protected void dessineParcours (Graphics g, int dim){
		Ville v1 = null;
		Ville v2 = null;
		try{
			for (int i=0; i<Graphe.listeVille.size()-1; i++){
				v1 = Graphe.listeVille.get(this.parcoursMin.get(i));
				v2 = Graphe.listeVille.get(this.parcoursMin.get(i+1));
				g.drawLine((int)(v1.getX()*dim), (int)(dim - (v1.getY()*dim)), 
						(int)(v2.getX()*dim), (int)(dim - (v2.getY()*dim)));
			}
			g.drawLine((int)(v2.getX()*dim), (int)(dim-(v2.getY()*dim)), 
					(int)(Graphe.listeVille.get(0).getX()*dim), (int)(dim-(Graphe.listeVille.get(0).getY()*dim)));
		}catch(IndexOutOfBoundsException e){}
	}
}
