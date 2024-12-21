/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Fall 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Oct 2022
 */

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>



/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Constructs the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    //below creates tree 1 as shown in the picture above
    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);
    // this marks the end of the created tree 1

    //prints "Tree 1:" which is where the test cases start for tree 1.
    cout << "Tree 1:" << endl;

    // Tests isEmployeePresentInOrg function for tree 1
    // employeePresent boolean variable is the return value of isEmployeePresentInOrg with head(head of tree 1) inserted and whatever id it is looking for.
    // employeePresent is true if the id is in the tree, otherwise it is false.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    asserts(employeePresent, "ID 6 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    asserts(!employeePresent, "ID -2 Not present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 12);
    asserts(employeePresent, "ID 12 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 10);
    asserts(employeePresent, "ID 10 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 4);
    asserts(employeePresent, "ID 4 Present in tree");
    // end of testing isEmployeePresentInOrg function for tree 1

    // Tests findEmployeeLevel function for tree 1
    // employeeLevel int variable is the return value of findEmployeeLevel with head(head of tree 1)
    // inserted as well as the id it wants to know the level for and the current level of head which is 0.
    // employeeLevel returns the level that the id inserted is in.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    int employeeLevel = Orgtree::findEmployeeLevel(head, 4, 0);
    asserts(employeeLevel == 1, "Level of ID 4 returns " + to_string(employeeLevel) + ", expected 1");
    employeeLevel = Orgtree::findEmployeeLevel(head, 5, 0);
    asserts(employeeLevel == 2, "Level of ID 5 returns " + to_string(employeeLevel) + ", expected 2");
    employeeLevel = Orgtree::findEmployeeLevel(head, 27, 0);
    asserts(employeeLevel == -1, "Level of ID 27 returns " + to_string(employeeLevel) + ", expected -1");
    employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    asserts(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");
    employeeLevel = Orgtree::findEmployeeLevel(head, 10, 0);
    asserts(employeeLevel == 3, "Level of ID 10 returns " + to_string(employeeLevel) + ", expected 3");
    // end of testing findEmployeeLevel function for tree 1

    // Tests findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // verifies the returned Employee* has the expected Employee ID
    // sharedEmployee Employee* node is the return value of findClosestSharedManager with head(head of tree 1)
    // inserted as well as the first and second employee you want to find the shared manager for.
    // sharedEmployee returns the shared manager of two employees.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    Employee* sharedEmployee = Orgtree::findClosestSharedManager(head, 1, 5);
    asserts(sharedEmployee->getEmployeeID() == 1, "closest shared between 1 and 5 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 1");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 1, 76);
    asserts(sharedEmployee->getEmployeeID() == 1, "closest shared between 1 and 76 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 76");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 4, 27);
    asserts(sharedEmployee->getEmployeeID() == 4, "closest shared between 4 and 27 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 4");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 10, 74);
    asserts(sharedEmployee->getEmployeeID() == 10, "closest shared between 10 and 74 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 10");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 12, 74);
    asserts(sharedEmployee->getEmployeeID() == 12, "closest shared between 12 and 74 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 12");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 2, 4);
    asserts(sharedEmployee->getEmployeeID() == 1, "closest shared between 7 and 4 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 1");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 5, 6);
    asserts(sharedEmployee->getEmployeeID() == 2, "closest shared between 5 and 6 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 2");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 4, 5);
    asserts(sharedEmployee->getEmployeeID() == 1, "closest shared between 4 and 5 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 1");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 12, 9);
    asserts(sharedEmployee->getEmployeeID() == 9, "closest shared between 12 and 9 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 9");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 10, 11);
    asserts(sharedEmployee->getEmployeeID() == 2, "closest shared between 10 and 11 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 2");
    sharedEmployee = Orgtree::findClosestSharedManager(head, 256, 273);
    asserts(sharedEmployee == nullptr, "closest shared between 256 and 273 returns nullptr if passed");
    // end of testing findClosestSharedManager function for tree 1

    // Tests findNumOfManagersBetween function
    // num int variable is the return value of findEmployeeLevel with head(head of tree 1)
    // inserted as well as the first and second employee you want to find the number of managers in between for.
    // employeeLevel returns the level that the id inserted is in.
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    asserts(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");
    numManagers = Orgtree::findNumOfManagersBetween(head, 7, 8);
    asserts(numManagers == 1, "Managers between 7 and 8 returns " + to_string(numManagers) + ", expected 1");
    numManagers = Orgtree::findNumOfManagersBetween(head, 12, 7);
    asserts(numManagers == 4, "Managers between 12 and 7 returns " + to_string(numManagers) + ", expected 4");
    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 1);
    asserts(numManagers == 0, "Managers between 1 and 1 returns " + to_string(numManagers) + ", expected 0");
    // end of testing findClosestSharedManager function for tree 1

    // Tests deleteOrgtree function
    // deletes the current tree(one that the root is head3).
    // This function prints every node in the tree and then deletes it after it prints it.
    Orgtree::deleteOrgtree(head);

    //prints all test cases for this tree passed and a new line
    cout << endl << "All test cases passed!" << endl;
    cout << endl;

    //creates a new head for the new tree 2, and this tree is an empty tree so the head equals nullptr.
    Employee *head2 = nullptr;

    //prints "Tree 2:" which is where the test cases start for tree 2.
    cout << "Tree 2:" << endl;

    // Tests isEmployeePresentInOrg function for tree 2
    // employeePresent boolean variable is the return value of isEmployeePresentInOrg with head2(head of tree 2) inserted and whatever id it is looking for.
    // employeePresent is true if the id is in the tree, otherwise it is false.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // prints everything as not present because tree is null
    employeePresent = Orgtree::isEmployeePresentInOrg(head2, 6);
    asserts(!employeePresent, "ID 6 Not present in tree");

    // Tests findEmployeeLevel function for tree 2
    // employeeLevel int variable is the return value of findEmployeeLevel with head2(head of tree 2)
    // inserted as well as the id it wants to know the level for and the current level of head which is 0.
    // employeeLevel returns the level that the id inserted is in.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This ends up -1 because tree is null
    employeeLevel = Orgtree::findEmployeeLevel(head2, 4, 0);
    asserts(employeeLevel == -1, "Level of ID 4 returns " + to_string(employeeLevel) + ", expected -1");

    // Tests findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // verifies the returned Employee* has the expected Employee ID
    // sharedEmployee Employee* node is the return value of findClosestSharedManager with head2(head of tree 2)
    // inserted as well as the first and second employee you want to find the shared manager for.
    // sharedEmployee returns the shared manager of two employees.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // returns nullptr because tree is null
    sharedEmployee = Orgtree::findClosestSharedManager(head2, 1, 5);
    asserts(sharedEmployee == nullptr, "closest shared between 1 and 5 returns nullptr if passed");

    // Tests findNumOfManagersBetween function
    // num int variable is the return value of findEmployeeLevel with head2(head of tree 2)
    // inserted as well as the first and second employee you want to find the number of managers in between for.
    // employeeLevel returns -1 because tree is null
    numManagers = Orgtree::findNumOfManagersBetween(head2, 10, 11);
    asserts(numManagers == -1, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected -1");

    // Tests deleteOrgtree function
    // deletes the current tree(one that the root is head2).
    // This function prints every node in the tree and then deletes it after it prints it. (is null and doesn't print anything in this case).
    Orgtree::deleteOrgtree(head2);

    //prints all test cases for this tree passed and a new line
    cout << endl << "All test cases passed!" << endl;
    cout << endl;

    //creates a new head for the new tree 3, and this tree has one employee node and the id of this node is 12
    Employee *head3 = new Employee(12);

    //prints "Tree 3:" which is where the test cases start for tree 3.
    cout << "Tree 3:" << endl;

    // Tests isEmployeePresentInOrg function for tree 3
    // employeePresent boolean variable is the return value of isEmployeePresentInOrg with head3(head of tree 3) inserted and whatever id it is looking for.
    // employeePresent is true if the id is in the tree, otherwise it is false.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    employeePresent = Orgtree::isEmployeePresentInOrg(head3, 12);
    asserts(employeePresent, "ID 12 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head3, -2);
    asserts(!employeePresent, "ID -2 Not Present in tree");
    // end of testing isEmployeePresentInOrg function for tree 3

    // Tests findEmployeeLevel function for tree 3
    // employeeLevel int variable is the return value of findEmployeeLevel with head3(head of tree 3)
    // inserted as well as the id it wants to know the level for and the current level of head which is 0.
    // employeeLevel returns the level that the id inserted is in.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    employeeLevel = Orgtree::findEmployeeLevel(head3, 12, 0);
    asserts(employeeLevel == 0, "Level of ID 12 returns " + to_string(employeeLevel) + ", expected 0");
    employeeLevel = Orgtree::findEmployeeLevel(head3, 27, 0);
    asserts(employeeLevel == -1, "Level of ID 27 returns " + to_string(employeeLevel) + ", expected -1");
    // end of testing findEmployeeLevel function for tree 3

    // Tests findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // verifies the returned Employee* has the expected Employee ID
    // sharedEmployee Employee* node is the return value of findClosestSharedManager with head3(head of tree 3)
    // inserted as well as the first and second employee you want to find the shared manager for.
    // sharedEmployee returns the shared manager of two employees.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    sharedEmployee = Orgtree::findClosestSharedManager(head3, 256, 273);
    asserts(sharedEmployee == nullptr, "closest shared between 256 and 273 returns nullptr if passed");
    sharedEmployee = Orgtree::findClosestSharedManager(head3, 12, 5);
    asserts(sharedEmployee->getEmployeeID() == 12, "closest shared between 12 and 5 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 12");
    // end of testing findClosestSharedManager function for tree 3

    // Tests findNumOfManagersBetween function
    // num int variable is the return value of findEmployeeLevel with head3(head of tree 3)
    // inserted as well as the first and second employee you want to find the number of managers in between for.
    // employeeLevel returns the level that the id inserted is in.
    numManagers = Orgtree::findNumOfManagersBetween(head3, 12, 12);
    asserts(numManagers == 0, "Managers between 12 and 12 returns " + to_string(numManagers) + ", expected 0");
    numManagers = Orgtree::findNumOfManagersBetween(head3, 10, 11);
    asserts(numManagers == -1, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected -1");
    // end of testing findNumOfManagersBetween function for tree 3

    // Tests deleteOrgtree function
    // deletes the current tree(one that the root is head3).
    // This function prints every node in the tree and then deletes it after it prints it.
    Orgtree::deleteOrgtree(head3);

    //prints all test cases for this tree passed and a new line
    cout << endl << "All test cases passed!" << endl;
    cout << endl;

    /*
     * Constructs the following organization chart for testing
     *                          68
     *           /    /          \         \        \
     *          27    64         29        35         69
     *          /    /  \       / | \             /   |   \  \
     *          9   76   54    5  6  112         227 226  209 2
     *         /    / \        |      |
     *       10    22 23      663    664
     */
    Employee *head4 = new Employee(68, vector<int>{27, 64, 29, 35, 69});
    Employee *emp27 = head4->getDirectReports().at(0);
    Employee *emp64 = head4->getDirectReports().at(1);
    Employee *emp29 = head4->getDirectReports().at(2);
    Employee *emp69 = head4->getDirectReports().at(4);


    emp27->addDirectReport(99);
    emp64->addDirectReports(vector<int>{76, 54});
    emp29->addDirectReports(vector<int>{5, 6, 112});
    emp69->addDirectReports(vector<int>{227, 226, 209, 2});

    Employee *emp76 = emp64->getDirectReports().at(0);
    Employee *emp5 = emp29->getDirectReports().at(0);
    Employee *emp112 = emp29->getDirectReports().at(2);

    emp76->addDirectReports(vector<int>{22, 23});
    emp5->addDirectReport(663);
    emp112->addDirectReport(664);
    // this marks the end of the created tree 4

    //prints "Tree 4:" which is where the test cases start for tree 4.
    cout << "Tree 4:" << endl;

    // Tests isEmployeePresentInOrg function for tree 4
    // employeePresent boolean variable is the return value of isEmployeePresentInOrg with head4(head of tree 4) inserted and whatever id it is looking for.
    // employeePresent is true if the id is in the tree, otherwise it is false.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, 227);
    asserts(employeePresent, "ID 227 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, -563);
    asserts(!employeePresent, "ID -563 Not present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, 543);
    asserts(!employeePresent, "ID 543 Not present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, 64);
    asserts(employeePresent, "ID 64 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, 112);
    asserts(employeePresent, "ID 112 Present in tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head4, 23);
    asserts(employeePresent, "ID 23 Present in tree");
    // end of testing isEmployeePresentInOrg function for tree 4

    // Tests findEmployeeLevel function for tree 4
    // employeeLevel int variable is the return value of findEmployeeLevel with head4(head of tree 4)
    // inserted as well as the id it wants to know the level for and the current level of head which is 0.
    // employeeLevel returns the level that the id inserted is in.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    employeeLevel = Orgtree::findEmployeeLevel(head4, 226, 0);
    asserts(employeeLevel == 2, "Level of ID 226 returns " + to_string(employeeLevel) + ", expected 2");
    employeeLevel = Orgtree::findEmployeeLevel(head4, 23, 0);
    asserts(employeeLevel == 3, "Level of ID 23 returns " + to_string(employeeLevel) + ", expected 3");
    employeeLevel = Orgtree::findEmployeeLevel(head4, 1022, 0);
    asserts(employeeLevel == -1, "Level of ID 1022 returns " + to_string(employeeLevel) + ", expected -1");
    employeeLevel = Orgtree::findEmployeeLevel(head4, 68, 0);
    asserts(employeeLevel == 0, "Level of ID 68 returns " + to_string(employeeLevel) + ", expected 0");
    employeeLevel = Orgtree::findEmployeeLevel(head4, 6, 0);
    asserts(employeeLevel == 2, "Level of ID 6 returns " + to_string(employeeLevel) + ", expected 2");
    // end of testing findEmployeeLevel function for tree 4

    // Tests findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // verifies the returned Employee* has the expected Employee ID
    // sharedEmployee Employee* node is the return value of findClosestSharedManager with head4(head of tree 4)
    // inserted as well as the first and second employee you want to find the shared manager for.
    // sharedEmployee returns the shared manager of two employees.
    // The call to asserts is self-explanatory explained in statement printed if the test that it is doing passes or not.
    // This is the same for all these cases that are tested.
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 99, 54);
    asserts(sharedEmployee->getEmployeeID() == 68, "closest shared between 99 and 54 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 68");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 68, 2048);
    asserts(sharedEmployee->getEmployeeID() == 68, "closest shared between 1 and 2048 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 68");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 664, 2048);
    asserts(sharedEmployee->getEmployeeID() == 664, "closest shared between 664 and 2048 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 664");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 227, 209);
    asserts(sharedEmployee->getEmployeeID() == 69, "closest shared between 227 and 209 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 69");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 663, 112);
    asserts(sharedEmployee->getEmployeeID() == 29, "closest shared between 663 and 112 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 29");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 22, 23);
    asserts(sharedEmployee->getEmployeeID() == 76, "closest shared between 22 and 23 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 76");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 22, 54);
    asserts(sharedEmployee->getEmployeeID() == 64, "closest shared between 22 and 54 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 64");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 664, 5);
    asserts(sharedEmployee->getEmployeeID() == 29, "closest shared between 664 and 5 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 29");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 69, 22);
    asserts(sharedEmployee->getEmployeeID() == 68, "closest shared between 69 and 22 returns " + to_string(sharedEmployee->getEmployeeID()) + ", expected 68");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, -5, -20);
    asserts(sharedEmployee == nullptr, "closest shared between -5 and -20 returns nullptr if passed");
    sharedEmployee = Orgtree::findClosestSharedManager(head4, 256, 273);
    asserts(sharedEmployee == nullptr, "closest shared between 256 and 273 returns nullptr if passed");
    // end of testing findClosestSharedManager function for tree 4

    // Tests findNumOfManagersBetween function
    // num int variable is the return value of findEmployeeLevel with head4(head of tree 4)
    // inserted as well as the first and second employee you want to find the number of managers in between for.
    // employeeLevel returns the level that the id inserted is in.
    numManagers = Orgtree::findNumOfManagersBetween(head4, 5, 6);
    asserts(numManagers == 1, "Managers between 5 and 6 returns " + to_string(numManagers) + ", expected 1");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 22, 209);
    asserts(numManagers == 4, "Managers between 22 and 209 returns " + to_string(numManagers) + ", expected 4");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 22, 664);
    asserts(numManagers == 5, "Managers between 22 and 664 returns " + to_string(numManagers) + ", expected 5");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 64, 64);
    asserts(numManagers == 0, "Managers between 64 and 64 returns " + to_string(numManagers) + ", expected 0");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 64, 2048);
    asserts(numManagers == -1, "Managers between 64 and 2048 returns " + to_string(numManagers) + ", expected -1");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 2048, 664);
    asserts(numManagers == -1, "Managers between 2048 and 664 returns " + to_string(numManagers) + ", expected -1");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 2048, 7048);
    asserts(numManagers == -1, "Managers between 2048 and 7048 returns " + to_string(numManagers) + ", expected -1");
    numManagers = Orgtree::findNumOfManagersBetween(head4, 27, 99);
    asserts(numManagers == 0, "Managers between 27 and 99 returns " + to_string(numManagers) + ", expected 0");
    // end of testing findClosestSharedManager function for tree 4

    // Tests deleteOrgtree function
    // deletes the current tree(one that the root is head4).
    // This function prints every node in the tree and then deletes it after it prints it.
    Orgtree::deleteOrgtree(head4);

    //prints all test cases for this tree passed
    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}