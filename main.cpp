#include <iostream>
#include "cpu.h"

using namespace std;

int main() {
    myCpu myCpu;

    myCpu.loadThreads("jobs.txt");
    myCpu.printThreads();

    return 0;
}
