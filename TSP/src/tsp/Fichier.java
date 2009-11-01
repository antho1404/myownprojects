package tsp;

	/**
	 * Classe permettant de g�rer l'exportation et l'importation de fichier xml et 
	 * de capture d'�cran du parcours
	 * @author Dejean Quentin, Estebe Anthony
	 */

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import com.thoughtworks.xstream.XStream;

public class Fichier {
 
    private static XStream xStream = new XStream();	//objet permettant de g�rer les xml grace � la librairie xstream
    private String dir;								//chemin du fichier � enregistrer ou importer
 
    //permet de choisir le fichier de destination
    private void choixFile (String opt){
    	JFileChooser save = new JFileChooser();
    	if (opt == "save")
    		save.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		if (save.showSaveDialog(null) == JFileChooser.APPROVE_OPTION)
			this.dir = save.getSelectedFile().getPath();
    }
    
    //permet de sauvegarder un fichier xml contenant les villes et une capture d'�cran du parcours
    public void save(MethodesResolution choix){
    	choixFile("save");
        BufferedWriter writer = null;
		try {
			writer = new BufferedWriter(new FileWriter(this.dir.concat("\\Villes.xml"), false));
		} catch (IOException e) {}
        Fichier.xStream.toXML(Graphe.listeVille, writer);
        saveGraphe(choix);
    }
   
    //permet de sauvegarder la capture d'�cran du parcours
    private void saveGraphe (MethodesResolution choix){
    	if (choix != null){
			BufferedImage image = new BufferedImage(480, 480, BufferedImage.TYPE_INT_RGB);
			Graphics2D g2 = image.createGraphics();
			g2.setBackground(Color.green);
			choix.g.dessineVilles(g2, 480);
			choix.dessineParcours(g2, 480);
			try {
				ImageIO.write(image, "png", new File(this.dir.concat("\\Graphe"+choix.getClass().getCanonicalName()+".png")));
			} catch (Exception e) {}
    	}
	}

    //permet de charger le contenu des villes contenue dans un xml
    @SuppressWarnings("unchecked")
	public void load() {
    	choixFile("load");
        BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(this.dir));
		} catch (FileNotFoundException e) {}
        Graphe.listeVille = (ArrayList<Ville>) Fichier.xStream.fromXML(reader);
    }
}
