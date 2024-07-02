package sorts;

import criteria.ICriterion;
import gerador.Produto;
import java.util.List;

/**
 * @author Andre
 * @version 1.0
 */
public class InsertionSortStrategy implements ISortingStrategy {
	private ICriterion criterion;
	
	public InsertionSortStrategy(ICriterion criterion) {
		this.criterion = criterion;
	}
	
	@Override
	public void sort(List<Produto> produtos) {
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
	public void setCriterion(ICriterion criterion) {
		this.criterion = criterion;
	}

	@Override
	public ICriterion getCriterion() {
		return criterion;
	}
	
}
