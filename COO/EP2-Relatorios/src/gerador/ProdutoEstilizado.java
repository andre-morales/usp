package gerador;

public class ProdutoEstilizado extends ProdutoPadrao {
	private boolean negrito;
	private boolean italico;
	private String cor;

	public ProdutoEstilizado(int id, String descricao, String categoria, int qtdEstoque, double preco, boolean negrito, boolean italico, String cor){
		super(id, descricao, categoria, qtdEstoque, preco);
		setNegrito(negrito);
		setItalico(italico);
		setCor(cor);
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
