package com.music.model.tag;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

/**
 * Class that represent ID3tagV1.0
 * @author antho
 */

public class tagv1_0 extends ID3tagV1{

	/*
	 * UNIMPLEMENTED METHODS OF TAG
	 */
	
	/*
	 * @see com.music.model.tag.Tag#readTag(java.io.File)
	 */
	@Override
	public boolean readTag(File file) {
		if (file.exists()) {
			// get the extension of the file
			RandomAccessFile f = null;
			try {
				f = new RandomAccessFile(file, "r");
				// get the size of the file
				super.size = file.length();
				if (super.size < 128) {
					f.close();
					return false;
				}
				f.seek(super.size - 128);
				byte[] tagID = new byte[3];
				byte[] track = new byte[30];
				byte[] artist = new byte[30];
				byte[] album = new byte[30];
				byte[] year = new byte[4];
				byte[] comment = new byte[30];
				byte[] genre = new byte[1];

				// check if the file contain a tag
				f.readFully(tagID);
				if (!(new String(tagID)).equals("TAG")) {
					f.close();
					return false;
				}

				// read track
				f.readFully(track);
				super.track = new String(track).trim();

				// read artist
				f.readFully(artist);
				super.artist = new String(artist).trim();

				// read album
				f.readFully(album);
				super.album = new String(album).trim();

				// read year
				f.readFully(year);
				super.year = new String(year).trim();

				// read comment
				f.readFully(comment);
				super.comment = new String(comment).trim();

				// read genre of the track
				f.readFully(genre);
				super.genre = ((int) genre[0] < super.TAB_GENRE.length && (int) genre[0] >= 0) ? super.TAB_GENRE[(int) genre[0]]
						: super.TAB_GENRE[super.TAB_GENRE.length - 1];
			} catch (FileNotFoundException e) {e.printStackTrace();} 
			catch (IOException e) {e.printStackTrace();}
			finally {
				try {f.close();return true;} 
				catch (IOException e) {e.printStackTrace();}
			}
		}
		return false;
	}

	/*
	 * @see com.music.model.tag.Tag#writeTag(java.io.File)
	 */
	@Override
	public boolean writeTag(File file) {
		if (file.exists()) {
			RandomAccessFile f = null;
			try {
				f = new RandomAccessFile(file, "rw");
				f.seek(f.length() - 128);

				// write tag balise
				f.writeBytes("TAG");

				// write track name
				StringBuffer track = (super.track != null) ? new StringBuffer(
						super.track) : new StringBuffer();
				track.setLength(30);
				f.writeBytes(track.toString());

				// write artist
				StringBuffer artist = (super.artist != null) ? new StringBuffer(
						super.artist) : new StringBuffer();
				artist.setLength(30);
				f.writeBytes(artist.toString());

				// write album
				StringBuffer album = (super.album != null) ? new StringBuffer(
						super.album) : new StringBuffer();
				album.setLength(30);
				f.writeBytes(album.toString());

				// write year
				StringBuffer year = (super.year != null) ? new StringBuffer(
						super.year) : new StringBuffer();
				year.setLength(4);
				f.writeBytes(year.toString());

				// write comment
				StringBuffer comment = (super.comment != null) ? new StringBuffer(
						super.comment)
						: new StringBuffer();
				comment.setLength(30);
				f.writeBytes(comment.toString());

				// write comment
				int i = 0;
				boolean find = false;
				while (i < 255 && !find)
					if (super.TAB_GENRE[i].equals(super.genre))
						find = true;
					else
						i++;
				f.writeByte(i);

				f.close();
				return true;

			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return false;
	}

	/*
	 * @see com.music.model.tag.Tag#getAlbum()
	 */
	@Override
	public String getAlbum() {
		return super.album;
	}

	/*
	 * @see com.music.model.tag.Tag#getArtist()
	 */
	@Override
	public String getArtist() {
		return super.artist;
	}

	/*
	 * @see com.music.model.tag.Tag#getComment()
	 */
	@Override
	public String getComment() {
		return super.comment;
	}

	/*
	 * @see com.music.model.tag.Tag#getGenre()
	 */
	@Override
	public String getGenre() {
		return super.genre;
	}

	/*
	 * @see com.music.model.tag.Tag#getNum()
	 */
	@Override
	public String getNum() {
		return "0";
	}

	/*
	 * @see com.music.model.tag.Tag#getTrack()
	 */
	@Override
	public String getTrack() {
		return super.track;
	}

	/*
	 * @see com.music.model.tag.Tag#getYear()
	 */
	@Override
	public String getYear() {
		return super.year;
	}

	/*
	 * @see com.music.model.tag.Tag#setAlbum(java.lang.String)
	 */
	@Override
	public void setAlbum(String album) {
		super.album = album;
	}

	/*
	 * @see com.music.model.tag.Tag#setArtist(java.lang.String)
	 */
	@Override
	public void setArtist(String artist) {
		super.artist = artist;
	}

	/*
	 * @see com.music.model.tag.Tag#setComment(java.lang.String)
	 */
	@Override
	public void setComment(String comment) {
		super.comment = comment;
	}

	/*
	 * @see com.music.model.tag.Tag#setGenre(java.lang.String)
	 */
	@Override
	public void setGenre(String genre) {
		super.genre = genre;
	}

	/*
	 * @see com.music.model.tag.Tag#setNum(java.lang.String)
	 */
	@Override
	public void setNum(String num) {
	}

	/*
	 * @see com.music.model.tag.Tag#setTrack(java.lang.String)
	 */
	@Override
	public void setTrack(String track) {
		super.track = track;
	}

	/*
	 * @see com.music.model.tag.Tag#setYear(java.lang.String)
	 */
	@Override
	public void setYear(String year) {
		super.year = year;
	}
}
