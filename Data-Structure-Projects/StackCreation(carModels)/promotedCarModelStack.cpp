/* I the undersigned promise that the submitted assignment is my own work. While I was
 * free to discuss ideas with others, the work contained is my own. I recognize that
 * should this not be the case; I will be subject to penalties as outlined in the course
 * syllabus.
 * Name: Riley Thompson
 * Red ID: 826526487
 */

#include "promotedCarModelStack.h"

/**
   * @brief push operation, pushing the latest promoted model onto the stack
            Both time and auxiliary space complexity need to be O(1) 
   * @param model 
   * @param price 
   */
void PromotedCarModelStack::push(string model, int price) {
    // newModel is the model that is to be pushed to the deque/stack.
    PromotedModel newModel = PromotedModel(model, price);

    // pushes newModel to the dequeModelInOrder deque.
    dequeModelInOrder.push_back(newModel);

    // isEmpty is true if there is no PromotedModel in the dequePriceMinToMax deque, otherwise it is false.
    bool isEmpty = dequePriceMinToMax.empty();

    //changes to true if it is the first model, so it won't add the same value twice.(flag)
    bool firstModel = false;

    /* checks if dequePriceMinToMax deque is empty and if so it pushes the value of newModel to the front, which
     * would be the front and back as it would be the first value pushed to the deque/stack.
     */
    if(isEmpty) {
        dequePriceMinToMax.push_front(newModel);

        /* changes to true as this call to push would be the first model added to the deque/when it is empty
         * and something is added.(flag)
         */
        firstModel = true;
    }

    // gets the price of the PromotedModel newModel.
    int priceOfNewModel = newModel.getPromotedPrice();
    // gets the current lowest price in the Deque from the front of the dequePriceMinToMax deque.
    int lowestPriceInDeque = dequePriceMinToMax.front().getPromotedPrice();
    // gets the current highest price in the Deque from the front of the dequePriceMinToMax deque.
    int highestPriceInDeque = dequePriceMinToMax.back().getPromotedPrice();

    /* checks if the price of the new model is lower or equal to the price of the current lowest model
     * (front of deque) and if it is, then that model would be pushed to the front as the most recent lowest priced
     * model. (does not put every model in the deque, dequePriceMinToMax, so it wouldn't have to search and can stay
     * in O(1) time complexity). Also, it does not run if it is the first model pushed to the deque as that would
     * make it add that PromotedModel twice.
     */
    if(priceOfNewModel <= lowestPriceInDeque && !firstModel) {
        dequePriceMinToMax.push_front(newModel);
        /* else it would check if the price of the new model is higher or equal to the price of the current highest model
         * (back of deque) and if it is, then that model would be pushed to the back as the most recent lowest priced
         * model. (does not put every model in the deque, dequePriceMinToMax, so it wouldn't have to search and can stay
         * in O(1) time complexity). Also, it does not run if it is the first model pushed to the deque as that would
         * make it add that PromotedModel twice.
         */
    } else if(priceOfNewModel >= highestPriceInDeque && !firstModel) {
        dequePriceMinToMax.push_back(newModel);
    }

    /* changes first model to false as the stack is no longer empty and following calls to the push function would
     * not change this value unless the deque/stack is empty.(flag)
     */
    firstModel = false;
}

/**
   * @brief pop operation, popping the latest promoted model off the stack
            Both time and auxiliary space complexity need to be O(1) 
   * @param  
   * @return PromotedModel
   */
PromotedModel PromotedCarModelStack::pop() {
    // isEmpty is true if there is no PromotedModel in the dequeModelInOrder deque, otherwise it is false.
    bool isEmpty = dequeModelInOrder.empty();

    /* checks if dequeModelInOrder deque is empty and if so it throws a logic error with the
     * message "Promoted car model stack is empty".
     */
    if(isEmpty) {
        throw std::logic_error("Promoted car model stack is empty");
    }

    // newestModel is the model that is to being popped from the deque/stack.
    PromotedModel newestModel = dequeModelInOrder.back();

    // gets the price of the PromotedModel newModel.
    int priceOfNewestModel = newestModel.getPromotedPrice();
    // gets the current lowest price in the Deque from the front of the dequePriceMinToMax deque.
    int lowestPriceInDeque = dequePriceMinToMax.front().getPromotedPrice();
    // gets the current highest price in the Deque from the front of the dequePriceMinToMax deque.
    int highestPriceInDeque = dequePriceMinToMax.back().getPromotedPrice();

    // This pops the last value in the deque, dequeModelInOrder.
    dequeModelInOrder.pop_back();

    /* checks to see if the most recent model added to the deque/is being removed is equal to
     * the lowest price in the deque, and if it is it will remove the first PromotedModel of
     * dequePriceMinToMax because that would be the lowest value in the stack and now it would
     * not be and the previous lower value is now.
     */
    if(priceOfNewestModel == lowestPriceInDeque) {
        dequePriceMinToMax.pop_front();
        /* checks to see if the most recent model added to the deque/is being removed is equal to
         * the highest price in the deque, and if it is it will remove the last PromotedModel of
         * dequePriceMinToMax because that would be the highest value in the stack and now it would
         * not be and the previous higher value is now.
         */
    } else if(priceOfNewestModel == highestPriceInDeque) {
        dequePriceMinToMax.pop_back();
    }

    // returns the model that was removed from the deque/stack(newestModel).
    return newestModel;
}

/**
   * @brief peek operation, peeking the latest promoted model at the top of the stack (without popping)
            Both time and auxiliary space complexity need to be O(1) 
   * @param 
   * @return PromotedModel
   */
PromotedModel PromotedCarModelStack::peek() {
    // isEmpty is true if there is no PromotedModel in the dequeModelInOrder deque, otherwise it is false.
    bool isEmpty = dequeModelInOrder.empty();

    /* checks if dequeModelInOrder deque is empty and if so it throws a logic error with the
     * message "Promoted car model stack is empty".
     */
    if(isEmpty) {
        throw std::logic_error("Promoted car model stack is empty");
    }

    /* newestModel is the most recent PromotedModel that was added to the deque/stack(is the back of the
     * dequeModelInOrder deque).
     */
    PromotedModel newestModel = dequeModelInOrder.back();

    // returns newestModel(most recent PromotedModel added to the deque/stack).
    return newestModel;
}

/**
   * @brief getHighestPricedPromotedModel, 
   *        getting the highest priced model among the past promoted models
            Both time and auxiliary space complexity need to be O(1)
   * @param 
   * @return PromotedModel
   */
PromotedModel PromotedCarModelStack::getHighestPricedPromotedModel() {
    // isEmpty is true if there is no PromotedModel in the dequeModelInOrder deque, otherwise it is false.
    bool isEmpty = dequeModelInOrder.empty();

    /* checks if dequeModelInOrder deque is empty and if so it throws a logic error with the
     * message "Promoted car model stack is empty".
     */
    if(isEmpty) {
        throw std::logic_error("Promoted car model stack is empty");
    }

    /* highestPriceModel returns the highest price model in the dequePriceMinToMax deque.
     * So this returns the back of the deque as that is the current highest model as this
     * deque is order from least to most current highest value.
     */
    PromotedModel highestPriceModel = dequePriceMinToMax.back();

    // returns the highest price model from the deque/stack(back of dequePriceMinToMax deque).
    return highestPriceModel;
}

/**
   * @brief getLowestPricedPromotedModel, 
   *        getting the lowest priced model among the past promoted models
            Both time and auxiliary space complexity need to be O(1)
   * @param 
   * @return PromotedModel
   */
PromotedModel PromotedCarModelStack::getLowestPricedPromotedModel() {
    // isEmpty is true if there is no PromotedModel in the dequeModelInOrder deque, otherwise it is false.
    bool isEmpty = dequeModelInOrder.empty();

    /* checks if dequeModelInOrder deque is empty and if so it throws a logic error with the
     * message "Promoted car model stack is empty".
     */
    if(isEmpty) {
        throw std::logic_error("Promoted car model stack is empty");
    }

    /* lowestPriceModel returns the lowest price model in the dequePriceMinToMax deque.
     * So this returns the front of the deque as that is the current lowest model as this
     * deque is order from most current lowest price model to what would be the current if
     * that front value is removed(lowest price to highest price).
     */
    PromotedModel lowestPriceModel = dequePriceMinToMax.front();

    // returns the lowest price model from the deque/stack(front of dequePriceMinToMax deque).
    return lowestPriceModel;
}