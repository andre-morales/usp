package formatters;

import gerador.Produto;
import java.io.PrintWriter;

/**
 * @author Andre
 * @version 1.0
 */
public class StandardFormatter implements IFormatter {

	@Override
	public void format(PrintWriter stream, Produto prod) {
		stream.print("<li>");
		stream.print(prod.formataParaImpressao());
		stream.print("</li>");
	}
}
