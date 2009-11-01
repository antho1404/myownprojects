package com.music.controller;

import com.music.model.Model;

/**
 * Abstract Class that represent a controller for the MVC (model, view, controller)
 * @author antho
 */

public abstract class AbstractController {
	
	protected Model model;	//model

	/**
	 * Constructor
	 * @param model
	 */
	public AbstractController(Model model) {
		this.model = model;
	}
	
	/**
	 * Function that permit to search a value in a field
	 * @param search : searching word
	 * @param opt : field where we want to search
	 */
	public abstract void search(String s, String opt);
}
