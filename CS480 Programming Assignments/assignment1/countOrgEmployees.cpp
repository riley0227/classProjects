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
#include <cstring>
#include <fstream>
using namespace std;

// Counts the num of employees under a starting node
void countNumOfEmployeesInOrgchart(EmployeeNode* currNode, unsigned int& count) {
    // If the current node is null, would return and not continue down the tree
    if (currNode == nullptr) {
        return;
    }

    // Add 1 to count
    count++;

    // Counts the employees in each child using recursion
    for (int i = 0; i < currNode->childrenOfCurrEmployee; i++) {
        countNumOfEmployeesInOrgchart(currNode->children[i], count);
    }
}

// Makes the array put in here(an integer array) have the integer values given from the line that is put in here(which would be line 2 of orgchart.txt)
// Essentially the array would be the number of children each manager can have at each levelbased of index
void convertRowTwoToArrOfInts(const std::string& line, int arr[]) {
    int i = 0;
    int j = 0;
    int currDigit = 0;
    int nextDigit = 0;

    for (i = 0; i < (int)line.length(); i++) {
        // Only add the numbers to the array, so if it's not a space
        if (line[i] != ' ') {
            currDigit = line[i] - '0';
            // Checks if there is another character number and would make it into a double digit integer
            if ((line[i + 1] != ' ') && (line[i + 1] != '\0')) {
                nextDigit = line[i + 1] - '0';
                arr[j] = (currDigit * 10) + nextDigit;
                j++;
                i++;
            } else {
                // Converts to an integer and stores it in the array
                arr[j] = currDigit;
                j++;
            }
        }
    }
};

int main(int argc, char **argv) {
    // opens orgchart
    std::ifstream orgchartfile(argv[1]);
    std::string orgchartline;

    // Reads first line of orgchart.txt and gets the last digit of it, which would be the managerlevels
    std::getline(orgchartfile, orgchartline);
    char lastCharOfman = orgchartline[orgchartline.length() - 1];
    int managerlevels = lastCharOfman - '0';
    
    // Gets the array for number number of children at each level
    std::getline(orgchartfile, orgchartline);
    int* managerchildrenarray = new int[managerlevels];
    convertRowTwoToArrOfInts(orgchartline, managerchildrenarray);

    // Gets number of children there can be for root node and the next level(1)
    int childrenOfRootNode = managerchildrenarray[0];
    int childrenOfNextLvl = managerchildrenarray[1];

    // Initializes the rootnode of the tree
    int rootlvl = 0;
    EmployeeNode rootNode = EmployeeNode(managerlevels, rootlvl, childrenOfRootNode, childrenOfNextLvl,  managerchildrenarray);

    // Reads the employeeID paths and puts all the employees into the chart with addEmployees()
    while(std::getline(orgchartfile, orgchartline)) {
        rootNode.addEmployees(orgchartline.c_str());
    }

    // Opens testfile
    std::ifstream testfile(argv[2]);
    std::string testfileline;

    unsigned int employeesUnderCurrNode = 0;

    // Reads the employeeID paths and finds that employee using findEmployee()
    // Then counts the number of employees under a node given with countNumOfEmployeesInOrgchart()
    while(std::getline(testfile, testfileline))
    {
        employeesUnderCurrNode = 0;

        EmployeeNode* foundNode = rootNode.findEmployee(testfileline.c_str());
        countNumOfEmployeesInOrgchart(foundNode, employeesUnderCurrNode);
        std::cout << employeesUnderCurrNode << "\n";
    }
    
    return 0;
};