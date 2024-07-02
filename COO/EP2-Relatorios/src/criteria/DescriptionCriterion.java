package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class DescriptionCriterion implements ICriterion {
	private OrderRule rule = OrderRule.ASCENDING;
	
	public DescriptionCriterion() {}
	
	public DescriptionCriterion(OrderRule rule) {
		this.rule = rule;
	}
	
	@Override
	public int compare(Produto a, Produto b) {
		int comp = a.getDescricao().compareToIgnoreCase(b.getDescricao());
		if (rule == OrderRule.DESCENDING) comp *= -1;
		return comp;
	}
}
