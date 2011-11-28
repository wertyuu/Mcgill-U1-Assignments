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

    if ( type == ExpressionTreeNode.VALUE ) {
        if ( value.charAt(0) == 'x' ) return x;
        else return (double)Integer.parseInt(value);
    } else if ( type == ExpressionTreeNode.FUNCTION ) {
        if ( value.charAt(0) == 'c' ) {
            return Math.cos( getLeftChild().evaluate(x) );
        } else if ( value.charAt(0) == 's' ) {
            return Math.sin( getLeftChild().evaluate(x) );
        } else if ( value.charAt(0) == 'e' ) {
            // only possibility left is exp function
            return Math.exp( getLeftChild().evaluate(x) );
        } else {
            throw new ExpressionTreeNodeException("Invalid Function; should be either cos, sin or exp");
        }
    } else {
        // only possibility left is an operator
        if ( value.charAt(0) == '+' ) {
            return ( getLeftChild().evaluate(x) + getRightChild().evaluate(x) );
        } else if ( value.charAt(0) == '-' ) {
            return ( getLeftChild().evaluate(x) - getRightChild().evaluate(x) );
        } else if ( value.charAt(0) == '*' ) {
            return ( getLeftChild().evaluate(x) * getRightChild().evaluate(x) );
        } else if ( value.charAt(0) == '/' ) {
            // only possibility left is '/' operator
            return ( getLeftChild().evaluate(x) / getRightChild().evaluate(x) );
        } else {
            throw new ExpressionTreeNodeException("Invalid operator; should be either +, -, * or /");
        }
    }
}


    /* Returns the root of a new expression tree representing the derivative of the
    expression represented by the tree rooted at the node on which it is called ***/
    public ExpressionTreeNode differentiate() throws ExpressionTreeNodeException {
        if ( type == ExpressionTreeNode.VALUE ) {
            if ( value.charAt(0) == 'x' ) {
                ExpressionTreeNode result = new ExpressionTreeNode();
                result.setValue("1");
                result.setType(0);
                return result;
            } else {
                ExpressionTreeNode result = new ExpressionTreeNode();
                result.setValue("0");
                result.setType(0);
                return result;
            }
        } else if ( type == ExpressionTreeNode.FUNCTION ) {
            if ( value.charAt(0) == 's' ) {
                // d/dx sin = cos
                ExpressionTreeNode result = deepCopy();
                result.setValue("cos");
                result.setLeftChild( getLeftChild().differentiate() );
                return result;
            } else if ( value.charAt(0) == 'c' ) {
                // d/dx cos = -sin
                ExpressionTreeNode result = new ExpressionTreeNode();
                ExpressionTreeNode child = new ExpressionTreeNode();
                ExpressionTreeNode sin = new ExpressionTreeNode();
                result.setValue("-");
                result.setType(2);
                child.setValue("0");
                child.setType(0);
                result.setLeftChild(child);
                sin.setValue("sin");
                sin.setType(1);
                sin.setLeftChild( getLeftChild().differentiate() );
                result.setRightChild(sin);
                return result;
            } else {
                // Only possibility is exp
                ExpressionTreeNode result = deepCopy();
                return result;
            }
        } else { // if ( type == ExpressionTreeNode.OPERATOR ) {
            // Only possibility is an Operator
            ExpressionTreeNode result = new ExpressionTreeNode();
            result.setValue( getValue() );
            result.setType(2);
            result.setLeftChild( getLeftChild().differentiate() );
            result.setRightChild( getRightChild().differentiate() );
            return result;
        }
    }
 
	public ExpressionTreeNode add (ExpressionTreeNode t) throws ExpressionTreeNodeException {
	// Write your code here	
            ExpressionTreeNode child1 = t.deepCopy();
            ExpressionTreeNode child2 = deepCopy();
            ExpressionTreeNode result = new ExpressionTreeNode();
            result.setType(2);
            result.setValue("+");
            result.setLeftChild(child1);
            result.setRightChild(child2);
            return result;
	}
 
	
	
	public static void main(String[] args) throws ExpressionTreeNodeException {
		String s;
		s ="((x)+(4))*(cos(x))";		
                String sss = "((2)-(sin(x)))*(exp(x)+(6))"; 
		ExpressionTreeNode n = new ExpressionTreeNode(s);		
		System.out.println(n.toString());
		ExpressionTreeNode nn = new ExpressionTreeNode("(x)");
		System.out.println(n.evaluate(0));
                
                ExpressionTreeNode nnn = new ExpressionTreeNode(sss);
                System.out.println(nnn.toString());
                System.out.println(nnn.evaluate(0));

                ExpressionTreeNode nnnn = n.add(nnn);
                System.out.println(nnnn.toString());
                System.out.println(nnnn.evaluate(0));

                System.out.println(n.differentiate().toString());
		
                System.out.println(nn.differentiate().toString());
	}

}
 
class ExpressionTreeNodeException extends Exception {
	
	ExpressionTreeNodeException(String s) {
		super(s);
	}
}
