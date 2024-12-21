/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include <deque>
#include <vector>

// is the processes class
class Process {
    public:
        // constructor for a process
        Process(int id, const std::deque<unsigned int>& burstTimes);

        // this would be the process id
        unsigned int id;
        
        //this would be the cpuBursts and ioBursts of the processes, spereated into 2 sperate deques
        std::deque<unsigned int> cpuBursts;
        std::deque<unsigned int> ioBursts;

        // this counts the executed cpu bursts and executed io bursts
        unsigned int executedCpuBursts;
        unsigned int executedIoBursts;

        // this is the wait time for the process
        unsigned int waitTime;
};

// is the scheduler class
class Scheduler {
    public:
        // constructor for a scheduler, time quantum inst used for FCFS, but default time quantum would be passed
        Scheduler(int timeQuantum);

        // time quantum for RR
        int timeQuantum;

        // all processes(initially processes all here)
        std::vector<Process> allProcesses;

        // completed process, so processes that have been completed fully
        std::vector<Process> completedProcesses;

        // processes in ready queue
        std::deque<Process> readyQueue;

        // processes in blocked queue
        std::deque<Process> blockedQueue;

        // function for FCFS
        void runFCFS();

        // function for RR
        void runRR();
};