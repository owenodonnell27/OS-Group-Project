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
    return (turnAround == -1) ? 0 : turnAround - toa; // Ensure no negative value
}

// Returns the thread's response time
int MyThread::getResponseTime() {
    return (responseTime >= toa) ? responseTime - toa : 0;  // Ensure no negative value
}

//returns thread priority
int MyThread::getPriority(){
    return priority;
}

//set current thread priority
void MyThread::setPriority(int newPriority){
    priority = newPriority;
}

//age implementation
void MyThread::age(){
    waitTime++;
    if (waitTime >= 3){
        if (priority > 1)
            priority--;
    }
}

