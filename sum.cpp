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
   cout<<"\nEnter the elements: ";
   for (int i = 0; i < n; i++)
   {
      cin>>a[i];
   }
   
   double sum_val = 0.0;
   double start_p, stop_p;
   start_p = omp_get_wtime();
   omp_set_num_threads(4);
#pragma omp parallel for reduction(+ : sum_val)
   for (int i = 0; i < n; i++)
   {
      sum_val += a[i];
   }

   stop_p = omp_get_wtime();
   cout << "\nSum of array = " << sum_val;
   cout << "\nTime Estimated = " << stop_p - start_p << " seconds.\n";

   return 0;
}
