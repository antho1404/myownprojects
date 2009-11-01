package com.music.model;

import java.util.ArrayList;

import com.music.observer.Observable;
import com.music.observer.Observer;

/**
 * Abstract Class used for the MVC (model, view, controller)
 * @author antho
 */

public abstract class Model implements Observable{
	
	private ArrayList<Observer> listObserver = new ArrayList<Observer>();	//list of the observer of this model
	
	/*
	 * METHODS
	 */
	
	/**
	 * Function that permit to search a value in a field
	 * @param search : searching word
	 * @param opt : field where we want to search
	 */
	public abstract void search(String search, String opt);

	
	/*
	 * UNIMPLEMENTED METHODS OF OBSERVABLE
	 */
	
	/*
	 * @see com.music.observer.Observable#addObserver(com.music.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obs) {
		this.listObserver.add(obs);
	}
	/*
	 * @see com.music.observer.Observable#notifyObserver(java.lang.String)
	 */
	@Override
	public void notifyObserver(Track t) {
		for(Observer obs : listObserver)
			obs.update(t);
	}
	/*
	 * @see com.music.observer.Observable#removeObserver()
	 */
	@Override
	public void removeObserver() {
		listObserver = new ArrayList<Observer>();
	}

}
