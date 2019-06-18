import java.utils.Scanner;

public class Program{
	public static void main{

		Scanner scan = new Scanner(System.In);
		int original, new, other;

		while(scan.hasNext()){
			int input = scan.nextInt();
			
			if(input < 0 || input > 2){
				System.out.println("Invalid input");
				break;	
			}
			else{
				if(input == 0){
					original++;			
				}
				else if( input == 1 ){
					new++;
				}
				else{
					other++;
				}
			}
		}
		scan.close();
		System.out.format("Original Trilogy: %d\nNew Trilogy: %d\nOther Trilogy: %d", original, new, other);
	}
}