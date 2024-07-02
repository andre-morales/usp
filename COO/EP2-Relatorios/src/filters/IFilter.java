package filters;

import gerador.Produto;
import java.util.function.Predicate;

/**
 *
 * @author Andre
 */
public interface IFilter extends Predicate<Produto> {
	default String getDescription() {
		return this.getClass().getName();
	}
}
