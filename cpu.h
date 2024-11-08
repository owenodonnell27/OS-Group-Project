#ifndef CPU_HEADER
#define CPU_HEADER

#include "thread.h"
#include <queue>
#include <string>

using namespace std;

class myCpu {
public:
    priority_queue<myThread> ready_queue;

    int loadThreads(string filename);
    void printThreads();
};

#endif