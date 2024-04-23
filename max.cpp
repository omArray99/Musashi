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
    double max_val=a[0];
    double max = a[0];
    double seq_start,seq_stop;
    seq_start = omp_get_wtime();
    for(int j = 0;j<n;j++){
        if(a[j]>max){
            max = a[j];
    }
}
    seq_stop = omp_get_wtime();
    cout<<"\nmin value = "<<max;
    cout<<"\nSequential Time = "<<seq_stop-seq_start<<endl;
    double para_start, para_stop;
	para_start=omp_get_wtime();
  	omp_set_num_threads(4);
	#pragma omp parallel for reduction(max : max_val)
  
	for( i=0;i<n; i++)
  	{
     	   //cout<<" thread id = "<< omp_get_thread_num() <<" and i = " << i; 
     		if(a[i] > max_val)
     		{
        		max_val = a[i];
     		}
  	}
	para_stop=omp_get_wtime();
  	cout<<"\nmin_val = "<< max_val;
	cout << "\n Parallel Estimated= " << para_stop-para_start;
}


