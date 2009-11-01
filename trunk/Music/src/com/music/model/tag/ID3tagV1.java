package com.music.model.tag;

/**
 * Abstract Class that represent id3tagV1
 * @author antho
 */

public abstract class ID3tagV1 extends Tag{
	
	protected long size;		//size of the file
	protected String track;		//name of the track
	protected String artist;	//artist of the track
	protected String album;		//album of the track
	protected String year;		//year of the album
	protected String comment;	//comments on the track
	protected String genre;		//kind of the music
}
