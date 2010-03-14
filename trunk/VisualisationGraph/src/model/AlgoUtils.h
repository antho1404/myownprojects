/**
  * @author Estebe Anthony
  */
  
#ifndef ALGOUTILS_H
#define ALGOUTILS_H

#include <list>
#include <string>
#include "Graph.h"
#include "AbstractModel.h"

/**
 * Characteristics of the choice
 */
#define _FIFO   0       /**< First in firt out (first value in a list)*/
#define _LIFO   1       /**< Last in first out (last value in a list)*/
#define _RDM    2       /**< Random value from the list*/
#define _USER   3       /**< Value selected by user*/

class AlgoUtils {

public:

	/**
	 * @fn AlgoUtils()
	 * @brief Constructor
	 */
	AlgoUtils();

	/**
	 * @fn AlgoUtils(AbstractModel *model)
	 * @brief Constructor
	 * @param the model which launch the algorithm
	 */
	AlgoUtils(AbstractModel *model);

	/**
	 * @fn AlgoUtils(AbstractModel *model, string name)
	 * @brief Constructor
	 * @param the model which launch the algorithm
	 * @param the name of the algorithm
	 */
	AlgoUtils(AbstractModel *model, string name);

	/**
	  * @fn void changeFlagInteraction(int flag)
	  * @brief Function that permit to assign the kind of interaction with the algorithm between
	  * _FIFO, _LIFO, _RDM, _USER
	  * @param flag that we want to assign
	  */
	virtual void changeFlagInteraction(int flag);

	/**
	  * @fn void changeSpeed(unsigned long time)
	  * @brief Change the time to wait when the algorithm is running in _FIFO, _LIFO or _RDM
	  * @param time to wait
	  */
	virtual void changeSpeed(unsigned long time);

	/**
	  * @fn void setName(string name)
	  * @brief Assign a name for the algorithm
	  * @param name of the algorithm
	  */
	void setName(string name);

	/**
	  * @fn void setModel(AbstractModel *model)
	  * @brief Assign the model to the algorithm
	  * @param the model assigned to the graphe
	  */
	void setModel(AbstractModel *model);

	/**
	 * @fn string getName()
	 * @brief Method that permit to know the name of the algorithm
	 * @return the name of the algorithm
	 */
	virtual string getName();

	/**
	  * @fn void _sleep(unsigned long time)
	  * @brief function that permit to wait
	  * @param time we want to sleep
	  */
	virtual void _sleep(unsigned long time);

	/**
	  * @fn void initAlgo()
	  * @brief function that permit to initialize the algorithm
	  * @param graph that we want to initialize
	  */
	virtual void initAlgo(Graph *g);

	/**
	 * @fn int chooseNode(list<int>* nodes)
	 * @brief function that permits to choose a node into a list of availables nodes given by an algorithm
	 * the selection depend of the kind of interaction choosen into _FIFO, _LIFO, _RDM and _USER
	 * @param the graph which contain nodes included in the second list of nodes
	 * @param list of availables node
	 */
	virtual int chooseNode(Graph *g, list<int>* nodes);

	/**
	 * @fn void setNodeSelected(int node)
	 * @brief Change the value of the selected node
	 * @param the node selected
	 */
	virtual void setNodeSelected(int node);

	/**
	  * \fn void notify(Graph *g)
	  * \brief Notify windows that the graphe has change
	  * \param the graph
	  */
	virtual void notify(Graph *g);

private:
	string name;			/**< name of the algorithm*/
	int selectedNode;		/**< node selected*/
	unsigned long sleepTime;/**< time to wait between two step of the algo*/
	int flagInteraction;	/**< kind of interaction with the algorithm*/
	AbstractModel *model;	/**< model which launch the algorithm*/
};

#endif // ALGOUTILS_H
