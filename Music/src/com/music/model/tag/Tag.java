package com.music.model.tag;

import java.io.File;

/**
 * Abstract Class that represent tag for a MP3 file
 * @author antho
 */

public abstract class Tag {
	
	final String TAB_GENRE[] = {										//array containing all the predefined kinds
			 "Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge","Hip-Hop", "Jazz","Metal", "New Age",
			 "Oldies","Other","Pop","R&B","Rap","Reggae","Rock","Techno","Industrial","Alternative","Ska","Death Metal",
			 "Pranks","Soundtrack","Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical",
			 "Instrumental","Acid","House","Game","Sound Clip","Gospel","Noise","AlternRock","Bass","Soul","Punk",
			 "Space","Meditative","Instrum. Pop","Instrum. Rock","Ethnic","Gothic","Darkwave","Techno-Industrial",
			 "Electronic","Pop-Folk","Eurodance","Dream","Southern Rock","Comedy","Cult","Gangsta","Top",
			 "Christian Rap","Pop/Funk","Jungle","Native American","Cabaret","New Wave","Psychadelic","Rave",
			 "Showtunes","Trailer","Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical","Rock & Roll",
			 "Hard Rock","Folk","Folk-Rock","National Folk","Swing","Fast Fusion","Bebob","Latin","Revival","Celtic",
			 "Bluegrass","Avantgarde","Gothic Rock","Prog. Rock","Psychedel. Rock","Symph. Rock","Slow Rock",
			 "Big Band","Chorus","Easy Listening","Acoustic","Humour","Speech","Chanson","Opera","Chamber Music",
			 "Sonata","Symphony","Booty Bass","Primus","Porn Groove","Satire","Slow Jam","Club","Tango","Samba",
			 "Folklore","Ballad","Power Ballad","Rhythmic Soul","Freestyle","Duet","Punk Rock","Drum Solo",
			 "Acapella","Euro-House","Dance Hall", "Unknow"
	};

	/*
	 * METHODS
	 */
	
	/**
	 * Abstract method that permit to read tag of a file
	 * @param file of the mp3
	 * @return true if a tag has been reading, else return false
	 */
	public abstract boolean readTag(File file);
	
	/**
	 * Abstract method that permit to read tag of a file
	 * @param file of the mp3
	 * @return true if the tag has been written, else return false
	 */
	public abstract boolean writeTag(File file);

	/*
	 * GETTER SETTER
	 */
	public abstract String getTrack();
	public abstract void setTrack(String track);
	
	public abstract String getArtist();
	public abstract void setArtist(String artist);
	
	public abstract String getAlbum();
	public abstract void setAlbum(String album);
	
	public abstract String getYear();
	public abstract void setYear(String year);
	
	public abstract String getComment();
	public abstract void setComment(String comment);
	
	public abstract String getGenre();
	public abstract void setGenre(String genre);
		
	public abstract String getNum();
	public abstract void setNum(String num);
}
