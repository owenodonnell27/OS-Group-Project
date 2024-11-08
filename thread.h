#ifndef THREAD_HEADER
#define THREAD_HEADER

class myThread {
public:
    int id;
    int priority;
    int toa;    // Time of arrival
    int ttc;    // Time to complete
    int state;

    bool operator<(const myThread& otherThread) const;
};

#endif