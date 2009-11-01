package com.music.model;


/**
 * Class allowing the creation of an object artist It inherits from an artist
 * 
 * @author antho
 */
public class Album extends Artist {

	private String albumName;
	private String albumDate;

	/**
	 * Constructor
	 */
	protected Album(){
		super();
		this.albumDate = Data.unknow;
		this.albumName = Data.unknow;
	}
	
	/**
	 * Constructor
	 * @param album : album name
	 * @param date : album's date
	 * @param artist : artist of the album
	 */
	protected Album(String album, String date, String artist) {
		super(artist);
		this.albumName = album;
		this.albumDate = date;
	}

	/*
	 * METHODS
	 */
	
	/**
	 * Function that test if the string s is contained in the field album's name
	 * @param s : string we want to know if it is in the album's name field
	 * @return true if the album name contains s, else return false
	 */
	protected boolean existAlbum(String s){
		return this.albumName.matches("^.*(?i)"+s+".*$");
	}
	
	/*
	 * GETTERS SETTERS
	 */
	public String getAlbumName() {
		return albumName;
	}

	public void setAlbumName(String albumName) {
		this.albumName = albumName;
	}

	public String getAlbumDate() {
		return albumDate;
	}

	public void setAlbumDate(String albumDate) {
		this.albumDate = albumDate;
	}

	// //////////////////////////////////////////////////////////////////////////////////////
	// ////// AFFICHAGE ////////
	// //////////////////////////////////////////////////////////////////////////////////////

	public String toString() {
		return super.toString()+"Album : "+this.albumName+" "+this.albumDate+"\n";
	}
}
