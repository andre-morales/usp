package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class PriceCriterion implements ICriterion {
	private OrderRule rule = OrderRule.ASCENDING;
	
	public PriceCriterion() {}

	public PriceCriterion(OrderRule rule) {
		this.rule = rule;
	}
	
	@Override
	public int compare(Produto a, Produto b) {
		int comp = Double.compare(a.getPreco(), b.getPreco());

		if (rule == OrderRule.DESCENDING) comp *= -1;
		return comp;
	}
}
