package com.music.observer;

import com.music.model.Track;

/**
 * Interface that implement the view and permit to connect the view and the model
 * @author antho
 */

public interface Observer {
	
	/**
	 * @param s
	 */
	public void update(Track t);
}
