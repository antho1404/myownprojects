package com.music.observer;

import com.music.model.Track;

/**
 * Interface that implement the model and permit to connect the view and the model
 * @author antho
 */

public interface Observable {
	
	/**
	 * Add an observer to the model, with that, the model will be observable by a lot of view
	 * @param obs : the view witch observe
	 */
	public void addObserver(Observer obs);
	
	/**
	 * Remove all observers
	 */
	public void removeObserver();
	
	/**
	 * Send an info at all observers
	 * @param str
	 */
	public void notifyObserver(Track t);
}
