package sorts;

import criteria.ICriterion;
import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public interface ISortingStrategy {
	public void sort(Produto[] produto);
	
	void setCriterion(ICriterion criterion);
	ICriterion getCriterion();
}
