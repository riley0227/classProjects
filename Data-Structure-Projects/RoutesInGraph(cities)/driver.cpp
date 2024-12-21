/**
 * Start of a driver file to test connectedCities.cpp
 * CS 210 Fall 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Nov 2022
 */

#include "connectedcities.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

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
    // prints graph 1
    cout << "Graph 1:" << endl;

    /* Construct a graph for testing(graph 1)
     *    SD ---> DL <--------
     *    ^                   |
     *    |                   |
     *    OD <--- JL <--------|--
     *                        |  |
     *    BV <---             |  |
     *    --->  LA ---> BU    |  |
     *          ^             |  |
     *          |             |  |
     *  SJ ---> SK ---> IV ---|  |
     *                           |
     *  <---------------         |
     *  SF ---> HT ---> NH ------|
     */

    // all the names of cities in graph 1
    vector<string> cities_1 {"SD", "LA", "SK", "IV", "JL", "SF", 
                             "DL", "HT", "OD", "NH", "BV", "SJ", "BU"};

    // trainRoutes vector for graph 1
    vector<pair<string, string>> trainRoutes;

    // adds all the train routes to trainRoutes vector for graph 1
    trainRoutes.emplace_back("JL", "OD");
    trainRoutes.emplace_back("OD", "SD");
    trainRoutes.emplace_back("SD", "DL");
    trainRoutes.emplace_back("BV", "LA");
    trainRoutes.emplace_back("LA", "BV");
    trainRoutes.emplace_back("LA", "BU");
    trainRoutes.emplace_back("SK", "IV");
    trainRoutes.emplace_back("SK", "LA");
    trainRoutes.emplace_back("SJ", "SK");

    trainRoutes.emplace_back("IV", "DL");
    
    trainRoutes.emplace_back("SF", "HT");
    trainRoutes.emplace_back("HT", "NH");
    trainRoutes.emplace_back("NH", "SF");
    trainRoutes.emplace_back("NH", "JL");

    // returns the cities of graph 1 sorted and stores in cities
    vector<CityNode> cities = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_1, trainRoutes);

    // cities returned from the above call are sorted according to 
    // the ascending order of the city names and 
    // the descending order of the size of reachableCities starting from those cities
    
    asserts(cities.at(0).getCity() == "HT", "First city should be HT");
    // Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(cities.at(0).getReachableCities().size() == 7, "Train starting from city HT can reach 7 cities"); 
    
    asserts(cities.at(1).getCity() == "NH", "Second city should be NH");
    // Reachable cities from NH are [NH, SF, HT, JL, OD, SD, DL]
    asserts(cities.at(1).getReachableCities().size() == 7, "Train starting from city NH can reach 7 cities");
    
    asserts(cities.at(2).getCity() == "SF", "Third city should be SF");
    // Reachable cities from SF are [SF, HT, NH, JL, OD, SD, DL]
    asserts(cities.at(2).getReachableCities().size() == 7, "Train starting from city SF can reach 7 cities");
    
    asserts(cities.at(3).getCity() == "SJ", "Fourth city should be SJ");
    // Reachable cities from SJ are [SJ, SK, IV, DL, LA, BV, BU]
    asserts(cities.at(3).getReachableCities().size() == 7, "Train starting from city SJ can reach 7 cities");

    asserts(cities.at(4).getCity() == "SK", "Fifth city should be SK");
    // Reachable cities from SK are [SK, IV, DL, LA, BV, BU]
    asserts(cities.at(4).getReachableCities().size() == 6, "Train starting from city SK can reach 6 cities");
    
    asserts(cities.at(5).getCity() == "JL", "Sixth city should be JL");
    // Reachable cities from JL are [JL, OD, SD, DL]
    asserts(cities.at(5).getReachableCities().size() == 4, "Train starting from city JL can reach 4 cities");
    
    asserts(cities.at(6).getCity() == "BV", "Seventh city should be BV");
    // Reachable cities from BV are [BV, LA, BU]
    asserts(cities.at(6).getReachableCities().size() == 3, "Train starting from city BV can reach 3 cities");
        
    asserts(cities.at(7).getCity() == "LA", "Eighth city should be LA");
    // Reachable cities from LA are [LA, BV, BU]
    asserts(cities.at(7).getReachableCities().size() == 3, "Train starting from city LA can reach 3 cities");

    asserts(cities.at(8).getCity() == "OD", "Ninth city should be OD");
    // Reachable cities from OD are [OD, SD, DL]
    asserts(cities.at(8).getReachableCities().size() == 3, "Train starting from city OD can reach 3 cities");

    asserts(cities.at(11).getCity() == "BU", "Twelfth city should be BU");
    // Reachable cities from BU are [BU]
    asserts(cities.at(11).getReachableCities().size() == 1, "Train starting from city BU can reach 1 city");

    // says all tests pass if all pass for graph 1
    cout << "All test cases passed for graph 1!" << endl;
    
    // prints graph 2
    cout << endl << "Graph 2:" << endl;

    /* Construct a graph for testing(graph 2)
     *
     *     --> NJ         -------------------------
     *    |    |         |                         |
     *    |    v         v                         |
     *    |    NY ----> ZD <-------------------    |
     *    |    |                               |   |
     *    |    v                               |   |
     *    |--- PA ----> TR -------------> RN   |   |
     *                                    |    |   |
     *  |--------------                   |    |   |
     *  |              |                  |    |   |
     *  |    GG <---- BO <-------         v    |   |
     *  |              -------> HO <---- ZO    |   |
     *  |                                      |   |
     *  |                                      |   |
     *  |             BY <------------ YS -----    |
     *  |             |                ^           |
     *  |             v                |           |
     *  |    OT <---- ZG ------------> SN          |
     *  |                                          |
     *  |                                          |
     *   ----> SA -------> RT -------> ST ---------
     *                     |
     *                     v
     *                     SC
     */

    // all the names of cities in graph 1
    vector<string> cities_2 {"NJ", "NY", "ZD", "PA", "TR", "RN", "GG", "BO", "HO", "ZO", "BY", "YS", "OT", "ZG", "RT", "SA", "SN", "ST", "SC"};

    // trainRoutes2 vector for graph 2
    vector<pair<string, string>> trainRoutes2;

    // adds all the train routes to trainRoutes2 vector for graph 2
    trainRoutes2.emplace_back("NJ", "NY");
    trainRoutes2.emplace_back("NY", "PA");
    trainRoutes2.emplace_back("PA", "NJ");
    trainRoutes2.emplace_back("PA", "TR");
    trainRoutes2.emplace_back("NY", "ZD");

    trainRoutes2.emplace_back("RN", "TR");

    trainRoutes2.emplace_back("RN", "ZO");
    trainRoutes2.emplace_back("ZO", "HO");
    trainRoutes2.emplace_back("HO", "BO");
    trainRoutes2.emplace_back("BO", "HO");
    trainRoutes2.emplace_back("BO", "GG");
    trainRoutes2.emplace_back("BO", "SA");
    trainRoutes2.emplace_back("SA", "RT");
    trainRoutes2.emplace_back("RT", "ST");
    trainRoutes2.emplace_back("RT", "SC");
    trainRoutes2.emplace_back("ST", "ZD");

    trainRoutes2.emplace_back("ZG", "OT");
    trainRoutes2.emplace_back("ZG", "SN");
    trainRoutes2.emplace_back("SN", "YS");
    trainRoutes2.emplace_back("YS", "BY");
    trainRoutes2.emplace_back("BY", "ZG");
    trainRoutes2.emplace_back("YS", "ZD");

    // returns the cities of graph 2 sorted and stores in cities2
    vector<CityNode> cities2 = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_2, trainRoutes2);

    // cities returned from the above call are sorted according to 
    // the ascending order of the city names and 
    // the descending order of the size of reachableCities starting from those cities

    asserts(cities2.at(0).getCity() == "RN", "First city should be RN");
    // Reachable cities from RN are [RN, TR, ZO, HO, BO, GG, SA, RT, ST, ZD, Sc]
    asserts(cities2.at(0).getReachableCities().size() == 11, "Train starting from city RN can reach 11 cities");

    asserts(cities2.at(1).getCity() == "ZO", "Second city should be ZO");
    // Reachable cities from ZO are [ZO, HO, BO, GG, SA, RT, ST, ZD, SC]
    asserts(cities2.at(1).getReachableCities().size() == 9, "Train starting from city ZO can reach 9 cities");

    asserts(cities2.at(2).getCity() == "BO", "Third city should be BO");
    // Reachable cities from SF are [BO, HO, GG, SA, RT, ST, ZD, SC]
    asserts(cities2.at(2).getReachableCities().size() == 8, "Train starting from city BO can reach 8 cities");

    asserts(cities2.at(3).getCity() == "HO", "Fourth city should be HO");
    // Reachable cities from SJ are [HO, BO, GG, SA, RT, ST, ZD, SC]
    asserts(cities2.at(3).getReachableCities().size() == 8, "Train starting from city HO can reach 8 cities");

    asserts(cities2.at(4).getCity() == "BY", "Fifth city should be BY");
    // Reachable cities from SK are [BY, ZG, OT, SN, YS, ZD]
    asserts(cities2.at(4).getReachableCities().size() == 6, "Train starting from city BY can reach 6 cities");

    asserts(cities2.at(5).getCity() == "SN", "Sixth city should be SN");
    // Reachable cities from JL are [SN, YS, BY, ZG, OT, ZD]
    asserts(cities2.at(5).getReachableCities().size() == 6, "Train starting from city SN can reach 6 cities");

    asserts(cities2.at(6).getCity() == "YS", "Seventh city should be YS");
    // Reachable cities from BV are [YS, BY, ZG, OT, SN, ZD]
    asserts(cities2.at(6).getReachableCities().size() == 6, "Train starting from city YS can reach 6 cities");

    asserts(cities2.at(7).getCity() == "ZG", "Eighth city should be ZG");
    // Reachable cities from LA are [ZG, OT, SN, YS, BY, ZD]
    asserts(cities2.at(7).getReachableCities().size() == 6, "Train starting from city ZG can reach 6 cities");

    asserts(cities2.at(8).getCity() == "NJ", "Ninth city should be NJ");
    // Reachable cities from OD are [NJ, NY, PA, TR, ZD]
    asserts(cities2.at(8).getReachableCities().size() == 5, "Train starting from city NJ can reach 5 cities");

    asserts(cities2.at(9).getCity() == "NY", "Tenth city should be NY");
    // Reachable cities from OD are [NY, PA, NJ, TR, ZD]
    asserts(cities2.at(9).getReachableCities().size() == 5, "Train starting from city NY can reach 5 cities");

    asserts(cities2.at(10).getCity() == "PA", "Eleventh city should be PA");
    // Reachable cities from OD are [PA, NJ, NY, ZD, TR]
    asserts(cities2.at(10).getReachableCities().size() == 5, "Train starting from city PA can reach 5 cities");

    asserts(cities2.at(11).getCity() == "SA", "Twelfth city should be SA");
    // Reachable cities from BU are [SA, RT, ST, ZD, SC]
    asserts(cities2.at(11).getReachableCities().size() == 5, "Train starting from city SA can reach 5 cities");

    asserts(cities2.at(12).getCity() == "RT", "Thirteenth city should be RT");
    // Reachable cities from BU are [RT, ST, ZD, SC]
    asserts(cities2.at(12).getReachableCities().size() == 4, "Train starting from city RT can reach 4 cities");

    asserts(cities2.at(13).getCity() == "ST", "Fourteenth city should be ST");
    // Reachable cities from BU are [ST, ZD]
    asserts(cities2.at(13).getReachableCities().size() == 2, "Train starting from city ST can reach 2 cities");

    asserts(cities2.at(14).getCity() == "GG", "Fifteenth city should be GG");
    // Reachable cities from BU are [GG]
    asserts(cities2.at(14).getReachableCities().size() == 1, "Train starting from city GG can reach 1 city");

    asserts(cities2.at(15).getCity() == "OT", "Sixteenth city should be OT");
    // Reachable cities from BU are [OT]
    asserts(cities2.at(15).getReachableCities().size() == 1, "Train starting from city OT can reach 1 city");

    asserts(cities2.at(16).getCity() == "SC", "Seventeenth city should be SC");
    // Reachable cities from BU are [SC]
    asserts(cities2.at(16).getReachableCities().size() == 1, "Train starting from city SC can reach 1 city");

    asserts(cities2.at(17).getCity() == "TR", "Eighteenth city should be TR");
    // Reachable cities from BU are [TR]
    asserts(cities2.at(17).getReachableCities().size() == 1, "Train starting from city TR can reach 1 city");

    asserts(cities2.at(18).getCity() == "ZD", "Nineteenth city should be ZD");
    // Reachable cities from BU are [ZD]
    asserts(cities2.at(18).getReachableCities().size() == 1, "Train starting from city ZD can reach 1 city");

    // says all tests pass if all pass for graph 2
    cout << "All test cases passed for Graph 2!" << endl;

    // prints graph 3
    cout << endl << "Graph 3:" << endl;

    /* Construct a graph for testing(graph 3)
     *        
     *                  YO
     *
     */

    // all the names of cities in graph 3(single node)
    vector<string> cities_3 {"YO"};

    // trainRoutes2 vector for graph 3(empty vector)
    vector<pair<string, string>> trainRoutes3;

    // returns the cities of graph 3 sorted and stores in cities3(just YO cityNode)
    vector<CityNode> cities3 = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_3, trainRoutes3);

    // cities returned from the above call are sorted according to 
    // the ascending order of the city names and 
    // the descending order of the size of reachableCities starting from those cities (just YO)

    asserts(cities3.at(0).getCity() == "YO", "First city should be YO");
    // Reachable cities from HT are [YO]
    asserts(cities3.at(0).getReachableCities().size() == 1, "Train starting from city YO can reach 1 cities");

    // says all tests pass if all pass for graph 3(one test case above)
    cout << "All test cases passed for Graph 3!" << endl;

    // prints graph 4
    cout << endl << "Graph 4:" << endl;

    /* Construct a graph for testing(graph 4)
     *        
     *                  YO ----> YE
     *
     */

    // all the names of cities in graph 4
    vector<string> cities_4 {"YO", "YE"};

    // trainRoutes2 vector for graph 4(1 train route added)
    vector<pair<string, string>> trainRoutes4;

    // adds all the train routes to trainRoutes4 vector for graph 4(one route)
    trainRoutes4.emplace_back("YO", "YE");

    // returns the cities of graph 4 sorted and stores in cities3([YO CityNode, YE CityNode])
    vector<CityNode> cities4 = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_4, trainRoutes4);

    // cities returned from the above call are sorted according to 
    // the ascending order of the city names and 
    // the descending order of the size of reachableCities starting from those cities

    asserts(cities4.at(0).getCity() == "YO", "First city should be YO");
    // Reachable cities from YO are [YO, YE]
    asserts(cities4.at(0).getReachableCities().size() == 2, "Train starting from city YO can reach 2 cities");

    asserts(cities4.at(1).getCity() == "YE", "Second city should be YE");
    // Reachable cities from YE are [YE]
    asserts(cities4.at(1).getReachableCities().size() == 1, "Train starting from city YE can reach 1 city");

    // says all tests pass if all pass for graph 4(one test case above)
    cout << "All test cases passed for Graph 4!" << endl;

    // prints graph 5
    cout << endl << "Graph 5:" << endl;

    /* Construct a graph for testing(empty)
     *        
     *                  
     *
     */

    // all the names of cities in graph 5(none)
    vector<string> cities_5 {};

    // trainRoutes2 vector for graph 5(none)
    vector<pair<string, string>> trainRoutes5;

    // returns the cities of graph 5 sorted and stores in cities5
    vector<CityNode> cities5 = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_5, trainRoutes5);

    // checks to make sure no city is added to the cities5 vector
    asserts(cities5.size() == 0, "No city is there, and so passes no node graph");

    // says all tests pass if all pass for graph 5(one test case above)
    cout << "All test cases passed for Graph 5!" << endl;

    // prints graph 6
    cout << endl << "Graph 6:" << endl;

    /* Construct a graph for testing(city goes to self)
     *        
     *      | --- |
     *      v     |      
     *      YO -- |
     */

    // all the names of cities in graph 6(one)
    vector<string> cities_6 {"YO"};

    // trainRoutes2 vector for graph 6
    vector<pair<string, string>> trainRoutes6;

    // adds all the train routes to trainRoutes6 vector for graph 6(one route to itself)
    trainRoutes6.emplace_back("YO", "YO");

    // returns the cities of graph 6 sorted and stores in cities6(YO)
    vector<CityNode> cities6 = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_6, trainRoutes6);

    // cities returned from the above call are sorted according to 
    // the ascending order of the city names and 
    // the descending order of the size of reachableCities starting from those cities(just YO)

    asserts(cities6.at(0).getCity() == "YO", "First city should be YO");
    //Reachable cities from HT are [YO]
    asserts(cities6.at(0).getReachableCities().size() == 1, "Train starting from city YO can reach 1 city");

    // says all tests pass if all pass for graph 6(one test case above)
    cout << "All test cases passed for Graph 6!" << endl;

    // says all test cases passed
    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}