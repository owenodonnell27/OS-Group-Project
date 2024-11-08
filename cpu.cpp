#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

int main() {
    cout << "CPU boot up" << endl; 

    // Print out the list of jobs
    ifstream f("jobs.txt");
    string line;
    while (getline(f, line)) {
        cout << "Job #" << line[0] << ", Time = " << line[2] << endl;
    }

    f.close();
    return 0;
}
