package com.music.controller;

import com.music.model.Model;

/**
 * Controller that permit to connect view and model (MCV)
 * @author antho
 */

public class Controller extends AbstractController{

	/**
	 * Constructor
	 * @param model
	 */
	public Controller(Model model) {
		super(model);
	}

	/*
	 * @see com.music.controller.AbstractController#search(java.lang.String, java.lang.String)
	 */
	@Override
	public void search(String s, String opt) {
		super.model.search(s, opt);
	}
}
