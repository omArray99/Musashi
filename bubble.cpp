#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<cstring>
using namespace std;

double start,stop,start_p,stop_p;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble_seq(int *a, int n) {
    double start = omp_get_wtime();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
    double stop = omp_get_wtime();
    cout << "Sequential time: " << stop - start << " seconds" << endl;
}

void bubble_parallel(int *a, int n) {
    double start_p = omp_get_wtime();
    
    for(int i = 0; i < n; i++) {
        omp_set_num_threads(2);
        #pragma omp parallel for 
        for(int j = 0; j < n - 1 - i; j++) {
            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
    double stop_p = omp_get_wtime();
    cout << "Parallel time: " << stop_p - start_p << " seconds" << endl;
}

int main()
{
  int n;
  cout<<"\n Enter total no of Elements = ";
  cin>>n;
  
  int *a = new int[n];
    for(int i = 0; i < n; i++) {
        a[i] = rand() % 100000;
    }
  

  int *b = new int[n];
    memcpy(b, a, n * sizeof(int)); // Create a copy for parallel version

    bubble_seq(a, n);
    bubble_parallel(b, n);

    delete[] a;
    delete[] b;
  
  /*a=new int[n];
  cout<<"\n enter elements=>";
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
  }
  
  bubble(a,n);
  cout<<"\n Sorted array is = \n";
  for(int i=0;i<n;i++)
  {
    cout<<a[i]<<" ";
  }
  
  bubble_seq(a,n);
  cout<<"\n Sequential sorted array is = \n";
  for(int i=0;i<n;i++)
  {
    cout<<a[i]<<" ";
  }*/

  return 0;
}

