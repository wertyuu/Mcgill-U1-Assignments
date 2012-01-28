package DoubleLinkedLists;

public class DoubleLinkedList {

    Node head;
    Node tail;

    public DoubleLinkedList() {
	head = null;
	tail = null;
    }

    public boolean isEmpty() {
	return (head == null);
    }

    /*
     * Methods written for the assignment
     * Jonathan Fokkan
     * 260447938
     * */
    public Object removeBefore(Object o) throws EmptyListException, NoSuchElementException {
        
	if (head == null) throw new EmptyListException();
	
        // If the element does not exist throw exception
        if ( head.content.equals(o) || !find(o) ) throw new NoSuchElementException();

        // If the object matches the second element cut the head off
        if ( head.next.content.equals(o) ) {
            return removeFirst();
        }

        Node crt = head.next.next;

        while ( !crt.content.equals(o) ) {
            crt = crt.next;
        }

        Object result = crt.prev.content;
        crt.prev.prev.next = crt;
        crt.prev = crt.prev.prev;
        return result;

    }

    public Object removeAfter(Object o) throws EmptyListException, NoSuchElementException {
        
	if (head == null) throw new EmptyListException();
	
        if ( tail.content.equals(o) || !find(o) ) throw new NoSuchElementException();

        // If the element matches the element before tail. RemoveLast.
        if ( tail.prev.content.equals(o) ) {
            return removeLast();
        }

        Node crt = head;

        while ( !crt.content.equals(o) ) {
            crt = crt.next;
        }

        Object result = crt.next.content;
        crt.next.next.prev = crt;
        crt.next = crt.next.next;
        return result;
    }

    // Method for inserting an object in the first position of a list
    public void insertFirst(Object o) {
	// Pack o into a Node 
	Node n = new Node(o);

	// put n at the beginning of the list
	n.next = head;

	if (head != null)
	    head.prev = n;

	// and modify the head of the list
	head = n;

	// make sure the tail is correct too
	if (tail == null)
	    tail = n;
    }

    // Method for inserting an object in the last position of a list                                       
    // Note that this is now O(1), as opposed to O(n) for the single linked list
    public void insertLast(Object o) {
	// Pack o into a Node
	Node n = new Node(o);

	// If the list is empty, we simply have to change head and tail                     
	if (head == null) {
	    head = n;
            tail = n;
            return;
	}

	// If the list is not empty, we need to change the tail
	tail.next = n;
	n.prev = tail;
	tail = tail.next;
    }


    // Method for printing the entire list (demonstrates traversal)
    // Note that we could also traverse the list backwards
    public void print() {
	for (Node crt = head; crt != null; crt = crt.next) 
	    System.out.println(crt.content);
    }

    // Method for removing the first element in the list; the object is returned
    // Note that this is O(1), since we have a sequence of primitive operations
    public Object removeFirst() throws EmptyListException {

	if (head == null) throw new EmptyListException();
	
	// Put a "finger" on the current head
	Node crt = head;

	// Move the head to the appropriate spot
	head = head.next;

	// Change the tail if need be too
	if (head == null)
	    tail = null;

	// Figure out what we need to return
	Object o = crt.content;

	// Clear out all pointer - the garbage collector will take care of this area in memory
	crt.content = null;
	crt.next = null;
	head.prev = null;

	// And we're done
	return o;
    }


    // Method for removing the last element in the list; the object is returned
    // This is O(1) as well
    public Object removeLast() throws EmptyListException {
   
	if (head == null) throw new EmptyListException();

	Object o;

	// If there is only one element, we need to modify the head and tail of the list
	if (head.next == null) {
	    o = head.content;
	    head.content = null;
	    head = null;
	    tail = null;
	    return o;
	}

	// Otherwise, we need to cut off the element right before the tail

	// We need to go to the second-to-last element
	Node crt = tail.prev;
	
	// Retrieve the object we want
	o = tail.content;
	
	// Remove all references that are not needed
	tail.content = null;
	crt.next = null;
	tail = crt;

	// And we're done
	return o;
    }

    // Method for finding an object in a list; returns true if the object is found
    public boolean find (Object o) {
	if (head == null) return false;
	
	// We need an index in the list
	for (Node crt = head; crt != null; crt = crt.next) {
	    if (o.equals(crt.content)) return true;
	}
	return false;
    }
}
