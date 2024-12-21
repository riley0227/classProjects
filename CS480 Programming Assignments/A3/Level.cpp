//
// Samantha James, RedID: 826078182
// Riley Thompson, RedID: 826526487
//

#include "PageTable.h"

// destructor for Level class
Level::~Level() {
    for (int i = 0; i < this->levelCapacity; i++) {
        this->nextLevels[i] = nullptr;
    }
    delete[] nextLevels;
    delete pgTablePtr;
}