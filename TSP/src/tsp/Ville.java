package tsp;

import java.awt.Graphics;
import java.util.Random;

	/**
	 * Classe permettant de cr�er un objet Ville contenant ses coordonn�es
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class Ville {
	
	private String nom;	//nom de la ville
	private double x;	//coordonn�e de la ville sur les x
	private double y;	//coordonn�e de la ville sur les y
	
	/**
	 * Constructor
	 * @param x : coordonn�e sur les x
	 * @param y : coordonn�e sur les y
	 */
	public Ville(String nom){
		this.nom = nom;
		Random rdm = new Random ();
		this.x = rdm.nextFloat();
		this.y = rdm.nextFloat();	
	}
	
	public Ville(double x, double y, String nom){
		this.nom = nom;
		this.x = x;
		this.y = y;
	}
	
	/**
	 * Methods
	 */
	//calcul de la distance entre 2 villes
	public double distance(Ville A, Ville B){	
		return Math.sqrt(((A.getX()-B.getX())*(A.getX()-B.getX()))+((A.getY()-B.getY())*(A.getY()-B.getY())));
	}
	
	/**
	 * Getter
	 */
	
	//retourne la valeur de X de la ville
	public double getX(){
		return this.x;
	}
	
	//retourne la valeur de Y de la ville
	public double getY(){
		return this.y;
	}
	
	//permet de dessiner les villes
	public void dessinVille (Graphics g, int dim, int i){
		g.fillOval((int)(this.x*dim)-2, (int)(dim-(this.y*dim)-2), 4, 4);
		if (this.nom == "")
			g.drawString(String.valueOf(i), (int)(this.x*dim)+2, (int)(dim-(this.y*dim))+2);
		else
			g.drawString(this.nom, (int)(this.x*dim)+2, (int)(dim-(this.y*dim))+2);
	}
}
