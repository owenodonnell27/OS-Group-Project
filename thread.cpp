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