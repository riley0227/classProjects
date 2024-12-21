/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/

#include "orgchart.h"
#include <iostream>
using namespace std;

// The constructor
EmployeeNode::EmployeeNode(int managerLevels, int currlevel, int childrenOfCurrEmployee, int childrenOfNextLvl, int* managerchildrenarray) {

    // This is an array of integers that was made from the second line in orgchart.txt/the amount of children a manager can have at each level
    this->managerchildrenarray = managerchildrenarray;
    this->managerLevels = managerLevels;
    this->currlevel = currlevel;
    this->childrenOfCurrEmployee = childrenOfCurrEmployee;
    this->childrenOfNextLvl = managerchildrenarray[currlevel];

    // Allocated memory for children array and initializes the nodes to nullptr
    this->children = new EmployeeNode*[childrenOfCurrEmployee];
    for (int i = 0; i < childrenOfCurrEmployee; i++) {
        children[i] = nullptr;
    }
}

//The deconstructor
EmployeeNode::~EmployeeNode() {
    for (int i = 0; i < childrenOfCurrEmployee; i++) {
        delete children[i];
    } 
    delete[] children;
}

// Creates a child node from a current node, used in addEmployees()
EmployeeNode* EmployeeNode::createChildNode(EmployeeNode* current) {
    // First checks if the current level is above the managers levels and if it is above, returns nullptr as it would skip the if statement.
    int nextLevel = current->currlevel;
    if (nextLevel < current->managerLevels) {
        return new EmployeeNode(
            current->managerLevels,
            current->currlevel + 1,
            current->managerchildrenarray[current->currlevel + 1],
            current->managerchildrenarray[current->currlevel + 2],
            current->managerchildrenarray
        );
    }
    return nullptr;
}

// Adds employees to the tree from their employeeID path
bool EmployeeNode::addEmployees(const char* employeeIDPath) {
    // Sets the current node to root
    EmployeeNode* currNode = this;

    // Goes to index afte e_
    int i = 2; 

    // Goes through employeeIDPath until end of the path given
    while (employeeIDPath[i] != '\0') {
        char currentChar = employeeIDPath[i];

        bool isDigit = currentChar >= '0' && currentChar <= '9';
        if (isDigit) {
            // Character to integer conversion, and is the childs index from path
            int childIndex = currentChar - '0';

            // Checks if child index in range allowed
            bool allowedChildIndex = (childIndex >= 0) && (childIndex < currNode->childrenOfCurrEmployee);
            if (allowedChildIndex) {
                // Sees if the child at the child index is not created, and if not, will create that child node
                int childThere = currNode->children[childIndex] == nullptr;
                if (childThere) {
                    currNode->children[childIndex] = createChildNode(currNode);
                }

                // Goes to the child node at the childIndex/moves the pointer to that node
                currNode = currNode->children[childIndex];
            } else {
                // The child node is invalid if gets here so would return false
                return false;
            }
        } else if (currentChar == '_') {
            //for 2 or more underscores returns false
            if (employeeIDPath[i + 1] == '_') {
                return false;
            }
            // This else if just goes to the next integer char and skips the underscores
            i++;
            continue;
        } else {
            // Returns false for invalid digits
            return false;
        }
        // Goes to next index
        i++;
    }

    // Created the entire employee path and adds the employee specified to tree, returning true
    return true;
}


// Finds an employee in tree or returns nullptr
EmployeeNode* EmployeeNode::findEmployee(const char *employeeIDPath) {
    std::cout << employeeIDPath << " ";
    
    // Sets the current node to root
    EmployeeNode* current = this;


    // Goes to index afte e_
    int i = 2; 

    // Goes through employeeIDPath until end of the path given
    while (employeeIDPath[i] != '\0') {
        char currentChar = employeeIDPath[i];

        bool isDigit = currentChar >= '0' && currentChar <= '9';
        if (isDigit) {
            // Character to integer conversion, and is the childs index from path
            int childIndex = currentChar - '0';

            // Checks if child index in range allowed
            bool allowedChildIndex = (childIndex >= 0) && (childIndex < current->childrenOfCurrEmployee);
            if (allowedChildIndex) {
                // Sees if the child at the child index is not created, and if not, does not return an employee(returns nullptr as not there)
                int childThere = current->children[childIndex] == nullptr;
                if (childThere) {
                    return nullptr;
                }

                // Goes to the child node at the childIndex/moves the pointer to that node
                current = current->children[childIndex];
            } else {
                return nullptr;
            }
        } else if (currentChar == '_') {
            //for 2 or more underscores returns null
            if (employeeIDPath[i + 1] == '_') {
                return nullptr;
            }
            // This else if just goes to the next integer char and skips the underscores
            i++;
            continue;
        } else {
            // Returns nullptr for invalid digits
            return nullptr;
        }
        // Goes to next index
        i++;
    }
    // There is an employee
    return current;
}
