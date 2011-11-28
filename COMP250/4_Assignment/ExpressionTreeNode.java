import java.lang.Math.*;

public class ExpressionTreeNode {

	static int VALUE = 0;
	static int FUNCTION = 1;
	static int OPERATOR = 2;
	
	private static int max(int i, int j) {
		if (i > j) return i;
		return j;
	}
	
	private static boolean isOperator(char c) {
		return (c=='+' || c=='-' || c=='*' || c=='/');
	}
	
	private static boolean isFunction(char c) {
		return(c=='c' || c=='s' || c=='e');
	}

    private String value;
    private int type;
    private ExpressionTreeNode leftChild, rightChild;
    
    /* Basic access methods */
    public String getValue() { 
		return value; 
	}
	
	public int getType() {
		return type;
	}

    public ExpressionTreeNode getLeftChild() { 
		return leftChild; 
	}

    public ExpressionTreeNode getRightChild() { 
		return rightChild; 
	}

    /* Basic setting methods */ 
    public void setValue(String s) { 
		value = s; 
	}
    
	// sets type of a node, thrown exception if the argument is invalid
	public void setType(int t) throws ExpressionTreeNodeException {
		if (t != ExpressionTreeNode.VALUE && t != ExpressionTreeNode.FUNCTION && t != ExpressionTreeNode.OPERATOR)
			throw new ExpressionTreeNodeException("Invalid type in set method");
		type = t;
	}
	
    // sets the left child of this node to n
    public void setLeftChild(ExpressionTreeNode n) { 
        leftChild = n; 
    }
    
    // sets the right child of this node to n
    public void setRightChild(ExpressionTreeNode n) { 
        rightChild = n; 
    }
	
	// Trivial consturctoor
	public ExpressionTreeNode() {
		value = "";
		type = -1;
		leftChild = null;
		rightChild = null;
	}
    

    // Returns the root of the tree describing the expression s
	// Note: It does not do a rigorous check for errors in the string!!!
    public ExpressionTreeNode(String s) throws ExpressionTreeNodeException {
		int i, parCount;
		leftChild = null;
		
		//System.out.println("Constructor: "+s);
				
		// assume that the string starts with a parenthesis
		// we will scan to the end of the paren and look at what follows
		// if the string is done, we have to construct the stuff inside the parenthesis
		// if it is not done, we have an operator node, and will have to construct on the left and right as appropriate
		i = 0;
		if (s.charAt(i) != '(') 
			throw new ExpressionTreeNodeException("String should start with an open parentheses");
		parCount = 1;
		i++;
		while (i < s.length() && parCount > 0) {
			if ( s.charAt(i) == '(' ) parCount++;
			if ( s.charAt(i) == ')' ) parCount--;
			i++;
		}
		if (parCount != 0)
			throw new ExpressionTreeNodeException("Parentheses are not balanced!");
		if (i == s.length()) {
			// we have no operator to follow
			// first, figure out what might be in the parentheses
			// check if this might be a variable or a value
			if (s.length() == 3) {
				// this must be an x or a digit
				value = s.substring(1,2);
				type = ExpressionTreeNode.VALUE;
				leftChild = null;
				rightChild = null;
				return;
			} 
			// check if the inner substring starts with a parentheses; if so, strip the outer parens
			if (s.charAt(1) == '(') {
				ExpressionTreeNode result = new ExpressionTreeNode(s.substring(1,s.length()-1));
				value = result.getValue();
				type = result.getType();
				leftChild = result.getLeftChild();
				rightChild = result.getRightChild();
				return;
			}
			// the only remaining possibility is that we have a function
			// so make a function node, and call connstructor for the argument
			if (!ExpressionTreeNode.isFunction(s.charAt(1)))
				throw new ExpressionTreeNodeException("Expecting function at position "+i);
			value = s.substring(1,4);
			type = ExpressionTreeNode.FUNCTION;
			leftChild = new ExpressionTreeNode(s.substring(4,s.length()-1));
			rightChild = null;
		} else {
			// next character should be an operator
			// System.out.println("Index: "+i);
			// System.out.println("Operator: "+s.charAt(i));
			// System.out.println("Left side: "+s.substring(0,i));
			// System.out.println("Right side: "+s.substring(i+1,s.length()));
			if (!ExpressionTreeNode.isOperator(s.charAt(i)))
				throw new ExpressionTreeNodeException("Expecting operator at position "+i);
			value = s.substring(i,i+1);
			type = ExpressionTreeNode.OPERATOR;
			leftChild = new ExpressionTreeNode(s.substring(0,i));
			rightChild = new ExpressionTreeNode(s.substring(i+1,s.length()));
		}
	}
				
    // Returns a copy of the subtree rooted at this node.
    public ExpressionTreeNode deepCopy() throws ExpressionTreeNodeException {
        ExpressionTreeNode n = new ExpressionTreeNode();
        n.setValue( getValue() );
		n.setType( getType());
        if ( getLeftChild()!=null ) n.setLeftChild( getLeftChild().deepCopy() );
        if ( getRightChild()!=null ) n.setRightChild( getRightChild().deepCopy() );
        return n;
    }
    
    // Returns a String representing the tree rooted at the current node 
	public String toString() {
		String result="";
		
		if (type == ExpressionTreeNode.VALUE)
			result = value;
		else if (type == ExpressionTreeNode.FUNCTION) 
			result = value + "(" + leftChild.toString() + ")";
		else
			result =  "(" + leftChild.toString() + ")" + value +  "(" + rightChild.toString() + ")";
		return result;
    } 


public double evaluate(double x) throws ExpressionTreeNodeException {

 // Write your code here
}


    /* Returns the root of a new expression tree representing the derivative of the
    expression represented by the tree rooted at the node on which it is called ***/
    public ExpressionTreeNode differentiate() {
		// WRITE YOUR CODE HERE

		return null; // remove this
    }
 
	public ExpressionTreeNode add (ExpressionTreeNode t) {
	// Write your code here	
	}
 
	
	
	public static void main(String[] args) throws ExpressionTreeNodeException {
		String s;
		s ="((x)+(4))*(cos(x))";		
		ExpressionTreeNode n = new ExpressionTreeNode(s);		
		System.out.println(n.toString());
		ExpressionTreeNode ss = new ExpressionTreeNode("(x)");
		System.out.println(ss.evaluate(0));
		
	}

}
 
class ExpressionTreeNodeException extends Exception {
	
	ExpressionTreeNodeException(String s) {
		super(s);
	}
}
