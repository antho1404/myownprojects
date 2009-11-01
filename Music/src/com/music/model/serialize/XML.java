package com.music.model.serialize;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import com.thoughtworks.xstream.XStream;

/**
 * Class that permit to serialize in XML
 * @author antho
 */

public class XML implements Serialize{

	static XStream xstream = new XStream(); //Object that permit to serialize in xml
	
	/*
	 * @see com.music.model.serialize.Serialize#exportObj(java.lang.Object, java.lang.String)
	 */
	@Override
	public void exportObj(Object obj, String dir) {
		BufferedWriter writer = null;
		try {
			writer = new BufferedWriter(new FileWriter(dir, false));
			xstream.toXML(obj, writer);
		} catch (IOException e) {
			System.err.println("Problème d'écriture sur le fichier : "+ dir);
		}
	}
	
	/*
	 * @see com.music.model.serialize.Serialize#importObj(java.lang.String)
	 */
	@Override
	public Object importObj(String dir) {
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(dir));
		} catch (FileNotFoundException e) {
			System.err.println("Impossible de charger le fichier : "+ dir);
		}
		return xstream.fromXML(reader);
	}
}
