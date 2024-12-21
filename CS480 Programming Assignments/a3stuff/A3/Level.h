#ifndef A3_LEVEL_H
#define A3_LEVEL_H

#include <vector>
#include "PageTable.h"
#include <map>

class PageTable;
using namespace std;

class Level {

public:
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
        if (!isLeaf) {
            this->nextLevels = new Level *[levelCapacity];
            for (int i = 0; i < levelCapacity; i++) {
                nextLevels[i] = nullptr;
            }
        }
        else {
            for (int i = 0; i < levelCapacity; i++) {
                maps[i].second = false;
            }
        }
        pgTablePtr = root;
    }
//
//    // overloaded constructor for leaf level
//    Level(int depth, PageTable* root, int levelCapacity) {
//        this->isleaf = true;
//        this->depth = depth;
//        this->levelCapacity = levelCapacity;
//        for (int i = 0; i < levelCapacity; i++) {
//            maps[i] = (pair<unsigned int, char>(-1, 'i'));
//        }
//        pgTablePtr = root;
//    }

    ~Level();


};

#endif //A3_LEVEL_H