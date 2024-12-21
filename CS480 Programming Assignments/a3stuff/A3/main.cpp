//
// Created by Samantha James on 3/14/2024.
// RedID: 82607182
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

#define NORMAL_EXIT 0
#define MAX_PHYSICAL_FRAMES 999999
#define DEFAULT_BITSTRING_UPDATE_INTERVAL 10

using namespace std;

int main(int argc, char **argv) {

    // declare needed variables and set them to the necessary default value
    int limMemAddr = MAX_PHYSICAL_FRAMES;   // not sure about default, might need boolean
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
            // optarg will contain the string following -n
            // Process appropriately (e.g. convert to integer atoi(optarg))
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

            case 'l':
                // sets what kind of log mode string will be used to determine output
                // will validate later
                logMode = optarg;
                break;

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
    // do we need to error check for if no level bit counts are provided?

//    cout << limMemAddr << " " << limPhysFrames << " " << bitUpdateInterval << " " << logMode << endl;
//    for (int i = 0; i < levelCount; i++) {
//        cout << levelSizes[i] << endl;
//    }

    // create PageTable (which creates root node)
    PageTable root = PageTable(levelCount, levelSizes);
    // for summary
    unsigned int pSize = (unsigned int)pow(2, root.bitShift[levelCount-1]);
    //root.level0->pgTablePtr = &root;

    // if just want bit masks then print here (no need to run)
    if (logMode == "bitmasks") {
        // THIS IS PRINTING WRONG (I changed the method signature to take in vector<unsigned int> instead of uint32_t which is an issue)
        log_bitmasks(levelCount, root.bitmasks);
        return 0;
    }

    // pass vector with level lengths and/or other opt arg values to variable in other classes
    // (sort of does this in PageTable constructor?)

    // open file and error check
    FILE *infile;
    infile = fopen(fileName, "r");
    if (infile == NULL) {
        cout << "Unable to open <<" << fileName << ">>" << endl;
        exit(NORMAL_EXIT);
    }

    // create variable for current virtual address
    unsigned int currVaddr;
    int addressCount = 1;
    // set offset based off the bitshift amount of leaf level of page table tree
    unsigned int offsetMask = ((unsigned int)pow(2, root.bitShift[levelCount-1])-1);
    unsigned int currOffset;

    // if log mode is offset, then take in virtual addresses and print their offsets (no need to run alg)
    if (logMode == "offset") {
        // then use the given print_num_inHex function
        p2AddrTr mtrace;
        // read in next address while not at end of fine and below address limit
        while ((NextAddress(infile, & mtrace)) && (addressCount <= limMemAddr)) {
            currVaddr = mtrace.addr;
            // mask current address with offset mask
            currOffset = currVaddr & offsetMask;
            // print offset in hex form
            print_num_inHex(currOffset);
            // increment addresses read in so far counter
            addressCount++;
        }
        // close file
        fclose(infile);
        return 0;
    }

    // read in all the trace addresses (to a limit if specified)
    // call function to insert trace into the tree (call on root)
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


    vector<uint32_t> vpns(levelCount, 0);
    // read in next address while not at end of fine and below address limit
    while ((NextAddress(infile, & mtrace)) && (addressCount <= limMemAddr)) {
        // convert string to unsigned int which is virtual address
        currVaddr = mtrace.addr;

        //cout << "Current virtual address: " << hex << currVaddr << dec << endl;
        // Logic for extracting VPNs for each level
        for (int level = 0; level < levelCount; ++level) {
            unsigned int maskOffset = root.bitmasks[level];
            unsigned int shift = root.bitShift[level];
            unsigned int vpnPart = PageTable::extractVPNFromVirtualAddress(currVaddr, maskOffset, shift);
            vpns[level] = vpnPart;
            //cout << "1" << endl;
        }

        //std::cout << "read in a line!" << std::endl;
        // extract VPN from virtual address
        currVPN = PageTable::extractVPNFromVirtualAddress(currVaddr, maskOffset, offsetSize);
        //print_num_inHex(currVPN);
        // call function that does mapping and inserting of VPN path

        // is it time to update bitstrings??
        if ((addressCount % bitUpdateInterval) == 0) {
            // iterate thru infoForPR
            // shift all bitstrings one to the right >> 1
//            for (auto const& [key, val] : infoForPR) {  // cant use with old version of C++
//                infoForPR[key][0] = val[0] >> 1;
//            }
            for (it = infoForPR.begin(); it != infoForPR.end(); it++) {
                infoForPR[it->first][0] = it->second[0] >> 1;
            }

            // if in recently accessed array and hasn't been updated this cycle add (1 << 15) to bitstring
            // and always update accessed time
            for (int i = 0; i < (int)recentAccesses.size(); i++) {
                // if bitstring for corresponding VPN in hashtable is not already updated
                if (infoForPR[recentAccesses[i].first][0] < (1 << 15)) {
                    // add 1<<15 to essentially prepend a 1 to the bitstring
                    infoForPR[recentAccesses[i].first][0] += (1 << 15);
                }
                // always update last accessed virtual time
                infoForPR[recentAccesses[i].first][2] = recentAccesses[i].second;
            }
            // clear recent accesses vector
            recentAccesses.clear();
        }
        // if is page table hit, then don't do page replacement
        // maybe this infoForPR.find(currVPN) == infoForPR.end()
        if (PageTable::searchMappedPfn(&root, currVaddr) == -1) {
            // if page replacement needs to occur
            if ((int)infoForPR.size() >= limPhysFrames) {
                // do page replacement!!
                isReplacement = true;
                numPReplaces++;
                // iterate thru infoForPR (use iterator) to find smallest bitstring (last access = tie-breaker)
                unsigned int minBitstring = 0xFFFFFF;
//                for (auto const &[key, val]: infoForPR) { // cant use with old version of C++
                for (it = infoForPR.begin(); it != infoForPR.end(); it++) {
                    if (it->second[0] < minBitstring) {
                        victimVPN = it->first;
                        minBitstring = it->second[0];
                    } else if (it->second[0] == minBitstring) {
                        // use last access to determine victim
                        if (it->second[2] < infoForPR[victimVPN][2]) {
                            victimVPN = it->first;
                            minBitstring = it->second[0];
                        }
                    }
                }
                // traverse tree path to set map object as invalid for old vpn
                PageTable::removeVPNmapping(&root, victimVPN);
                // assign vpn being replaced for victimVPN, assign that vpn's bitstring to victimBitstring
                victimBitstring = infoForPR[victimVPN][0];
                // assign resulting frame to be reallocated to currFrame
                currFrame = infoForPR[victimVPN][1];
                // remove entry from infoForPR
                infoForPR.erase(victimVPN);
            }

            // see if address path does not already exist
            // insert path into page table
            if (PageTable::insertMapForVpn2Pfn(&root, currVaddr, currFrame)) {
                // set physical frame number to currFrane
                addrFrame = currFrame;

                // page table miss
                isHit = false;

                // create new entry for infoForPR map
                    infoForPR[currVPN] = {initialBitstring, addrFrame, (unsigned int)addressCount};

                // add to recent addresses array if not the previous bth address
                if ((addressCount % bitUpdateInterval) != 0) {
                    recentAccesses.push_back(make_pair(currVPN, addressCount));
                }

                // increment next open physical frame number
                currFrame++;
            }
        }
        else {
            isReplacement = false;
            // otherwise set existing frame value to address frame
            addrFrame = PageTable::searchMappedPfn(&root, currVaddr);

            // page table hit !
            infoForPR[currVPN][2] = addressCount;
            isHit = true;
            pTableHits++;

            // add to recent addresses array
            if ((addressCount % bitUpdateInterval) != 0) {
                recentAccesses.push_back(make_pair(currVPN, addressCount));
            }

        }
        // once inserted, print virtual address and physical address

        if (logMode == "va2pa") {
            // print the virtual addresses to physical addresses
            // (Use the given log_va2pa function)
            currOffset = currVaddr & offsetMask;
            currPA = PageTable::calculatePA(addrFrame, currOffset, offsetSize);
            log_va2pa(currVaddr, currPA);
        }
        else if (logMode == "vpns_pfn") {
            // Log VPNs for each level followed by the frame number
            log_vpns_pfn(levelCount, vpns.data(), addrFrame);
            //cout << "Logged VPNs to PFN." << endl;
        }
        else if (logMode == "vpn2pfn_pr") {
            // print vpn, pfn, replaced victim vpn + bitstring if replacement, and page hit or miss
            // (Use the given log_mapping function)

            if (isReplacement) {
                log_mapping(currVPN, addrFrame, victimVPN, victimBitstring, isHit);
            }
            else {
                log_mapping(currVPN, addrFrame, -1, 0, isHit);
            }

        }

        // increment the number of addresses read in so far
        addressCount++;
    }
    // close file
    fclose(infile);

    if (logMode == "summary") {

        tBytesUsed = sizeof(root);
        PageTable::countBytes(root.level0, tBytesUsed);

        log_summary(pSize,
                        numPReplaces,
                        pTableHits,
                        addressCount-1,
                    (unsigned int)infoForPR.size(),
                        tBytesUsed);
    }

    return 0;
}