package com.music.model;

import java.io.File;

/**
 * Abstract Class that represent a track
 * 
 * @author antho
 */

public abstract class Track extends Album implements Data {

	private String trackDirectory; // directory of the file
	private long trackSize; // size of the file
	private int trackNumber; // number of the track
	private String trackName; // name of the track
	private int trackTime; // time of the track
	private String trackGenre; // kind of the track
	private String trackExtention; // extension of the file
	private int playedTime;			//number of played time
	private int bitrate;			//bitrate of the track		
	private int grade;			//grade of the track
	

	/**
	 * Constructor
	 * 
	 * @param dir
	 *            : directory of the track file
	 * @param ext
	 *            : extension of the track
	 */
	public Track(String dir, String ext) {
		super();
		File f = new File(dir);
		this.trackDirectory = dir;
		this.trackSize = f.length();
		this.trackExtention = ext;
		this.trackNumber = 0;
		this.trackName = Data.unknow;
		this.trackGenre = Data.unknow;
		this.trackTime = 0;
		this.playedTime = 0;
		this.bitrate = 0;
		this.grade = 0;
	}

	/*
	 * METHODS
	 */

	/**
	 * Function that permit to know if this object contain a searched value
	 * 
	 * @param s
	 *            : searching word
	 * @param opt
	 *            : field where we want to search
	 * @return true if the value of s is in the field of opt, else return false
	 */
	public boolean contains(String s, String opt) {
		s = s.toLowerCase();
		if (opt.equals(Data.trackValue))
			return this.trackName.matches("^.*(?i)" + s + ".*$");
		else if (opt.equals(Data.albumValue))
			return existAlbum(s);
		else if (opt.equals(Data.artistValue))
			return existArtist(s);
		else if (opt.equals(Data.kindValue))
			return this.trackGenre.matches("^.*(?i)" + s + ".*$");
		else
			return this.trackGenre.matches("^.*(?i)" + s + ".*$")
					|| this.trackName.matches("^.*(?i)" + s + ".*$")
					|| existAlbum(s) || existArtist(s);
	}

	/*
	 * GETTER SETTER
	 */
	
	//SETTER
	
	public void setTrackNumber(int trackNumber) {
		this.trackNumber = trackNumber;
	}

	public void setTrackName(String trackName) {
		this.trackName = trackName;
	}

	public void setTrackTime(int trackTime) {
		this.trackTime = trackTime;
	}

	public void setTrackGenre(String trackGenre) {
		this.trackGenre = trackGenre;
	}

	public void setTrackDirectory(String trackDirectory) {
		this.trackDirectory = trackDirectory;
	}

	public void setTrackSize(long trackSize) {
		this.trackSize = trackSize;
	}

	public void setTrackExtention(String trackExtention) {
		this.trackExtention = trackExtention;
	}
	
	public void setPlayedTime(int playedTime) {
		this.playedTime = playedTime;
	}
	
	public void setBitrate(int bitrate) {
		this.bitrate = bitrate;
	}
	
	public void setGrade(int grade) {
		this.grade = grade;
	}
	
	//GETTERS

	public String getTrackDirectory() {
		return trackDirectory;
	}

	public long getTrackSize() {
		return trackSize;
	}

	public int getTrackNumber() {
		return trackNumber;
	}

	public String getTrackName() {
		return trackName;
	}

	public int getTrackTime() {
		return trackTime;
	}

	public String getTrackGenre() {
		return trackGenre;
	}

	public String getTrackExtention() {
		return trackExtention;
	}
	
	public int getPlayedTime() {
		return playedTime;
	}
	
	public int getBitrate() {
		return bitrate;
	}
	
	public int getGrade() {
		return grade;
	}
	
	/*
	 * UNIMPLEMENTED METHODS
	 */
	
	/**
	 * @return the value of this object in string
	 */
	@Override
	public String toString() {
		return super.toString() + "Track : " + this.trackNumber + " "
				+ this.trackName + " " + this.trackGenre;
	}
}
