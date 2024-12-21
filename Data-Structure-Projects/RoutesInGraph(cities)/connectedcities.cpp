/* I the undersigned promise that the submitted assignment is my own work. While I was
 * free to discuss ideas with others, the work contained is my own. I recognize that
 * should this not be the case; I will be subject to penalties as outlined in the course
 * syllabus.
 * Name: Riley Thompson
 * Red ID: 826526487
 */

#include <map>
#include "connectedcities.h"
#include <vector>
#include <string>
#include <algorithm>

/**
 * <p>
 * Part A 
 * ---------------------------------------------------------------------------------------
 * For each city in a city list, find the list of reachable cities starting from the city 
 * following the train routes, and sort the cities in the descending order based on the 
 * number of their reachable cities.  
 * 
 * Required specifications - 
 *
 * Given a list of cities, and a list of one-way train routes from one city to another:
 *
 * 1) Create a graph with each node in the graph as an instance of the CityNode class,
 *    the graph can use any STL collection by your choice.
 *
 * 2) Populate the direct routes information to each CityNode's directRoutedCities collection.
 *    This is like an adjacency list graph representation.
 *
 * 3) For each city node in the graph, use Depth First Search algorithm to find all reachable 
 *    cities starting from the city following the train routes and store those reachable cities to 
 *    the CityNode's reachableCities collection. 
 *
 *    IMPORTANT: The reachable cities must include the starting city itself.  
 *
 *    Note: The train route can go from the starting city and stop at several cities 
 *          before reaching the destination city, all cities including the starting city and 
 *          the destination city along the path would be counted as reachable cities from 
 *          the city where the train starts.
 *
 * 4) Sort the cities in the descending order based on the number of their reachable cities,
 *    so that after sorting, starting from the first city in the sorted order, the train can 
 *    reach the greatest number of destination cities following the given one-way routes. 
 *
 * 5) You must use a RECURSIVE algorithm to implement the Depth First Search part to find
 *    all reachable cities from a starting city given the train routes, using an iterative 
 *    approach would result in a 30% penalty to your assignment 4 grade.  
 *
 * 6) You may add necessary helper functions as needed. Follow the comments for hints.
 * 
 * Assumptions - 
 * 1) Each city is represented by a unique two-letter code like "SD", "LA", 
 *    "SF", "SJ", "NY", etc.
 * 2) Each one-way train route is represented by a pair of city codes; for example, 
 *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to 
 *    Los Angeles (LA). 
 *
 * <p>
 * Part B
 * ---------------------------------------------------------------------------------------
 * Show the upper bound of the time complexity of this function would be O(c^2 + c * r) 
 * where:
 * c is the number of cities
 * r is the number of direct routes between cities
 * 
 * ---------------------------------------------------------------------------------------
 * @param  cities  a list of cities with each city identified by a two letter code
 * @param  routes  pairs of one-way train routes with each one-way train route represented 
 *                 by a pair of city codes; for example, route {"SD", "LA"} means train 
 *                 can go one-way from San Diego (SD) to Los Angeles (LA).
 *
 *                 NOTE: examples of routes are { {"SD", "LA"},
 *                                                {"LA", "SJ"},
 *                                                {"SJ", "SF"}
 *                                              }   
 *                       refer to driver.cpp for more examples.  
 *
 * @return       A list of CityNode in the descending order based on the number of their 
 *               reachable cities following the train routes
 * @see
 */
vector<CityNode> ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(vector<string> cities, vector<pair<string, string>> trainRoutes) {

    // creates a map by calling correlatedCityToCityNode
    map<string, CityNode> cityMap = correlateCityToCityNode(cities);

    // adds the direct routes of cities to the nodes in the map
    addDirectRoutesOfCities(cityMap, trainRoutes);

    // adds reachable cities to the nodes in the map
    callAddReachableCitiesForAllNodes(cityMap, cities);

    // creates a vector of strings with the name of all the cities sorted in order
    vector<string> sortedCities = sortTheCities(cityMap, cities);

    //creates CityNode vector from vector of strings
    vector<CityNode> sortedCitiesWithNodes = sortedCitiesToSortedCitiesNodes(cityMap, sortedCities);

    //returns sortedCitiesWithNodes
    return sortedCitiesWithNodes;
}

/**
 * Creates a graph with each node in the graph as an instance of the CityNode class,
 * the graph can use any STL collection(map).
 * @param cities a list of cities with each city identified by a two letter code
 * @return cityMap which is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 */
map<string, CityNode> ConnectedCities::correlateCityToCityNode(vector<string> &cities) {
    // is a map with string as key and CityNode as value, named cityMap
    map<string, CityNode> cityMap;

    // creates different nodes for each city/ keys for each city
    for(int i = 0; i < cities.size(); i++) {
        // node of the current city
        CityNode currCityNode = CityNode(cities.at(i));
        // string/unique 2 letter code of current city
        string currCityString = cities.at(i);
        // adds adds the currentCityNode and currCityString to map
        cityMap.emplace(currCityString, currCityNode);
    }

    // returns the cityMap created
    return cityMap;
}

/**
 * Populates the direct routes information to each CityNode's directRoutedCities collection.
 * This is like an adjacency list graph representation.
 * @param cityMap is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 * @param trainRoutes all the train routes in the graph
 */
void ConnectedCities::addDirectRoutesOfCities(map<string, CityNode> &cityMap, vector<pair<string, string>> &trainRoutes) {
    // adds all direct routes to each node, loops through all train routes and adds to the key values
    for(int i = 0; i < trainRoutes.size(); i++) {
        // gets the current city it's at(first value in pair)
        string currCity = trainRoutes.at(i).first;
        // gets the city train route goes to(direct route)(second value in pair)
        string currCityTo = trainRoutes.at(i).second;
        // gets the current cityNode through the map and adds the direct city, which is where the route goes to,  to the directRoutedCities of the current cityNode
        cityMap.at(currCity).addADirectRoutedCity(currCityTo);
    }
}

/**
 * For each city node in the graph, it uses Depth First Search algorithm to find all reachable
 * cities starting from the city following the train routes and store those reachable cities to
 * the CityNode's reachableCities collection.
 * @param city the name of the current city being passed to the addReachableCitiesToNode function which changes each recursive cycle through the function
 * @param nodeToGetReachableCities the node it is getting all the reachable cities for and adding the reachable cities to that node
 * @param cityMap is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 * @return "" returns just quotes so nothing as just recursively goes through the function and adds to reachable cities of the nodeToGetReachableCities node
 */
string ConnectedCities::addReachableCitiesToNode(string city, CityNode &nodeToGetReachableCities, map<string, CityNode> &cityMap){
    // checks if current reachable city is in the vector of reachable cities which means it has been visited, if it hasn't adds
    // that city to the that vector
    // if the city is not in reachable cities goes to city and then goes through directRoutes of that city

    // cityInReachCities changes to 1 if the current city has been visited
    int cityInReachCities = 0;

    // loops through reachable cities and if it finds that the city is in reachable cities, changes cityInReachCities to 1
    for(int i = 0; i < nodeToGetReachableCities.getReachableCities().size(); i++) {
        if(city == nodeToGetReachableCities.getReachableCities().at(i)) {
            cityInReachCities = 1;
        }
    }

    // if cityInReachCities is 0, means that the city hasn't been visited and will continue into the if statement
    if(cityInReachCities == 0) {
        // adds the reachable cities to the nodes reachableCities vector
        nodeToGetReachableCities.addReachableCity(city);
            // loops through all the direct routes of the current city and recursively calls this function on those direct routed cities
            // this makes the function keep getting called until there has been a city already visited or nowhere else to go and all teh reachable
            // cities are added
            for (int i = 0; i < cityMap.at(city).getDirectRoutedCities().size(); i++) {
                string currDirectRoutedCity = cityMap.at(city).getDirectRoutedCities().at(i);
                addReachableCitiesToNode(currDirectRoutedCity, nodeToGetReachableCities, cityMap);
            }
    }

    // returns "" when complete and will exit the recursive function
    return "";
}

/**
 * is a function that loop to add all reachableCities for all nodes, calling recursion function, addReachableCitiesToNode for each node.
 * @param cityMap is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 * @param cities a list of cities with each city identified by a two letter code
 */
void ConnectedCities::callAddReachableCitiesForAllNodes(map<string, CityNode> &cityMap, vector<string> &cities){
    // goes through all the cities, gotten from the cities vector, and recursively calls addReachableCitiesToNode/adds all reachable cities for all nodes through this loop
    for(int i = 0; i < cities.size(); i++) {
        // is the current city
        string currCity = cities.at(i);
        // calls addReachableCitiesToNode for each city, and gives paramenter of the name of that city, the node of that city, and the cityMap
        addReachableCitiesToNode(currCity, cityMap.at(currCity), cityMap);
    }
}

/**
 * Sorts the cities in the descending order based on the number of their reachable cities,
 * so that after sorting, starting from the first city in the sorted order, the train can
 * reach the greatest number of destination cities following the given one-way routes.
 * @param cityMap is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 * @param cities a list of cities with each city identified by a two letter code
 * @return returns a string vector of the city names sorted in order
 */
vector<string> ConnectedCities::sortTheCities(map<string, CityNode> &cityMap, vector<string> &cities) {
    // temporary unsortedCities vector
    vector<string> unsortedCities;

    // adds cities to unsorted cities in an unsorted order
    for (int i = 0; i < cities.size(); i++) {
        string currCity = cities.at(i);
        unsortedCities.push_back(currCity);
    }

    // sorts the vector, unsortedCities, alphabetically
    std::stable_sort(unsortedCities.begin(), unsortedCities.end());

    // creates a string that will hold the current greatest of unsorted part of vector
    string greatest = "";

    // orders the cities from most reachable cities to least
    // finds the greatest, and moves to position i each time which sorts in order
    for (int i = 0; i < unsortedCities.size(); i++) {
        // changes greatest to the city at i
        greatest = unsortedCities.at(i);
        //compares all the values greater than i and stored the greatest value into greatest, and puts it at position i
        for(int j = i + 1; j < unsortedCities.size(); j++) {
            // current node with the greatest number of reachable cities actual amount of reachable cities
            int currGreatestNumReachableCities = cityMap.at(greatest).getReachableCities().size();
            // the amount of reachable cities in the current node
            int currCityNumReachableCities = cityMap.at(unsortedCities.at(j)).getReachableCities().size();
            // if the current node has a greater number of reachable cities than the current greatest number of reachable cities, that city becomes the greatest city
            if(currCityNumReachableCities > currGreatestNumReachableCities) {
                    greatest = unsortedCities.at(j);
            }

        }
        // removes the greatest city from current spot and puts it at i(could be removing and putting back in same place if city at i is the greatest)
        for(int k = 0; k < unsortedCities.size(); k++) {
            // checks if unsortedCities is at k, if is goes into if statement
            if (unsortedCities.at(k) == greatest) {
                // erases value at k(greatest value)
                unsortedCities.erase(unsortedCities.begin() + k);
                // adds the greatest value to position i
                unsortedCities.insert(unsortedCities.begin() + i, greatest);
            }
        }

    }

    // creates sortedCities vector
    vector<string> sortedCities;
    // puts the unsortedCities vector into sortedCities vector as it is now a sorted vector
    sortedCities = unsortedCities;
    // returns sortedCities
    return sortedCities;
}

/**
 * creates CityNode vector from vector of strings(uses map that has the key as the string and the value as the CityNode of that string)
 * @param cityMap is a map with the string of the city as key and that CityNode as value, so can easily access the city nodes.
 * @param sortedCities is the sortedCities vector that has a list of strings with the cities sorted in the correct order
 * @return a vector with CityNode's that are in proper order by number of its reachableCities by train, then alphabetically
 */
vector<CityNode> ConnectedCities::sortedCitiesToSortedCitiesNodes(map<string, CityNode> &cityMap, vector<string> &sortedCities) {
    // creates a vector of CityNode's named sortedCitiesWithNodes
    vector<CityNode> sortedCitiesWithNodes;

    // loops through the sortedCities vector and adds the node that corresponds with that vector to the sortedCitiesWithNodes vector
    for(int i = 0; i < sortedCities.size(); i++) {
        // the city node that comes from the cityMap, corresponding to the key value of the current city at position i of sortedCities vector
        CityNode currCityNode = cityMap.at(sortedCities.at(i));
        // adds the currCityNode to the vector sortedCitiesWithNodes
        sortedCitiesWithNodes.push_back(currCityNode);
    }

    // returns sortedCitiesWithNodes vector
    return sortedCitiesWithNodes;
}