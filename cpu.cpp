#include "cpu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int MyCpu::loadThreadsFromFile(string filename) {
    ifstream f(filename);
    string line;

    while (getline(f, line)) {
        istringstream job(line);
        MyThread newThread;
        
        job >> newThread.id >> newThread.priority >> newThread.toa >> newThread.ttc >> newThread.state;

        ready_queue.push(newThread);
    }
    f.close();
    return 0;
}

int MyCpu::loadThread(MyThread thread) {
    allThreads.push_back(thread);

    sort(allThreads.begin(), allThreads.end(), [](const MyThread &a, const MyThread &b) {return a.toa > b.toa;});
    return 0;
}

int MyCpu::runNextThread() {
    running = ready_queue.top();
    ready_queue.pop();
    cout << "Thread " << running.id << " taking the CPU." << endl;
    running.ttc -= timeSlice;
    cout << "Thread " << running.id << " doing work on the CPU. Has " << running.ttc << " left." << endl;
    if(running.ttc > 0) {
        ready_queue.push(running);
        cout << "Thread " << running.id << " giving up the CPU." << endl;
    }
    else {
        cout << "Thread " << running.id << " is done." << endl;
    }
    return 0;
}

int MyCpu::runCPU() {
    while(!ready_queue.empty() || !allThreads.empty()) {

        if(!allThreads.empty()) {
            while(allThreads.back().toa == time) {
                cout << "Adding thread to pq\n";
                MyThread readyThread = allThreads.back();
                allThreads.pop_back();
                ready_queue.push(readyThread);
            }
        }
        if(!ready_queue.empty()) {
            cout << "Running next thread\n";
            runNextThread();
        }
        time++;
        cout << "Time is now " << time << endl;
    }
    return 0;
}

void MyCpu::printThreads() {

    while(!ready_queue.empty()) {
        MyThread thread = ready_queue.top();
        cout << "ID: " << thread.id << ", Priority: " << thread.priority << ", TOA: " << thread.toa
             << ", TTC: " << thread.ttc << ", State:" << thread.state << endl;

        ready_queue.pop();
    }
}