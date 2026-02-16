#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>   // Added for CSV file handling

using namespace std;
using namespace chrono;

// ---------------- N-ARY SEARCH FUNCTION ----------------
int nArySearch(vector<int>& arr, int key, int low, int high, int partitions)
{
    while (low <= high)
    {
        int size = high - low + 1;
        int step = size / partitions;

        if (step == 0)
            return -1;

        for (int i = 1; i <= partitions; i++)
        {
            int mid = low + i * step - 1;

            if (mid > high)
                mid = high;

            if (arr[mid] == key)
                return mid;

            if (arr[mid] > key)
            {
                high = mid - 1;
                break;
            }
            else
            {
                low = mid + 1;
            }
        }
    }

    return -1;
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
    srand(time(0));

    // Create CSV file
    ofstream file("Practical4_NArySearch_Results.csv");
    file << "InputSize,Partitions,AverageTime_ms,RandomKey\n";

    int configurations[3] = {50000, 70000, 100000};
    int searches = 20000;   // Increased for visible timing

    for (int config = 0; config < 3; config++)
    {
        int N = configurations[config];

        cout << "\n-----------------------------------\n";
        cout << "Configuration " << config + 1 << endl;
        cout << "Input Size: " << N << endl;
        cout << "Partitions\tAverage Time (milliseconds)" << endl;

        // Generate random sorted array
        vector<int> arr(N);
        for (int i = 0; i < N; i++)
            arr[i] = rand();

        sort(arr.begin(), arr.end());

        for (int partitions = 2; partitions <= 8; partitions++)
        {
            auto start = high_resolution_clock::now();

            for (int i = 0; i < searches; i++)
            {
                int key = arr[rand() % N];  // Random key from array
                nArySearch(arr, key, 0, N - 1, partitions);
            }

            auto end = high_resolution_clock::now();

            double timeTaken = duration<double, milli>(end - start).count();

            cout << partitions << "\t\t"
                 << timeTaken / searches << endl;

            // Write to CSV file
            file << N << "," 
                 << partitions << "," 
                 << timeTaken / searches << "," 
                 << arr[rand() % N] << "\n"; // Random key used
        }
    }

    file.close();
    return 0;
}
