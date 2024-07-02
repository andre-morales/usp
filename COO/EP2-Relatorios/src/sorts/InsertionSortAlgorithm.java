package sorts;

import gerador.Produto;
import java.util.Comparator;
import java.util.List;

/**
 * @author Andre
 * @version 1.0
 */
public class InsertionSortAlgorithm implements ISortingAlgorithm {
	private Comparator<Produto> criterion;
	
	@Override
	public void sort(List<Produto> produtos) {
		if (criterion == null) throw new IllegalStateException("Critério de ordenação não definido!");
		
		var ini = 0;
		var fim = produtos.size() - 1;
		for(int i = 0; i <= fim; i++){
			Produto x = produtos.get(i);				
			int j = (i - 1);

			while(j >= ini){
				if (criterion.compare(x, produtos.get(j)) < 0) {
					produtos.set(j + 1, produtos.get(j));
					j--;
				} else break;
			}

			produtos.set(j + 1, x);
		}
	}

	@Override
	public void setCriterion(Comparator<Produto> criterion) {
		this.criterion = criterion;
	}

	@Override
	public Comparator<Produto> getCriterion() {
		return criterion;
	}
	
}
