import java.lang.*;

public class MergeSort {
    public static void sort (Comparable[] a) {
	mergesort(a, 0, a.length-1);
    }
    
    static void mergesort (Comparable[] a, int i, int j) {
	//System.out.println("Calling with " + i + " " + j);
	if (j-i < 1) return;
	int mid = (i+j)/2;
	mergesort(a, i, mid);
	mergesort(a, mid+1, j);
	merge(a, i, mid, j);
    }

    static void merge(Comparable[] a, int p, int mid, int q) {
	//System.out.println("Calling merge with " + p + " " + mid + " " + q);
	Comparable[] tmp = new Comparable[q-p+1];
	int i = p; 
	int j = mid+1;
	int k = 0;
	while (i <= mid && j <= q) {
	    if (a[i].compareTo(a[j])<=0) 
		tmp[k] = a[i++];
	    else 
		tmp[k] = a[j++];
	    k++;
	}
	if (i <= mid && j > q) {
	    while (i <= mid) 
		tmp[k++] = a[i++];
	} else {
	    while (j <= q)
		tmp[k++] = a[j++];
	}
	for (k = 0; k < tmp.length; k++) {
	    a[k+p] = tmp[k];
	}
    }
}
    
