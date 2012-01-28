import SingleLinkedLists.*;

public class TestSingleLinkedList {
    
    public static void main(String[] args) {
	
	SingleLinkedList l = new SingleLinkedList();
	l.insertFirst("Ann");
	System.out.println("List after inserting Ann");
	l.print();

	l.insertFirst("Bob");
        System.out.println("List after inserting Bob");
	l.print();

	l.insertLast("Cathy");
        System.out.println("List after inserting Cathy last");
	l.print();

	l.insertLast("Tom");
        System.out.println("List after inserting Tom last");
	l.print();
        
	l.insertLast("Frank");
        System.out.println("List after inserting Frank last");
	l.print();
        
	try{
	    System.out.println("Removed element after Bob: " + l.removeAfter("Bob"));
	    System.out.println("List after removal: ");
	    l.print();
	} catch (EmptyListException e) {
	    System.out.println(e);
	} catch (NoSuchElementException e) {
            System.out.println(e);
        }

        /*
	try{
	    System.out.println("Removed element before Frank: " + l.removeBefore("Frank"));
	    System.out.println("List after removal: ");
	    l.print();
	} catch (EmptyListException e) {
	    System.out.println(e);
	} catch (NoSuchElementException e) {
            System.out.println(e);
        }
        */

        /*
	try{
	    System.out.println("Removed last element: " + l.removeLast());
	    System.out.println("List after removal: ");
	    l.print();
	} catch (EmptyListException e) {
	    System.out.println(e);
	}

	System.out.println("Is Bob still in the list?");
	System.out.println(l.find("Bob"));

        try{
            System.out.println("Removed first element: " + l.removeFirst());
            System.out.println("List after removal: ");
            l.print();
        } catch (EmptyListException e) {
            System.out.println(e);
        }

	System.out.println("Is Bob still in the list?");
	System.out.println(l.find("Bob"));
    */
    }

}
