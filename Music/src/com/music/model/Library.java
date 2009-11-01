package com.music.model;

import java.io.File;
import java.util.ArrayList;

import javax.swing.JOptionPane;

import com.music.model.serialize.Serialize;
import com.music.model.serialize.XML;

/**
 * Class that contain all the track and permit operation of this track list
 * @author antho
 */

public class Library extends Model implements Data{

	private ArrayList<Track> trackList = new ArrayList<Track>();	//list of tracks
	private Serialize serialize;									//object that permit to serialize the track list
	
	/**
	 * Constructor
	 */
	@SuppressWarnings("unchecked")
	public Library(){
		serialize = new XML();
		File lib = new File(Data.dirLib);
		//if the library has already been serialized
		if (lib.exists() && lib.length() != 0) {
			System.out.println("chargement lib");
			this.trackList = (ArrayList<Track>) serialize.importObj(Data.dirLib);
			System.out.println("lib chargée");
		}
		//if the library doesn't exist
		else {
			this.trackList = new ArrayList<Track>();
			int rep = JOptionPane.showConfirmDialog(null,
					"Librairie vide \ncharger nouvelle librairie à partir de : \n"
							+ Data.dirMusic + " ?", "Chargement de librairie",
					JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE);
			if (rep == 0) {
				// Files.fileChooser("write");
				listDirectory(Data.dirMusic);
				serialize.exportObj(this.trackList, Data.dirLib);
			}
		}
//		for (Track t : this.trackList)
//			System.out.println(t.toString());
	}
	
	/*
	 * METHODS
	 */
	/**
	 * Scan all of sub directory of node and add new tracks to the list
	 * @param dir : directory that we want to scan
	 */
	private void listDirectory(String node) {
		File f = new File(node);
		File[] child = f.listFiles();
		String s, dest;
		for (int i = 0; i < child.length; i++){
			s = child[i].getName();
			dest = node.concat("/").concat(s);
			if (child[i].isFile()){// && !child[i].getName().startsWith(".")) {
				if(s.matches("^.*(?i)mp3$"))
					this.trackList.add(new MP3(dest));
				if(s.matches("^.*(?i)wma$"))
					this.trackList.add(new WMA(dest));
			} else 
				if (child[i].isDirectory())
					listDirectory(dest);
		}
	}

	/**
	 * 
	 */
	public void showLibrary() {
		for (Track t : this.trackList)
			notifyObserver(t);
//			System.out.println(t.toString());
	}

	/*
	 * UNIMPLEMENTED METHODS OF ABSTRACTMODEL
	 */
	
	/*
	 * @see com.music.model.Model#search(String search, String opt)
	 */
	@Override
	public void search(String s, String opt) {
		for (Track t : this.trackList){
//			System.out.println(t.toString());
			if (t.contains(s, opt))
				notifyObserver(t);
		}
	}

}
