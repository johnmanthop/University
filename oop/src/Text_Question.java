import java.util.Random;

/**
 * @author Stergios Moumtzis
 */

class Text_Question implements Question{

    String category;
    String question;
    String[] answers;
    int correct;

    /**
     * Fields:
     * @param category Indicates the question`s category
     * @param question Indicates the question itself
     * @param a1 indicates the first possible answer
     * @param a2 indicates the second possible answer
     * @param a3 indicates the third possible answer
     * @param a4 indicates the fourth possible answer
     * @param correct Indicates the correct answer of the current question(1 or 2 or 3 or 4)
     */
    public Text_Question(String category,String question,String a1,String a2,String a3,String a4,int correct)
    {
        this.category = category;
        this.question = question;
        this.answers = new String[4];
        this.answers[0] = a1;
        this.answers[1] = a2;
        this.answers[2] = a3;
        this.answers[3] = a4;
        this.correct = correct;
        shuffle();
    }

    /**
     * Method used to shuffle the answers array
     */
    private void shuffle() {
        Random generator = new Random();
        int correctPoss = correct-1;
        String correctAnswer = answers[correctPoss];
        for (int i = 0; i < 3; ++i) {
            int randomPos = generator.nextInt(4);
            String temp = answers[i];
            answers[i] = answers[randomPos];
            answers[randomPos] = temp;
        }
        for(int i = 0; i < 4; ++i){
            if(correctAnswer.compareTo(answers[i]) == 0){
                correct = i+1;
                break;
            }
        }
    }
    @Override
    public String getCategory() {
        return category;
    }

    @Override
    public String getQuestion() {
        return question;
    }

    @Override
    public String[] getAnswers() {
        return answers;
    }

    @Override
    public int getCorrect() {
        return correct;
    }

    @Override
    public String getSpecial() {
        return null;
    }
}

