#ifndef THREAD_HEADER
#define THREAD_HEADER

class MyThread {
public:    
    // Thread constructors
    MyThread() {}
    MyThread(int id, int priority, long long toa, long long ttc): 
        id(id), priority(priority), toa(toa), ttc(ttc), state(0), toc(-1), responseTime(-1) {}

    // operator overloading used for CPU's priority queue
    // Based off priority and toa
    bool operator<(const MyThread& otherThread) const;

    // Returns the thread's turn around time
    int getTurnAround();

    // Returns the thread's response time
    int getResponseTime();

    int id;
    int priority;

    // Time of arrival
    long long toa;    

    // Time to complete
    long long ttc;    

    // 1: running, 2: ready, 3: blocked, 0: otherwise
    int state;

    // Time of completion
    long long toc;

    // Time when the thread first gets to use the cpu
    long long responseTime;
};

#endif