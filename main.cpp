#include <iostream>
#include "cpu.h"

using namespace std;

int main() {
    // Init the CPU and threads
    MyCpu myCpu;
    MyThread myThread1(1, 2, 1, 5, 0);
    MyThread myThread2(2, 1, 3, 2, 0);

    // Load the threads to the CPU
    myCpu.loadThread(myThread1);
    myCpu.loadThread(myThread2);

    // Set the CPU to start at time = 0 and timeSlice = 1
    // myCpu.setTime(0);
    myCpu.setTimeSlice(1);

    // Start the CPU
    myCpu.runCPU();

    myCpu.printCompletedThreads();

    return 0;
}
