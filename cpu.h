#ifndef CPU_HEADER
#define CPU_HEADER

#include "thread.h"
#include <queue>
#include <string>
#include <vector>

using namespace std;

class MyCpu {
public:
    // Load files from a file (currently disabled)
    int loadThreadsFromFile(string filename);

    // Load one thread
    int loadThread(MyThread thread);

    // Function to run the next thread in the ready_queue
    int runNextThread();

    // Run the CPU which wont stop until all the threads are done
    int runCPU();

    // print all the threads in the ready_queue (was used mostly for testing/debugging)
    void printThreads();

    // Set the time that the CPU is at
    void setTime(int newTime) {time = newTime;}

    // Set how much time the CPU works on one thread for
    void setTimeSlice(int newTimeSlice) {timeSlice = newTimeSlice;}

private:
    // Threads that will arrive in the future
    vector<MyThread> futureThreads;

    // All threads that are ready
    priority_queue<MyThread> ready_queue;

    // The one thread that is running
    MyThread running;

    // Blocked threads
    vector<MyThread> blocked;

    // Time interval and how much time CPU work on one thread
    int time;
    int timeSlice;
};

#endif