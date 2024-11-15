#include "thread.h"

bool MyThread::operator<(const MyThread& otherThread) const {
    // If the threads have the same priority, the one that arrived first gets priority
    if(priority == otherThread.priority) {
        return toa > otherThread.toa;
    }
    else {
        return priority > otherThread.priority;
    }
}

// Returns the thread's turn around time
int MyThread::getTurnAround() {
    return (toc == -1) ? 0 : toc - toa; // Ensure no negative value
}

// Returns the thread's response time
long long MyThread::getResponseTime() {
    return (responseTime >= toa) ? responseTime - toa : 0;  // Ensure no negative value
}
