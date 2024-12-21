#ifndef SORTCAR_H
#define SORTCAR_H

#include <vector>
#include <string>

using namespace std;

class SortCar {

public:
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
  static vector<string> sortCarInventory(vector<string> carInventory, vector<string> promotionOrder);
};

#endif