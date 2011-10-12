import java.lang.*;
import java.util.Scanner;
import java.util.Random;

import java.util.Arrays;

public class SortBenchmark {

    public static void main (String[] args) {
        System.out.print("Enter size of the array:");
        Scanner keyboard = new Scanner(System.in);
        int size = keyboard.nextInt();
	// initialize an array of integers
        Integer[] integers_1 = new Integer[size];
        Integer[] integers_2 = new Integer[size];

        Random generator = new Random(999);

        for(int i=0; i < integers_1.length; i++) {
            int a = generator.nextInt();
            integers_1[i] = new Integer(a);
            integers_2[i] = new Integer(a);
        }

        //Testing
        System.out.println("integers_1: " + Arrays.deepToString(integers_1));
        System.out.println("integers_2: " + Arrays.deepToString(integers_2));

	//call the selectionSort algorithm and measure its running time
        long startTime_selection = System.currentTimeMillis();
        SelectionSort.sort(integers_1);
        long endTime_selection = System.currentTimeMillis();
        long runTime_selection = endTime_selection - startTime_selection;

	// call the mergeSort algorithm and measure its running time
        long startTime_merge = System.currentTimeMillis();
        MergeSort.sort(integers_2);
        long endTime_merge = System.currentTimeMillis();
        long runTime_merge = endTime_merge - startTime_merge;

        //Testing
        System.out.println("integers_1: " + Arrays.deepToString(integers_1));
        System.out.println("integers_2: " + Arrays.deepToString(integers_2));

        //Delivering result
        System.out.println("SelectionSort: " + runTime_selection + "ms");
        System.out.println("mergeSort: " + runTime_merge + "ms");
    }
}
