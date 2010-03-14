/**
  * @author Estebe Anthony
  */
  
#include "GraphXml.h"
#include "xml/tinyxml.h"
#include "../Graph/GraphMatrix.h"
#include <sstream>
#include <iostream>
#include <dirent.h>

GraphXML::GraphXML() {
	directory = "Graph/";
	ext = ".graph";
}

void GraphXML::exportGraph(Graph *g, string dir) {
	TiXmlDocument doc;

	//Adding header
	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);

	TiXmlElement *elem;

	TiXmlElement *graph = new TiXmlElement("graph");
	graph->SetAttribute("name", g->getName().c_str());

	//Order of the graph
	elem = new TiXmlElement("order");
	ostringstream oss;
	oss << g->getOrder();
	elem->LinkEndChild(new TiXmlText((oss.str()).c_str()));
	graph->LinkEndChild(elem);

	//List of nodes
	TiXmlElement *nodeList = new TiXmlElement("listNode");
	list<string*> *summit = g->getSummits();
	for (list<string*>::iterator it = summit->begin(); it != summit->end(); it++) {
		//Add node
		elem = new TiXmlElement("node");
		elem->SetAttribute("num", ((*it)[_NUMBER]).c_str());
		elem->SetAttribute("tag", ((*it)[_TAG]).c_str());
		elem->SetAttribute("state", ((*it)[_STATE]).c_str());
		nodeList->LinkEndChild(elem);
	}
	graph->LinkEndChild(nodeList);

	//List of edges
	TiXmlElement *edgeList = new TiXmlElement("listEdge");
	list<int*> *edges = g->getEdges();
	for (list<int*>::iterator it = edges->begin(); it != edges->end(); it++) {
		//Add edge
		elem = new TiXmlElement("edge");
		elem->SetAttribute("start", (*it)[_SOURCE_NODE]);
		elem->SetAttribute("end", (*it)[_DEST_NODE]);
		elem->SetAttribute("value", (*it)[_VALUE]);
		elem->SetAttribute("state", (*it)[_EDGE_STATE]);
		edgeList->LinkEndChild(elem);
	}
	graph->LinkEndChild(edgeList);

	doc.LinkEndChild(graph);
	string file = dir;
	file.append(ext);
	doc.SaveFile(file.c_str());
}

Graph* GraphXML::importGraph(string graph, bool file) {
	Graph *g = NULL;
	string fileDir;
	if (file)
		fileDir = graph;
	else {
		fileDir = directory;
		fileDir.append(graph);
		fileDir.append(ext);
	}
	TiXmlDocument *doc = new TiXmlDocument(fileDir.c_str());
        if (doc->LoadFile()) {
		TiXmlHandle *hDoc = new TiXmlHandle(doc);
		TiXmlElement *elem = hDoc->FirstChildElement().Element();
		//New graph from file
		g = new GraphMatrix(0, elem->Attribute("name"));
		//Adding nodes
		TiXmlElement *list = elem->FirstChildElement("listNode");
		TiXmlElement *elemList = list->FirstChildElement();
		int num, state;
		string tag;
		while (elemList) {
			g->addNode();
			num = atoi(elemList->Attribute("num"));
			state = atoi(elemList->Attribute("state"));
                        tag = elemList->Attribute("tag");
			g->setState(num, state);
                        g->setTag(num, tag.c_str());
			elemList = elemList->NextSiblingElement();
		}
		//Adding Edges
		list = elem->FirstChildElement("listEdge");
		elemList = list->FirstChildElement();
		int src, dest, value;
		while (elemList) {
			src = atoi(elemList->Attribute("start"));
			dest = atoi(elemList->Attribute("end"));
			value = atoi(elemList->Attribute("value"));
			state = atoi(elemList->Attribute("state"));
			g->addEdge(src, dest);
			g->setEdgeValue(src, dest, value);
			g->setEdgeState(src, dest, state);
			elemList = elemList->NextSiblingElement();
		}
	} else {
		cerr << "Error while loading xml graph" << endl;
		g = new GraphMatrix(0, "Unknow");
	}
	findAll();
	return g;
}

list<string>* GraphXML::findAll() {
	list<string> *result = new list<string> ();
	struct dirent *lecture;
	DIR *rep = opendir(this->directory.c_str());
	while ((lecture = readdir(rep))) {
		if (endWith(lecture->d_name, this->ext)){
			string s = lecture->d_name;
			result->push_back(s.substr(0, s.length()-ext.size()));
		}
	}
	closedir(rep);
	return result;
}

bool GraphXML::endWith(string word, string ending) {
	if (word.length() >= ending.size()) {
		unsigned int lastMatchPos = word.rfind(ending);
		bool isEnding = true;
		for (unsigned int i = lastMatchPos + ending.length(); (i < word.length()) && isEnding; i++)
			if ((word[i] != '\n') && (word[i] != '\r'))
				isEnding = false;
		return isEnding;
	}
	return false;
}

//string
