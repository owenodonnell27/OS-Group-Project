#ifndef CPU_HEADER
#define CPU_HEADER

#include "thread.h"
#include <queue>
#include <string>
#include <vector>

using namespace std;

class MyCpu {
public:
    int loadThreadsFromFile(string filename);
    int loadThread(MyThread thread);
    int runNextThread();
    int runCPU();
    void printThreads();
    void setTime(int newTime) {time = newTime;}
    void setTimeSlice(int newTimeSlice) {timeSlice = newTimeSlice;}

private:
    vector<MyThread> allThreads;
    priority_queue<MyThread> ready_queue;
    MyThread running;
    vector<MyThread> blocked;
    int time;
    int timeSlice;
};

#endif