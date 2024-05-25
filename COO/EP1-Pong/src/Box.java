import java.awt.geom.Rectangle2D;

/**
 * Classe que representa um retângulo qualquer no jogo. Usado na detecção de colisões.
 */
public class Box {
	public final double x, y, width, height;
	private final Rectangle2D.Double rect;
	
	/**
	 * Instancia um retângulo com um centro e dimensões
	 * @param cx Coordenada X do centro do retângulo.
	 * @param cy Coordenada Y do centro do retângulo.
	 * @param w Largura do retângulo.
	 * @param h Altura do retângulo.
	 */
	public Box(double cx, double cy, double w, double h) {
		x = cx - w / 2;
		y = cy - h / 2;
		width = w;
		height = h;
		rect = new Rectangle2D.Double(x, y, width, height);
	}

	/**
	 * Obtém um retângulo representando uma parede do jogo.
	 * @param wall A parede em questão.
	 * @return Um retângulo com as mesmas dimensões da parede.
	 */
	public static Box ofWall(Wall wall) {
		return new Box(wall.getCx(), wall.getCy(), wall.getWidth(), wall.getHeight());
	}

	/**
	 * Obtém um retângulo representando a área de contato de um dos jogadores.
	 * @param player Uma instância de um jogador.
	 * @return Um retângulo de dimensões equivalentes ao do jogador.
	 */
	public static Box ofPlayer(Player player) {
		return new Box(player.getCx(), player.getCy(), player.getWidth(), player.getHeight());
	}

	/**
	 * Obtém um retângulo representando a área de contato da bola do jogo.
	 * @param ball A instância da bola.
	 * @return Um retângulo de dimensões equivalentes a da bola.
	 */
	public static Box ofBall(Ball ball) {
		return new Box(ball.getCx(), ball.getCy(), ball.getWidth(), ball.getHeight());
	}

	/**
	 * Verifica se esse retângulo possui interseção com outro.
	 * @param box Outro retângulo.
	 * @return Verdadeiro se há interseção, falso caso contrário.
	 */
	public boolean intersects(Box box) {
		return rect.intersects(box.rect);
	}
}
