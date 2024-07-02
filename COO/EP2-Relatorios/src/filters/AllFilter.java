package filters;

import gerador.Produto;

/**
 *
 * @author Andre
 */
public class AllFilter implements IFilter {

	@Override
	public boolean test(Produto t) {
		return true;
	}

	@Override
	public String getDescription() {
		return "todos";
	}
}
