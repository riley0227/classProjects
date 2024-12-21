#ifndef PROMOTEDCARMODELSTACK_H
#define PROMOTEDCARMODELSTACK_H

#include <ctype.h>  // character manipualtion, e.g. tolower()
#include <stdio.h> 
#include <string>
#include <deque>
#include <stdexcept>

using namespace std;

class PromotedModel {

private:
  string model;
  int promotedPrice;

public:
  PromotedModel() {
    this -> model = "";
    this -> promotedPrice = -1;
  }

  PromotedModel(string m, int p) {
    this -> model = m;
    this -> promotedPrice = p;
  }

  inline string getModel() {
    return model;
  }

  inline int getPromotedPrice() {
    return promotedPrice;
  }
};

class PromotedCarModelStack {

private:  
  // These are the member variables used to create the stack
  // I used deque as it allows me to see and push to front and back

  /* dequePriceMinToMax is to sort the order of all the min/max values there are in the
   * deque, so when a new min value occurs that PromotedModel gets pushed to the front and
   * when a new max value occurs that PromotedModel gets pushed to the back(explained more in .cpp file).
   */
  std::deque<PromotedModel> dequePriceMinToMax;

  //This is the normal deque/stack where each PromotedModel is put to the end through the push member function
  std::deque<PromotedModel> dequeModelInOrder;

public:
  /**
   * @brief push operation, pushing the latest promoted model onto the stack
            Both time and auxiliary space complexity need to be O(1) 
   * @param model 
   * @param price 
   */
  void push(string model, int price);
  
  /**
   * @brief pop operation, popping the latest promoted model off the stack
            Both time and auxiliary space complexity need to be O(1) 
   * @param  
   * @return PromotedModel
   *         should throw a logic_error exception with an error message 
   *         “Promoted car model stack is empty” if the PromotedCarModelStack is empty
   */
  PromotedModel pop();

  /**
   * @brief peek operation, peeking the latest promoted model at the top of the stack (without popping)
            Both time and auxiliary space complexity need to be O(1) 
   * @param 
   * @return PromotedModel
   *         should throw a logic_error exception with an error message 
   *         “Promoted car model stack is empty” if the PromotedCarModelStack is empty
   */
  PromotedModel peek();

  /**
   * @brief getHighestPricedPromotedModel, 
   *        getting the highest priced model among the past promoted models
            Both time and auxiliary space complexity need to be O(1)
   * @param 
   * @return PromotedModel
   *         should throw a logic_error exception with an error message 
   *         “Promoted car model stack is empty” if the PromotedCarModelStack is empty
   */
  PromotedModel getHighestPricedPromotedModel();

  /**
   * @brief getLowestPricedPromotedModel, 
   *        getting the lowest priced model among the past promoted models
            Both time and auxiliary space complexity need to be O(1)
   * @param 
   * @return PromotedModel
   *         should throw a logic_error exception with an error message 
   *         “Promoted car model stack is empty” if the PromotedCarModelStack is empty
   */
  PromotedModel getLowestPricedPromotedModel();

};

#endif