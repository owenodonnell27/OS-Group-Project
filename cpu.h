#ifndef CPU_HEADER
#define CPU_HEADER


#include "thread.cpp"
#include <queue>
#include <string>

using namespace std;

class myCpu {
public:
    int loadThreads(string filename);

    priority_queue<myThread> pq;
};

#endif