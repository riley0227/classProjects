/**
 *  Program #5
 *  Creates a Vector class
 *  CS160-7
 *  April 06, 2022
 *  @author  Riley Thompson
  */

import java.util.Arrays;
import java.util.Iterator;

public class Vector<E> extends AbstractListADT<E> implements Iterable<E>{

    protected E[] myList;
 
    /**
     * This is the constructor for the Vector class.
     * Instance field values are set in this class.
     * This constructor sets myList to the DEFAULT_CAPACITY
     * which is 10.  Then it sets size to 0.
     */
    @SuppressWarnings("unchecked")
    public Vector() {
        myList = (E[]) new Object[DEFAULT_CAPACITY];
        size = 0;
    }

    /**
     * This is the constructor for the Vector class.
     * Instance field values are set in this class.
     * This constructor takes in the capacity as a parameter
     * and sets myList to that capacity and then sets 
     * size to 0.
     * @param capacity
     */
    @SuppressWarnings("unchecked")
    public Vector(int capacity) {
        myList = (E[]) new Object[capacity];
        size = 0;
    }

    /**
     * This is the constructor for the Vector class.
     * Instance field values are set in this class.
     * This constructor takes in another vector, setting the
     * list from that vector to myList, with same capacity and 
     * same data in it.  Also setting the size to otherVector's
     * size.
     * @param otherVector
     */
    @SuppressWarnings("unchecked")
    public Vector(Vector<E> otherVector) {
        if (otherVector != null) {
            this.myList = (E[]) new Object[otherVector.capacity()];
            this.myList = otherVector.data();
            size = otherVector.size();
        }
    }

    /**
     * returns the size of the storage space currently allocated to the
	 * vector expressed as number of elements.
     * returns the capacity/length of myList.
     * @return myList.length
     */
    @Override
    public int capacity() {
        return myList.length;
    }

    /**
     * returns a reference to the first/front element of myList / of the vector.
     * @return myList[0]
     */
    @Override
    public E front() {
        return myList[0];
    }

    /**
     * returns a reference to the last/back element of myList / of the vector.
     * @return myList[size-1]
     */
    @Override
    public E back() {
        return myList[size - 1];
    }

    /**
	 * @return a reference to the memory array used internally by the
	 * vector to store its owned elements.
	 */
    @Override
    public E[] data() {
        return myList;
    }

    /**
	 * Pushes / adds the element into a vector from the back
     * Does so my checking if capacity isn't beig enough to add,
     * it will double the capacity, then it will add the element
     * to myList and increment size by 1.
	 * @param element - item to insert at the back of the vector
	 */
    @Override
    public void pushback(E element) {
        if(size == capacity()) {
            resize(capacity() * 2);
        }
        myList[size] = element;
        size++;
    }

    /**
     * removes the element in the back of myList / of the vector.
     * Does this by creating the object removedValue, which takes the
     * last value in the list, then removes the value by setting it 
     * to null, decrements the size by 1.
	 * @return removedValue.
	 */
    @Override
    public E popback() {
        E removedValue = myList[size - 1];
        myList[size - 1] = null;
        size--;
        return removedValue;
    }

    /**
	 * insert() – inserts a new element before the element at the specified
	 * position
     * Does so my checking if capacity isn't beig enough to add,
     * it will double the capacity, then it creates a tempList, then
     * uses a for loop to add the positions up to the insertPosition if 
     * i < insertPosition,
     * then at insert position, if i == insertPosition, the tempList adds that new element 
     * from the parameter, and 
     * to add to the back with the values after insert position
     * it creates tempList = myList[i-1] because now it has an extra
     * elemnt in tempList so you have to subtract 1 from myList.  
     * Then increments size by 1 and sets myList to tempList.
	 * @param insertPosition - index at which to insert
	 * @param element to insert
	 */
    @Override
    @SuppressWarnings("unchecked")
    public void insert (int insertPosition, E element) {
        if(size == capacity()) {
            resize(capacity() * 2);
        }

        E[] tempList = (E[]) new Object[myList.length];
        for (int i = 0; i < myList.length; i++) {
            if (i < insertPosition) {
                tempList[i] = myList[i];
            } else if (i == insertPosition) {
                tempList[i] = element;
            } else {
                tempList[i] = myList[i - 1];
            }
        }
        size++;
        myList = tempList;
    }

    /**
	 * It is used to remove elements from a container from the 
	 * specified position.
     * It does this by going to the position that is removed
     * and deletes it by sliding over the elements in myList that
     * are above it.  Basically decreases the elements  position/index by
     * 1, which deletes that element and then set the last element to null
     * to get rid of that element as you have one less.  Then
     * decrements size by 1.
	 * @param position - index of element to remove
	 */
    @Override
    public void erase(int position) {
        for (int i = position; i < size - 1; i++) {
            myList[i] = myList[i + 1];
        }
        myList[size - 1] = null;
        size--;
    }

    /**
	 * It is used to remove elements from a container from the 
	 * startRangePosition (inclusive) to endRangePosition (exclusive).
     * It does this by creating a subtract this int value which is how
     * many elements are being deleted.  Then goes through a for loop
     * and takes the values that are above subtract this and slides them
     * into the positions of the erased values, then decrements size
     * by how many values were deleted.
	 * @param startRangePosition first index to remove
	 * @param endRangePosition stop at this index (but don't erase it)
	 */
    @Override
    public void erase(int startRangePosition, int endRangePosition) {
        int subtractThis = endRangePosition - startRangePosition;
        for (int i = startRangePosition; i < size - subtractThis; i++) {
            myList[i] = myList[i + subtractThis];
        }
        size -= subtractThis;
    }

    /**
	 * It is used to swap the contents of one vector with another vector of
	 * same type. Sizes may differ.
     * Does this by setting the list from the other vector to myList, 
     * with same capacity and same data in it.  Also setting the
     * size to other's size, making the vectors swap.
	 * @param other vector with which to swap
	 */
    @Override
    @SuppressWarnings("unchecked")
    public void swap(Vector<E> other) {
        this.myList = (E[]) new Object[other.capacity()];
        this.myList = other.data();
        size = other.size();
    }

    /**
	 * Reduces the capacity of the container to fit its size and
	 * destroys all elements beyond the capacity.
     * Does this by creating the capacity equal to the size/elements
     * and then creates a tempList with that capacity.  Then takes 
     * the elements that are in that size, which is the elements that aren't 
     * null from myList, puts them into tempList and then sets myList
     * to tempList.
	 */
    @Override
    @SuppressWarnings("unchecked")
    public void shrinkToFit() {
        int capacity = size;
        E[] tempList = (E[]) new Object[capacity];
        for (int i = 0; i < tempList.length; i++) {
            tempList[i] = myList[i];
        }
        myList = tempList;
    }

    /**
	 * Resizes the container to newSize / the given number of elements.
     * Does this by creating a tempList 
     * of the new size, then copies the myList into tempList, then
     * sets myList to tempList.
	 * @param newSize resize to container to this number of elements
	 */
    @Override
    @SuppressWarnings("unchecked")
    public void resize(int newSize) {
        E[] tempList = (E[]) new Object[newSize];
        tempList = Arrays.copyOf(myList, tempList.length);
        myList = tempList;
    }

    /**
	 * begin()
     * returns an iterator pointing to the first element, 
     * To do this it calls iterator();
	 * @return An iterator pointing to the first element.
	 */	
    @Override
    public Iterator<E> begin() {
        return iterator();
    }

    /**
     * @return a new IteratorHelper object, which has the hasNext()
     * and next() methods.
     */
    @Override
    public Iterator<E> iterator() {
        return new IteratorHelper();
    }

    /**
     * is the iterator helper class which implements iterator<E>
     * and has the next() and hasNext() methods.
     */
    class IteratorHelper implements Iterator<E> {
        /**
         * creates a count as need to compare to size and add
         * to count which iterates through myList/the vector.
         */
        int count = 0;  
        
        /**
         * Checks to see if the iterator has another element to
         * go to, checks to see if count is less than size
         * and if it is, it has another element to go to.
         * @return a boolean if count is less than size
         * it is true, otherwise, false.
         */
        public boolean hasNext() {
            return count < size();
        }

        /**
         * This creates a blank element equal to null and if it
         * has an element infront of it, the element is 
         * equal to the next element in myList, which is count++, 
         * incrementing the count by 1 and creating element
         * to the element that is next, otherwise, element stays null.  
         * Then returns element.
         * @return the next element that it iterates to.
         */
        public E next() {
            E element = null;
            if (hasNext()) {
                element = myList[count++];
            }
            return element;
        }
    }

    /**
	 * Get the element at the index. If the index is invalid an error occurs.
	 * @param index of vector from which to return an element
	 * @return the element at the given index
	 * @throws IllegalArgumentException if index is invalid
	 */
    @Override
    public E at(int index) throws IllegalArgumentException{
        return myList[index];
    }

    /**
     * reserve() – Requests that the vector capacity be at least enough 
	 * to contain n elements.
     * It checks to see if reserveSize is greater than capacity and if
     * it is, it resizes the array to be capacity of reserveSize, otherwise
     * it stays the same capacity and no change is needed
     * @param reserveSize
     */
    public void reserve(int reserveSize) {
        if (reserveSize >= capacity()) {
            resize(reserveSize);
        }     
    }

    /**
	 * rbegin()
     * returns an iterator pointing to the last element, 
     * This does this by calling riterator();
	 * @return An iterator pointing to the last element.
	 */	
    public Iterator<E> rbegin() {
        return riterator();
    }
    /**
     * @return a new RIteratorHelper object, which has the hasNext()
     * and next() methods.
     */
    public Iterator<E> riterator() {
        return new RIteratorHelper();
    }

    /**
     * is the reverse iterator helper class which implements iterator<E>
     * and has the next() and hasNext() methods.
     */
    class RIteratorHelper implements Iterator<E> {
        /**
         * creates a Reversecount as need to compare to 0 and 
         * subtract from count which iterates backwards through 
         * myList/the vector.  The count starts at the last index of the 
         * Vector and then gets subtracted from.
         */
        int reverseCount = size() - 1;  
        
        /**
         * Checks to see if the iterator has another element to
         * go to, checks to see if count is greater than  or equal to
         * zero and if it is, it has another element to go to.
         * @return a boolean if count is greater than or equal to zero
         * it is true, otherwise, false.
         */
        public boolean hasNext() {
            return reverseCount >= 0;
        }

        /**
         * This creates a blank element equal to null and if it
         * has an element behind it, the element is 
         * equal to the element behind it or next element in myList, which 
         * is count--, decrementing the reverseCount by 1 and creating element
         * to the element that is next, otherwise, element stays null.  
         * Then returns element.
         * @return the next element that it iterates to.
         */
        public E next() {
            E element = null;
            if (hasNext()) {
                element = myList[reverseCount--];
            }
            return element;
        }
    }
}
