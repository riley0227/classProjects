//
// Samantha James, RedID: 826078182
// Riley Thompson, RedID: 826526487
//

#ifndef A3_PAGETABLE_H
#define A3_PAGETABLE_H

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <limits>
#include "Level.h"

#define MAX_BITS_PER_ENTRY 32

using namespace std;

class PageTable {

    // declare all public members and functions of class
public:
    int levelCount;
    vector<unsigned int> bitmasks;
    vector<unsigned int> bitShift;
    vector<unsigned int> entryCount;
    Level* level0;

    // overloaded constructor to initialize members and create root
    PageTable(int levelCount, vector<unsigned int> levelSizes) {
        this->levelCount = levelCount;
        // start shift amount at 32 (total bits per entry)
        int currShiftAmount = MAX_BITS_PER_ENTRY;
        // decrement shift amount then calculate bitmask, bitShift, and entryCount for each level (add to respective vectors)
        for (int i = 0; i < levelCount; i++) {
            currShiftAmount -= levelSizes[i];
            bitmasks.push_back(((unsigned int)pow(2, levelSizes[i])-1) << currShiftAmount);
            bitShift.push_back(currShiftAmount);
            entryCount.push_back((unsigned int)pow(2, levelSizes[i]));
        }
        // if more than 1 level, set level0 to NOT be a leaf
        if (levelCount > 1) {
            this->level0 = new Level(false, 0, this, (int)entryCount[0]);
        }
        // if only one level, set level0 as a leaf
        else {
            this->level0 = new Level(true, 0, this, (int)entryCount[0]);
        }
    }

    // search given page table and return mapped physical frame num of virtual address VPN
    static int searchMappedPfn(PageTable *pageTable, unsigned int virtualAddress);

    // insert VPN along page table tree path (VPN->PFN mapping) or update an existing mapping (page replacement)
    static bool insertMapForVpn2Pfn (PageTable *pagetable, unsigned int virtualAddress, int frame);

    // apply bitmask and bit shift for given virtual address to return VPN
    static unsigned int extractVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift);

    // apply shifting and adding to get physical address from PFN and offset
    static unsigned int calculatePA(int pfn, unsigned int offset, int offsetSize);

    // make mapping invalid for a virtual page that is being replaced
    static void removeVPNmapping(PageTable* pageTable, unsigned int virtualAddress);

    // count total bytes used (recursive)
    static void countBytes(Level* curr, unsigned long &count);

};

#endif //A3_PAGETABLE_H
