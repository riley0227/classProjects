import java.util.Scanner;

public class DescendingOrder {
    // TODO: Write a void method selectionSortDescendTrace() that takes 
    //       an integer array and the number of elements in the array as arguments, 
    //       and sorts the array into descending order.

    /**
     * 
     * @param numbers
     * @param numElements
     */
    public static void selectionSortDescendTrace(int [] numbers, int numElements) {
        int largestValIndx = 0;
        int temp = 0;

        for (int i = 0; i < numElements - 1; i++) {

            largestValIndx = i;

            for (int j = i + 1; j < numElements; j++) {
         
                if (numbers[j] > numbers[largestValIndx]) {
                    largestValIndx = j;
                }
            }
            temp = numbers[i];
            numbers[i] = numbers[largestValIndx];
            numbers[largestValIndx] = temp;
            for (i = 0; i < numElements; i++) {
                System.out.print(numbers[i] + " ");
            }
            System.out.println();
        }
    }
   
   
    /**
     * 
     * @param args
     */
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
      
        int input = 0;
        int numElements = 0;
        int [] numbers = new int[10];
        // TODO: Read in a list of up to 10 positive integers; stop when
        //       -1 is read. Then call selectionSortDescendTrace() method.


        while (numElements < 10 && input != -1) {
            input = scnr.nextInt();
            if (input != -1) {
            numbers[numElements] = input;
            numElements++;
            }
        }

        selectionSortDescendTrace(numbers, numElements);
        scnr.close();

    }
}

