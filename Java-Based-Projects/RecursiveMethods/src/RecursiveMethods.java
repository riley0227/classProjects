/**
 *  Program #6
 *  This is a Recursive methods program which has 
 *  recursive methods in a RecursiveMethod class.
 *  CS160-3
 *  04/17/2022
 *  @author  Riley Thompson
  */

public class RecursiveMethods {

    /**
     * This is a recursive method which returns the amount of ways an object can advance when it can
     * move either 2 or 1 space when it goes to n spaces total.  It checks to see if n is 0 and if it
     * is, it returns 0 as you don't have to move any spaces to get there.  Then, you would return n
     * when n equals 1 or n equals 2 as when there is 1 way to solve when n = 1 and 2 ways when
     * n=2, and then you would recursively call byLeapsAndBounds of the previous and the one before that,
     * which would go until you reach n == 1 and n == 2, which would add those to total, making it return
     * the amount of ways it can be done.
     * 
     * Base case (n == 0), (n == 1),  or (n==2)
     * Sample input: byLeapsAndBounds(3)      Expected Output: 3
     * Sample input: byLeapsAndBounds(5)      Expected Output: 8
     * Sample input: byLeapsAndBounds(7)      Expected Output: 21
     * @param n
     * @return the total distinct ways in which the object can advance the required n spaces.
     */
    public int byLeapsAndBounds(int n) {
        if (n == 0) {
            return 0;
        }
        
        if (n == 1 || n == 2) {
            return n;
        } else {
            return byLeapsAndBounds(n-1) + byLeapsAndBounds(n-2);
        }
    }

    /**
     * This is a recursive method which takes two Strings as parameters,
     * str and subStr. Then it returns the number of times subStr occurs within str.
     * To do this, the method first checks to make sure the string has values in it,
     * if it doesn't it returns 0, as there would be no mathing substring.  Then
     * checks to see if the substr first letter equals the first letter of str 
     * and if it does, it checks to see if the subStr equals the str of those first
     * letters that match the length of subStr.  If it does, then it adds one as it
     * matches, and then subtracts the length of subStr creating a newString with the Str
     * without the subStr as it is already part of the count, then returns 1 + subCount(newString, subStr)
     * which is the newString that is created without the subStr.  Otherwise, if no subStr
     * of the first letter is found, it just creates a newString without the first letter, and
     * moves to check to see if the second letter has a subStr, and calls subCount(newString, subString),
     * which is the newString without the first letter.
     * 
     * Base case (str.length() == 0)
     * Sample input: subCount("aaaa","a")      Expected Output: 4
     * Sample input: subCount("abcabcabcab123", "abc")      Expected Output: 3
     * Sample input: subCount("rtryrttyryrtrt", "rt")      Expected Output: 4
     * @param str
     * @param subStr
     * @return the number of times subStr occurs within str
     */
    public int subCount(String str, String subStr) {
        if (str.length() == 0) {
            return 0;
        }
        if (str.substring(0, 1).equals(subStr.substring(0, 1))) {
            if(str.substring(0, subStr.length()).equals(subStr)) {
                String newString = str.substring(subStr.length(), str.length());
                return 1 + subCount(newString, subStr);
            }
        }
        String newString = str.substring(1, str.length());
        return subCount(newString, subStr);
    }

    /**
     * This is a recursive method which finds the index in the array where the target value
     * is, otherwise it returns 0.  To do this, a midTarget is found by doing the leftIndex +
     * the right index divided by two, then creates an indexOPfTarget which would be used
     * when the index is found.  Then it checks if the array has a length of zero it returns
     * -1.  Then checks if the element at the index of midTarget is the value and if so
     * the indexOfTarget id midTarget as the index is in the right spot for that value and
     * indexOfTarget is returned.  Then if that isn't true it checks to see if there is no
     * indecies to check left(if the left - right index is 0, there is nothing left to check)
     * it returns -1 as nothing is found for target.  Then if nothing is found and there is 
     * values left to check, it checks to see if the element at array is larger than the target
     * value, and if that is the case it calls the method again and will search the first half,
     * otherwise it would chekc the second half, as the valeus would be either smaller in the
     * first or second half, and it would keep going down the binary tree until the value is found.
     * 
     * Base case (str.length() == 0)
     * 
     * Example array: int[]sampleArr = {1,2,3,5,6,8,13};
     * Sample input: binarySearch(sampleArr,3,0,sampleArr.length-1)      Expected Output: 2
     * Sample input: binarySearch(sampleArr,13,0,sampleArr.length-1)      Expected Output: 6
     * Sample input: binarySearch(sampleArr,57,0,sampleArr.length-1)      Expected Output: -1
     * @param array
     * @param target
     * @param left
     * @param right
     * @return the index where the target value is in the array, otherwise returns -1.
     */
    public int binarySearch(int[]array, int target, int left, int right) {
        int midTarget = (left + right) / 2;
        int indexOfTarget;
        if (array.length == 0) {
            return -1;
        }
        if (array[midTarget] == target) {
            indexOfTarget = midTarget;
            return indexOfTarget;
        } else if ((right - left) == 0) { 
            return -1;
        } else {
            if (array[midTarget] > target) {
                return binarySearch(array, target, left, midTarget);
            } else {
                return binarySearch(array, target, midTarget + 1, right);
            }
        }
    }
}
