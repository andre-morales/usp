package filters;

import gerador.Produto;

/**
 *
 * @author Andre
 */
public class StockFilter implements IFilter {
	private int parameter;
	
	public StockFilter(int parameter) {
		this.parameter = parameter;
	}
	
	@Override
	public boolean test(Produto t) {
		return t.getQtdEstoque() <= parameter;
	}

	@Override
	public String getDescription() {
		return "estoque <= " + parameter;
	}
}
