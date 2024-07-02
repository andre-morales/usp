package sorts;

import criteria.ICriterion;
import gerador.Produto;
import java.util.List;

/**
 * @author Andre
 * @version 1.0
 */
public interface ISortingStrategy {
	public void sort(List<Produto> produto);
	
	void setCriterion(ICriterion criterion);
	ICriterion getCriterion();
}
