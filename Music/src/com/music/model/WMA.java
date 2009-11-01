package com.music.model;

/**
 * Class for WMA files
 * @author antho
 */

public class WMA extends Track{

	/**
	 * Constructor
	 * @param dir : directory of the WMA File
	 */
	public WMA(String dir) {
		super(dir, "wma");
	}
}
