//
// Samantha James, RedID: 826078182
// Riley Thompson, RedID: 826526487
//

#ifndef A3_LEVEL_H
#define A3_LEVEL_H

#include <vector>
#include "PageTable.h"
#include <map>

class PageTable;
using namespace std;

class Level {

public:
    // declare public member variables for PageTable class (instantiated in contructor)
    bool isleaf;
    int depth;
    Level** nextLevels;
    int levelCapacity;
    PageTable* pgTablePtr;
    // map of <virtualAddr, pair<physicalFrame, valid/invalid>
    map<unsigned int, pair<unsigned int, bool> > maps;

    // overloaded constructor for levels
    Level(bool isLeaf, int depth, PageTable* root, int levelCapacity) {
        this->isleaf = isLeaf;
        this->depth = depth;
        this->levelCapacity = levelCapacity;
        // if it is not a leaf, create next level array and instantiate with nullptrs
        if (!isLeaf) {
            this->nextLevels = new Level *[levelCapacity];
            for (int i = 0; i < levelCapacity; i++) {
                nextLevels[i] = nullptr;
            }
        }
        // if is a leaf, create map and instantiate valid/invalid marker to invalid
        else {
            for (int i = 0; i < levelCapacity; i++) {
                maps[i].second = false;
            }
        }
        pgTablePtr = root;
    }

    // destructor (defined in Level.cpp)
    ~Level();

};

#endif //A3_LEVEL_H