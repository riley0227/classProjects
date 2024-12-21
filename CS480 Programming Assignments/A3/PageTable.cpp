//
// Samantha James, RedID: 826078182
// Riley Thompson, RedID: 826526487
//

#include "PageTable.h"
#include <vector>


// search given page table and return mapped physical frame num of virtual address VPN
// parameters = page table pointer, virtual address to search upon vpn path
// return = physical frame vpn is mapped to or -1 if not found
int PageTable::searchMappedPfn(PageTable *pageTable, unsigned int virtualAddress) {
    // start current level as level0 (member of root)
    Level *currentLevel = pageTable->level0;
    // extract the first vpn part from the virtual address (this will get redone in loop)
    unsigned int vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);

        // Iterate through each level of the page table until reaching leaf level
        for (int i = 0; i < pageTable->levelCount; ++i) {
            // extract current vpn part for the current level
            vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);
            // if it is a leaf then break out of loop
            if (currentLevel->isleaf) {
                break;
            }
            // if not a leaf move to next level
            else {
                currentLevel = currentLevel->nextLevels[vpnPart];
                // if the next level isnt there return -1 as virtual address isnt mapped in tree
                if (currentLevel == nullptr) {
                    return -1;
                }
            }
        }
    // if the vpn path exists but is invalid, return -1
    if (currentLevel->maps[vpnPart].second == false) {
        return -1;
    }
    // return physical frame that vpn path is mapped to if mapping is valid
    return currentLevel->maps[vpnPart].first;

}

// insert VPN along page table tree path (VPN->PFN mapping) or update an existing mapping (page replacement)
// parameters = page table pointer, virtual address to insert, frame to map the vpn to
// return = boolean of whether the vpn was inserted (returns false if it already exists in the tree)
bool PageTable::insertMapForVpn2Pfn (PageTable* pageTable, unsigned int virtualAddress, int frame){
    // start current level as level0 (member of root)
    Level* currentLevel = pageTable->level0;
    // extract the first vpn part from the virtual address (this will get redone in loop)
    unsigned int VPNPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);
    // create needed vars
    bool isLeaf = false;
    int i;

    // if more than single level tree (page table)
    if (pageTable->levelCount > 1) {
        // Iterate through each level of the page table based on how many levels
        for (i = 0; i < pageTable->levelCount; i++) {
            // gets VPN part from virt address for current level
            VPNPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);

            // if i is equal to total number of levels in page, isLeaf is true
            if (i == (pageTable->levelCount - 1)) {
                isLeaf = true;
            }
            // if dont have next level, one will need to be created
            if (currentLevel->nextLevels[VPNPart] == nullptr) {
                // if is not leaf, then new level, pointer to pageTable object with that level, num entries for new level
                currentLevel->nextLevels[VPNPart] = new Level(isLeaf, i, pageTable, pageTable->entryCount[i+1]);
            }

            //moves to the next level to go through again
            currentLevel = currentLevel->nextLevels[VPNPart];
        }
    }
        // once we are at leaf level, if the mapping is currently invalid
        if (currentLevel->maps[VPNPart].second == false) {
            // assign frame parameter as mapping for vpn and set mapping to be valid
            currentLevel->maps[VPNPart].first = (unsigned int) frame;
            currentLevel->maps[VPNPart].second = true;
            // return true since it was inserted
            return true;
        }
        // return false since mapping already was valid and existed for vpn (was found but not newly inserted)
        return false;

}

// apply bitmask and bit shift for given virtual address to return VPN
// parameters = full virtual address, desired bit mask, and desired right shift amount
// return = resulting vpn extraction from the virtual address provided
unsigned int PageTable::extractVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift){
    // apply mask and shift to virtual address
    unsigned int maskedAddress = virtualAddress & mask;
    unsigned int vpn = maskedAddress >> shift;
    return vpn;
}

// create the physical address from the frame number and offset info
// parameters = physical frame number, offset from the corresponding virtual address, how many bits the offset is
// return = resulting full physical address
unsigned int PageTable::calculatePA(int pfn, unsigned int offset, int offsetSize) {
    // shift the pfn left by size of offset then add the offset
    unsigned int pa = pfn << offsetSize;
    pa = pa + offset;
    return pa;
}

// make map object for given vpn invalid (page was replaced and frame was reallocated)
// parameters = page table pointer, the vpn that needs to be traced and marked as invalid mapping
void PageTable::removeVPNmapping(PageTable* pageTable, unsigned int currVPN) {
    // shift the vpn up to simulate it being a full virtual address (since we reused the code structure from our search function)
    unsigned int virtualAddress = currVPN << pageTable->bitShift[(pageTable->levelCount)-1];
    // start current level as level0 (member of root)
    Level *currentLevel = pageTable->level0;
    // extract the first vpn part from the virtual address (this will get redone in loop)
    unsigned int vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[0], pageTable->bitShift[0]);

    // Iterate through each level of the page table based on how many levels
    for (int i = 0; i < pageTable->levelCount; ++i) {
        // extract the first vpn part from the virtual address for current level
        vpnPart = extractVPNFromVirtualAddress(virtualAddress, pageTable->bitmasks[i], pageTable->bitShift[i]);
        // break once reach leaf level
        if (currentLevel->isleaf) {
            break;
        }
        // if not at leaf level, continue traversing tree along vpn path
        else {
            currentLevel = currentLevel->nextLevels[vpnPart];
        }
    }
    // once reach leaf for given vpn, set map valid/invalid indicator to invalid
    currentLevel->maps[vpnPart].second = false;
}

// count the number of bytes used in the page table (like count employees from A1)
// implemented as a recursive DFS
// parameters = level pointer to the current level, address of count variable
void PageTable::countBytes(Level* curr, unsigned long &count) {
    // increment count with size of current instantiated level
    count += sizeof(curr);

    // base case if reach a null ptr return (back to call stack)
    if (curr == nullptr) {
        return;
    }
    // base case if current is a leaf return (back to call stack)
    if(curr->isleaf) {
        return;
    }

    // looping through all children of each valid node using recursion and DFS
    for (int i = 0; i < curr->levelCapacity; i++) {
        countBytes(curr->nextLevels[i], count);
    }
}