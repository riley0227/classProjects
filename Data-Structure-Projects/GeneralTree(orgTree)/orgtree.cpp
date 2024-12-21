/* I the undersigned promise that the submitted assignment is my own work. While I was
 * free to discuss ideas with others, the work contained is my own. I recognize that
 * should this not be the case; I will be subject to penalties as outlined in the course
 * syllabus.
 * Name: Riley Thompson
 * Red ID: 826526487
 */

#include "orgtree.h"

/**
 * Check if an employee is present in an organization chart. 
 * 
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 * @see         
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
  // base case 1: empty organization chart
  // checks if head is null, if so, it is empty organization chart/empty head, so then returns false
  if(head == nullptr) {
    return false;
  }

  // base case 2: if the employee is found, return true
  int headID = head->getEmployeeID(); //head id is the ID of the head employee.
  //checks if the headID is equal to the employee id and if it is, it returns true.
  if(headID == e_id) {
    return true;
  }

  // searches employee from each child of the head
  // return true if the employee is found in one of the child subtree
  // searches through the vector(getDirectReports) which contains the children of the head node.
  for(int i = 0; i < head->getDirectReports().size(); i++)
  {
    // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
    Employee *curr = head->getDirectReports().at(i);
    // recursively calls on each child subtree, which goes through the subtrees of the children and returns true if the id that it is searching for is
    // anywhere in the subtree of the curr node, returns true as it is present in the tree.
    if (isEmployeePresentInOrg(curr, e_id)) {
      return true;
    }
  }

  // if not found, returns false
  return false;
}

/**
 * Find the level of an employee in an organization chart / tree. 
 * 
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth... 
 * 
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization 
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present
 * @see         
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
  // base case 1: empty organization chart
  // checks if head is null, if so, it is empty organization chart so then returns Employee::NOT_FOUND which is -1.
  if(head == nullptr) {
    return Employee::NOT_FOUND;
  }

  // base case 2: the employee is found, returns the employee level
  // creates a headID int variable which gets the id of the head node
  int headID = head->getEmployeeID();
  // if the head node ID is equal to the id that is being looked for, returns the current headlevel which is the level where the head is.
  if(headID == e_id) {
    return headLevel;
  }

  // searches employee from each child of the head
  // searches through the vector(getDirectReports) which contains the children of the head node.
  for(int i = 0; i < head->getDirectReports().size(); i++) {
    // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
    Employee *curr = head->getDirectReports().at(i);
    // the int variable headLvlOfChild adds 1 to the current head level as the child's head level adds one to it.
    int headLvlOfChild = headLevel + 1;
    // recursively calls findEmployeeLevel with the curr node(child of head) with the one higher level, and if it is greater than 0 that means the employee
    // is in the tree, not at the initial head and therefore returns the employee level where the id is as it recursively searches through the tree until the employee is found.
    // employee level is the integer variable that stores the level of the employee that the head level needs to be known for, and this is returned when in tree.
    if (findEmployeeLevel(curr, e_id, headLvlOfChild) > 0) {
      int employeeLevel = findEmployeeLevel(curr, e_id, headLvlOfChild);
      return employeeLevel;
    }
  }
  // if not found, return Employee::NOT_FOUND(-1).
  return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2. 
 * 
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee; 
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart 
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   closest shared manager in the org chart between employee e1 and employee e2
   *           if head is nullptr, returns nullptr
   *           if neither e1 or e2 is present, returns empty employee           
   *           if e1 is present and e2 is not, returns e1
   *           if e2 is present and e1 is not, returns e2
   *           if e1 and e2 both are present, returns their shared manager
   *              if e1 is a manager (ancestor) of e2, returns e1
   *              else if e2 is a manager (ancestor) of e1, returns e2
   *              else returns the shared manager of e1 and e2
 * @see         
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {
  // base case 1: empty organization chart
  // checks if head is null, if so, it is empty organization chart so then returns nullptr.
  if(head == nullptr) {
    return nullptr;
  }

  // base case 2: either e1_id or e2_id is the same as the head / root
  // creates a headID int variable which gets the id of the head node
  int headID = head->getEmployeeID();
  // if the head node ID is equal to the e1_id, returns the current head.
  if(headID == e1_id) {
    return head;
  }
  // if the head node ID is equal to the e2_id, returns the current head.
  if(headID == e2_id) {
    return head;
  }


  // Recursively traverses through direct reports of the head to find
  // where e1 and e2 are
  /*
     For each recursive call (starting from the root), you need to handle three possible scenarios:
     1) if e1 is found in one subtree, and e2 is found from another subtree; 
        the head at that recursive step would be the closest shared manager of e1 and e2.

        you can use the returned pointer (being NOT NULL) from findClosestSharedManager 
        to see if e1 or e2 is found from a subtree (one of the base cases).*/

     /*2) if either e1 or e2 is first found in one subtree (following one subtree), 
        but the other employee is NOT found from any other subtree, then the found 
        employee must either be the manager of the other employee, or the other employee 
        is NOT in the org chart; in either case, the first found employee should be 
        returned as the shared manager.

     3) if neither e1 or e2 is found in the org chart, return nullptr
  */

  //checks if both employees are present in the org tree at the current head and if they both are, continues in this if statement
  if(isEmployeePresentInOrg(head, e1_id) && isEmployeePresentInOrg(head, e2_id)) {
    // searches through the vector(getDirectReports) which contains the children of the head node.
    for(int i = 0; i < head->getDirectReports().size(); i++) {
      // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
      Employee *curr = head->getDirectReports().at(i);
      // if isEmployeePresentInOrg() calls(if e1_id and e2_id are in there) shows that the current had has both id's in it, it will continue down the tree and return
      // a recursive call findClosestSharedManager on the subtree of the current node as it needs to look further.
      // theSharedEmployee Employee node returns the closestSharedManager, which would continue down the tree and call the same function until it is able to
      // find the shared manager, then theSharedEmployee is returned.
      if(isEmployeePresentInOrg(curr, e1_id) && isEmployeePresentInOrg(curr, e2_id)) {
        Employee *theSharedEmployee = findClosestSharedManager(curr, e1_id, e2_id);
        return theSharedEmployee;
      }
      // if e1 is present in the child subtree and e2 isn't, this shows that the head would be the shared manager as the 2 employees would both be below the shared
      //manager in different trees, so this returns head.
      if (isEmployeePresentInOrg(curr, e1_id) && !isEmployeePresentInOrg(curr, e2_id)) {
        return head;
      }
      // if e2 is present in the child subtree and e1 isn't, this shows that the head would be the shared manager as the 2 employees would both be below the shared
      //manager in different trees, so this returns head.
      if (!isEmployeePresentInOrg(curr, e1_id) && isEmployeePresentInOrg(curr, e2_id)) {
        return head;
      }
    }

  // else if the e1_id is present in the current organization and e2_id is not present continues in this if statement.
  // This if statement returns the actual employee of the e1_id.  Basically in this case e1_id is going to be the shared employee as it is the only id of
  // the 2 id's that are in the tree at the head that is given.
  } else if(isEmployeePresentInOrg(head, e1_id) && !isEmployeePresentInOrg(head, e2_id)) {
      // searches through the vector(getDirectReports) which contains the children of the head node.
    for(int i = 0; i < head->getDirectReports().size(); i++) {
      // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
      Employee *curr = head->getDirectReports().at(i);
      // currID is the int variable holding the id of the current employee.
      int currID = curr->getEmployeeID();
      //if the currentID is equal to e1_ID, returns curr as this is the id that is present in the orgtree and e1_id is found.
      if (currID == e1_id) {
        return curr;
      // else if it has searched through all the children of the current head(i >= head->getDirectReports().size() - 1), it will call a recursive call on the
      // children and search the tree until e1_id is found.
      } else if(i >= head->getDirectReports().size() - 1) {
        // searches through the vector(getDirectReports) which contains the children of the head node.
        for(int j = 0; j < head->getDirectReports().size(); j++) {
          // curr2 Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
          Employee *curr2 = head->getDirectReports().at(j);
          // if isEmployeePresentInOrg() of the child returns true, it means that e1_id is in that subtree, so then searches that subtree with head curr2
          // by returning the recursive call of findClosestSharedManager() with the curr2.
          // empOfE1_ID is the Employee* node found through recursion, that is the employee of e1_id.
          if(isEmployeePresentInOrg(curr2, e1_id)) {
            Employee *empOfE1_ID = findClosestSharedManager(curr2, e1_id, e2_id);
            return empOfE1_ID;
          }
        }
      }
    }
  // else if the e2_id is present in the current organization and e1_id is not present continues in this if statement.
  // This if statement returns the actual employee of the e2_id.  Basically in this case e2_id is going to be the shared employee as it is the only id of
  // the 2 id's that are in the tree at the head that is given.
  } else if(!isEmployeePresentInOrg(head, e1_id) && isEmployeePresentInOrg(head, e2_id)) {
    // searches through the vector(getDirectReports) which contains the children of the head node.
    for(int i = 0; i < head->getDirectReports().size(); i++) {
      // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
      Employee *curr = head->getDirectReports().at(i);
      // currID is the int variable holding the id of the current employee.
      int currID = curr->getEmployeeID();
      //if the currentID is equal to e2_ID, returns curr as this is the id that is present in the orgtree and e2_id is found.
      if (currID == e2_id) {
        return curr;
      // else if it has searched through all the children of the current head(i >= head->getDirectReports().size() - 1), it will call a recursive call on the
      // children and search the tree until e2_id is found.
      } else if(i >= head->getDirectReports().size() - 1) {
        // searches through the vector(getDirectReports) which contains the children of the head node.
        for(int j = 0; j < head->getDirectReports().size(); j++) {
          // curr2 Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
          Employee *curr2 = head->getDirectReports().at(j);
          // if isEmployeePresentInOrg() of the child returns true, it means that e2_id is in that subtree, so then searches that subtree with head curr2
          // by returning the recursive call of findClosestSharedManager() with the curr2.
            // empOfE2_ID is the Employee* node found through recursion, that is the employee of e2_id.
          if(isEmployeePresentInOrg(curr2, e2_id)) {
            Employee *empOfE2_ID = findClosestSharedManager(curr2, e1_id, e2_id);
            return empOfE2_ID;
          }
        }
      }
    }
  }

  //if e1_id and e2_id are not found, returns nullptr.
  return nullptr;
}

/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 * @see         
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {
  // Continue only if both employee nodes e1_id and e2_id are in the org chart tree
  // otherwise, return Employee::NOT_FOUND
  // checks first if both e1_id and e2_id are in the tree and if so, continues otherwise goes over this and returns Employee::NOT_FOUND.
  if(isEmployeePresentInOrg(head, e1_id) && isEmployeePresentInOrg(head, e2_id)) {
    // checks if e1_id and e2_id are equal, and if they are return 0, as this is the same employee and there wouldn't be a -1 manger in between them, so returns 0 instead
    // Also returns 0, when back to back employees(one is parent of other)(shown in test cases), but this is done so through the same calculations below this if statement
    if(e1_id == e2_id) {
      return 0;
    }
    // The closestSharedManager Employee* node finds/is the closest shared manager for the 2 id's.
    Employee* closestSharedManager = findClosestSharedManager(head, e1_id, e2_id);
    // closestSharedManagerID is the ID of the closest shared manager
    int closestSharedManagerID = closestSharedManager->getEmployeeID();
    // levelOfClosestSharedManager finds/is the level of the closest shared manager
    int levelOfClosestSharedManager = findEmployeeLevel(head, closestSharedManagerID, 0);
    // levelOfe1_id is level of the employee with id e1_id.
    int levelOfe1_id = findEmployeeLevel(head, e1_id, 0);
    // levelOfe2_id is level of the employee with id e2_id.
    int levelOfe2_id = findEmployeeLevel(head, e2_id, 0);
    // numManagerBetween is the number of managers between the 2 employees.
    int numManagersBetween = (levelOfe1_id - levelOfClosestSharedManager) + (levelOfe2_id - levelOfClosestSharedManager) - 1;
    // returns the number of Managers between the 2 employees.
    return numManagersBetween;
  }

  //returns Employee::NOT_FOUND if either e1_id or e2_id is not in the tree.
  return Employee::NOT_FOUND;
}

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 
 *
 * DO NOT worry about removing them from the vector directReports
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None 
 * 
 * @see         
 */

// goes through this function and call recursively till hits a nullptr node which means it at the bottom of the tree then starts deleting the tree.
// (order shown through printing)
void Orgtree::deleteOrgtree(Employee* head) {
  // base case: empty tree or organization chart
  // checks if head is null, if so, it is empty organization chart so then returns and exits out of the function
  if(head == nullptr) {
    return;
  }

  // deletes children recursively
  // searches through the vector(getDirectReports) which contains the children of the head node.
  for(int i = 0; i < head->getDirectReports().size(); i++) {
    // curr Employee* node returns the current employee that it gets at i in the vector of children from the head node(current employee looking at).
    Employee *curr = head->getDirectReports().at(i);
    // recursively calls deleteOrgtree with curr as head, which will make it get to the bottom of the tree and and start removing nodes in the correct order.
    deleteOrgtree(curr);
  }

  // print the head id and creates a new line before deleting the head.
  cout << head->getEmployeeID() << endl;
  // Then deletes the head.
  delete head;
}