public class Player {
    private char symbol;
    private Score score;

    public Player(char symbol) {
        this.symbol = symbol;
        this.score = new Score();
    }

    public char getSymbol() {
        return symbol;
    }

    public int getScore() {
        return this.score.getScore();
    }

    public void setScore(int score) {
        this.score.setScore(score);
    }

    public void increaseScore() {
        this.score.increaseScore();
    }

    public void decreaseScore() {
        this.score.decreaseScore();
    }

    public int compare(Player player) {
        return Integer.compare(this.score.getScore(), player.getScore());
    }
}
