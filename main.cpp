#include <iostream>
#include "cpu.h"

using namespace std;

int main() {
    MyCpu myCpu;
    MyThread myThread1(1, 2, 1, 5, 0);
    MyThread myThread2(2, 1, 3, 2, 0);

    myCpu.loadThread(myThread1);
    myCpu.loadThread(myThread2);

    myCpu.setTime(0);
    myCpu.setTimeSlice(1);
    // myCpu.loadThreads("jobs.txt");
    // myCpu.printThreads();
    myCpu.runCPU();

    return 0;
}
