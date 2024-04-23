#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int main()
{
   int n;
   cout << "Enter no. of elements: ";
   cin >> n;
   double a[n];
   //int num;
   cout<<"\nEnter the elements: ";
   for (int i = 0; i < n; i++)
   {
      cin>>a[i];
   }


   double seq_start,seq_stop;
   seq_start = omp_get_wtime();
   double seq_sum = 0.0;
   for (int i = 0; i < n; i++)
   {
      seq_sum += a[i];
   }
   double seq_avg = seq_sum / n;
   seq_stop = omp_get_wtime();
   cout<<"Averge: "<<seq_avg<<endl;
   cout<<"Time Estimated: "<<seq_stop-seq_start<<" seconds."<<endl;

   double sum_val = 0.0;
   double start_p, stop_p;
   start_p = omp_get_wtime();
   omp_set_num_threads(4);
#pragma omp parallel for reduction(+ : sum_val)
   for (int i = 0; i < n; i++)
   {
      sum_val += a[i];
   }

   double average_val = sum_val / n;

   stop_p = omp_get_wtime();
   cout << "\nAverage of array = " << average_val;
   cout << "\nTime Estimated = " << stop_p - start_p << " seconds.\n";

   return 0;
}
