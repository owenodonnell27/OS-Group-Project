#ifndef THREAD_HEADER
#define THREAD_HEADER

class MyThread {
public:    
    // Thread constructors
    MyThread() {}
    MyThread(int id, int priority, int toa, int ttc, int state): 
        id(id), priority(priority), toa(toa), ttc(ttc), state(state), turnAround(-1), responseTime(-1) {}

    // operator overloading used for CPU's priority queue
    // Based off priority and toa
    bool operator<(const MyThread& otherThread) const;

    // Set the turn around time
    void setTurnAround(int x) {turnAround = x;}

    // Returns the thread's turn around time
    int getTurnAround();

    // Returns the thread's response time
    int getResponseTime();

    int id;
    int priority;

    // Time of arrival
    int toa;    

    // Time to complete
    int ttc;    

    // 1: running, 2: ready, 3: blocked, 0: otherwise
    int state;

    // These variables will be changed by the CPU to help calculate turn around, waiting time, and response time
    int turnAround;
    int responseTime;
};

#endif