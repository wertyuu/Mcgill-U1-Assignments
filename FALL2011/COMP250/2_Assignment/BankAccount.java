public class BankAccount implements Comparable<BankAccount> {

    String name = "";
    double balance = 0;

    public BankAccount (String s, int n) {
	name = s;
	balance = n;
    }

    public int compareTo(BankAccount a) {
	if (balance < a.balance)
	    return -1;
	if (balance > a.balance)
	    return 1;
	return 0;
    }
    
    public void print() {
	System.out.println(name + " " + balance);
    }

    public static void main(String[] args) {

	BankAccount[] a = new BankAccount[5];
	a[0] = new BankAccount("B", 5);
	a[1] = new BankAccount("A", 7);
	a[2] = new BankAccount("C", 2);
	a[3] = new BankAccount("D", 3);
	a[4] = new BankAccount("Z", 8);

	MergeSort.sort(a);

	for (int i = 0; i < a.length; i++)
	    a[i].print();
    }
}