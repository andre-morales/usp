package formatters;

import gerador.Produto;
import java.io.PrintWriter;

/**
 *
 * @author Andre
 */
public class BoldFormatter implements IFormatter {
	public IFormatter base;
	
	public BoldFormatter(IFormatter base) {
		this.base = base;
	}
	
	@Override
	public void format(PrintWriter stream, Produto prod) {
		stream.print("<span style=\"font-weight:bold\">");
		base.format(stream, prod);
		stream.print("</span>");
	}
	
}
