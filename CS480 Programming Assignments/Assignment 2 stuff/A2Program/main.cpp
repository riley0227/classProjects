/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "scheduler.h"
#include "log.h"
#include "log.c"

#define NORMAL_EXIT 0
#define ERROR 1

// converts given line to a deque of unsigned integers
void convertRowTwoToDequeOfInts(const std::string& line, std::deque<unsigned int>& burstTimes) {
    // current digit processed
    int currDigit = 0;
    // incase there is more than 1 digit in deque
    int nextDigit = 0;

    // goes through each chanracter in line
    for (int i = 0; i < (int)line.length(); ++i) {
        // if not a space
        if (line[i] != ' ') { 
            // convert chararacter to integer
            currDigit = line[i] - '0';

            // makes sure that a number digit(burst) is greater than 0
            if (currDigit <= 0) {
                std::cout << "A burst number must be bigger than 0";
                exit(NORMAL_EXIT);
            }

            // Checks if there is another character number and would make it into a double digit integer
            if ((i + 1 < (int)line.length()) && (line[i + 1] != ' ')) { 
                nextDigit = line[i + 1] - '0';
                burstTimes.push_back((currDigit * 10) + nextDigit); 
                i++; 
            } else {
                // Converts to an integer and stores it in the deque
                burstTimes.push_back(currDigit); 
            }
        }
    }
    // makes sure that total number of burst times is odd
    if (burstTimes.size() % 2 == 0) {
        std::cout << "There must be an odd number of bursts for each process";
        exit(NORMAL_EXIT);
    }
}

int main(int argc, char **argv) {
    // default time quantum is 2(if FCFS, is unused)
    int timeQuantum = 2;
    std::string schedulingStrat = "fcfs";
    std::ifstream burstsFile;
    std::string burstsLine;

    int Option;
    // goes through the options
    while ((Option = getopt(argc, argv, "s:q:")) != -1) {
        switch (Option) {
        // the scheduling strategy
        case 's': 
            schedulingStrat = optarg;
            break;
        // the time quantum
        case 'q': 
            timeQuantum = std::atoi(optarg);
            break;

        default:
            exit(NORMAL_EXIT);
        }
    }

    int idx = optind;
    if (idx < argc) {
        std::string fileName = argv[optind];
        burstsFile = std::ifstream(fileName);
    }

    // makes sure time quantumm is greater than 0
    if (timeQuantum <= 0) {
        std::cout << "Time quantum must be a number and bigger than 0";
        exit(NORMAL_EXIT);
    }       
    // checks if the file is not existent or cannot be opened
    if (!burstsFile.is_open()) {
        std::cout << "Unable to open " << argv[idx];
        exit(NORMAL_EXIT);
    }

    // will be the process id
    int processNumber = 0;
    // initialized scheudler with the given time quantum
    Scheduler scheduler(timeQuantum);

    // reads and goes through each line from the given  burst file
    while (std::getline(burstsFile, burstsLine)) {
        // is a deque for burst times of a single process
        std::deque<unsigned int> burstTimes;

        //converst the current line to a deque or burst times for current process
        convertRowTwoToDequeOfInts(burstsLine, burstTimes);

        // get burstTimees size to put in an unsigned int array
        size_t amntNums = (unsigned int)burstTimes.size();
        // initialzied unsinged int array
        unsigned int* bursts = new unsigned int[amntNums];
        // puts burstTimes from deque into bursts array, so can be executed from the log file given
        for (int i = 0; i < (unsigned int)burstTimes.size(); ++i) {
            bursts[i] = burstTimes[i];
        }
        // prints the integers of the bursts from the log file
        log_process_bursts (bursts, (unsigned int)burstTimes.size());
        // deletes the bursts array as no longer needed and not used again
        delete[] bursts;
        
        //gets the current process and adds it to the scheduler
        Process process = Process(processNumber, burstTimes);
        scheduler.allProcesses.push_back(process);

        // increments process id number as going to the next process
        processNumber++;
    }

    // based on the strategy, either runs the First come first server function or the round robin function
    if (schedulingStrat == "fcfs") {
        scheduler.runFCFS();
    } else if (schedulingStrat == "rr") {
        scheduler.runRR();
    }

    // gets the competed processes from the scheduler
    std::vector<Process> completedProcesses = scheduler.completedProcesses;

    // goes through each completed process and would get the turnaround size and waittime for each one, and uses the given log file to print the results of those
    for (int j = 0; j < (int)completedProcesses.size(); ++j) {
        unsigned int turnaroundTime =  completedProcesses[j].executedCpuBursts + completedProcesses[j].executedIoBursts + completedProcesses[j].waitTime;
        log_process_completion (completedProcesses[j].id, turnaroundTime, completedProcesses[j].waitTime);
    }

    // exits the program
    return 0;
}
