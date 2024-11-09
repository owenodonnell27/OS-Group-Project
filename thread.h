#ifndef THREAD_HEADER
#define THREAD_HEADER

class MyThread {
public:
    int id;
    int priority;
    int toa;    // Time of arrival
    int ttc;    // Time to complete
    int state;
    
    MyThread() {}
    MyThread(int id, int priority, int toa, int ttc, int state): id(id), priority(priority), toa(toa), ttc(ttc), state(state) {}

    bool operator<(const MyThread& otherThread) const;
};

#endif