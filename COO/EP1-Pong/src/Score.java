/**
	Esta classe representa um placar no jogo. A classe princial do jogo (Pong)
	instancia dois objeto deste tipo, cada um responsável por gerenciar a pontuação
	de um player, quando a execução é iniciada.
*/
public class Score {
	private Player player;
	private String playerName;
	private int score;

	/**
		Construtor da classe Score.

		@param playerId uma string que identifica o player ao qual este placar está associado.
	*/
	public Score(String playerId){
		this.playerName = playerId;
		player = Player.getById(playerName);
	}

	/**
		Método de desenho do placar.
	*/
	public void draw(){
		// Player 1 a esquerda, player 2 a direita
		if (player.getIndex() == 1) {
			GameLib.setColor(player.getColor());
			GameLib.drawText(playerName + ": " + score, 70, GameLib.ALIGN_LEFT);	
		} else {
			GameLib.setColor(player.getColor());
			GameLib.drawText(playerName + ": " + score, 70, GameLib.ALIGN_RIGHT);		
		}			
	}

	/**
		Método que incrementa em 1 unidade a contagem de pontos.
	*/
	public void inc(){
		score++;
	}

	/**
		Método que devolve a contagem de pontos mantida pelo placar.

		@return o valor inteiro referente ao total de pontos.
	*/
	public int getScore(){
		return score;
	}
}
