/**
 * Driver file for CS 210 Program 2
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Oct, 2022
 *
 * Runs the student code and provides 1 test case.
 * This case may not test everything and it is
 * always recommended that you implement your own
 * tests. Driver files will not necessarily be
 * provided for all projects.
 */


#include <stdlib.h>
#include <iostream>

#include "promotedCarModelStack.h"

using namespace std;

bool equalsIgnoreCase(const string& a, const string& b) {
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

void testHighestLowestPeek(string highestPricedModel,
                          int highestPrice,
                          string lowestPricedModel,
                          int lowestPrice,
                          string peekModel,
                          int peekModelPrice,
                          PromotedCarModelStack stack) {

    if (equalsIgnoreCase(stack.getHighestPricedPromotedModel().getModel(), highestPricedModel)) {
        cout << "Stack highest priced model matches" << endl;
    } else {
        cout << "FAILED: Stack highest priced model does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.getHighestPricedPromotedModel().getPromotedPrice() == highestPrice) {
        cout << "Stack highest priced model's price matches" << endl;
    } else {
        cout << "FAILED: Stack highest priced model's price does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (equalsIgnoreCase(stack.getLowestPricedPromotedModel().getModel(), lowestPricedModel)) {
        cout << "Stack lowest priced model matches" << endl;
    } else {
        cout << "FAILED: Stack lowest priced model does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.getLowestPricedPromotedModel().getPromotedPrice() == lowestPrice) {
        cout << "Stack lowest priced model's price matches" << endl;
    } else {
        cout << "FAILED: Stack lowest priced model's price does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (equalsIgnoreCase(stack.peek().getModel(), peekModel)) {
        cout << "Stack peek matches" << endl;
    } else {
        cout << "FAILED: Stack peek does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.peek().getPromotedPrice() == peekModelPrice) {
        cout << "Stack peek price matches" << endl;
    } else {
        cout << "FAILED: Stack peek price does NOT match" << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {

    PromotedCarModelStack stack;

    cout << "Pushing m3 at 35,000" << endl;
    stack.push("m3", 35000);
    testHighestLowestPeek("m3", 35000,
                          "m3", 35000,
                          "m3", 35000, stack);

    cout << endl << "Pushing ms at 64,000" << endl;
    stack.push("ms", 64000);
    testHighestLowestPeek("ms", 64000,
                          "m3", 35000,
                          "ms", 64000, stack);

    cout << endl << "Pushing my at 38,000" << endl;
    stack.push("my", 38000);
    testHighestLowestPeek("ms", 64000,
                          "m3", 35000,
                          "my", 38000, stack);

    cout << endl << "Popping from stack" << endl;
    PromotedModel popped = stack.pop();

    if (equalsIgnoreCase(popped.getModel(), "my")) {
        cout << "Popped model matches" << endl;
    } else {
        cout << "FAILED: Popped model does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (popped.getPromotedPrice() == 38000) {
        cout << "Popped price matches" << endl;
    } else {
        cout << "Popped price does NOT match" << endl;
        exit(EXIT_FAILURE);
    }

    testHighestLowestPeek("ms", 64000,
                          "m3", 35000,
                          "ms", 64000, stack);

    cout << endl << "SUCCESS! All tests passed!" << endl;

    exit(EXIT_SUCCESS);
}
