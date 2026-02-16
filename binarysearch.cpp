#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

int binarySearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int startSize = 300000;
    int endSize = 500000;
    int stepSize = 20000;
    int searches = 2000;

    // Open CSV file in APPEND mode
    ofstream file("Practical4_BinarySearch.csv", ios::app);

    // Write header only if file is empty
    file.seekp(0, ios::end);
    if (file.tellp() == 0) {
        file << "InputSize,Time_microseconds\n";
    }

    cout << "InputSize\tTime(us)\n";

    for (int n = startSize; n <= endSize; n += stepSize) {

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (2 * n);

        sort(arr.begin(), arr.end());

        auto start = high_resolution_clock::now();

        for (int i = 0; i < searches; i++) {
            int key = rand() % (2 * n);
            binarySearch(arr, key);
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << n << "\t\t" << duration.count() << endl;

        // Write to CSV
        file << n << "," << duration.count() << "\n";
    }

    file.close();

    cout << "\nData successfully appended to Practical4_BinarySearch.csv\n";

    return 0;
}
