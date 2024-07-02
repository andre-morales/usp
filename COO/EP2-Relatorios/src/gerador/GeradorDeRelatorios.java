package gerador;

import criteria.ICriterion;
import filters.IFilter;
import formatters.IFormatter;
import sorts.ISortingAlgorithm;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class GeradorDeRelatorios {
	private List<Produto> produtos;
	private ISortingAlgorithm sortingAlgorithm;
	private ICriterion sortingCriterion;
	private IFilter filter;
	private IFormatter formatter;

	public GeradorDeRelatorios(Collection<Produto> produtos, ISortingAlgorithm algoritmo, ICriterion criterio, IFilter filtro, IFormatter formatter){
		this.filter = filtro;
		this.sortingCriterion = criterio;
		this.sortingAlgorithm = algoritmo;
		this.formatter = formatter;
		
		// Clona a lista de produtos
		this.produtos = new ArrayList<>();
		this.produtos.addAll(produtos);
	}

	private void ordena(){
		sortingAlgorithm.setCriterion(sortingCriterion);
		sortingAlgorithm.sort(produtos);
	}
	
	public void debug(){
		System.out.println("Gerando relatório para array contendo " + produtos.size() + " produto(s)");
		System.out.println("parametro filtro: '" + filter.getDescription() + "'"); 
	}

	public void geraRelatorio(String arquivoSaida) throws IOException {
		debug();
		ordena();

		try (PrintWriter out = new PrintWriter(arquivoSaida)) {
			// Imprime o cabeçalho
			out.println("<!DOCTYPE html><html>");
			out.println("<head><title>Relatorio de produtos</title></head>");
			out.println("<body>");
			out.println("Relatorio de Produtos:");
			out.println("<ul>");
			
			// Cria uma stream de produtos, filtra eles de acordo com o predicado e converte a
			// stream em uma lista novamente. A coalescência de uma stream() em uma lista é uma operação
			// preguiçosa (lazy-evaluation), e não deve consumir mais memória com cópias.
			List<Produto> filteredProducts = produtos.stream().filter(this.filter).toList();
			
			// Passa todos os produtos pelo formatador
			for (Produto p : filteredProducts) {
				formatter.format(out, p);
			}
			
			// Imprime o rodapé
			out.println("</ul>");
			out.println(filteredProducts.size() + " produtos listados, de um total de " + produtos.size() + ".");
			out.println("</body>");
			out.println("</html>");
		}
	}
}
