package formatters;

import gerador.Produto;
import java.io.PrintWriter;

/**
 *
 * @author Andre
 */
public class ItalicFormatter implements IFormatter {
	public IFormatter base;
	
	public ItalicFormatter(IFormatter base) {
		this.base = base;
	}
	
	@Override
	public void format(PrintWriter stream, Produto prod) {
		stream.print("<span style=\"font-style:italic\">");
		base.format(stream, prod);
		stream.print("</span>");
	}
	
}
