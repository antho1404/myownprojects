package com.music.view;

import java.awt.BorderLayout;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.DefaultListModel;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.music.controller.AbstractController;
import com.music.model.Data;
import com.music.model.Track;
import com.music.observer.Observer;

@SuppressWarnings("serial")
public class IHM extends JFrame implements Observer, Data{
	
	private AbstractController controler;
	
	private String[] optSearch = new String[]{Data.allValue, Data.artistValue, Data.albumValue, Data.trackValue, Data.kindValue};
	private DefaultListModel dlmArtist;
	private DefaultListModel dlmAlbum;
	private DefaultListModel dlmTrack;
	
	//Components
	private JTextField inputSearch;
	private JList listAlbum;
	private JList listArtist;
	private JList listTrack;
	private JComboBox cbSearch;

	//Actions
	private ActionSearch action;
	
	public IHM(AbstractController ctrl) {
		super();

		this.controler = ctrl;
		this.action = new ActionSearch();
		
		this.inputSearch = new JTextField(12);
		this.inputSearch.getDocument().addDocumentListener(this.action);
		
		this.cbSearch = new JComboBox(this.optSearch);
		this.cbSearch.addItemListener(this.action);
		
		JPanel pan = new JPanel();pan.add(new JLabel("Rechercher :"));pan.add(inputSearch);pan.add(cbSearch);
		
		this.dlmArtist = new DefaultListModel();
		this.listArtist = new JList(this.dlmArtist);
		this.dlmAlbum = new DefaultListModel();
		this.listAlbum = new JList(this.dlmAlbum);
		this.dlmTrack = new DefaultListModel();
		this.listTrack = new JList(this.dlmTrack);
		this.listAlbum.setAutoscrolls(true);
		this.listArtist.setAutoscrolls(true);
		this.listTrack.setAutoscrolls(true);

		JPanel pan2 = new JPanel();
		pan2.add(listArtist);
		pan2.add(listAlbum);

		listAlbum.setVisible(true);
		listArtist.setVisible(true);
//		listTrack.setVisible(true);
		
		super.setLayout(new BorderLayout());
		super.add(pan, BorderLayout.NORTH);
		super.add(pan2, BorderLayout.CENTER);
		super.add(listTrack, BorderLayout.SOUTH);
		
		super.setDefaultCloseOperation(EXIT_ON_CLOSE);
		super.setSize(800, 640);
		super.setVisible(true);
	}

	public class ActionSearch implements DocumentListener, ItemListener{
		
		private void launchSearch(){
			dlmArtist.removeAllElements(); //OU dlm = new DefaultListModel();
			dlmAlbum.removeAllElements(); //OU dlm = new DefaultListModel();
			dlmTrack.removeAllElements(); //OU dlm = new DefaultListModel();
			controler.search(inputSearch.getText(), cbSearch.getSelectedItem().toString());
		}
		
		@Override
		public void changedUpdate(DocumentEvent e) {}
		@Override
		public void insertUpdate(DocumentEvent e) {
			launchSearch();
		}
		@Override
		public void removeUpdate(DocumentEvent e) {
			launchSearch();
		}
		@Override
		public void itemStateChanged(ItemEvent e) {
			launchSearch();
		}
	}

	@Override
	public void update(Track t) {
		dlmAlbum.addElement(t.getAlbumName());
		dlmArtist.addElement(t.getArtistName());
		dlmTrack.addElement(t.getTrackNumber()+" "+t.getTrackName()+" "+t.getTrackGenre()+" "+t.getGrade());
	}
}
