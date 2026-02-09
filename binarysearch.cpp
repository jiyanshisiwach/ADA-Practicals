#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
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
    }
    return 0;
}
