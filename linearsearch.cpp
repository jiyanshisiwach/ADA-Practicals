#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <fstream>   // For CSV file
using namespace std;
using namespace chrono;

int linearSearch(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int main() {

    srand(time(0));   // Seed random generator

    int startSize = 300000;
    int endSize = 500000;
    int stepSize = 20000;
    int searches = 2000;

    // Create CSV file
    ofstream file("Practical1_LinearSearch_Results.csv");
    file.seekp(0, ios::end);
    if (file.tellp() == 0) {
    file << "InputSize,Time_ms\n";
    }
    cout << "InputSize\tTime(ms)\n";

    for (int n = startSize; n <= endSize; n += stepSize) {

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (2 * n);

        auto start = high_resolution_clock::now();

        for (int i = 0; i < searches; i++) {
            int key = rand() % (2 * n);
            linearSearch(arr, key);
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << n << "\t\t" << duration.count() << endl;

        // Write to CSV
        file << n << "," << duration.count() << "\n";
        
    }

    file.close();

    cout << "\nCSV file generated successfully!\n";

    return 0;
}
