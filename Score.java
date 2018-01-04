public class Score {
    private int score;

    public Score() {
        this.score = 0;
    }

    public int getScore() {
        return this.score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public void increaseScore() {
        this.score++;
    }

    public void decreaseScore() {
        this.score--;
    }
}
