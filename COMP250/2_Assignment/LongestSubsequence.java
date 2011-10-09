import java.util.Arrays;

public class LongestSubsequence {

    public static int LongestSubsequence (int[] a) {
	// your code goes here
	// you can define other functions, if you want
        return LndS(a,0,a.length-1);
    }

    public static int LndS (int[] a, int p, int q) {
        int m = (p + q) / 2;

        if ((q - p) < 1) {
            return 1;
        } else {
            int i = LndS(a,p,m);
            int j = LndS(a,m+1,q);

            if (a[m] <= a[m+1]) {
                return i + j;
            } else {
                return Math.max(i,j);
            }
        }
    }

    public static void main (String[] args) {
	// here you should declare and initialize an array, and run your 
	// method on it to check it.
        int[] a = new int[] {1,1,1,1,7,1,1,1,1};

        System.out.println("Array:"+Arrays.toString(a));

        System.out.println("Longest:"+LongestSubsequence(a));
    }
}
