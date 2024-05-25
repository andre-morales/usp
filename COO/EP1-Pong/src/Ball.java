import java.awt.Color;
import java.awt.Point;
import java.awt.geom.Point2D;

/**
	Esta classe representa a bola usada no jogo. A classe princial do jogo (Pong)
	instancia um objeto deste tipo quando a execução é iniciada.
*/
public class Ball {

	private Point2D.Double start;
	private double cx, cy;
	private double width, height;
	private double speed;
	private double dirX, dirY;
	private double timeDelta;
	private Color color;

	@SuppressWarnings("unused")
	private int fps;
	private int frameCounter;
	private long lastFPS;

	/**
		Construtor da classe Ball. Observe que quem invoca o construtor desta classe define a velocidade da bola 
		(em pixels por millisegundo), mas não define a direção deste movimento. A direção do movimento é determinada 
		aleatóriamente pelo construtor.

		@param cx coordenada x da posição inicial da bola (centro do retangulo que a representa).
		@param cy coordenada y da posição inicial da bola (centro do retangulo que a representa).
		@param width largura do retangulo que representa a bola.
		@param height altura do retangulo que representa a bola.
		@param color cor da bola.
		@param speed velocidade da bola (em pixels por millisegundo).
	*/
	public Ball(double cx, double cy, double width, double height, Color color, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.speed = speed;

		// Reinicia a bola no campo
		start = new Point.Double(cx, cy);
		reset();

		lastFPS = System.currentTimeMillis();
	}

	/**
		Método chamado sempre que a bola precisa ser (re)desenhada.
	*/
	public void draw(){
		GameLib.setColor(color);
		GameLib.fillRect(cx, cy, width, height);
	}

	/**
		Método chamado quando o estado (posição) da bola precisa ser atualizado.
		
		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void update(long delta){
		timeDelta = delta;
		countFPS();

		if (GameLib.isKeyPressed(GameLib.KEY_CONTROL)) {
			reset();
		}
		
		move(false);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.
	
		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/
	public void onPlayerCollision(String playerId){
		// Desfaz a colisão movendo a bola para a posição anterior a colisão
		move(true);

		// Reflete a bola na vertical
		reflect(false);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/
	public void onWallCollision(String wallId){
		// Desfaz a colisão movendo a bola para a posição anterior a colisão
		move(true);

		// Se bateu numa parede do topo ou de baixo, reflete a bola horizontalmente
		if (isWideWall(wallId)) {
			reflect(true);	
		}

		// Se bateu na parede lateral, reflete a bola verticalmente
		if (isTallWall(wallId)){
			reflect(false);
		}
	}

	/**
		Método que verifica se houve colisão da bola com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/
	public boolean checkCollision(Wall wall){
		var wallRect = Box.ofWall(wall);
		var ballRect = Box.ofBall(this);
		boolean collides = wallRect.intersects(ballRect);
		return collides;
	}

	/**
		Método que verifica se houve colisão da bola com um jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/	
	public boolean checkCollision(Player player){
		var playerRect = Box.ofPlayer(player);
		var ballRect = Box.ofBall(this);
		// Se há interseção entre o quadrado da bola e do player
		if(playerRect.intersects(ballRect)) {
			// O jogador 1 está a esquerda, haverá colisão com o player 1 apenas se a bola estiver
			//  vindo da direita.
			if (player.getIndex() == 1) {
				return dirX < 0;
			// O jogador 2 está a direita, deixe a bola passar se ela estiver vindo por trás do
			// jogador.
			} else {
				return dirX > 0;
			}
		}
		return false;
	}

	/** Reflete a bola em relação a uma parede horizontal ou vertical */
	private void reflect(boolean horizontal) {
		if (horizontal) {
			dirY *= -1;
		} else {
			dirX *= -1;
		}
	}

	/** Reinicia a bola no meio do campo com uma direção aleatória */
	private void reset() {
		cx = start.x;
		cy = start.y;

		// Gera um ângulo aleatório de 30 a 45 graus
		double angle = 30 + Math.random() * 15;
		
		// Decide aleatóriamente se a bola será lançada para cima ou para baixo
		boolean upOrDown = randomBool();
		angle = (upOrDown) ? angle : -angle;

		// Decide aleatoriamente se a bola vai para esquerda ou para a direita
		boolean leftOrRight = randomBool();
		angle = (leftOrRight) ? angle : angle + 180;

		// Calcula dirX e dirY no círculo unitário
		dirX = Math.cos(Math.toRadians(angle));
		dirY = Math.sin(Math.toRadians(angle));
	}

	/**
	 * Movimenta a bola na direção atual.
	 * @param reverse Se o movimento deve ser reverso a direção.
	 */
	private void move(boolean reverse) {
		cx += dirX * speed * timeDelta * ((reverse) ? -1 : 1);
		cy += dirY * speed * timeDelta * ((reverse) ? -1 : 1);
	}

	/**
		Método que devolve a coordenada x do centro do retângulo que representa a bola.
		@return o valor double da coordenada x.
	*/
	public double getCx(){
		return cx;
	}

	/**
		Método que devolve a coordenada y do centro do retângulo que representa a bola.
		@return o valor double da coordenada y.
	*/
	public double getCy(){
		return cy;
	}

	/**
	 * Obtém a largura da bola.
	 * @return o valor da largura.
	 */
	public double getWidth() {
		return width;
	}

	/**
	 * Obtém a altura da bola.
	 * @return o valor da altura.
	 */
	public double getHeight() {
		return height;
	}

	/**
		Método que devolve a velocidade da bola.
		@return o valor double da velocidade.
	*/
	public double getSpeed(){
		return speed;
	}

	/** Executa a contagem de FPS */
	private void countFPS() {
		frameCounter++;
		long now = System.currentTimeMillis(); 
		if (now - lastFPS > 1000) {
			fps = frameCounter;
			frameCounter = 0;
			lastFPS = now;
			//System.out.println("FPS: " + fps + " IDELT: " + (1.0 / (timeDelta / 1000.0)));
		}
	}

	/** Gera true/false pseudo-aleatóriamente */
	private static boolean randomBool() {
		return Math.random() > 0.5;
	}

	/** Verifica se o id da parede corresponde a uma parede vertical */
	private static boolean isTallWall(String id) {
		return id.equals("Left") || id.equals("Right");
	}
	
	/** Verifica se o id da parede corresponde a uma parede horizontal */
	private static boolean isWideWall(String id) {
		return id.equals("Top") || id.equals("Bottom");
	}
}