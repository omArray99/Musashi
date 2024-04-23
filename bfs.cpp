#include<iostream>
#include<stdlib.h>
#include<queue>
#include<omp.h>
double start,stop,start_p,stop_p;
using namespace std;

class node
{
	public:
    		node *left, *right;
    		int data;
};    

class Breadthfs
{
	public: 
 	node *insert(node *, int);
 	void bfs(node *);
};

node *insert(node *root, int data)
{
    	if(!root)
    	{   	 
   		root=new node;
   	 	root->left=NULL;
   	 	root->right=NULL;
   	 	root->data=data;
   	 	return root;
    	}
    	queue<node *> q;
    	q.push(root);
    	while(!q.empty())
    	{
   		node *temp=q.front();
   	 	q.pop(); 
   	 	if(temp->left==NULL)
   	 	{		 
   		 	temp->left=new node;
   		 	temp->left->left=NULL;
   		 	temp->left->right=NULL;
   		 	temp->left->data=data;    
   		 	return root;
   	 	}
   	 	else
   	 	{
   	 		q.push(temp->left);
   	 	}
   	 	if(temp->right==NULL)
   	 	{	 		 
   			temp->right=new node;
   		 	temp->right->left=NULL;
   		 	temp->right->right=NULL;
   		 	temp->right->data=data;    
   		 	return root;
   	 	}
   	 	else
   	 	{
   	 		q.push(temp->right);
   	 	}
    	}   
    	return 0;
}

void bfs(node *head)
{
	start_p=omp_get_wtime();
   	queue<node*> q;
   	q.push(head);   	 
   	int qSize;
   	while (!q.empty())
   	{
   		qSize = q.size();
   		#pragma omp parallel for
            	//creates parallel threads
   		for (int i = 0; i < qSize; i++)
   		{
   			node* currNode;
   			#pragma omp critical
   			{
   				currNode = q.front();
   			   	q.pop();
   			   	cout<<"\t"<<currNode->data;
   			}// prints parent node
   			#pragma omp critical
   			{
   			 	if(currNode->left)// push parent's left node in queue
   					q.push(currNode->left);
   			 	if(currNode->right)
   				 	q.push(currNode->right);
   			 }// push parent's right node in queue   	 
   		}
   	}
	stop_p=omp_get_wtime();	
}

int main()
{
    	node *root=NULL;
    	int data,n=5,i;
   	int ans;
    	int a[n];
	for( i= 0; i<n; i++)
	{
	   	a[i]=rand()%1500;
	   	root=insert(root,a[i]);
	}
    	bfs(root);
    	cout << "\n Time Parallel  = " << stop_p-start_p;
    	return 0;
}
