#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <fstream>   // Added for CSV file

using namespace std;
using namespace chrono;

// Algorithm 1: Independent if statements
void maxMinIndependent(const vector<int>& arr) {
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
        if (arr[i] < minVal)
            minVal = arr[i];
    }
}

// Algorithm 2: If-else structure
void maxMinIfElse(const vector<int>& arr) {
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
        else if (arr[i] < minVal)
            minVal = arr[i];
    }
}

int main() {

    srand(time(0));

    int startSize = 100000;
    int endSize = 300000;
    int stepSize = 20000;
    int iterations = 2000;

    // Create CSV file
    ofstream file("Practical3_MaxMin_Results.csv", ios::app);
    file.seekp(0, ios::end);
    if (file.tellp() == 0) {
    file << "InputSize,Independent_ms,IfElse_ms\n";
    }
    cout << "InputSize\tIndependent(ms)\tIfElse(ms)\n";

    for (int n = startSize; n <= endSize; n += stepSize) {

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (2 * n);

        auto start1 = high_resolution_clock::now();
        for (int i = 0; i < iterations; i++)
            maxMinIndependent(arr);
        auto stop1 = high_resolution_clock::now();

        auto start2 = high_resolution_clock::now();
        for (int i = 0; i < iterations; i++)
            maxMinIfElse(arr);
        auto stop2 = high_resolution_clock::now();

        auto time1 = duration_cast<milliseconds>(stop1 - start1).count();
        auto time2 = duration_cast<milliseconds>(stop2 - start2).count();

        cout << n << "\t\t" << time1 << "\t\t" << time2 << endl;

        // Write to CSV
        file << n << ","
             << time1 << ","
             << time2 << "\n";
    }

    file.close();

    cout << "\nCSV file generated successfully!\n";

    return 0;
}
