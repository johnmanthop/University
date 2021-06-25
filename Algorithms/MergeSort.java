import java.util.*;
import java.io.*;

//Original merge code customized from www.geeksforgeeks.org/counting-inversions/

public class MergeSort {

    /*
      Does a sort and the custom inversion count by the rule A_j+1 = A_i
    */
    static long custom_count(int[] array, int left_index, int mid_index, int right_index) {
        //split given array in 2
        int[] left_half  = Arrays.copyOfRange(array, left_index, mid_index + 1);
        int[] right_half = Arrays.copyOfRange(array, mid_index + 1, right_index + 1);
        
        //find the max of the left array in O(n)
        int max = -1;
        for (int el : left_half) {
            if (el > max) max = el;
        }
        //create lookup table of max+1 size, so we can have O(1) detection of special inversions
        int[] lookup = new int[max + 1];
        //map the element to the number of times it appears, ex: lookup[5] = 10 : element 5 appears 10 times
        for (int el : left_half) {
            lookup[el]++;
        }
 
        int i = 0, j = 0, k = left_index;
        long cost = 0;
 
        while (i < left_half.length && j < right_half.length) {
            if (left_half[i] <= right_half[j]) {
                array[k++] = left_half[i++];
            } else {
                array[k++] = right_half[j++];
                //in case of inversion
                //find the ammount of inversions that are there
                //that is the size of the left array (mid index) minus the amount of traversed elements (i + left)
                int all_invs = (mid_index + 1) - (left_index + i);
                //special inversions are the number of times that the right[j] + 1 element appears, that we can find in O(1) with the table
                int spc_invs = lookup[right_half[j-1] + 1];
                //add the cost
                cost += 2 * spc_invs;
                cost += 3 * (all_invs - spc_invs);
            }
        }
        //add the leftover elements to the array (so that it is sorted)
        while (i < left_half.length)  array[k++] = left_half[i++];
        while (j < right_half.length) array[k++] = right_half[j++];

        return cost;
    }
    
    /*
      recursive function to do merge and count
    */
    static long custom_merge(int[] array, int left_index, int right_index) {
        long count = 0;
        //Usual recursive code to do merge sort, nothing special
        if (left_index < right_index) {
            int mid_index = (left_index + right_index) / 2;

            count += custom_merge(array, left_index, mid_index);
            count += custom_merge(array, mid_index + 1, right_index);
            count += custom_count(array, left_index, mid_index, right_index);
        }
 
        return count;
    }

    /*
      helper function to double the size of an array, in case its limit is reached
    */
    static int[] double_size(int[] array) {
        int[] temp = new int[array.length * 2];

        for (int i = 0; i < array.length; ++i) {
            temp[i] = array[i];
        }

        return temp;
    }
    /*
      main function
    */
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File(args[0]));
        int cap = 100000;
        int i = 0;
        int[] arr = new int[cap];
        //add file data to a primitive array
        //and double its size in case its size is reached
        while (sc.hasNext()) {
            arr[i++] = sc.nextInt();
            if (i == arr.length - 1) arr = double_size(arr);
        }
        System.out.println("Total cost: " + custom_merge(arr, 0, i - 1));
    }
}