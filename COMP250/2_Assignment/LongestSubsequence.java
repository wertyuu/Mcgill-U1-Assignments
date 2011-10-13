import java.util.Arrays;

public class LongestSubsequence {

    public static int LongestSubsequence (int[] a) {
	// your code goes here
	// you can define other functions, if you want
        return LndS(a,0,a.length-1);
    }

    public static int LndS (int[] a, int p, int q) {
        int m = (p + q) / 2;
        int i;
        int j;

        if ((q - p) < 1) {
            return 1;
        } else {
            i = LndS(a,p,m);
            j = LndS(a,m+1,q);
            
            if (a[m] <= a[m+1]) {
                int breakPoint = 0;
                boolean broken = false;
                for(int x = p; x <q; x++) {
                    if(a[x] > a[x+1]){
                        breakPoint = x;
                        broken = true;
                        break;
                    }
                }

                if(broken && breakPoint > m) {
                    return Math.max(i + LndS(a,m+1,breakPoint) , LndS(a,breakPoint, q) );
                } else if (broken && breakPoint < m){
                    int breakPoint2 = 0;
                    boolean brokenAfterM = false;

                    for(int x = m + 1; x < q; x++){
                        if(a[x]>a[x+1]) {
                            breakPoint2 = x;
                            brokenAfterM = true;
                            break;
                        }
                    }

                    if(brokenAfterM){
                        return Math.max((LndS(a,breakPoint,m)+LndS(a,m,breakPoint2)),(LndS(a,breakPoint2+1,q)));
                    } else if(!brokenAfterM){
                        return LndS(a,breakPoint, m) + j;
                    }

                } else if (!broken) {
                    return i+j;
                }
            }/* else if(a[m] > a[m+1]){
                return Math.max(i,j);
            }*/else {
                return Math.max(i,j);
            }
        }
        //Unreachable return
        return 3;
    }

    public static void main (String[] args) {
	// here you should declare and initialize an array, and run your 
	// method on it to check it.
        int[] a = new int[] {1,2,3,4,3,4,4,5,6,3,7,8,9,10,11};

        System.out.println("Array:"+Arrays.toString(a));

        System.out.println("Longest:"+LongestSubsequence(a));
    }
}
