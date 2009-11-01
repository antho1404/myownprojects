package com.music.model.serialize;

/**
 * Interface that permit to serialize an object
 * @author antho
 */

public interface Serialize {

	/**
	 * Serialize an object
	 * @param obj : Object that we want to serialize
	 * @param dir : directory of the file that contains the serialized file
	 */
	public void exportObj(Object obj, String dir);
	
	/**
	 * Unserialize an object
	 * @param dir : directory of the file
	 * @return an object of the file unserialized
	 */
	public Object importObj(String dir);
}
