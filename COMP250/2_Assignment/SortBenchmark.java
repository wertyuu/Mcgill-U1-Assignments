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
        Integer[] integers = new Integer[size];

        Random generator_selection = new Random(999);
        for(int i=0; i < integers.length; i++) {
            integers[i] = new Integer(generator_selection.nextInt());
        }

	//call the selectionSort algorithm and measure its running time
        long startTime_selection = System.currentTimeMillis();
        SelectionSort.sort(integers);
        long endTime_selection = System.currentTimeMillis();
        long runTime_selection = endTime_selection - startTime_selection;

        Random generator_merge = new Random(999);
        for(int i=0; i < integers.length; i++) {
            integers[i] = new Integer(generator_merge.nextInt());
        }

	// call the mergeSort algorithm and measure its running time
        long startTime_merge = System.currentTimeMillis();
        MergeSort.sort(integers);
        long endTime_merge = System.currentTimeMillis();
        long runTime_merge = endTime_merge - startTime_merge;

        //Delivering result
        System.out.println("SelectionSort: " + runTime_selection + "ms");
        System.out.println("mergeSort: " + runTime_merge + "ms");
    }
}
