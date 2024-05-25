import java.awt.Color;
import java.util.Map;
import java.util.HashMap;

/**
	Esta classe representa os jogadores (players) do jogo. A classe princial do jogo (Pong)
	instancia dois objetos deste tipo quando a execução é iniciada.
*/
public class Player {
	private static int playerIndexCounter = 0;
	private static Map<String, Player> players = new HashMap<>();

	private double cx, cy;
	private double width, height;
	private Color color;
	private String id;
	private int index;
	private double speed;
	private double[] bounds;
	/**
		Construtor da classe Player.

		@param cx coordenada x da posição inicial do player (centro do retangulo que o representa).
		@param cy coordenada y da posição inicial do player (centro do retangulo que o representa).
		@param width largura do retangulo que representa o player.
		@param height altura do retangulo que representa o player.
		@param color cor do player.
		@param id uma string que identifica o player
		@param v_limit um array de double contendo dois valores (em pixels) que determinam os limites verticais da área útil da quadra.   
		@param speed velocidade do movimento vertical do player (em pixels por millisegundo).
	*/
	public Player(double cx, double cy, double width, double height, Color color, String id, double[] v_limit, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.index = ++playerIndexCounter;
		this.id = id;
		this.speed = speed;
		this.bounds = v_limit;

		players.put(id, this);
	}

	/**
		Método chamado sempre que o player precisa ser (re)desenhado.
	*/
	public void draw(){
		GameLib.setColor(color);
		GameLib.fillRect(cx, cy, width, height);
	}

	/**
		Método chamado quando se deseja mover o player para cima. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para cima estiver pressionada.

		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveUp(long delta){
		cy -= speed * delta;
		boundY();
	}

	/**
		Método chamado quando se deseja mover o player para baixo. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para baixo estiver pressionada.

		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveDown(long delta){
		cy += speed * delta;
		boundY();
	}

	/**
		Método que devolve a string de identificação do player.
		@return a String de indentificação.
	*/
	public String getId() { 
		return id; 
	}

	/**
	 * Obtém o índice desse jogador.
	 * @return Um inteiro 1 para o jogador da esquerda, 2 para o da direita.
	 */
	public int getIndex() {
		return index;
	}

	/**
	 * Obtém a cor do jogador.
	 * @return A cor.
	 */
	public Color getColor() {
		return color;
	}

	/**
		Método que devolve a largura do retangulo que representa o player.
		@return um double com o valor da largura.
	*/
	public double getWidth() { 
		return width; 
	}

	/**
		Método que devolve a algura do retangulo que representa o player.
		@return um double com o valor da altura.
	*/
	public double getHeight() { 
		return height;
	}

	/**
		Método que devolve a coordenada x do centro do retangulo que representa o player.
		@return o valor double da coordenada x.
	*/
	public double getCx() { 
		return cx;
	}

	/**
		Método que devolve a coordenada y do centro do retangulo que representa o player.
		@return o valor double da coordenada y.
	*/
	public double getCy() { 
		return cy;
	}

	/** Limita a posição Y do jogador dentro da caixa */
	private void boundY() {
		double minY = bounds[0] + height / 2;
		double maxY = bounds[1] - height / 2;
		if (cy < minY) cy = minY;
		if (cy > maxY) cy = maxY;
	}

	/**
	 * Obtém o player associado ao nome.
	 * @param playerId O nome do player que foi passado para o construtor de Player.
	 * @return Uma instância de player associada a este nome, ou null se não houver player com este nome.
	 */
	public static Player getById(String playerId) {
		return players.get(playerId);
	}
}
