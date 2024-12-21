/**
 *  Program #4
 *  This is a program a genric methods prgram
 *  CS160-3
 *  03/14/2022
 *  @author  Riley Thompson
  */

import java.util.*;

public class GenMethods {
    /**
     * identification method to get identification
     * @return "Program 4, Riley Thompson";
     */
    public static String getIdentificationString(){
        return "Program 4, Riley Thompson";
    }

    /**
     * Removes duplciates in the Arraylist, list, in a new arraylist
     * that then adds the elements that does not have another element in the array.
     * This makes it so there is only one of each element.
     * Then returns the noDuplicates/new array with no repeating elements.
     * @param <E>
     * @param list
     * @return noDuplicates
     */
    public static <E> ArrayList<E> removeDuplicates(ArrayList<E> list){
        ArrayList<E> noDuplicates = new ArrayList<E>();
        for(int i = 0; i < list.size(); i++){
            if(!noDuplicates.contains(list.get(i))){
                noDuplicates.add(list.get(i));
            }
        }
        return noDuplicates;
    }

    /**
     * This shuffles the list that is put into the parameter.  
     * It takes that list, and for numTimes or 30 times, it takes 2 random elements
     * in the arraylist.  Puts one of the random indexes elements value in a temp 
     * variable so the value isn't changed and puts the second randInx elements value in that
     * indexes spot, then changes the second indexes elemnt value with the temp value
     * @param <E>
     * @param list
     */
    public static <E> void shuffle(ArrayList<E> list){
        int numTimes = 30;
        Random rand = new Random(340L);
        for(int i = 0; i < numTimes; i++){
            int randIdx = rand.nextInt(list.size());
            int randIdx2 = rand.nextInt(list.size());
            E tempVal = list.get(randIdx);
            list.set(randIdx, list.get(randIdx2));
            list.set(randIdx2, tempVal);
        }
    }

    /**
     * This goes through the arraylist given in the parameter and finds the max 
     * value from this.  It sets the value of max to the first element,
     *  then compares the other elements to it and if they are larger, then max
     * is set to that and so on.
     * @param <E>
     * @param list
     * @return max
     */
    public static <E extends Comparable<E>> E max(ArrayList<E> list){
        E max = list.get(0);
		for (int i = 1; i < list.size(); i++) {
			if (list.get(i).compareTo(max) > 0){
                max = list.get(i);
            }
		}
		return max;
    }

    /**
     * This finds the index of where the value key is.  So it goes through the array
     * and if the value of the element of the list mathces the key, it returns that
     * index, otherwise if none of the indexes of list match key, -1 is returned.
     * @param <E>
     * @param list
     * @param key
     * @return i or -1
     */
    public static <E extends Comparable<E>> int linearSearch(E[] list, E key){
        for (int i = 0; i<list.length; i++) {
            if (list[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * This goes through the array given in the parameter and finds the max 
     * value from this.  It sets the value of max to the first element,
     * then compares the other elements to it and if they are larger, then max
     * is set to that and so on.
     * @param <E>
     * @param list
     * @return max
     */
    public static <E extends Comparable<E>> E max(E[] list){
        E max = list[0];
        for (int i = 1; i < list.length; i++) {
            if (list[i].compareTo(max) > 0) {
                max = list[i];
            }
        }
        return max;
    }

    /**
     * This goes through the array given in the parameter and finds the max 
     * value from this.  It sets the value of max to the first element,
     * then compares the other elements to it and if they are larger, then max
     * is set to that and so on.  This method goes through the elements in each row
     * then moves on to the next row, through the whole 2d array.
     * @param <E>
     * @param list
     * @return max
     */
    public static <E extends Comparable<E>> E max(E[][] list){
        E max = list[0][0];
        for (int i = 0; i < list.length; i++) {
            for (int j = 0; j < list[i].length; j++) {
                if (list[i][j].compareTo(max) > 0) {
                    max = list[i][j];
                }
            }
        }
        return max;
    }

    /**
     * This is the main method which does the functions it is asked in the
     * instructions, explained below in the method.
     * @param args
     */
    public static void main(String[] args){
        //Creates a scanner
        Scanner scnr = new Scanner(System.in);

        //takes in int which is used to then create an array with that number 
        //of values(list is the name of array)
        int n = scnr.nextInt();
        Integer[] list = new Integer[n];

        //Creates a linked list named linked
        LinkedList<Integer> linked = new LinkedList<Integer>();

        //sets the values of each element of list to those inputed
        //adds the vlaues inputed to the linkedList
        for(int i = 0; i < n; i++){
            int num = scnr.nextInt();
            list[i] = num;
            linked.add(num);
        }
        //Prints out list(array), and Linked(LinkedList).
        System.out.println(Arrays.toString(list));
        System.out.println(linked);

        //Reads in k key value to search for in list.
        Integer k = scnr.nextInt();
        
        //Calls linearSearch(list, k) and prints the result
        int idxOfK = linearSearch(list, k);
        if(idxOfK == -1){
            System.out.println("Key " + k + " was not found");
        } else {
            System.out.println("Key " + k + " was found at position " + idxOfK);
        }

        //Calls max(list) and prints the result
        Integer max = max(list);
        System.out.println(max + " is the max element");

        //Read in an integer m for first dimension of a 2-D array and p for 
        //the second dimension.
        int m = scnr.nextInt();
        int p = scnr.nextInt();

        //Initialize a 2-D array using m and p named 'list2'.
        Integer[][] list2 = new Integer[m][p];
        
        //Reads in m x p elements to fill 'list2'.
        for(int i = 0; i < m; i++){
            for(int j = 0; j < p; j++)
            list2[i][j] = scnr.nextInt();    
        }

        //Prints 'list2'
        for(int i = 0; i < m; i++){
            for(int j = 0; j < p; j++){
                System.out.print(list2[i][j]);
            }
            System.out.println();
        }

        //Calls max(list2) and prints the result:
        Integer max2 = max(list2);
        System.out.println(max2 + " is the max element");

        //Instantiates an ArrayList of type Integer named 'alist' from 'linked'. 
        ArrayList<Integer> alist = new ArrayList<>(linked);

        //Prints out 'alist'
        System.out.println(alist);

        //Call removeDuplicates using 'alist' as the parameter, puts it in 
        //new, uniqueAList, arraylist.  Then prints the new list.
        ArrayList<Integer> uniqueAlist = removeDuplicates(alist);
        System.out.println(uniqueAlist);

        //shuffles uniqueAlist, then prints uniqueAlist.
        shuffle(uniqueAlist);
        System.out.println(uniqueAlist);

        //Finds the max element of 'alist' and prints the result.
        Integer max3 = max(alist);
        System.out.println(max3 + " is the max element");
        
        //closes scanner.
        scnr.close();
    }
}
