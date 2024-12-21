//
// Created by Samantha James on 3/15/2024.
//

#include "PageTable.h"
#include <vector>


// search given page table and return mapped physical frame num of virtual address VPN
int PageTable::searchMappedPfn(PageTable *pageTable, unsigned int virtualAddress) {
    // get root level(or root of page table)(not entirely sure without level class)
    Level *currentLevel = pageTable->level0;
    //unsigned int currentVPN = 0;
    unsigned int vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);
    //unsigned int pfn = 0;

        // Iterate through each level of the page table based on how many levels
        for (int i = 0; i < pageTable->levelCount; ++i) {
            vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);
            if (currentLevel->isleaf) {
                //get physical from virtual address
                break;
                // if not leaf, wouldnt be mapped to PFN so go to next level
            } else {
                currentLevel = currentLevel->nextLevels[vpnPart];
                //if the next level isnt there breaks out as virtual address isnt mapped there
                if (currentLevel == nullptr) {
                    return -1;
                }
            }
        }
    if (currentLevel->maps[vpnPart].second == false) {
        return -1;
    }
    return currentLevel->maps[vpnPart].first;

}

// insert VPN along page table tree path (VPN->PFN mapping) or update an existing mapping (page replacement)
bool PageTable::insertMapForVpn2Pfn (PageTable* pageTable, unsigned int virtualAddress, int frame){
    // get root level(or root of page table)(not entirely sure without level class)
    Level* currentLevel = pageTable->level0;
    unsigned int VPNPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);
    bool isLeaf = false;
    int i;

    // if single level
    if (pageTable->levelCount > 1) {
        // Iterate through each level of the page table based on how many levels
        for (i = 0; i < pageTable->levelCount; i++) {
            // gets VPN form virt adress for
            VPNPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);

            // if i is equal to total number of levels in page, isLeaf is true
            if (i == (pageTable->levelCount - 1)) {
                isLeaf = true;
                //cout << "is leaf" << endl;
                //currentLevel->nextLevels[VPNPart] = new Level(i + 1, pagetable, pagetable->entryCount[i + 1]);
            }
            // if dont have next level, one will need to be created
            if (currentLevel->nextLevels[VPNPart] == nullptr) {

//            else {
                // if is not leaf, then new level, pointer to pageTable object with that level, num entries for new level
                currentLevel->nextLevels[VPNPart] = new Level(isLeaf, i, pageTable, pageTable->entryCount[i+1]);
//            }
            }

            //moves to the next level to go through again
            currentLevel = currentLevel->nextLevels[VPNPart];

        }
    }
        // if level is leaf, breaks out of function
            // insert leaf level with map objects
            //VPNPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[(pageTable->levelCount)-1], pageTable->bitShift[(pageTable->levelCount)-1]);
            //if (currentLevel->nextLevels == nullptr) {
                if (currentLevel->maps[VPNPart].second == false) { // seg faulting here !!
                    currentLevel->maps[VPNPart].first = (unsigned int) frame;
                    currentLevel->maps[VPNPart].second = true;
                    //cout << frame << " created" << endl;
                    return true;
                }
            //}
            return false;

}

// apply bitmask and bit shift for given virtual address to return VPN
unsigned int PageTable::extractVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift){
    unsigned int maskedAddress = virtualAddress & mask;
    unsigned int vpn = maskedAddress >> shift;
    return vpn;
}

unsigned int PageTable::calculatePA(int pfn, unsigned int offset, int offsetSize) {
    unsigned int pa = pfn << offsetSize;
    pa = pa + offset;
    return pa;
}

void PageTable::removeVPNmapping(PageTable* pageTable, unsigned int currVPN) {

    unsigned int virtualAddress = currVPN << pageTable->bitShift[(pageTable->levelCount)-1];
    // get root level(or root of page table)(not entirely sure without level class)
    Level *currentLevel = pageTable->level0;
    unsigned int vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);

    // Iterate through each level of the page table based on how many levels
    for (int i = 0; i < pageTable->levelCount; ++i) {
        vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);
        if (currentLevel->isleaf) {
            //get physical from virtual address
            break;
            // if not leaf, wouldnt be mapped to PFN so go to next level
        } else {
            currentLevel = currentLevel->nextLevels[vpnPart];
        }
    }
    currentLevel->maps[vpnPart].second = false;
}

void PageTable::countBytes(Level* curr, unsigned long &count) {
    // increment count
    count += sizeof(curr);

    // if reach a null ptr return
    if (curr == nullptr) {
        return;
    }
    // base case if current is a leaf to continue for loop (back to call stack)
    if(curr->isleaf) {
        return;
    }

    // looping through all children of each valid node using recursion
    for (int i = 0; i < curr->levelCapacity; i++) {
        countBytes(curr->nextLevels[i], count);
    }
}