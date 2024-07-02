package sorts;

import criteria.ICriterion;
import gerador.Produto;
import java.util.List;

/**
 * @author Andre
 * @version 1.0
 */
public class QuickSortStrategy implements ISortingStrategy {
	private ICriterion criterion;
	
	public QuickSortStrategy(ICriterion criterion) {
		this.criterion = criterion;
	}
	
	@Override
	public void sort(List<Produto> produtos) {
		doSort(produtos, 0, produtos.size() - 1);
	}

	private void doSort(List<Produto> produtos, int ini, int fim) {
		if(ini < fim) {
			int q = particiona(produtos, ini, fim);

			doSort(produtos, ini, q);
			doSort(produtos, q + 1, fim);
		}
	}
	
	private int particiona(List<Produto> produtos, int ini, int fim){
		Produto x = produtos.get(ini);
		int i = (ini - 1);
		int j = (fim + 1);

		while(true){
			do{ 
				j--;
			} while(criterion.compare(produtos.get(j), x) > 0);

			do{
				i++;
			} while(criterion.compare(produtos.get(i), x) < 0);
			
			if(i < j){
				Produto temp = produtos.get(i);
				produtos.set(i, produtos.get(j)); 				
				produtos.set(j, temp);
			}
			else return j;
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
