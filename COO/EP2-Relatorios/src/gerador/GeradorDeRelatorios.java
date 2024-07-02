package gerador;

import criteria.ICriterion;
import filters.IFilter;
import static gerador.MainCLI.*;
import java.io.PrintWriter;
import java.io.IOException;

import java.util.*;
import sorts.ISortingAlgorithm;

public class GeradorDeRelatorios {
	private List<Produto> produtos;
	private int format_flags;	
	
	private ISortingAlgorithm sortingAlgorithm;
	private ICriterion sortingCriterion;
	private IFilter filter;

	public GeradorDeRelatorios(Collection<Produto> produtos, ISortingAlgorithm algoritmo, ICriterion criterio, IFilter filtro, int format_flags){
		this.produtos = new ArrayList<>();
		this.produtos.addAll(produtos);

		this.format_flags = format_flags;
		
		this.filter = filtro;
		this.sortingCriterion = criterio;
		this.sortingAlgorithm = algoritmo;
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

		PrintWriter out = new PrintWriter(arquivoSaida);

		out.println("<!DOCTYPE html><html>");
		out.println("<head><title>Relatorio de produtos</title></head>");
		out.println("<body>");
		out.println("Relatorio de Produtos:");
		out.println("<ul>");
		
		// Cria uma stream de produtos, filtra eles de acordo com o predicado e converte a 
		// stream em uma lista novamente. A coalescência de uma stream() em uma lista é uma operação
		// preguiçosa (lazy-evaluation), e não deve consumir mais memória com cópias.
		List<Produto> filteredProducts = produtos.stream().filter(this.filter).toList();
		
		for (Produto p : filteredProducts) {
			out.print("<li>");

			if((format_flags & FORMATO_ITALICO) > 0){
				out.print("<span style=\"font-style:italic\">");
			}

			if((format_flags & FORMATO_NEGRITO) > 0){
				out.print("<span style=\"font-weight:bold\">");
			} 

			out.print(p.formataParaImpressao());

			if((format_flags & FORMATO_NEGRITO) > 0){
				out.print("</span>");
			} 

			if((format_flags & FORMATO_ITALICO) > 0){
				out.print("</span>");
			}

			out.println("</li>");
		}		

		out.println("</ul>");
		out.println(filteredProducts.size() + " produtos listados, de um total de " + produtos.size() + ".");
		out.println("</body>");
		out.println("</html>");

		out.close();
	}
}
