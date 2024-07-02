package criteria;

import gerador.Produto;

/**
 * @author Andre
 * @version 1.0
 */
public class AscDescriptionCriterion implements ICriterion {
	@Override
	public int compare(Produto a, Produto b) {
		return a.getDescricao().compareToIgnoreCase(b.getDescricao());
	}
}
