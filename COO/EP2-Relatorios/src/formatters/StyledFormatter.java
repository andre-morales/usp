package formatters;

import gerador.Produto;
import gerador.ProdutoColorido;
import java.io.PrintWriter;

/**
 *
 * @author Andre
 */
public class StyledFormatter implements IFormatter {
	public IFormatter base;
	
	public StyledFormatter(IFormatter base) {
		this.base = base;
	}
	
	@Override
	public void format(PrintWriter stream, Produto prod) {
		// Se o produto não é um subtipo que permite estilização por produto, não aplique nenhuma
		// outra formatação
		if (!(prod instanceof ProdutoColorido)) {
			base.format(stream, prod);
			return;
		}
		
		// Caso contrário, formate o produto.
		ProdutoColorido pcol = (ProdutoColorido)prod;
		
		String italics = pcol.isItalico() ? "font-style:italic;" : "";
		String bold    = pcol.isNegrito() ? "font-weight:bold;" : "";
		String color   = "color:" + pcol.getCor();
		
		stream.print("<span style='" + italics + bold + color + "'>");
		base.format(stream, prod);
		stream.print("</span>");
	}
}
