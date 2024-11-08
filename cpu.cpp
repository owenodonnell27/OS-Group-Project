#include "cpu.h"
#include <fstream>

using namespace std;

int myCpu::loadThreads(string filename) {

    string line;
    ifstream f(filename);
    while (getline(f, line)) {
        myThread newThread;
        newThread.id = (int)line[0];
        newThread.ttc = (int)line[2];
        newThread.priority = (int)line[4];
        newThread.toa = (int)line[6];
        newThread.state = (int)line[8];
        newThread.ioTime = (int)line[10];

        pq.push(newThread);
    }

    f.close();
    return 0;
}