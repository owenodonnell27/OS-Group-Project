#ifndef THREAD_HEADER
#define THREAD_HEADER

class MyThread {
public:    
    // Thread constructors
    MyThread() {}
    MyThread(int id, int priority, int toa, int ttc, int state): id(id), priority(priority), toa(toa), ttc(ttc), state(state) {}

    // operator overloading used for CPU's priority queue
    // Based off priority and toa
    bool operator<(const MyThread& otherThread) const;

    int id;
    int priority;

    // Time of arrival
    int toa;    

    // Time to complete
    int ttc;    

    // 1: running, 2: ready, 3: blocked, 0: otherwise
    int state;
};

#endif