#include "cpu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

MyCpu::MyCpu() : time(0), timeSlice(1) {  // Ensure both variables are initialized
    //cout << "Debug: Initial time: " << time << endl;  // Debugging initial time
}

int MyCpu::loadThreadsFromFile(string filename) {
    ifstream f(filename);
    string line;

    while (getline(f, line)) {
        istringstream job(line);
        MyThread newThread;
        
        job >> newThread.id >> newThread.priority >> newThread.toa >> newThread.ttc >> newThread.state;

        readyQueue.push(newThread);
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
    // Print a separator for each time step
    cout << "==============================" << endl;
    cout << "Time " << time << endl;
    cout << "------------------------------" << endl;
    cout << "Running next thread" << endl;

    // The thread with the highest priority becomes the running thread
    running = readyQueue.top();
    readyQueue.pop();
    cout << "Thread " << running.id << " taking the CPU at time " << time << "." << endl;
    //cout << "Debug: Thread " << running.id << " Arrival Time (TOA): " << running.toa << endl;

    //cout << "Debug: Before checking, responseTime for Thread " << running.id << " is " << running.responseTime << endl;

    // The first time the thread uses the CPU, log the current time to calculate the response time
    if (running.responseTime == -1) {
        running.responseTime = time;  // Correctly set response time to the current time
        //cout << "Debug: Setting response time for Thread " << running.id << " to " << running.responseTime << " (current time: " << time << ")" << endl;
    }

    // Thread using the CPU
    running.ttc -= timeSlice;
    cout << "Thread " << running.id << " doing work on the CPU. Has " << running.ttc << " left." << endl;

    // Check if the thread has completed its work
    if (running.ttc <= 0) {
        running.turnAround = (time + 1) - running.toa;  // Correct turnaround time calculation
        //cout << "Debug: Calculated Turnaround Time for Thread " << running.id << ": " << running.turnAround << endl;
        MyThread completedThread = running;  // Make a copy of `running`
        completedThreads.push_back(completedThread);  // Push the copy to avoid shallow copy issues
        cout << "Thread " << running.id << " is done." << endl;
    }
 else {
        readyQueue.push(running);
        cout << "Thread " << running.id << " giving up the CPU." << endl;
    }

    return 0;
}


int MyCpu::runCPU() {
    
    // As long as there are threads in the readyQueue or coming in the future
    while(!readyQueue.empty() || !futureThreads.empty()) {
        cout << "Time " << time << endl;
        // Check if the threads in futureThreads can be added to readyQueue
        if(!futureThreads.empty()) {
            /* while(futureThreads.back().toa == time) {
                //cout << "Adding thread to ready queue\n";
                cout << "Debug: Adding thread " << futureThreads.back().id << " to ready queue at time " << time << endl;
                MyThread readyThread = futureThreads.back();
                futureThreads.pop_back();
                readyQueue.push(readyThread);
            } */

            while (!futureThreads.empty() && futureThreads.back().toa == time) {
                MyThread readyThread = futureThreads.back();
                futureThreads.pop_back();
                readyQueue.push(readyThread);
                //cout << "Debug: Adding thread " << readyThread.id << " to ready queue at time " << time << endl;
            }
        }
        // If there are threads in readyQueue, let them use the CPU
        if(!readyQueue.empty()) {
            cout << "Running next thread\n";
            //cout << "Debug: Running next thread from ready queue at time " << time << endl;
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
             << "    Turn around time: " << thread.turnAround 
             << "    Response time: " << thread.responseTime << endl;
    }
    cout << "==============================" << endl;
}


// print arrival time of threads
void MyCpu::printArrivalTimes() {
    // Copy the readyQueue to preserve the order
    priority_queue<MyThread> tempQueue = readyQueue;
    
    while (!tempQueue.empty()) {
        MyThread thread = tempQueue.top();
        tempQueue.pop();
        cout << "Thread ID: " << thread.id << ", Arrival Time (TOA): " << thread.toa << endl;
    }
}
