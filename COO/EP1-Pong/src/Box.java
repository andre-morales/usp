import java.awt.geom.Rectangle2D;

public class Box {
	private Rectangle2D.Double rect;
	
	public Box(double cx, double cy, double w, double h) {
		rect = new Rectangle2D.Double(cx - w / 2, cy - h / 2, w, h);
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
