package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class AscStockCriterion implements ICriterion {

	@Override
	public int compare(Produto a, Produto b) {
		return Integer.compare(a.getQtdEstoque(), b.getQtdEstoque());
	}
}
