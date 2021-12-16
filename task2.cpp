#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <algorithm>
using namespace std::chrono;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    double* arr = new double[n];
    for (long int i = 0; i < n; i++) {
        arr[i] = (double)rand() / RAND_MAX;

    }
    for (int num = 1; num <= 10; num++) {
        double max_value = arr[0];
        auto start = high_resolution_clock::now();
#pragma omp parallel for num_threads(num) reduction(max : max_value)
        for (int i = 0; i < n; i++) {
            max_value =std::max(max_value, arr[i]);
        }
        auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
        printf("thread(s): %d , time: %lld,max value =%f \n", num, duration.count(),max_value);

    }
    delete[] arr;
    return 0;
}