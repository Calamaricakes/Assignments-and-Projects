package projectPackage;

public class Person{
	private String name;
	private int maximumBooks;
	
	public Person(){
		name = "unknown name";
		maximumBooks = 3;
	}
	
	public String getName(){
		return name;
	}
	
	public void setName(String anyName){
		name = anyName;
	}

	public int getMaximumBooks() {
		return maximumBooks;
	}

	public void setMaximumBooks(int maximumBooks) {
		this.maximumBooks = maximumBooks;
	}
	
	
}

