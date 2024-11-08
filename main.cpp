#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include "cpu.h"

using namespace std;

int main() {
    cout << "CPU boot up" << endl; 

    myCpu myCpu;

    myCpu.loadThreads("jobs.txt");
    myThread t = myCpu.pq.top();
    int x = t.id;

    cout << x << endl;

    return 0;
}
