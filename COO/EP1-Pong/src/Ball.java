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
	private double direction;
	private double dirX, dirY;
	private Color color;
	private int frameCounter;
	private int fps;
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
		start = new Point.Double(cx, cy);
		this.width = width;
		this.height = height;
		this.color = color;
		this.speed = speed * 0.5;

		// Gera um ângulo aleatório
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
		cx += dirX * speed * delta;
		cy += dirY * speed * delta;
		//countFPS(delta);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.
	
		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/
	public void onPlayerCollision(String playerId){
		reflect(false);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/
	public void onWallCollision(String wallId){
		// Se bateu numa parede do topo ou de baixo, reflita a direção da bola
		if (isWideWall(wallId)) {
			reflect(true);	
		}

		// Se bateu na parede lateral, reflete a bola
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

	public double getWidth() {
		return width;
	}

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

	@SuppressWarnings("unused")
	private void countFPS(double delta) {
		frameCounter++;
		long now = System.currentTimeMillis(); 
		if (now - lastFPS > 1000) {
			fps = frameCounter;
			frameCounter = 0;
			lastFPS = now;
			System.out.println("FPS: " + fps + " IDELT: " + (1.0 / (delta / 1000.0)));
		}
	}

	private static boolean isTallWall(String id) {
		return id.equals("Left") || id.equals("Right");
	}

	private static boolean isWideWall(String id) {
		return id.equals("Top") || id.equals("Bottom");
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

		boolean randomBool = Math.random() > 0.5;
		double angle = (Math.random() - 0.5) * 45;
		direction = (randomBool) ? angle : 180 - angle;
		dirX = Math.cos(direction);
		dirY = Math.sin(direction);
		//direction = 300;
	}
}