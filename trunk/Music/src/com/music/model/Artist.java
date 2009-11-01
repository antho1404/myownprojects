package com.music.model;

/**
 * Class allowing the creation of an object artist
 * @author antho
 */

public class Artist {

	private String artistName;	//Artist name

	/**
	 * Constructor
	 */
	protected Artist(){
		this.artistName = Data.unknow;
	}
	
	/**
	 * @param artist : artist's name
	 */
	protected Artist(String artist) {
		this.artistName = artist;
	}

	/*
	 * METHODS
	 */
	
	/**
	 * Function that test if the string s is contained in the field album's name
	 * @param s : string we want to know if it is in the artist's name field
	 * @return true if the artist name contains s, else return false

	 */
	protected boolean existArtist(String s){
		return this.artistName.matches("^.*(?i)"+s+".*$");
	}

	/*
	 * GETTER SETTER
	 */
	
	public void setArtistName(String s) {
		this.artistName = s;
	}
	
	public String getArtistName() {
		return this.artistName;
	}
	
	

	/*
	 * UNIMPLEMENTED METHODS
	 */
	
	/*
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Artist : "+this.artistName+"\n";
	}
}
