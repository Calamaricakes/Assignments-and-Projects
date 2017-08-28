package textBookExercise;

public class OverloadingMultiType {
	
	public static boolean testMethod(boolean input){
		return !input;
	}
	
	public static int testMethod(int input){
		return input*input;
	}
	
	public static double testMethod(double input){
		return (int) input ;
	}
	
	public static String testMethod(String input){
		return input.toUpperCase();
	}
	
	public static void main(String[] args){
		System.out.println(testMethod(true));
		System.out.println(testMethod(2));
		System.out.println(testMethod(12.50));
		System.out.println(testMethod("manly man man"));

	}
}
