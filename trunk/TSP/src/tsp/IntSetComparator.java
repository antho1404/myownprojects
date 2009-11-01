package tsp;

import java.util.*;

	/**
	 * Classe permettant de faire le classement des set
	 * @author Dejean Quentin, Estebe Anthony
	 */

public class IntSetComparator implements Comparator<Set<Integer>>{

	//compare les valeurs de deux set
	public int compare(Set<Integer> set1, Set<Integer> set2) {
		if (set1.size()<set2.size())
			return -1;
		if (set1.size()>set2.size())
			return 1;
		return set1.toString().compareTo(set2.toString());
	}
}
