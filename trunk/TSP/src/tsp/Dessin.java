package tsp;

	/**
	 * Classe permettant de dessiner les villes, le parcours, et de g�rer les �venements souris
	 * @author Dejean Quentin, Estebe Anthony
	 */

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Dessin extends JPanel implements MouseListener, MouseMotionListener{
		
	private boolean carte = false;
	private final int dim = 480;	//taille du cadre
	private Fenetre fen;			//fenetre contenant le cadre
	
	public Dessin(Fenetre fen){
		this.fen = fen;
	}
	
	public void setCarte (boolean bool){
		this.carte = bool;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		if (this.carte){
			BufferedImage fond = null;
			try {
				fond = ImageIO.read(new File("img/france.png"));
			} catch (IOException e) {}
			g.drawImage(fond, 0, 0, null);
		}
		
		//�couteurs souris
		this.fen.graphique.getContentPane().addMouseListener(this);
		this.fen.graphique.getContentPane().addMouseMotionListener(this);
		
		g.setColor(Color.gray);
		for (int i=0; i<11;i++){	//Dessin de la grille
			g.drawLine(0, ((i*this.dim)/10), this.dim, ((i*this.dim)/10));
			g.drawLine(((i*this.dim)/10), 0, ((i*this.dim)/10), this.dim);
		}
		//Dessin des villes
		g.setColor(Color.red);
		this.fen.graphe.dessineVilles(g, this.dim);
		//Dessin du parcours
		g.setColor(Color.black);
		if (this.fen.choix != null){
			this.fen.choix.dessineParcours(g, this.dim);
			this.fen.graphique.setTitle("Graphique     ==> "+this.fen.choix.getClass().getCanonicalName()+" sur "+this.fen.graphe.getDim()+" villes");
			this.fen.textResult1.setText(String.valueOf(this.fen.choix.dist*Integer.valueOf(this.fen.echelle.getText())).substring(0,8).concat(" "+this.fen.dimEchelle.getSelectedItem()));
			this.fen.textResult2.setText(String.valueOf(this.fen.choix.time/1000).concat(" s"));
			repaint();
		}
	}

	//Ecouteur de pression du clic de la souris
	public void mousePressed(MouseEvent e) {
		double x = (double)e.getX()/dim;
		double y = (dim-(double)e.getY())/dim;
		try{
			if((Graphe.listeVille.size()<1) || (Graphe.listeVille.get(Graphe.listeVille.size()-1).getX() != x 
					&& Graphe.listeVille.get(Graphe.listeVille.size()-1).getY() != y)){
				Graphe.listeVille.add(new Ville(x,y,""));
				fen.spinnerV.setValue(Graphe.listeVille.size());
				fen.slider.setValue(fen.slider.getValue()+1);
				repaint();
			}
		}
		catch (IndexOutOfBoundsException e1){}
	}	
	//Ecouteur de mouvement de souris
	public void mouseMoved(MouseEvent e) {
		int echelle = Integer.parseInt(this.fen.echelle.getText());
		setToolTipText("x="+((float)e.getX()/480)*echelle+"   "+"y="+((float)e.getY()/480)*echelle);		
	}
	public void mouseClicked(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
	public void mouseDragged(MouseEvent e) {}
}