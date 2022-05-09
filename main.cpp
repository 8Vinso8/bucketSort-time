#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace chrono;
static void BucketSort(int* data, int count) {
    int minValue = data[0];
    int maxValue = data[0];

    for (int i = 1; i < count; i++)
    {
        if (data[i] > maxValue)
            maxValue = data[i];
        if (data[i] < minValue)
            minValue = data[i];
    }

    int bucketLength = maxValue - minValue + 1;
    auto* bucket = new vector<int>[bucketLength];

    for (int i = 0; i < bucketLength; i++)
    {
        bucket[i] = vector<int>();
    }

    for (int i = 0; i < count; i++)
    {
        bucket[data[i] - minValue].push_back(data[i]);
    }

    int k = 0;
    for (int i = 0; i < bucketLength; i++)
    {
        int bucketSize = bucket[i].size();

        if (bucketSize > 0)
        {
            for (int j = 0; j < bucketSize; j++)
            {
                data[k] = bucket[i][j];
                k++;
            }
        }
    }
}


int main()
{
    high_resolution_clock::time_point t1, t2;
    vector<int> v;
    vector<long long int> times;
    for (int i = 1; i <= 8; i++)
    {
        long long duration_total = 0;
        for (int j = 0; j < 10; j++)
        {
            for (int n = 0; n < pow(10, i); n++)
            {
                v.emplace_back(rand());
            }
            t1 = high_resolution_clock::now();
            BucketSort(&v[0], v.size());
            t2 = high_resolution_clock::now();
            long long duration = duration_cast<microseconds>(t2 - t1).count();
            duration_total += duration;

            v.clear();
        }
        long long int average_duration = duration_total / 10;
        times.emplace_back(average_duration);
        cout << i << "...";
    }
    cout << endl;

    for (int i = 0; i < 8; i++)
    {
        cout << pow(10, i + 1) << " : " << times[i] << "us"<< endl;
    }
    return 0;
}