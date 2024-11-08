#include "cpu.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int myCpu::loadThreads(string filename) {
    ifstream f(filename);
    string line;

    while (getline(f, line)) {
        istringstream job(line);
        myThread newThread;
        
        job >> newThread.id >> newThread.priority >> newThread.toa >> newThread.ttc >> newThread.state;

        ready_queue.push(newThread);
    }
    f.close();
    return 0;
}

void myCpu::printThreads() {

    while(!ready_queue.empty()) {
        myThread thread = ready_queue.top();
        cout << "ID: " << thread.id << ", Priority: " << thread.priority << ", TOA: " << thread.toa
             << ", TTC: " << thread.ttc << ", State:" << thread.state << endl;

        ready_queue.pop();
    }
}