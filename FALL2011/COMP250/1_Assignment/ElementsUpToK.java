import java.util.Arrays;

public class ElementsUpToK{
    public static void main(String[] argv){
        //Here the array is declared and initialized
        int[] a = { 1 , 4 , 4 , 3 , 4 , 3 , 5 , 2 , 5 , 1 , 5 };
        
        int[] e = getDuplicatesK(a,3);
        System.out.println(Arrays.toString(e));
    }

    public static int[] getDuplicatesK(int[] c, int k){
        int[] result = new int[1];

        for(int i = 0; i < c.length; i++){
            if((getNumOccurences(c, c[i])) <= k && getNumOccurences(result, c[i]) == 0){
                if(i > 0){                              //checking if we are on the first iteration so as to know whether to create a new array
                    //Mimics an arraylist when adding new element to array
                    int[] tempResult = new int[result.length + 1];
                    for(int n = 0; n < result.length; n++){
                        tempResult[n] = result[n];
                    }
                    result = tempResult;
                    result[result.length - 1] = c[i];
                }else{
                    result[0]= c[i];
                }
            }
        }

        return result;
    }

    public static int getNumOccurences(int[] b, int val) {
        int result = 0;
        
        for(int i = 0; i < b.length; i++){
            if(b[i]==val){
                result +=1;
            }
        }
        return result;
    }

}
