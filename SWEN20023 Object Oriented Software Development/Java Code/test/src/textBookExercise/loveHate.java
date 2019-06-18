package textBookExercise;

public class loveHate {
	public static void main(String[] args){
		String sentence = "I hate made up sentences";
		int indexOfHate = sentence.indexOf("hate");
		sentence =  sentence.substring(0,indexOfHate) + "love" + sentence.substring(indexOfHate + "hate".length());	
		System.out.println(sentence);
	}
}
