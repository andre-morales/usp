package gerador;

import java.text.NumberFormat;

public class ProdutoColorido implements Produto {
	private static final String SEPARADOR = ", ";

	private int id;
	private String descricao;
	private String categoria;
	private int qtdEstoque;
	private double preco;
	private boolean negrito;
	private boolean italico;
	private String cor;

	public ProdutoColorido(int id, String descricao, String categoria, int qtdEstoque, double preco, boolean negrito, boolean italico, String cor){
		setId(id);
		setDescricao(descricao);
		setCategoria(categoria);
		setQtdEstoque(qtdEstoque);
		setPreco(preco);
		setNegrito(negrito);
		setItalico(italico);
		setCor(cor);
	}

	// metodo que devolve uma String que representa o produto, a ser usada na geração dos relatorios.
	@Override
	public String formataParaImpressao(){
		NumberFormat fmt = NumberFormat.getCurrencyInstance();
		StringBuilder sb = new StringBuilder();
		sb.append(getDescricao());
		sb.append(SEPARADOR);
		sb.append(getCategoria());
		sb.append(SEPARADOR);
		sb.append(fmt.format(getPreco()));
		sb.append(SEPARADOR);
		sb.append(getQtdEstoque());
		sb.append(" unidade(s) em estoque");
		return sb.toString();
	}
	
	private void setId(int id){
		this.id = id;
	}

	private void setDescricao(String descricao){
		this.descricao = descricao;
	}

	private void setCategoria(String categoria){
		this.categoria = categoria;
	}

	public void setQtdEstoque(int qtdEstoque){
		this.qtdEstoque = qtdEstoque;
	}
	
	public void setPreco(double preco){
		this.preco = preco;
	}

	public int getId(){
		return this.id;
	}

	public String getDescricao(){
		return this.descricao;
	}

	public String getCategoria(){
		return this.categoria;
	}

	public int getQtdEstoque(){
		return this.qtdEstoque;
	}
	
	public double getPreco(){
		return this.preco;
	}
	
	public boolean isNegrito() {
		return negrito;
	}

	public void setNegrito(boolean negrito) {
		this.negrito = negrito;
	}

	public boolean isItalico() {
		return italico;
	}

	public void setItalico(boolean italico) {
		this.italico = italico;
	}

	public String getCor() {
		return cor;
	}

	public void setCor(String cor) {
		this.cor = cor;
	}
}
