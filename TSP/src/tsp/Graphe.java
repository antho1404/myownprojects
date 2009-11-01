package tsp;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

	/**
	 * Classe permettant de cr�er un objet Graphe contenant les villes
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class Graphe {

		public static ArrayList<Ville> listeVille;		//tableau contenant des objet Ville
		public static double[][] distPoints;			//tableau contenant les distances entre les villes
		private boolean placeMemoire;					//permet d'utiliser soit la m�thode de calcul des distance soit le tableau les contenant.
		
		
		/**Constructor
		 * @param nbVilles : nombre de villes
		 */
		public Graphe (int nbVilles){
			this.placeMemoire = false;
			Graphe.listeVille = new ArrayList<Ville>();
			for (int i=0; i<nbVilles; i++)
				Graphe.listeVille.add(new Ville(String.valueOf(i)));
		}
		
		/**Methods*/
		
		//retourne la distance entre les villes a et b
		public double calculDist (int a, int b){
			if (!this.placeMemoire)
				return Graphe.listeVille.get(a).distance(Graphe.listeVille.get(a), Graphe.listeVille.get(b));
			else 
				return Graphe.distPoints[a][b];		
		}

		/**Getter*/
		
		//retourne le nombre de villes du graphe
		public int getDim(){
			return Graphe.listeVille.size();
		}
		
		/**Setter*/
		
		public void setPlaceMemoire(boolean bool){
			if (bool){
				Graphe.distPoints = new double[getDim()][getDim()];
				for (int i=0; i<getDim(); i++)
					for (int j=0; j<getDim(); j++)
						Graphe.distPoints[i][j] = calculDist(i,j);
			}
			this.placeMemoire = bool;
		}
		
		/**Graphic*/
		
		//dessine les villes sur un graphique
		public void dessineVilles (Graphics g,int dim){
			g.setColor(new Color(235,235,235));
			g.setColor(Color.gray);
			for (int i=0; i<11;i++){	//Dessin de la grille
				g.drawLine(0, ((i*dim)/10), dim, ((i*dim)/10));
				g.drawLine(((i*dim)/10), 0, ((i*dim)/10), dim);
			}
			g.setColor(Color.red);
			for (int i=0; i<Graphe.listeVille.size(); i++)
				Graphe.listeVille.get(i).dessinVille(g, dim, i);
		}
}
