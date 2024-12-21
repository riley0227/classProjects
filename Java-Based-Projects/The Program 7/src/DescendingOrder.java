import java.util.Scanner;

public class DescendingOrder {
    // TODO: Write a void method selectionSortDescendTrace() that takes 
    //       an integer array and the number of elements in the array as arguments, 
    //       and sorts the array into descending order.
    public static void selectionSortDescendTrace(int [] numbers, int numElements) {
        int smallest = numbers[0];
        int temp = 0;

        for (int i = 0; i < numElements - 1; ++i) {

            smallest = i;
            for (int j = i + 1; j < numElements; ++j) {
         
               if (numbers[j] < numbers[smallest]) {
                  smallest = j;
               }
            }
            temp = numbers[i];
            numbers[i] = numbers[smallest];
            numbers[smallest] = temp;
         }
    }
   
   
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
      
        int input, i = 0;
        int numElements = 0;
        int [] numbers = new int[10];
        // TODO: Read in a list of up to 10 positive integers; stop when
        //       -1 is read. Then call selectionSortDescendTrace() method.
        int currentNumber = -1;
        while (numElements < 10 && currentNumber != -1) {
            System.out.println("hiadf");
            numbers[numElements] = scnr.nextInt();
            numElements++;
        }
        selectionSortDescendTrace(numbers, numElements);

        scnr.close();

    }
}

