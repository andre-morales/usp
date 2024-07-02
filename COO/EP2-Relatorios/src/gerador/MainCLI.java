package gerador;

import criteria.AscDescriptionCriterion;
import criteria.AscPriceCriterion;
import criteria.AscStockCriterion;
import criteria.ICriterion;
import filters.AllFilter;
import filters.CategoryFilter;
import filters.IFilter;
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
	public static final String ALG_INSERTIONSORT = "quick";
	public static final String ALG_QUICKSORT = "insertion";

	public static final String CRIT_DESC_CRESC = "descricao_c";
	public static final String CRIT_PRECO_CRESC = "preco_c";
	public static final String CRIT_ESTOQUE_CRESC = "estoque_c";
	
	public static final String FILTRO_TODOS = "todos";
	public static final String FILTRO_ESTOQUE_MENOR_OU_IQUAL_A = "estoque_menor_igual";
	public static final String FILTRO_CATEGORIA_IGUAL_A = "categoria_igual";

	public static final String FORMATO_NEGRITO = "negrito";
	public static final String FORMATO_ITALICO = "italico";
	public static final String FORMATO_ESTILIZADO = "estilizado";
	
	public static void main(String [] args) {
		if(args.length < 4){
			System.out.println("Uso:");
			System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
			System.out.println("Onde:");
			System.out.println("\talgoritmo: 'quick' ou 'insertion'");
			System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c'");
			System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual'"); 
			System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem"); 
			System.out.println("\topções de formatação: 'negrito' e/ou 'italico'");
			System.out.println();
			System.exit(1);
		}

		String opcao_algoritmo = args[0];
		String opcao_criterio_ord = args[1];
		String opcao_criterio_filtro = args[2];
		String opcao_parametro_filtro = args[3];
		
		// Obtém o resto do array de argumentos e os considera opções de formatação
		String[] formatOptions = Arrays.copyOfRange(args, 4, args.length);
		
		// Cria os objetos estratégia utilizados pelo gerador de relatórios
		ICriterion sortingCrit = getCriterionOf(opcao_criterio_ord);
		ISortingAlgorithm sortingStrat = getSortingStrategyOf(opcao_algoritmo);
		IFilter filter = getFilterOf(opcao_criterio_filtro, opcao_parametro_filtro);
		IFormatter formatter = getFormatterOf(formatOptions);
		
		// Carrega os produtos
		Collection<Produto> produtos = carregaProdutos();
				
		// Instancia um novo gerador de relatórios com os produtos e as estratégias pedidas
		GeradorDeRelatorios gdr = new GeradorDeRelatorios(produtos, sortingStrat, sortingCrit, filter, formatter);

		try {
			gdr.geraRelatorio("saida.html");
		} catch(IOException e){
			e.printStackTrace();
		}
	}
	
	public static Collection<Produto> carregaProdutos(){
		//return DefaultProducts.get();
		return SheetReader.readFrom("./produtos.csv");
	} 
	
	private static IFormatter getFormatterOf(String... args) {
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
	
	private static ICriterion getCriterionOf(String name) {
		switch(name) {
			case CRIT_PRECO_CRESC:
				return new AscPriceCriterion();
			case CRIT_DESC_CRESC:
				return new AscDescriptionCriterion();
			case CRIT_ESTOQUE_CRESC:
				return new AscStockCriterion();
			default:
				throw new RuntimeException("Criterio invalido!");
		}
	}
	
	private static ISortingAlgorithm getSortingStrategyOf(String name) {
		switch(name) {
			case ALG_INSERTIONSORT: return new InsertionSortAlgorithm();
			case ALG_QUICKSORT: return new QuickSortAlgorithm();
			default:
				throw new RuntimeException("Algoritmo invalido!");
		}
	}
	
	private static IFilter getFilterOf(String name, String... params) {
		switch(name) {
			case FILTRO_TODOS: return new AllFilter();
			case FILTRO_ESTOQUE_MENOR_OU_IQUAL_A:
				return new StockFilter(Integer.parseInt(params[0]));
			case FILTRO_CATEGORIA_IGUAL_A:
				return new CategoryFilter(params[0]);
			default:
				throw new RuntimeException("Filtro invalido!");	
		}
	}
}
