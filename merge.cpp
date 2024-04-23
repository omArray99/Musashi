#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void mergesort(int a[], int i, int j, int depth = 0);
void mergesort_seq(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort_seq(int a[], int i, int j) {
    int mid;
    if (i < j) {
        mid = (i + j) / 2;
        mergesort_seq(a, i, mid);
        mergesort_seq(a, mid + 1, j);
        merge(a, i, mid, mid + 1, j);
    }
}

void mergesort(int a[], int i, int j, int depth) {
    int mid;
    if (i < j) {
        mid = (i + j) / 2;
        if (depth < 2) {  // Control the depth of parallelism
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    mergesort(a, i, mid, depth + 1);
                }
                #pragma omp section
                {
                    mergesort(a, mid + 1, j, depth + 1);
                }
            }
        } else {
            mergesort(a, i, mid, depth + 1);
            mergesort(a, mid + 1, j, depth + 1);
        }
        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2) {
    int *temp = new int[j2 - i1 + 1];
    int i = i1, j = i2, k = 0;
    while (i <= j1 && j <= j2) {
        if (a[i] < a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= j1) {
        temp[k++] = a[i++];
    }
    while (j <= j2) {
        temp[k++] = a[j++];
    }
    for (i = i1, j = 0; i <= j2; i++, j++) {
        a[i] = temp[j];
    }
    delete[] temp;
}

int main() {
    int *a, n, i;
    cout << "Enter total number of elements: ";
    cin >> n;

    a = new int[n];
    for (i = 0; i < n; i++) {
        a[i] = rand() % 10000;
    }

    double start_s = omp_get_wtime();
    mergesort_seq(a, 0, n - 1);
    double stop_s = omp_get_wtime();
    /*cout << "\nSorted array by sequential mergesort:";
    for (i = 0; i < n; i++) {
        cout << " " << a[i];
    }*/
    cout << "\nTime Sequential: " << stop_s - start_s << " seconds";

    // Re-initialize array for fairness in comparison
    for (i = 0; i < n; i++) {
        a[i] = rand() % 10000;
    }

    double start = omp_get_wtime();
    mergesort(a, 0, n - 1);
    double stop = omp_get_wtime();
    /*cout << "\nSorted array by parallel mergesort:";
    for (i = 0; i < n; i++) {
        cout << " " << a[i];
    }*/
    cout << "\nTime Parallel: " << stop - start << " seconds";

    delete[] a;
    return 0;
}

