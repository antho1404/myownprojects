package com.music.model;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

import com.music.model.tag.Tag;
import com.music.model.tag.tagv1_0;
import com.music.model.tag.tagv1_1;

/**
 * Class for MP3 files
 * @author antho
 */

public class MP3 extends Track{
	
	private String tagVersion;	//Version of the tag
	
	/**
	 * Constructor
	 * @param dir : directory of the file
	 */
	public MP3(String dir) {
		super(dir, "mp3");
		importTags(dir);
	}
	
	/*
	 * METHODS
	 */
	
	/**
	 * Function that permit to know the version of the mp3tag 
	 * @param file : directory of the file
	 * @return the version of id3tag of the file, if the file have no tag, return an empty string
	 */
	public String getID3Version(File file) {
		RandomAccessFile input = null;
		String result = "";
		try {
			input = new RandomAccessFile(file, "r");
//			if (input.read() == 'I' && input.read() == 'D' && input.read() == '3')
//				result = "ID3v2.".concat(String.valueOf(input.read()));
//			else 
				if (input.length() >= 128) {
					input.seek(input.length() - 128);
					if (input.readUnsignedByte() == 'T' && input.readUnsignedByte() == 'A' && input.readUnsignedByte() == 'G') {
						input.seek(input.length() - 3);
						if(input.readUnsignedByte() == 0)
							result = (input.readUnsignedByte() == 0) ? "ID3v1.0" : "ID3v1.1";					
					}
				}
		} catch (FileNotFoundException e) {e.printStackTrace();}
		catch (IOException e){e.printStackTrace();}
		finally {
			try {input.close();} 
			catch (IOException e) {e.printStackTrace();}
		}
		return result;
	}

	/**
	 * function that permit to load all of the tag of the file
	 * @param dir : directory of the file
	 */
	private void importTags(String dir){
		this.tagVersion = getID3Version(new File(dir));
		Tag tag = null;
		if(this.tagVersion.equals("ID3v1.0"))
			tag = new tagv1_0();
		if(this.tagVersion.equals("ID3v1.1"))
			tag = new tagv1_1();
		if(tag != null)
			if(tag.readTag(new File(super.getTrackDirectory()))){
				super.setAlbumDate(tag.getYear());
				super.setAlbumName(tag.getAlbum());
				super.setArtistName(tag.getArtist());
				super.setTrackGenre(tag.getGenre());
				super.setTrackName(tag.getTrack());
				super.setTrackNumber(Integer.valueOf(tag.getNum()));
			}
	}
}
