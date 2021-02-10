/**
 * @author Stergios Moumtzis
 */
public class Image_Question extends Text_Question{

    String picName;
    /**
     * Fields:
     * @param category Indicates the question`s category
     * @param question Indicates the question itself
     * @param a1       indicates the first possible answer
     * @param a2       indicates the second possible answer
     * @param a3       indicates the third possible answer
     * @param a4       indicates the fourth possible answer
     * @param correct  indicates the correct answer of the current question(1 or 2 or 3 or 4)
     * @param picName  indicates the filename of the picture
     */
    public Image_Question(String category, String question, String a1, String a2, String a3, String a4, int correct,String picName) {
        super(category, question, a1, a2, a3, a4, correct);
        this.picName = picName;

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

    public String getSpecial() { return picName; }
}