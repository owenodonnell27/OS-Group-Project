#include "thread.h"

bool MyThread::operator<(const MyThread& otherThread) const {
    if(priority == otherThread.priority) {
        return toa > otherThread.toa;
    }
    else {
        return priority > otherThread.priority;
    }
}