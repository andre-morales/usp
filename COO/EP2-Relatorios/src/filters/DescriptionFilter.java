package filters;

import gerador.Produto;

/**
 *
 * @author Andre
 */
public class DescriptionFilter implements IFilter {
	private String query;
	
	public DescriptionFilter(String query) {
		this.query = query.toLowerCase();
	}
	
	@Override
	public boolean test(Produto t) {
		return t.getDescricao().toLowerCase().contains(query);
	}

	@Override
	public String getDescription() {
		return "desc contem '" + this.query + "'";
	}
}
