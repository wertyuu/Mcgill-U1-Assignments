package DoubleLinkedLists;

class Node {

    Object content;
    Node next;
    Node prev;

    public Node (Object o) {
	content = o;
	next = null;
	prev = null;
    }
}