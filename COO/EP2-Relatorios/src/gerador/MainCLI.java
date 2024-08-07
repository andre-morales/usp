package gerador;

import criteria.DescriptionCriterion;
import criteria.PriceCriterion;
import criteria.StockCriterion;
import criteria.ICriterion;
import criteria.OrderRule;
import filters.AllFilter;
import filters.CategoryFilter;
import filters.DescriptionFilter;
import filters.IFilter;
import filters.PriceFilter;
import filters.StockFilter;
import formatters.BoldFormatter;
import formatters.IFormatter;
import formatters.ItalicFormatter;
import formatters.StandardFormatter;
import formatters.StyledFormatter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;
import sorts.ISortingAlgorithm;
import sorts.InsertionSortAlgorithm;
import sorts.QuickSortAlgorithm;

/**
 * @author Andre
 * @version 1.0
 */
public class MainCLI {
	public static final String SHEET_PATH = "./produtos.csv";
	public static final String OUTPUT_PATH = "saida.html";
	
	public static final String ALG_INSERTIONSORT = "quick";
	public static final String ALG_QUICKSORT = "insertion";

	public static final String CRIT_DESC_CRESC = "descricao_c";
	public static final String CRIT_PRECO_CRESC = "preco_c";
	public static final String CRIT_ESTOQUE_CRESC = "estoque_c";
	public static final String CRIT_DESC_DECRESC = "descricao_d";
	public static final String CRIT_PRECO_DECRESC = "preco_d";
	public static final String CRIT_ESTOQUE_DECRESC = "estoque_d";
	
	public static final String FILTRO_TODOS = "todos";
	public static final String FILTRO_ESTOQUE_MENOR_OU_IQUAL_A = "estoque_menor_igual";
	public static final String FILTRO_CATEGORIA_IGUAL_A = "categoria_igual";
	public static final String FILTRO_PRECO_ENTRE = "preco_entre";
	public static final String FILTRO_DESC_CONTEM = "desc_contem";

	public static final String FORMATO_NEGRITO = "negrito";
	public static final String FORMATO_ITALICO = "italico";
	public static final String FORMATO_ESTILIZADO = "estilizado";
	
	public static void main(String[] args) {
		// Verificação de sanidade dos argumentos
		if(args.length < 4){
			printHelp();
			System.exit(1);
		}
		
		// Extrai as opções dos argumentos
		String opcao_algoritmo = args[0];
		String opcao_criterio_ord = args[1];
		String opcao_criterio_filtro = args[2];
		String opcao_parametro_filtro = args[3];
		
		// Obtém o resto do array de argumentos e os considera opções de formatação
		String[] formatOptions = Arrays.copyOfRange(args, 4, args.length);
		
		// Cria todos objetos estratégia utilizados pelo gerador de relatórios
		ICriterion sortingCrit = getSortCriterionFor(opcao_criterio_ord);
		ISortingAlgorithm sortingStrat = getSortAlgorithmFor(opcao_algoritmo);
		IFilter filter = getFilterFor(opcao_criterio_filtro, opcao_parametro_filtro);
		IFormatter formatter = getFormatterFor(formatOptions);
		
		// Carrega os produtos
		Collection<Produto> produtos = carregaProdutos();
				
		// Instancia um novo gerador de relatórios com os produtos e as estratégias pedidas
		GeradorDeRelatorios gdr = new GeradorDeRelatorios(produtos, sortingStrat, sortingCrit, filter, formatter);

		try {
			gdr.geraRelatorio(OUTPUT_PATH);
		} catch(IOException e){
			System.err.println("ERRO NA GERAÇÃO DO RELATÓRIO: ");
			e.printStackTrace();
			System.exit(-1);
		}
	}
	
	public static void printHelp() {
		System.out.println("Uso:");
		System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
		System.out.println("Onde:");
		System.out.println("\talgoritmo: 'quick' ou 'insertion'");
		System.out.println("\tcriterio de ordenação: 'preco_[c/d]' ou 'descricao_[c/d]' ou 'estoque_[c/d]'");
		System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'preco_entre' ou 'desc_contem'"); 
		System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem"); 
		System.out.println("\topções de formatação: qualquer combinação de 'negrito', 'italico', 'estilizado'");
		System.out.println();
	}
	
	public static Collection<Produto> carregaProdutos(){
		//return DefaultProducts.get();
		return SheetReader.readFrom(SHEET_PATH);
	} 
	
	/**
	 * Obtém um formatador decorado para a sequência pedida.
	 */
	private static IFormatter getFormatterFor(String... args) {
		IFormatter formatter = new StandardFormatter();
		for (String fmt : args) {
			if (fmt == null) continue;
			if (fmt.isEmpty()) continue;
			
			switch(fmt) {
			case FORMATO_NEGRITO:
				formatter = new BoldFormatter(formatter);
				break;
			case FORMATO_ITALICO:
				formatter = new ItalicFormatter(formatter);
				break;
			case FORMATO_ESTILIZADO:
				formatter = new StyledFormatter(formatter);
				break;
			default:
				throw new RuntimeException("Formatador inválido: " + fmt);
			}
		}
		return formatter;
	}
	
	/** Obtém o critério de ordenação com o nome dado. */
	private static ICriterion getSortCriterionFor(String name) {
		switch(name) {
			case CRIT_PRECO_CRESC:		return new PriceCriterion();
			case CRIT_PRECO_DECRESC:	return new PriceCriterion(OrderRule.DESCENDING);
			case CRIT_DESC_CRESC:		return new DescriptionCriterion();
			case CRIT_DESC_DECRESC:		return new DescriptionCriterion(OrderRule.DESCENDING);
			case CRIT_ESTOQUE_CRESC:	return new StockCriterion();
			case CRIT_ESTOQUE_DECRESC:	return new StockCriterion(OrderRule.DESCENDING);
			default:
				throw new RuntimeException("Criterio invalido!");
		}
	}
	
	/** Obtém o algoritmo de ordenação com o nome dado. */
	private static ISortingAlgorithm getSortAlgorithmFor(String name) {
		switch(name) {
			case ALG_INSERTIONSORT: return new InsertionSortAlgorithm();
			case ALG_QUICKSORT: return new QuickSortAlgorithm();
			default:
				throw new RuntimeException("Algoritmo invalido!");
		}
	}
	
	/** Obtém uma instância de filtro com o nome e parâmetros dados. */
	private static IFilter getFilterFor(String name, String... params) {
		switch(name) {
			case FILTRO_TODOS: return new AllFilter();
			case FILTRO_ESTOQUE_MENOR_OU_IQUAL_A:
				return new StockFilter(Integer.parseInt(params[0]));
			case FILTRO_CATEGORIA_IGUAL_A:
				return new CategoryFilter(params[0]);
			case FILTRO_PRECO_ENTRE:
				return new PriceFilter(params[0]);
			case FILTRO_DESC_CONTEM:
				return new DescriptionFilter(params[0]);
			default:
				throw new RuntimeException("Filtro invalido!");	
		}
	}
}
