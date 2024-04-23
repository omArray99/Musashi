#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
int main()
{
  	// double arr[1100];
	double stop, start_p, stop_p;
	start_p=omp_get_wtime();
  	omp_set_num_threads(4);
  	//double min_val=9.0;
  	int i, n;
  	cout<<"Enter no. elements : ";
  	cin>>n;
    double a[n];
    for(int i= 0; i<n; i++)
  	{
  	a[i]=rand()%5000;
  	}
    double min_val=a[0];
    double min = a[0];
    double seq_start,seq_stop;
    seq_start = omp_get_wtime();
    for(int j = 0;j<n;j++){
        if(a[j]<min){
            min = a[j];
    }
}
    seq_stop = omp_get_wtime();
    cout<<"\nmin value = "<<min;
    cout<<"\nSequential Time = "<<seq_stop-seq_start<<endl;
    double para_start, para_stop;
	para_start=omp_get_wtime();
  	omp_set_num_threads(4);
	#pragma omp parallel for reduction(min : min_val)
  
	for( i=0;i<n; i++)
  	{
     	   //cout<<" thread id = "<< omp_get_thread_num() <<" and i = " << i; 
     		if(a[i] < min_val)
     		{
        		min_val = a[i];
     		}
  	}
	para_stop=omp_get_wtime();
  	cout<<"\nmin_val = "<< min_val;
	cout << "\n Parallel Estimated= " << para_stop-para_start;
}


