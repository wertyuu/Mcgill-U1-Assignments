package DoubleLinkedLists;

public class NoSuchElementException extends Exception {

    public NoSuchElementException() {
	super("Illegal operation. No Such Element at specified location.");
    }
}
