/*
 * Ioannis Manthopoulos
 * imanthoc@csd.auth.gr
 * 3579
*/
//part of the code is from https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/

//Grade this version

import java.io.*;
import java.util.*;

public class Knapsack {
    /*
     * Function to perform the the modified knapsack algorithm, but finding minimum value instead of maximum
     * and searching for exact size.
     */
    private static void kn(int[] sizes, int m, int S) {
        int[] M = new int[S + 1]; //M array as of normal algorithm

        M[0] = 0;
        for (int i = 1; i <= S; ++i) M[i] = Integer.MAX_VALUE; //init M to +infinity

        for (int i = 1; i <= S; ++i) { //for every possible size
            for (int j = 0; j < m; ++j) {  //for every possible packet
                if (sizes[j] <= i) { //if the packet fits
                    int temp = M[i - sizes[j]];
                    //add the packet if it follows the minimum formula (because we need the minimum amount of items)
                    if (temp != Integer.MAX_VALUE && temp + 1 < M[i]) {              
                        M[i] = temp + 1;
                    }
                }
            }
        }

        if (M[S] == Integer.MAX_VALUE) { //if there is no solution (the edge of the array has not been reached)
            System.out.println("There is no solution for the unbounded case.");
        } else {
            System.out.println("The minimum number of boxes for the unbounded case is: " + M[S]);
        }
    }
    
    /*
     * Driver function to read file data and call the algorithm
     */
    public static void main(String[] args) {
        try {
            int size;
            int am;
            int[] sizes;
            int[] amounts;
            Scanner sc = new Scanner(new File(args[0]));
            
            size = sc.nextInt();
            am   = sc.nextInt();
            sizes   = new int[am];
            amounts = new int[am];
            for (int i = 0; i < am; ++i) {
                sc.nextInt();
                sizes[i]   = sc.nextInt();
                amounts[i] = sc.nextInt();
            }
            
            kn(sizes, sizes.length, size);
        } catch (FileNotFoundException e) {}
        
    }
}
