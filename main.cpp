#include <iostream>
#include <fstream>
#include "cpu.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the filename is provided
    if (argc != 2) {
        cerr << "Usage: ./scheduler <filename>" << endl;
        return 1;
    }

    string filename = argv[1];

    // Initialize the CPU
    MyCpu MyCpu;

    // Load threads from the file
    if (MyCpu.loadThreadsFromFile(filename) != 0) {
        cerr << "Error loading threads from file: " << filename << endl;
        return 1;
    }

    // Set the CPU time slice (example: 1 unit)
    MyCpu.setTimeSlice(1);

    // Run the CPU simulation
    MyCpu.runCPU();

    // Print completed thread statistics
    MyCpu.printCompletedThreads();

    return 0;
}
