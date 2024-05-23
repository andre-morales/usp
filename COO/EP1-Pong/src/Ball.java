import java.awt.Color;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

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
		this.speed = speed;

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
		double radsAngle = Math.toRadians(direction);
		cx += Math.cos(radsAngle) * speed * delta;
		cy += Math.sin(radsAngle) * speed * delta;
		
		//countFPS(delta);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.
	
		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/
	public void onPlayerCollision(String playerId){

	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/
	public void onWallCollision(String wallId){

	}

	/**
		Método que verifica se houve colisão da bola com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/
	public boolean checkCollision(Wall wall){
		var wallRect = getWallRect(wall);
		var ballRect = getBallRect();
		boolean collides = boxCollide(wallRect, ballRect);
		if (collides) {
			if (isWideWall(wall)) {
				reflect(true);	
			}

			if (isTallWall(wall)){
				reset();
			}
		}
		return collides;
	}

	/**
		Método que verifica se houve colisão da bola com um jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/	
	public boolean checkCollision(Player player){
		var playerRect = getPlayerRect(player);
		var ballRect = getBallRect();
		boolean collides = boxCollide(playerRect, ballRect);
		if (collides) {
			reflect(false);
		}
		return collides;
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
		Método que devolve a velocidade da bola.
		@return o valor double da velocidade.

	*/
	public double getSpeed(){
		return speed;
	}

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

	private static boolean isTallWall(Wall wall) {
		var id = wall.getId();
		return id.equals("Left") || id.equals("Right");
	}

	private static boolean isWideWall(Wall wall) {
		var id = wall.getId();
		return id.equals("Top") || id.equals("Bottom");
	}

	private void reflect(boolean horizontal) {
		if (horizontal) {
			direction = 360 - direction;
		} else {
			direction = 180 - direction;
		}
	}

	private void reset() {
		cx = start.x;
		cy = start.y;
		direction = Math.random() * 360;
		//direction = 300;
	}

	private static Rectangle2D getWallRect(Wall wall) {
		double cx_ = wall.getCx() - wall.getWidth() / 2;
		double cy_ = wall.getCy() - wall.getHeight() / 2;
		return new Rectangle2D.Double(cx_, cy_, wall.getWidth(), wall.getHeight());
	}

	private Rectangle2D getBallRect() {
		double x = cx - width / 2;
		double y = cy - height / 2;
		return new Rectangle2D.Double(x, y, width, height);
	}

	private Rectangle2D getPlayerRect(Player player) {
		double cx_ = player.getCx() - player.getWidth() / 2;
		double cy_ = player.getCy() - player.getHeight() / 2;
		return new Rectangle2D.Double(cx_, cy_, player.getWidth(), player.getHeight());
	}

	/** Verifica se dois retângulos possuem interseção */
	private static boolean boxCollide(Rectangle2D A, Rectangle2D B) {
		return A.intersects(B);
		
	}

	/*public static class Square extends Rectangle2D.Double {
		private Rectangle2D.Double rect;

		public Square(double cx, double cy, double w, double h) {
			rect = new Rectangle2D.Double(cx - w / 2, cy - h / 2, w, h);
		}
	}*/
}
