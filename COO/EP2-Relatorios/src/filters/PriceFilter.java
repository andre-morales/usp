package filters;

import gerador.Produto;

/**
 *
 * @author Andre
 */
public class PriceFilter implements IFilter {
	private double min;
	private double max;
	
	public PriceFilter(String range) {
		String[] sp = range.split(":");
		min = Double.parseDouble(sp[0]);
		max = Double.parseDouble(sp[1]);
	}
	
	@Override
	public boolean test(Produto t) {
		double preco = t.getPreco();
		return preco >= min && preco <= max;
	}

	@Override
	public String getDescription() {
		return "preco [" + min + ", " + max + "]";
	}
}
