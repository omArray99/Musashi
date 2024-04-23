#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
int main()
{

	/*double stop, start_p, stop_p;
	start_p=omp_get_wtime();
  	omp_set_num_threads(4);*/
  	int n;
  	cout<<"Enter no. elements : ";
  	cin>>n;
    double a[n];
    for(int i= 0; i<n; i++)
  	{
  	a[i]=rand()%1000;
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
  	omp_set_num_threads(6);
	#pragma omp parallel for reduction(min : min_val)
 
	for(int i=0;i<n; i++)
  	{
     		if(a[i] < min_val)
     		{
        		min_val = a[i];
     		}
  	}
	para_stop=omp_get_wtime();
  	cout<<"\nmin_val = "<< min_val;
	cout << "\n Parallel Estimated= " << para_stop-para_start;
}


