package sorts;

import gerador.Produto;
import java.util.Comparator;
import java.util.List;

/**
 * @author Andre
 * @version 1.0
 */
public interface ISortingAlgorithm {
	public void sort(List<Produto> produto);
	
	void setCriterion(Comparator<Produto> criterion);
	Comparator<Produto> getCriterion();
}
