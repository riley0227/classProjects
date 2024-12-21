/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/

#ifndef A1EMPLOYEETREE
#define A1EMPLOYEETREE

class EmployeeNode {
public:
    EmployeeNode **children; 
    int managerLevels;
    int currlevel;
    int childrenOfCurrEmployee;
    int childrenOfNextLvl;
    int* managerchildrenarray;

    EmployeeNode(int managerLevels, int currlevel, int childrenOfCurrEmployee, int childrenOfNextLvl, int* managerchildrenarray);
    ~EmployeeNode();
    bool addEmployees(const char *employeeIDPath);
    EmployeeNode* createChildNode(EmployeeNode* current);
    EmployeeNode* findEmployee(const char *employeeIDPath);
    void countNumOfEmployeesInOrgchart (EmployeeNode* startNode, unsigned int &count);
};

#endif
