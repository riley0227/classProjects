//
// Samantha James, RedID: 826078182
// Riley Thompson, RedID: 826526487
//

#include "log_helpers.h"
#include "vaddr_tracereader.h"
#include "PageTable.h"
#include "Level.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <getopt.h>
#include <algorithm>

// define magic numbers here
#define NORMAL_EXIT 0
#define MAX_PHYSICAL_FRAMES 999999
#define DEFAULT_BITSTRING_UPDATE_INTERVAL 10

using namespace std;

int main(int argc, char **argv) {

    // declare needed variables and set them to the necessary default value
    // these vars are used for parsing/setting command line args
    int limMemAddr = MAX_PHYSICAL_FRAMES;
    int limPhysFrames = MAX_PHYSICAL_FRAMES;
    int bitUpdateInterval = DEFAULT_BITSTRING_UPDATE_INTERVAL;
    string logMode = "summary"; // default log mode
    int currArgNum;
    const char* fileName;
    vector<unsigned int> levelSizes;
    int levelCount = 0;
    unsigned int currLevelSize = 0;
    unsigned int levelBitsSum = 0;

    // process optional command line arguments (USE GETOPT)
    // this code is based off the sample code in the a3progtips pdf
    int Option;
    while ( (Option = getopt(argc, argv, "n:f:b:l:")) != -1) {
        switch (Option) {
            // -n is for number limit of memory addresses to read in
            case 'n':
                // set limit of processing first N memory accesses
                // must be valid positive integer
                currArgNum = stoi(optarg);
                if (currArgNum < 1) {
                    cout << "Number of memory accesses must be a number and greater than 0" << endl;
                    exit(NORMAL_EXIT);
                }
                limMemAddr = currArgNum;
                break;
            // -f is for limit of frames available in physical memory
            case 'f':
                // set number of available physical frames
                // must be valid positive integer
                currArgNum = stoi(optarg);
                if (currArgNum < 1) {
                    cout << "Number of available frames must be a number and greater than 0" << endl;
                    exit(NORMAL_EXIT);
                }
                limPhysFrames = currArgNum;
                break;
            // -b is for number of accessed between bitstring updates
            case 'b':
                // set number of memory accesses between bitstring updates (for NFU with aging)
                // must be valid positive integer
                currArgNum = stoi(optarg);
                if (currArgNum < 1) {
                    cout << "Bit string update interval must be a number and greater than 0" << endl;
                    exit(NORMAL_EXIT);
                }
                bitUpdateInterval = currArgNum;
                break;
            // -l is for log mode
            case 'l':
                // sets what kind of log mode string will be used to determine output
                // will validate later
                logMode = optarg;
                break;
            // if improper letter for arg provided
            default:
                // go with default which is -l summary
                // process all addresses
                // unlimited physical frames (999999)
                // bitstring update interval = 10
                // all of these defaults are set in initial statements
                cout << "incorrect usage of optional command arguments" << endl;
                exit(NORMAL_EXIT);
        }
    }
    // first mandatory argument, optind is defined by getopt as index is argv of required args
    int idx = optind;
    /* argv[idx] now has the first mandatory argument: the trace filepath*/
    /* argv[idx+1] through argv[argc-1] would be the arguments for
     * specifying the number of bits for each page table level, one number
     * per each level */
    // if required arg is there then read in file name
    if (idx < argc) {
        fileName = argv[idx];
    }
    // if no required args provided #issues
    else {
        cout << "incorrect usage of required command argument file" << endl;
        exit(NORMAL_EXIT);
    }
    // once done with file name, increment index in argv to prep for level sizes
    idx++;
    // while there are still command line args to read in
    while (idx < argc){
        // convert next arg to unsigned int
        currLevelSize = stoul(argv[idx]);
        // error check that it's a valid # of bits
        if (currLevelSize < 1) {
            cout << "Level " << levelCount << " page table must have at least 1 bit" << endl;
            exit(NORMAL_EXIT);
        }
        // add to total # of bits for page table
        levelBitsSum += currLevelSize;
        // error check that total bits for page table <= 28
        if (levelBitsSum > 28) {
            cout << "Too many bits used for the page table" << endl;
            exit(NORMAL_EXIT);
        }
        // if all good, add to levelSizes vector and increment idx and levelCount
        levelSizes.push_back(currLevelSize);
        idx++;
        levelCount++;
    }

    // create PageTable (which creates root node)
    PageTable root = PageTable(levelCount, levelSizes);
    // for summary calculate page size
    unsigned int pSize = (unsigned int)pow(2, root.bitShift[levelCount-1]);

    // if just want bit masks then print here (no need to open file or run)
    if (logMode == "bitmasks") {
        // (I changed the method signature to take in vector<unsigned int> instead of uint32_t)
        log_bitmasks(levelCount, root.bitmasks);
        // end program after bitmasks are printed
        return 0;
    }

    // open file and error check
    FILE *infile;
    infile = fopen(fileName, "r");
    // if file not found/not opened properly then fail
    if (infile == NULL) {
        cout << "Unable to open <<" << fileName << ">>" << endl;
        exit(NORMAL_EXIT);
    }

    // create variables for reading in and counting virtual addresses
    unsigned int currVaddr;
    int addressCount = 0; // start at zero since increment at the beginning of the while loop (right after address read in)

    // set offset from bitshift amount of leaf level of page table tree
    unsigned int offsetMask = ((unsigned int)pow(2, root.bitShift[levelCount-1])-1);
    unsigned int currOffset;

    // if log mode is offset, then take in virtual addresses and print their offsets (no need to run alg)
    if (logMode == "offset") {
        // then use the given print_num_inHex function
        p2AddrTr mtrace;
        // read in next address while not at end of fine and below address limit
        while ((NextAddress(infile, & mtrace)) && (addressCount < limMemAddr)) {
            currVaddr = mtrace.addr;
            // increment addresses read in so far counter
            addressCount++;
            // mask current address with offset mask
            currOffset = currVaddr & offsetMask;
            // print offset in hex form
            print_num_inHex(currOffset);
        }
        // close file and end program
        fclose(infile);
        return 0;
    }


    unsigned int currVPN;
    int offsetSize = (int)root.bitShift[levelCount-1];
    unsigned int maskOffset = (unsigned int)((pow(2,32)-1) - (pow(2, offsetSize)-1));
    unsigned int currPA;
    unsigned int addrFrame;
    int currFrame = 0;
    p2AddrTr mtrace;
    // map of vpn -> [bitstring, frame#, last access]
    map<unsigned int, vector<unsigned int>> infoForPR;
    unsigned int initialBitstring = 1 << 15;
    unsigned int victimVPN;
    unsigned int victimBitstring;
    vector<pair<unsigned int, int>> recentAccesses;
    bool isHit = false;
    bool isReplacement = false;
    map<unsigned int, vector<unsigned int>>::iterator it;

    // for summary
    unsigned int numPReplaces = 0;
    unsigned int pTableHits = 0;
    unsigned long tBytesUsed = 0;

    // read in next address while not at end of fine and below address limit
    // complete demand page table insertion and searches with page replacement and log statements based on log mode
    while ((NextAddress(infile, & mtrace)) && (addressCount < limMemAddr)) {
        // access virtual address from trace file
        currVaddr = mtrace.addr;

        // increment the number of addresses read in so far
        addressCount++;

        //std::cout << "read in a line!" << std::endl;
        // extract VPN from virtual address
        currVPN = PageTable::extractVPNFromVirtualAddress(currVaddr, maskOffset, offsetSize);
        //print_num_inHex(currVPN);
        // call function that does mapping and inserting of VPN path

        // is it time to update bitstrings??
        if ((addressCount % bitUpdateInterval) == 0) {
//            for (auto const& [key, val] : infoForPR) {  // cant use with old version of C++ (caused it to not run in autograder)
//                infoForPR[key][0] = val[0] >> 1;
//            }
            // iterate thru infoForPR hashmap
            // shift all bitstrings one to the right >> 1
            for (it = infoForPR.begin(); it != infoForPR.end(); it++) {
                infoForPR[it->first][0] = it->second[0] >> 1;
            }
            // add the current vpn to recently accesssed (so that it can be updated too if it already exists in hashmap)
            recentAccesses.push_back(make_pair(currVPN, addressCount));
            // if in recently accessed array and hasn't been updated this cycle add (1 << 15) to bitstring
            // and always update accessed time
            for (int i = 0; i < (int)recentAccesses.size(); i++) {
                // if exists in hashtable still (hasn't been removed within last update cycle)
                if (infoForPR.find(recentAccesses[i].first) != infoForPR.end()) {
                    // if bitstring for corresponding VPN in hashtable is not already updated and
                    if (infoForPR[recentAccesses[i].first][0] < initialBitstring) {
                        // add 1<<15 to essentially prepend a 1 to the bitstring
                        infoForPR[recentAccesses[i].first][0] += initialBitstring;
                    }
                    // always update last accessed virtual time in hashmap
                    infoForPR[recentAccesses[i].first][2] = recentAccesses[i].second;
                }
            }
            // clear recent accesses vector
            recentAccesses.clear();
        }
        // if is page table miss, then enter to see if page replacement is needed page replacement
        if (PageTable::searchMappedPfn(&root, currVaddr) == -1) {
            // if hashtable has mapped objects to all possible frames, page replacement needs to occur
            if ((int)infoForPR.size() >= limPhysFrames) {
                // do page replacement!!
                // set/increment vars for log statements
                isReplacement = true;
                numPReplaces++;

                // set min before loop as a value larger than any possible bitstring
                unsigned int minBitstring = 0xFFFFFF;
                // iterate thru infoForPR (use iterator) to find smallest bitstring (last access = tie-breaker)
//                for (auto const &[key, val]: infoForPR) { // cant use with old version of C++ in autograder (lame)
                for (it = infoForPR.begin(); it != infoForPR.end(); it++) {
                        // if bitstring is smaller set as min bitstring and set vpn as victim
                        if (it->second[0] < minBitstring) {
                            victimVPN = it->first;
                            minBitstring = it->second[0];
                        }
                        // if the bitstring is equal to the current min, use the last access time to determine victim
                        // replace if current vpn has been accesses longer ago than the current min
                        else if (it->second[0] == minBitstring) {
                            // use last access to determine victim
                            if (it->second[2] < infoForPR[victimVPN][2]) {
                                victimVPN = it->first;
                                minBitstring = it->second[0];
                            }
                        }
                }
                // traverse tree path to set map object as invalid for old vpn
                PageTable::removeVPNmapping(&root, victimVPN);
                // vpn being replaced is already victimVPN, assign that vpn's bitstring to victimBitstring
                victimBitstring = infoForPR[victimVPN][0];
                // assign resulting frame to be reallocated to currFrame
                currFrame = infoForPR[victimVPN][1];
                // remove entry from infoForPR hashtable
                infoForPR.erase(victimVPN);
            }

            // see if address path does not already exist
            // insert path into page table if not already there
            if (PageTable::insertMapForVpn2Pfn(&root, currVaddr, currFrame)) {
                // set physical frame number that was allocated to currFrame
                addrFrame = currFrame;

                // page table miss
                isHit = false;

                // create new entry for infoForPR hashmap
                infoForPR[currVPN] = {initialBitstring, addrFrame, (unsigned int)addressCount};

                // add to recent addresses array if not the previous bth address (was already added and updated above)
                if ((addressCount % bitUpdateInterval) != 0) {
                    recentAccesses.push_back(make_pair(currVPN, addressCount));
                }

                // increment next open physical frame number (only matters until page replacement starts occurring)
                currFrame++;
            }
        }
        // otherwise if entry already exists and not insert or page replacement is necessary
        else {
            isReplacement = false;
            // set existing frame value to address frame that vpn is already mapped to
            addrFrame = PageTable::searchMappedPfn(&root, currVaddr);

            // update last access virtual time
            infoForPR[currVPN][2] = addressCount;
            // page table hit !
            isHit = true;
            pTableHits++;

            // add to recent addresses array if not the previous bth address (was already added and updated above)
            if ((addressCount % bitUpdateInterval) != 0) {
                recentAccesses.push_back(make_pair(currVPN, addressCount));
            }
        }

        // once inserted/accessed...
        // if log mode is va2pa print virtual address and physical address it is mapped to
        if (logMode == "va2pa") {
            // print the virtual addresses to physical addresses
            // (Use the given log_va2pa function)
            currOffset = currVaddr & offsetMask;
            currPA = PageTable::calculatePA(addrFrame, currOffset, offsetSize);
            log_va2pa(currVaddr, currPA);
        }
        // if log mode is vpns_pfn print vpn parts for each level and the frame it is mapped to
        else if (logMode == "vpns_pfn") {
            // create vector to store vpn parts, initialize with zeros
            vector<uint32_t> vpns(levelCount, 0);
            // Logic for extracting VPNs for each level
            for (int level = 0; level < levelCount; ++level) {
                // determine offset and shift for each level, extract vpn part, and add it to an array
                unsigned int maskOffset = root.bitmasks[level];
                unsigned int shift = root.bitShift[level];
                unsigned int vpnPart = PageTable::extractVPNFromVirtualAddress(currVaddr, maskOffset, shift);
                vpns[level] = vpnPart;
            }
            // Log VPNs for each level followed by the frame number it is mapped to
            log_vpns_pfn(levelCount, vpns.data(), addrFrame);
        }
        // if log mode is vpn2pfn_pr print the vpn to pfn mapping, if it was a hit or miss, and extra details if page replacement occurred
        else if (logMode == "vpn2pfn_pr") {
            // print vpn, pfn, replaced victim vpn + bitstring if replacement, and page hit or miss
            // (Use the given log_mapping function)
            // if there was replacement pass in victim vpn and bitstring, otherwise pass in -1 for victim vpn
            if (isReplacement) {
                log_mapping(currVPN, addrFrame, victimVPN, victimBitstring, isHit);
            }
            else {
                log_mapping(currVPN, addrFrame, -1, 0, isHit);
            }
        }
    // restart while loop
    }
    // close trace file
    fclose(infile);

    // if the log mode is summary, print summary statistics from program execution using calculated values
    if (logMode == "summary") {
        // start bytes used as size of the root, then call recursive function to calculate bytes used, using DFS
        tBytesUsed = sizeof(root);
        PageTable::countBytes(root.level0, tBytesUsed);

        // print the summary statistics (page size, # of page replacements, # of page table hits and misses, # of addresses processed, # of frames allocated, and total bytes used
        log_summary(pSize,
                        numPReplaces,
                        pTableHits,
                        addressCount,
                    (unsigned int)infoForPR.size(),
                        tBytesUsed);
    }

    return 0;
}