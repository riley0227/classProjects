#include "PageTable.h"



Level::~Level() {
    for (int i = 0; i < this->levelCapacity; i++) {
        this->nextLevels[i] = nullptr;
    }
    delete[] nextLevels;
    delete pgTablePtr;
}