/**
	Esta classe representa um placar no jogo. A classe princial do jogo (Pong)
	instancia dois objeto deste tipo, cada um responsável por gerenciar a pontuação
	de um player, quando a execução é iniciada.
*/

public class Score {
	private static int playerIndexCounter = 0;
	private int playerId;
	private String playerName;
	private int score;

	/**
		Construtor da classe Score.

		@param playerId uma string que identifica o player ao qual este placar está associado.
	*/
	public Score(String playerId){
		// O primeiro player a ser criado será o 1, o segundo o 2, etc.
		++playerIndexCounter;
		this.playerId = playerIndexCounter;
		this.playerName = playerId;
	}

	/**
		Método de desenho do placar.
	*/
	public void draw(){
		// Player 1 a esquerda, player 2 a direita
		int alignment = GameLib.ALIGN_LEFT;
		if (playerId == 2 || playerName.equals("Player 2")) {
			alignment = GameLib.ALIGN_RIGHT;
		}

		GameLib.drawText("" + score, 70, alignment);			
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
