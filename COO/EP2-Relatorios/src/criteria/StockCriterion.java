package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class StockCriterion implements ICriterion {
	private OrderRule rule = OrderRule.ASCENDING;
	
	public StockCriterion() {}
	
	public StockCriterion(OrderRule rule) {
		this.rule = rule;
	}
	
	@Override
	public int compare(Produto a, Produto b) {
		int comp = Integer.compare(a.getQtdEstoque(), b.getQtdEstoque());
		if (rule == OrderRule.DESCENDING) comp *= -1;
		return comp;
	}
}
