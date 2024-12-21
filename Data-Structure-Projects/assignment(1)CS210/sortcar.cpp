#include "sortcar.h"

/**
 * @brief sort car inventory
 * 
 * @param carInventory      input car inventory array
 * @param promotionOrder    car promotion order
 * @return vector<string>   sorted car inventory according to the car promotion order
 * 
 * Time complexity has to be linear: O(N), N is the size/length of the input car inventory array
 * Space complexity has to be constant: O(1), hint: sorting can be done by mutating 
 *                                      the input car inventory array.
 */
vector<string> SortCar::sortCarInventory(vector<string> carInventory, vector<string> promotionOrder) {
    string low = promotionOrder[0]; //first promotion in promotion order
    string mid = promotionOrder[1]; //second promotion in promotion order
    int countOfStart = 0; //count for index of sorted area
    string tempSwap = ""; //for swapping strings in carInventory vector

     //next 2 if statements check edge cases
    if(carInventory.size() == 0) {
        return carInventory;
    }
    if(carInventory.size() == 1) {
        return carInventory;
    }

    //sorts first index of promotion order in carInventory
    for(int i = 0; i < carInventory.size(); i++) {
        if (carInventory[i] == low) {
            tempSwap = carInventory[i];
            carInventory[i] = carInventory[countOfStart];
            carInventory[countOfStart] = tempSwap;
            countOfStart++;
        }
    }

    //sorts first index of promotion order in carInventory
    int indexAfterPromLowComplete = countOfStart; //first index of second part of promotion order to sort
    int countOfMid = indexAfterPromLowComplete; //second part of index sorted

    //sorts second index of promotion order in carInventory
    for(int i = indexAfterPromLowComplete; i < carInventory.size(); i++) {
        if (carInventory[i] == mid) {
            tempSwap = carInventory[i];
            carInventory[i] = carInventory[countOfMid];
            carInventory[countOfMid] = tempSwap;
            countOfMid++;
        }
    }
    return carInventory;
}
  
