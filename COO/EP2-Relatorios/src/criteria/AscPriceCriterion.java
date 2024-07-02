package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class AscPriceCriterion implements ICriterion {

	@Override
	public int compare(Produto a, Produto b) {
		return Double.compare(a.getPreco(), b.getPreco());
	}
}
