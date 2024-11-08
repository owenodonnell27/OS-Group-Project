#include "thread.h"

bool myThread::operator<(const myThread& otherThread) const {
    if(priority == otherThread.priority) {
        return toa > otherThread.toa;
    }
    else {
        return priority > otherThread.priority;
    }
}