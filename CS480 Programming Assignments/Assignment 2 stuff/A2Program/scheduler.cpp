/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include <algorithm>
#include "scheduler.h"
#include "log.h"
#include <deque>

Process::Process(int id, const std::deque<unsigned int>& burstTimes) {
    this->id = id;
    this->executedCpuBursts = 0;
    this->executedIoBursts = 0;

    for (int i = 0; i < (int)burstTimes.size(); ++i) {
        if (i % 2 == 0) {
            // even index is a CPU burst
            cpuBursts.push_back(burstTimes[i]);
        } else {
            // odd index is an IO burst
            ioBursts.push_back(burstTimes[i]);
        }
    }
}

//scheduler class
Scheduler::Scheduler(int timeQuantum) {
    this->timeQuantum = timeQuantum;
}

void Scheduler::runFCFS() {
    //total time since scheuler starts
    unsigned int timeElapsed = 0;

    // adds processes to ready queue
    for (int i = 0; i < (int)allProcesses.size(); ++i) {
        readyQueue.push_back(allProcesses[i]);
    }

    //while there is still stuff in either queue, runs
    while (!readyQueue.empty() || !blockedQueue.empty()) {
        // if ready queue isn't empty
        if (!readyQueue.empty()) {
            // removes and puts from of readyQueue in currentProcess
            Process currentProcess = readyQueue.front();
            readyQueue.pop_front();

            // determines and sets the wait time for the current process
            int waitTime = timeElapsed - (currentProcess.executedCpuBursts + currentProcess.executedIoBursts);
            currentProcess.waitTime = (waitTime);

            // gets the next cpu burts and pops it from front of cpu bursts
            int cpuBurst = currentProcess.cpuBursts.front();
            currentProcess.cpuBursts.pop_front();

           // Updates the number of executed CPU bursts for the current process and the total elapsed time.
            currentProcess.executedCpuBursts += cpuBurst;
            timeElapsed += cpuBurst;
            
            // prints/logs what is happening and if process is entering io or is completed
            if (!currentProcess.cpuBursts.empty() && !currentProcess.ioBursts.empty()) {
                log_cpuburst_execution (currentProcess.id, currentProcess.executedCpuBursts, currentProcess.executedIoBursts, timeElapsed, ENTER_IO);
            } else if (currentProcess.cpuBursts.empty() && currentProcess.ioBursts.empty()) {
                log_cpuburst_execution (currentProcess.id, currentProcess.executedCpuBursts, currentProcess.executedIoBursts, timeElapsed, COMPLETED);
            }

            // deque to set blocked queue to after all minipulation of blocked queue is done
            std::deque<Process> tempBlockedQueue;
            // while blocked queue isn't empty(temporarily getting to empty) - goes thorugh blocked queue and updated ready queue with values if done with the ioburst
            while (!blockedQueue.empty()) {
                // gets first process in blocked queue and removes it
                Process blockedProcess = blockedQueue.front();
                blockedQueue.pop_front();

                // gets io burst time currently
                int ioBurstsforcur = blockedProcess.ioBursts.front();

                // gets remaining io burst after cpu burst has been executed
                int ioBurstAfterCPU = ioBurstsforcur - cpuBurst;

                // if io burst is completed
                if (ioBurstAfterCPU <= 0) {
                    // update executed I/O bursts with the full time of current burst and pops the burst
                    blockedProcess.executedIoBursts += ioBurstsforcur;
                    blockedProcess.ioBursts.pop_front();
                    
                    // pushes the process to ready queue as no longer blocked as io burst done
                    readyQueue.push_back(blockedProcess);
                } else {
                    // if io burst not completed, sets executed io burst as what has already been completed + the difference between current I/O burst and time after the CPU burst.
                    blockedProcess.executedIoBursts += (ioBurstsforcur - ioBurstAfterCPU);

                    // updates the io burst to remaining io time left and puts it to tempBlockedQueue as still needs to be in blocked queue
                    blockedProcess.ioBursts.front() = ioBurstAfterCPU;
                    tempBlockedQueue.push_back(blockedProcess);
                }
            }

            // if there are cpu burts push current process to back of blocked queue as cpuburst is done executing
            if (!currentProcess.cpuBursts.empty()) {
                tempBlockedQueue.push_back(currentProcess);
            } else {
                // else means completed and puts that at end of completed processes
                completedProcesses.push_back(currentProcess);
            }
            // puts the temp blocked queue through stable sort
            std::stable_sort(tempBlockedQueue.begin(), tempBlockedQueue.end(), [](const Process& proc1, const Process& proc2) {
                return proc1.ioBursts.front() < proc2.ioBursts.front();
            });

            // updates the blocked queue to new one, with updated values
            blockedQueue = tempBlockedQueue;
        // else if ready queue empty and blocked queue not
        } else if (!blockedQueue.empty()){
            int frontIoBurst = blockedQueue.front().ioBursts.front();

            // deque to set blocked queue to after all minipulation of blocked queue is done
            std::deque<Process> tempBlockedQueue;

            // while blocked queue isn't empty(temporarily getting to empty) - goes thorugh blocked queue and updated ready queue with values if done with the ioburst
            while (!blockedQueue.empty()) {
                // gets first process in blocked queue and removes it
                Process blockedProcess = blockedQueue.front();
                blockedQueue.pop_front();

                // gets io burst time currently
                int ioBurstsforcur = blockedProcess.ioBursts.front();

                // after io burst of front is executed, subtract that from this processes ioBurst done.
                ioBurstsforcur -= frontIoBurst;

                // if io burst is completed
                if (ioBurstsforcur <= 0) {
                    // update executed I/O bursts with the full time of current burst and pops the burst
                    blockedProcess.executedIoBursts += blockedProcess.ioBursts.front();
                    blockedProcess.ioBursts.pop_front();
                    
                    // pushes the process to ready queue as no longer blocked as io burst done
                    readyQueue.push_back(blockedProcess);
                } else {
                    // if io burst not completed, sets executed io burst as what has already been completed + the time after the front burst.
                    blockedProcess.executedIoBursts += frontIoBurst;
                    
                    // updates the io burst to remaining io time left and puts it to tempBlockedQueue as still needs to be in blocked queue
                    blockedProcess.ioBursts.front() = ioBurstsforcur;
                    tempBlockedQueue.push_back(blockedProcess);
                }
            }

            // blocked queue is set to the temp queue as that is the new blocked queue
            blockedQueue = tempBlockedQueue;
            // updates total time elapsed
            timeElapsed += frontIoBurst;
        }
    }
}

void Scheduler::runRR() {
    // flag for if quantum time has expired or not
    int qTimeExpired = false;

    //total time since scheuler starts
    int timeElapsed = 0;

    // adds processes to ready queue
    for (int i = 0; i < (int)allProcesses.size(); ++i) {
        readyQueue.push_back(allProcesses[i]);
    }

    //while there is still stuff in either queue, runs
    while (!readyQueue.empty() || !blockedQueue.empty()) {
        // if ready queue isn't empty
        if (!readyQueue.empty()) {
            // removes and puts from of readyQueue in currentProcess
            Process currentProcess = readyQueue.front();
            readyQueue.pop_front();

            // determines and sets the wait time for the current process
            int waitTime = timeElapsed - (currentProcess.executedCpuBursts + currentProcess.executedIoBursts);
            currentProcess.waitTime = (waitTime);

            // gets the next cpu burts and pops it from front of cpu bursts
            int cpuBurst = currentProcess.cpuBursts.front();

            // is variable for how much is left of the cpuburst after the time quatum is ran
            int remainingTimeCpuBurst = cpuBurst - timeQuantum;

            // if the time quantum had exceeded the amount in cpu burst, this just gets the amount of time that is left in the cpu burst
            int timeLeft = timeQuantum - std::abs(remainingTimeCpuBurst);

           qTimeExpired = false;
           if(remainingTimeCpuBurst > 0) {
                // quatum time expired is false unless the remaining time in cpu burst is greater than 0 and doesnt move to blocked queue
                qTimeExpired = true;
                //the current cpu burst would set to the remaing time in cpu burst, and exectues that time
                currentProcess.cpuBursts.front() = remainingTimeCpuBurst;
                currentProcess.executedCpuBursts += timeQuantum;
                // add the amount of time run to total time elapsed
                timeElapsed += timeQuantum;
            } else {
                // else(no remaining time in cpu burst) and the current cpu burst would removed from ready queue and executes the time that was left in cpu burst
                currentProcess.cpuBursts.pop_front();
                currentProcess.executedCpuBursts += timeLeft;
                // add the amount of time run to total time elapsed
                timeElapsed += timeLeft;
            }

            // prints/logs what is happening and if process has time quantum expired, entering io, or is completed
            if (qTimeExpired) {
                log_cpuburst_execution (currentProcess.id, currentProcess.executedCpuBursts, currentProcess.executedIoBursts, timeElapsed, QUANTUM_EXPIRED);
            } else if (!currentProcess.cpuBursts.empty() && !currentProcess.ioBursts.empty()) {
                log_cpuburst_execution (currentProcess.id, currentProcess.executedCpuBursts, currentProcess.executedIoBursts, timeElapsed, ENTER_IO);
            } else {
                log_cpuburst_execution (currentProcess.id, currentProcess.executedCpuBursts, currentProcess.executedIoBursts, timeElapsed, COMPLETED);
            }

            // deque to set blocked queue to after all minipulation of blocked queue is done
            std::deque<Process> tempBlockedQueue;
            // while blocked queue isn't empty(temporarily getting to empty) - goes thorugh blocked queue and updated ready queue with values if done with the ioburst
            while (!blockedQueue.empty()) {
                // gets first process in blocked queue and removes it
                Process blockedProcess = blockedQueue.front();
                blockedQueue.pop_front();

                // gets io burst time currently
                int ioBurstsforcur = blockedProcess.ioBursts.front();
                int ioBurstAfterRound = 0;

                // if the time quantum has expired, the io burst after round is subtracting the time quantum as that was the time executed otherwise it is the remaining cpu burst time
                if(qTimeExpired){
                    ioBurstAfterRound = ioBurstsforcur - timeQuantum;
                } else {
                    ioBurstAfterRound = ioBurstsforcur - std::abs(timeLeft);
                }

                // if io burst is completed
                if (ioBurstAfterRound <= 0) {
                    // update executed I/O bursts with the full time of current burst and pops the burst
                    blockedProcess.executedIoBursts += ioBurstsforcur;
                    blockedProcess.ioBursts.pop_front();
                    
                    // pushes the process to ready queue as no longer blocked as io burst done
                    readyQueue.push_back(blockedProcess);
                } else {
                    // if io burst not completed, sets executed io burst as what has already been completed + the difference between current I/O burst and time of io burst after round.
                    blockedProcess.executedIoBursts += (ioBurstsforcur - ioBurstAfterRound);

                    // updates the io burst to remaining io time left and puts it to tempBlockedQueue as still needs to be in blocked queue
                    blockedProcess.ioBursts.front() = ioBurstAfterRound;
                    tempBlockedQueue.push_back(blockedProcess);
                }
            }

            // if the time quantum has expired(did not get to end of cpu burst), pushes the current process to back of ready queue
            if(qTimeExpired) {
                readyQueue.push_back(currentProcess);
            }
            // if time quantum not expired, means either complete or done with the current cpu burst
            if(!qTimeExpired){
                // if there are cpu burts push current process to back of blocked queue as cpuburst is done executing
                if (!currentProcess.cpuBursts.empty()) {
                    tempBlockedQueue.push_back(currentProcess);
                } else {
                    // else means completed and puts that at end of completed processes
                    completedProcesses.push_back(currentProcess);
                }
            }

            // puts the temp blocked queue through stable sort
            std::stable_sort(tempBlockedQueue.begin(), tempBlockedQueue.end(), [](const Process& proc1, const Process& proc2) {
                return proc1.ioBursts.front() < proc2.ioBursts.front();
            });

            // updates the blocked queue to new one, with updated values
            blockedQueue = tempBlockedQueue;

        // else if ready queue empty and blocked queue not
        } else if (!blockedQueue.empty()){
            //gets the first io burst(shortest time/tied shortest)
            int frontIoBurst = blockedQueue.front().ioBursts.front();
            
            // deque to set blocked queue to after all minipulation of blocked queue is done
            std::deque<Process> tempBlockedQueue;
            // while blocked queue isn't empty(temporarily getting to empty) - goes thorugh blocked queue and updated ready queue with values if done with the ioburst
            while (!blockedQueue.empty()) {
                // gets first process in blocked queue and removes it
                Process blockedProcess = blockedQueue.front();
                blockedQueue.pop_front();

                // gets io burst time currently
                int ioBurstsforcur = blockedProcess.ioBursts.front();

                ioBurstsforcur -= frontIoBurst;
                
                // if io burst is completed
                if (ioBurstsforcur <= 0) {
                    // update executed I/O bursts with the full time of current burst(adds the current io burst) and pops the burst
                    blockedProcess.executedIoBursts += blockedProcess.ioBursts.front();
                    blockedProcess.ioBursts.pop_front();
                    
                    // pushes the process to ready queue as no longer blocked as io burst done
                    readyQueue.push_back(blockedProcess);
                } else {
                    // if io burst not completed, sets executed io burst as what has already been completed + the front io burst.
                    blockedProcess.executedIoBursts += frontIoBurst;
                    // updates the io burst to remaining io time left and puts it to tempBlockedQueue as still needs to be in blocked queue, also executing the time the front io burst did
                    blockedProcess.ioBursts.front() = ioBurstsforcur;
                    tempBlockedQueue.push_back(blockedProcess);
                }
            }
            // blocked queue is set to the temp queue as that is the new blocked queue
            blockedQueue = tempBlockedQueue;
            // updates total time elapsed
            timeElapsed += frontIoBurst;
        }
    }
}