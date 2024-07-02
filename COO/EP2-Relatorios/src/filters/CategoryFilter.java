package filters;

import gerador.Produto;

/**
 *
 * @author Andre
 */
public class CategoryFilter implements IFilter {
	private String category;
	
	public CategoryFilter(String category) {
		this.category = category;
	}
	
	@Override
	public boolean test(Produto t) {
		return t.getCategoria().equalsIgnoreCase(category);
	}
	
	@Override
	public String getDescription() {
		return "categoria = " + category;
	}
}
