/**
 * Driver file for CS 210 Program 1
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Sept, 2022
 *
 * Runs the student code and provides 3 test cases.
 * These cases may not test everything and it is
 * always recommended that you implement your own
 * tests. Driver files will not necessarily be
 * provided for all projects.
 */

#include "sortcar.h"

#include <string>
#include <iostream>

// Bad practice but ok for small project
using namespace std;

void printvector(string prefix, vector<string> v) {
    cout << prefix << " ";
    for (auto m: v)
        cout << m << ' ';
    cout << "\n";
}

// test sorting inventory array with one car model (one element)
void test_oneEleArr() {

    vector<string> order {"mx", "my", "mz"};
    vector<string> invarr {"mz"};

    vector<string> order_stu (order); // deep copy
    vector<string> invarr_stu (invarr); // deep copy

    printvector("Order:", order);
    printvector("Car Inventory:", invarr);

    // to use the solution output
    //vector<string> expected = SortCar().sortCarInventory(invarr, order);
    vector<string> expected {"mz"};
    vector<string> result_from_student = SortCar::sortCarInventory(invarr_stu, order_stu);

    printvector("Expected:", expected);
    printvector("Returned:", result_from_student);

    if (expected != result_from_student)
        cout << "Test FAILED: Returned did not match expected" << endl;
    else
        cout << "Test Passed" << endl;
}

void test_twoEleArr() {

    vector<string> order {"my", "mx", "mz"};
    vector<string> invarr {"my", "my"};

    vector<string> order_stu (order); // deep copy
    vector<string> invarr_stu (invarr); // deep copy

    printvector("Order:", order);
    printvector("Car Inventory:", invarr);

    // to use the solution output
    //vector<string> expected = SortCar().sortCarInventory(invarr, order);
    vector<string> expected {"my", "mz"};
    vector<string> result_from_student = SortCar::sortCarInventory(invarr_stu, order_stu);

    printvector("Expected:", expected);
    printvector("Returned:", result_from_student);

    if (expected != result_from_student)
        cout << "Test FAILED: Returned did not match expected" << endl;
    else
        cout << "Test Passed" << endl;
}

void test_multipleEleArr() {

    vector<string> order {"mx", "my", "mz"};
    vector<string> invarr {"mz", "my", "mz", "mx", "mx",
                           "mx", "my", "mz", "my", "mx"};
    //vector<string> invarr {"mz"};
    vector<string> order_stu (order); // deep copy
    vector<string> invarr_stu (invarr); // deep copy

    printvector("Order:", order);
    printvector("Car Inventory:", invarr);

    // to use the solution output
    //vector<string> expected = SortCar().sortCarInventory(invarr, order);
    vector<string> expected {"mx", "mx", "mx", "mx", "my",
                             "my", "my", "mz", "mz", "mz"};
    vector<string> result_from_student = SortCar::sortCarInventory(invarr_stu, order_stu);

    printvector("Expected:", expected);
    printvector("Returned:", result_from_student);

    if (expected != result_from_student)
        cout << "Test FAILED: Returned did not match expected" << endl;
    else
        cout << "Test Passed" << endl;
}

int main() {
    test_oneEleArr();
    cout << endl;
    test_twoEleArr();
    cout << endl;
    test_multipleEleArr();
}