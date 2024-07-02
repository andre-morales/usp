package gerador;

import criteria.AscDescriptionCriterion;
import criteria.AscPriceCriterion;
import criteria.AscStockCriterion;
import criteria.ICriterion;
import filters.AllFilter;
import filters.CategoryFilter;
import filters.IFilter;
import filters.StockFilter;
import java.io.IOException;
import java.util.List;
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

	// operador bit a bit "ou" pode ser usado para combinar mais de  
	// um estilo de formatacao simultaneamente (veja como no main)
	public static final int FORMATO_PADRAO  = 0b0000;
	public static final int FORMATO_NEGRITO = 0b0001;
	public static final int FORMATO_ITALICO = 0b0010;
	
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
		
		String [] opcoes_formatacao = new String[2];
		opcoes_formatacao[0] = args.length > 4 ? args[4] : null;
		opcoes_formatacao[1] = args.length > 5 ? args[5] : null;
		int formato = FORMATO_PADRAO;
		
		for(int i = 0; i < opcoes_formatacao.length; i++) {
			String op = opcoes_formatacao[i];
			formato |= (op != null ? op.equals("negrito") ? FORMATO_NEGRITO : (op.equals("italico") ? FORMATO_ITALICO : 0) : 0); 
		}
		
		// Cria os objetos estratégia utilizados pelo gerador de relatórios
		ICriterion sortingCrit = getCriterionOf(opcao_criterio_ord);
		ISortingAlgorithm sortingStrat = getSortingStrategyOf(opcao_algoritmo);
		IFilter filter = getFilterOf(opcao_criterio_filtro, opcao_parametro_filtro);
		
		// Carrega os produtos
		List<Produto> produtos = List.of(carregaProdutos());
		
		// Instancia um novo gerador de relatórios com os produtos e as estratégias pedidas
		GeradorDeRelatorios gdr = new GeradorDeRelatorios(produtos, sortingStrat, sortingCrit, filter, formato);

		try {
			gdr.geraRelatorio("saida.html");
		} catch(IOException e){
			e.printStackTrace();
		}
	}
	
	public static Produto [] carregaProdutos(){
		return new Produto [] { 
			new ProdutoPadrao( 1, "O Hobbit", "Livros", 2, 34.90),
			new ProdutoPadrao( 2, "Notebook Core i7", "Informatica", 5, 1999.90),
			new ProdutoPadrao( 3, "Resident Evil 4", "Games", 7, 79.90),
			new ProdutoPadrao( 4, "iPhone", "Telefonia", 8, 4999.90),
			new ProdutoPadrao( 5, "Calculo I", "Livros", 20, 55.00),
			new ProdutoPadrao( 6, "Power Glove", "Games", 3, 499.90),
			new ProdutoPadrao( 7, "Microsoft HoloLens", "Informatica", 1, 19900.00),
			new ProdutoPadrao( 8, "OpenGL Programming Guide", "Livros", 4, 89.90),
			new ProdutoPadrao( 9, "Vectrex", "Games", 1, 799.90),
			new ProdutoPadrao(10, "Carregador iPhone", "Telefonia", 15, 499.90),
			new ProdutoPadrao(11, "Introduction to Algorithms", "Livros", 7, 315.00),
			new ProdutoPadrao(12, "Daytona USA (Arcade)", "Games", 1, 12000.00),
			new ProdutoPadrao(13, "Neuromancer", "Livros", 5, 45.00),
			new ProdutoPadrao(14, "Nokia 3100", "Telefonia", 4, 249.99),
			new ProdutoPadrao(15, "Oculus Rift", "Games", 1, 3600.00),
			new ProdutoPadrao(16, "Trackball Logitech", "Informatica", 1, 250.00),
			new ProdutoPadrao(17, "After Burner II (Arcade)", "Games", 2, 8900.0),
			new ProdutoPadrao(18, "Assembly for Dummies", "Livros", 30, 129.90),
			new ProdutoPadrao(19, "iPhone (usado)", "Telefonia", 3, 3999.90),
			new ProdutoPadrao(20, "Game Programming Patterns", "Livros", 1, 299.90),
			new ProdutoPadrao(21, "Playstation 2", "Games", 10, 499.90),
			new ProdutoPadrao(22, "Carregador Nokia", "Telefonia", 14, 89.00),
			new ProdutoPadrao(23, "Placa Aceleradora Voodoo 2", "Informatica", 4, 189.00),
			new ProdutoPadrao(24, "Stunts", "Games", 3, 19.90),
			new ProdutoPadrao(25, "Carregador Generico", "Telefonia", 9, 30.00),
			new ProdutoPadrao(26, "Monitor VGA 14 polegadas", "Informatica", 2, 199.90),
			new ProdutoPadrao(27, "Nokia N-Gage", "Telefonia", 9, 699.00),
			new ProdutoPadrao(28, "Disquetes Maxell 5.25 polegadas (caixa com 10 unidades)", "Informatica", 23, 49.00),
			new ProdutoPadrao(29, "Alone in The Dark", "Games", 11, 59.00),
			new ProdutoPadrao(30, "The Art of Computer Programming Vol. 1", "Livros", 3, 240.00),
			new ProdutoPadrao(31, "The Art of Computer Programming Vol. 2", "Livros", 2, 200.00),
			new ProdutoPadrao(32, "The Art of Computer Programming Vol. 3", "Livros", 4, 270.00)
		};
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
