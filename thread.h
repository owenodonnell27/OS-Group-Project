#ifndef THREAD_HEADER
#define THREAD_HEADER

class MyThread {
public:    
    // Default Constructor
    MyThread() : id(0), priority(0), toa(0), ttc(0), state(0), turnAround(-1), responseTime(-1) {}

    // Parameterized Constructor
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
    long long getResponseTime();

    int id;
    int priority;
    int toa; // Time of arrival
    int ttc; // Time to complete

    // 1: running, 2: ready, 3: blocked, 0: otherwise
    int state;

    // These variables will be changed by the CPU to help calculate turn around, waiting time, and response time
    int turnAround;
    long long responseTime;
};

#endif