/**
  * @author Estebe Anthony
  *
  */

#ifndef GRAPH_H_
#define GRAPH_H_

/**
 * @brief Characteristics of nodes
 */
#define _NUMBER		0		/**< Number of a node*/
#define _TAG		1       /**< Tag of a node*/
#define _STATE		2       /**< State of a node*/

/**
 * @brief Options for the states
 */
#define _CHOICE_STATE	-1		/**< State that permit to select node*/

/**
 * @brief Characteristics of edges
 */
#define _SOURCE_NODE	0		/**< the source node of an edge*/
#define _DEST_NODE		1		/**< the dest node of an edge*/
#define _VALUE			2		/**< the value of the edge*/
#define _EDGE_STATE		3		/**< the state of the edge*/

/**
 * @brief Edges states
 */
#define _NOT_VISITED	0		/**< the state when the edge was not visited*/
#define _VISITED		1		/**< the state when the edge was been visited*/
#define _ON_EDGE		2		/**< the state of the current edge*/

#include "Summit.h"
#include <list>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Graph {

public:

	/**
	 * @fn Graph(int order)
	 * @brief Constructor
	 * @param number of summit of the graph
	 */
	Graph(int order);

	/**
	 * @fn Graph(int order, string name)
	 * @brief Constructor
	 * @param number of summit of the graph
	 * @param name of the graph
	 */
	Graph(int order, string name);

	/**
	 * @brief Destroyer
	 */
	virtual ~Graph();

	/**
	 * @fn virtual int getOrder()
	 * @brief Get the order of the graph
	 * @return the order of the graph
	 */
	virtual int getOrder();

	/**
	 * @fn void setOrder(int order)
	 * @brief Instantiate the order of the graph
	 * @param order of the new graph
	 */
	virtual void setOrder(int order);

	/**
	 * @fn virtual void addEdge(int nodeA, int nodeB) = 0
	 * @brief Add new edge in the graph
	 * @param start node included in the graph
	 * @param end node included in the graph
	 */
	virtual void addEdge(int nodeA, int nodeB) = 0;

	/**
	 * @fn virtual void removeEdge(int nodeA, int nodeB) = 0
	 * @brief Remove edge in the graph
	 * @param start node included in the graph
	 * @param end node included in the graph
	 */
	virtual void removeEdge(int nodeA, int nodeB) = 0;

	/**
	 * @fn virtual int addNode() = 0
	 * @brief Add a node to the graph
	 * @return the number of the node
	 */
	virtual int addNode() = 0;

	/**
	 * @fn virtual void removeNode(int node) = 0
	 * @brief Remove a node to the graph
	 * @param node we want to remove
	 */
	virtual void removeNode(int node) = 0;

	/**
	 * @fn virtual bool isSuccessor(int nodeA, int nodeB) = 0
	 * @brief Function that permit to know if the nodeA is successor of the nodeB
	 * @param a node A of the graph
	 * @param a node B of the graph
	 * @return true if nodeA is a successor of nodeB, else return false
	 */
	virtual bool isSuccessor(int nodeA, int nodeB) = 0;

	/**
	 * @fn virtual list<int>* successors(int node)
	 * @brief Get the successor of a node
	 * @param begin node of the graph
	 * @return a list with the successors of the node
	 */
	virtual list<int>* successors(int node);

	/**
	 * @fn virtual int numberSuccessors(int node)
	 * @brief Function that permit to know the number of successors
	 * @param begin node of the graph
	 * @return the number of successors of node
	 */
	virtual int numberSuccessors(int node);

	/**
	 * @fn virtual bool isPredecessor(int nodeA, int nodeB)
	 * @brief Function that permit to know if the nodeA is predecessor of the nodeB
	 * @param a node A of the graph
	 * @param a node B of the graph
	 * @return true if nodeA is a predecessor of nodeB, else return false
	 */
	virtual bool isPredecessor(int nodeA, int nodeB);

	/**
	 * @fn virtual list<int>* predecessors(int node)
	 * @brief Get the predecessor of a node
	 * @param begin node of the graph
	 * @return a list with the predecessor of node
	 */
	virtual list<int>* predecessors(int node);

	/**
	 * @fn virtual int numberPredecessors(int node)
	 * @brief Function that permit to know the number of predecessors
	 * @param begin node of the graph
	 * @return the number of predecessors of node
	 */
	virtual int numberPredecessors(int node);

	/**
	 * @fn virtual bool isNeighbor(int nodeA, int nodeB)
	 * @brief Function that permit to know if the nodeA is a neighbor of the nodeB
	 * @param a node A of the graph
	 * @param a node B of the graph
	 * @return true if nodeA is a neighbor of nodeB, else return false
	 */
	virtual bool isNeighbor(int nodeA, int nodeB);

	/**
	 * @fn virtual list<int>* neighbors(int node)
	 * @brief Find the neighbors of a node
	 * @param begin node of the graph
	 * @return a list with all neighbors of node
	 */
	virtual list<int>* neighbors(int node);

	/**
	 * @fn virtual int numberNeighbors(int node)
	 * @brief Function that permit to know the number of neighbors
	 * @param begin node of the graph
	 * @return the number of neighbors of node
	 */
	virtual int numberNeighbors(int node);

	/**
	 * @fn virtual int getEdgeValue(int nodeA, int nodeB) = 0
	 * @brief Function that permit to know the value of the edge nodeA, nodeB
	 * @param source of the edge
	 * @param destination of the edge
	 * @return the value of the edge (nodeA, nodeB)
	 */
	virtual int getEdgeValue(int nodeA, int nodeB) = 0;

	/**
	 * @fn virtual void setEdgeValue(int nodeA, int nodeB, int value) = 0
	 * @brief Assign a value to the edge nodeA, nodeB
	 * @param source of the edge
	 * @param destination of the edge
	 * @param value of the edge
	 */
	virtual void setEdgeValue(int nodeA, int nodeB, int value) = 0;

	/**
	 * @fn virtual int getEdgeState(int nodeA, int nodeB) = 0
	 * @brief Function that permit to know the the state of the edge nodeA, nodeB
	 * @param source of the edge
	 * @param destination of the edge
	 * @return the edge state of the edge nodeA, nodeB
	 */
	virtual int getEdgeState(int nodeA, int nodeB) = 0;

	/**
	 * @fn virtual void setEdgeState(int nodeA, int nodeB, int state) = 0
	 * @brief Assign a state of the edge
	 * @param source of the edge
	 * @param destination of the edge
	 * @param state of the edge
	 */
	virtual void setEdgeState(int nodeA, int nodeB, int state) = 0;

	/**
	 * @fn virtual bool isSymmetric(int nodeA, int nodeB)
	 * @brief Function that permits to know if an edge is symmetric
	 * @param start node of the graph
	 * @param end node of the graph
	 */
	virtual bool isSymmetric(int nodeA, int nodeB);

	/**
	 * @fn virtual list<int*>* getEdges()
	 * @brief function that permit to get all edges of the graph
	 * @return the list of edges
	 */
	virtual list<int*>* getEdges();

	/**
	 * @fn virtual list<string*>* getSummits()
	 * @brief function that permit to get all summit of the graph
	 * @return the list of summit with the value, the tag and the state of the summit
	 */
	virtual list<string*>* getSummits();

	/**
	 * @fn virtual void setState(int node, int state)
	 * @brief Function that change the state of a node
	 * @param the node that we whant to change the state
	 * @param the new state of node
	 */
	virtual void setState(int node, int state);

	/**
	 * @fn virtual int getState(int node)
	 * @brief Function that return the state of a node
	 * @param the node that we want to know the state
	 * @return the state of the node given in paramtre
	 */
	virtual int getState(int node);

	/**
	 * @fn virtual void setTag(int node, string tag)
	 * @brief Function that change the tag of a node
	 * @param the node that we whant to change the tag
	 * @param the new tag of node
	 */
	virtual void setTag(int node, string tag);

	/**
	 * @fn virtual void setTag(int node, string tag)
	 * @brief Function that change the tag of a node
	 * @param the node that we whant to change the tag
	 * @param the new tag of node
	 */
	virtual void setTag(int node, int tag);

	/**
	 * @fn virtual string getTag(int node)
	 * @brief Function that return the tag of a node
	 * @param the node that we want to know the tag
	 * @return the state of the node given in paramtre
	 */
	virtual string getTag(int node);

	/**
	 * @fn virtual int getTag(int node)
	 * @brief Function that return the tag of a node
	 * @param the node that we want to know the tag
	 * @return the state of the node given in paramtre
	 */
	virtual int getTagInt(int node);

	/**
	 * @fn string getName()
	 * @brief Return the name of the graph
	 * @return name of the graph
	 */
	virtual string getName();

	/**
	  * @fn void setName(string name)
	  * @brief Function that permit to assign a name for the graph
	  * @param name of the graph
	  */
	virtual void setName(string name);

private:
	string name;	/**< name of the graph*/
	int order;		/**< order of the graph*/
	int *state;		/**< state of each nodes*/
	string *tags;	/**< tags of each nodes*/
};

#endif /* GRAPHE_H_ */
