package formatters;

import gerador.Produto;
import java.io.PrintWriter;

/**
 *
 * @author Andre
 */
public interface IFormatter {
	public void format(PrintWriter stream, Produto prod);
}
