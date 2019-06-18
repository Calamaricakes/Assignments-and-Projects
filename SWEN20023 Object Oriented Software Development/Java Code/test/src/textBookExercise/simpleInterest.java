package textBookExercise;

public class simpleInterest {
	public static void main(String[] args){
		double principle = 1000;
		double interestRate = 0.05;
		int numberOfYears = 5;
		double afterInterestPrinciple;
		afterInterestPrinciple = principle * interestRate * numberOfYears;
		System.out.println("Principle after interest = " + afterInterestPrinciple);
	}
}
