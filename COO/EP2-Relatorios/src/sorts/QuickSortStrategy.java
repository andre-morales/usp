package sorts;

import criteria.ICriterion;
import gerador.Produto;

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
	public void sort(Produto[] produtos) {
		doSort(produtos, 0, produtos.length - 1);
	}

	private void doSort(Produto[] produtos, int ini, int fim) {
		if(ini < fim) {
			int q = particiona(produtos, ini, fim);

			doSort(produtos, ini, q);
			doSort(produtos, q + 1, fim);
		}
	}
	
	private int particiona(Produto[] produtos, int ini, int fim){
		Produto x = produtos[ini];
		int i = (ini - 1);
		int j = (fim + 1);

		while(true){
			do{ 
				j--;
			} while(criterion.compare(produtos[j], x) > 0);

			do{
				i++;
			} while(criterion.compare(produtos[i], x) < 0);
			
			if(i < j){
				Produto temp = produtos[i];
				produtos[i] = produtos[j]; 				
				produtos[j] = temp;
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
