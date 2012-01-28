package SingleLinkedLists;

public class NoSuchElementException extends Exception {

    public NoSuchElementException() {
	super("Illegal operation. There is no Element at the specfied location.");
    }
}
