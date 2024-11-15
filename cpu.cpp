#include "cpu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int MyCpu::loadThreadsFromFile(string filename) {
    ifstream f(filename);
    string line;

    // Using the data on each line of the supplied file, create a thread and add it to the CPU
    while (getline(f, line)) {
        istringstream job(line);
        vector<int> jobArgs;
        int arg;

        while(job >> arg) {
            jobArgs.push_back(arg);
        }

        MyThread newThread(jobArgs[0], jobArgs[1], jobArgs[2], jobArgs[3]);
        loadThread(newThread);
    }
    f.close();
    return 0;
}

int MyCpu::loadThread(MyThread thread) {
    // Add thread to the vector of future threads
    futureThreads.push_back(thread);

    // Sort threads so that the threads with the closest toa are towards the end
    sort(futureThreads.begin(), futureThreads.end(), [](const MyThread &a, const MyThread &b) {return a.toa > b.toa;});
    return 0;
}

int MyCpu::runNextThread() {
    // The thread with the highest priority becomes the running thread
    running = readyQueue.top();
    readyQueue.pop();
    cout << "Thread " << running.id << " taking the CPU." << endl;

    // The first time that the thread uses the cpu, log the time to get the response time
    if(running.responseTime == -1) {
        running.responseTime = time;

        //Debug statement
        cout << "Debug: Setting response time for Thread " << running.id << " to " << running.responseTime << endl;
    }
    
    // Thread using the CPU
    running.ttc -= timeSlice;
    cout << "Thread " << running.id << " doing work on the CPU. Has " << running.ttc << " left." << endl;

    // Depening if the thread still needs to the CPU it will be added back to ready queue
    // otherwise, it will be forgotten
    if(running.ttc > 0) {
        readyQueue.push(running);
        cout << "Thread " << running.id << " giving up the CPU." << endl;
    }
    else {
        // If the thread has completed, set the turnAround time
        running.toc = time + timeSlice;
        completedThreads.push_back(running);
        cout << "Thread " << running.id << " is done." << endl;
    }
    return 0;
}

int MyCpu::runCPU() {
    
    // As long as there are threads in the readyQueue or coming in the future
    while(!readyQueue.empty() || !futureThreads.empty()) {
        cout << "Time " << time << endl;
        // Check if the threads in futureThreads can be added to readyQueue
        if(!futureThreads.empty()) {
            while(futureThreads.back().toa == time) {
                //cout << "Adding thread to ready queue\n";
                cout << "Debug: Adding thread " << futureThreads.back().id << " to ready queue at time " << time << endl;
                MyThread readyThread = futureThreads.back();
                futureThreads.pop_back();
                readyQueue.push(readyThread);
            }
        }
        // If there are threads in readyQueue, let them use the CPU
        if(!readyQueue.empty()) {
            //cout << "Running next thread\n";
            cout << "Debug: Running next thread from ready queue at time " << time << endl;
            runNextThread();
        }
        // Increment the time
        time++;
    }
    return 0;
}

void MyCpu::printReadyThreads() {

    while(!readyQueue.empty()) {
        MyThread thread = readyQueue.top();
        cout << "ID: " << thread.id << ", Priority: " << thread.priority << ", TOA: " << thread.toa
             << ", TTC: " << thread.ttc << ", State:" << thread.state << endl;

        readyQueue.pop();
    }
}

// print all threads once completed
void MyCpu::printCompletedThreads() {
    cout << "==============================" << endl;
    cout << "Statistics" << endl;
    cout << "------------------------------" << endl;
    for (MyThread thread : completedThreads) {
        /* Debug: Print all details of the thread before printing statistics
        cout << "Debug: Thread ID: " << thread.id
             << ", TOA: " << thread.toa
             << ", Turn around time: " << thread.turnAround
             << ", Response time: " << thread.responseTime << endl;
        */

        cout << "Thread: " << thread.id 
             << "    Turn around time: " << thread.getTurnAround()
             << "    Response time: " << thread.getResponseTime() << endl;
    }
  cout << "==============================" << endl;
  printCPUStats();
  cout << "==============================" << endl;
}

// print cpu stats (average response time, average turnaround)
void MyCpu::printCPUStats() {

    // Does so by taking the average of all the thread stats
    int numThreads = 0;
    float responseSum = 0;
    float turnAroundSum = 0;

    for(MyThread thread: completedThreads) {
        numThreads++;
        responseSum += thread.getResponseTime();
        turnAroundSum += thread.getTurnAround();
    }

    float averageResponse = responseSum / numThreads;
    float averageTurnAround = turnAroundSum / numThreads;

    cout << "The average response time was " << averageResponse << " and the average turn around was " << averageTurnAround << endl;
}