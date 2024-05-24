import java.awt.geom.Rectangle2D;

public class Box {
	public final double x, y, width, height;
	private final Rectangle2D.Double rect;
	
	public Box(double cx, double cy, double w, double h) {
		x = cx - w / 2;
		y = cy - h / 2;
		width = w;
		height = h;
		rect = new Rectangle2D.Double(x, y, width, height);
	}

	public static Box ofWall(Wall wall) {
		return new Box(wall.getCx(), wall.getCy(), wall.getWidth(), wall.getHeight());
	}

	public static Box ofPlayer(Player player) {
		return new Box(player.getCx(), player.getCy(), player.getWidth(), player.getHeight());
	}

	public static Box ofBall(Ball ball) {
		return new Box(ball.getCx(), ball.getCy(), ball.getWidth(), ball.getHeight());
	}

	/** Verifica se dois retângulos possuem interseção */
	public boolean intersects(Box box) {
		return rect.intersects(box.rect);
	}
}
