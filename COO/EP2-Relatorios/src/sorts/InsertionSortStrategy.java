package sorts;

import criteria.ICriterion;
import gerador.Produto;

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
	public void sort(Produto[] produtos) {
		var ini = 0;
		var fim = produtos.length - 1;
		for(int i = 0; i <= fim; i++){
			Produto x = produtos[i];				
			int j = (i - 1);

			while(j >= ini){
				if (criterion.compare(x, produtos[j]) < 0) {
					produtos[j + 1] = produtos[j];
					j--;
				} else break;
			}

			produtos[j + 1] = x;
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
