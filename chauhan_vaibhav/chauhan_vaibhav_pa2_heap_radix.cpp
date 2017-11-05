#include<iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void heapify(int A[],int root,int size)
{
	int left,right,largest,temp;
	
	left = 2*root;						//Left child
	right = 2*root + 1;					//Right child
	
	if(left<=size && A[left]>A[root])
	{
		largest = left;
	}
	else
	{
		largest = root;
	}
	if(right<=size && A[right]>A[largest])
	{
		largest = right;
	}
	
	if(largest != root)
	{
		temp = A[root];
		A[root] = A[largest];
		A[largest] = temp;
		
		heapify(A,largest,size);
	}
}

//Building heap
void build_heap(int A[],int size)
{
	int i;
	
	for(i=size/2;i>=1;i--)
	{
		heapify(A,i,size);
	}
}

//Heap for numbers less than 20
void heap_graph(int A[], int size)
{
	build_heap(A,size);
	
	int i,temp;
	
	for(i=size;i>1;i--)
	{
		temp = A[1];
		A[1] = A[i];
		A[i] = temp;
		
		int j,k;
		for(k=1;k<size+1;k++)
		{
			for(j=0;j<A[k];j++)
			{
				cout<<"*";							//Various stages of numbers to be sorted shown by stars(histogram)
			}
			cout<<endl;
		}
		cout<<endl<<endl;
		
		heapify(A,1,i-1);
	}
}

void heap(int A[], int size)
{
	build_heap(A,size);			//Initial build heap
	
	int i,temp;
	
	for(i=size;i>1;i--)
	{
		temp = A[1];
		A[1] = A[i];			//Swap smallest number with largest
		A[i] = temp;
		
		heapify(A,1,i-1);		//Heapify for the remaining tree 
	}
}

//Radix sort for numbers less than 20 
void radix_graph(int A[], int size)
{
	int digits = 3;

	int B[size],C[10]={0};
	
	int e=1,mod=10,i;
	
	for(i=0;i<size;i++)
	{
		B[i] = A[i];
	}
	
	while(digits--)
	{
		for(i=0;i<10;i++)
		{
			C[i]=0;
		}
		
		for(i=0;i<size;i++)
		{
			A[i] = B[i];
		}
		
		for(i=0;i<size;i++)
		{
			C[(A[i]%mod)/e]++;
		}
		
		for(i=1;i<10;i++)
		{
			C[i]+=C[i-1];
		}
		
		for(i=size-1;i>=0;i--)
		{
			C[(A[i]%mod)/e]--;
			B[C[(A[i]%mod)/e]] = A[i];
		}
		
		int j;
		for(i=0;i<size;i++)
		{
			for(j=0;j<B[i];j++)
			{
				cout<<"*";							//Various stages of numbers to be sorted shown by stars(histogram)
			}
			cout<<endl;
		}
		cout<<endl<<endl;
		
		e*=10,mod*=10;
	}
}

//Radix sort
void radix(int A[], int size)
{
	int digits = 4;

	int B[size],C[10]={0};
	
	int e=1,mod=10,i;
	
	for(i=0;i<size;i++)
	{
		B[i] = A[i];
	}
	
	while(digits--)
	{
		for(i=0;i<10;i++)
		{
			C[i]=0;
		}
		
		for(i=0;i<size;i++)
		{
			A[i] = B[i];
		}
		
		for(i=0;i<size;i++)
		{
			C[(A[i]%mod)/e]++;  
		}
		
		for(i=1;i<10;i++)
		{
			C[i]+=C[i-1];		//Offset calculation
		}
		
		for(i=size-1;i>=0;i--)
		{
			C[(A[i]%mod)/e]--;
			B[C[(A[i]%mod)/e]] = A[i];		//Stable sorting
		}
		
		e*=10,mod*=10;
	}
}


int main()
{
	int sort_num,data_num;
	cout<<"Enter 1 for heap sort, 2 for radix sort"<<endl;
	cin>>sort_num;
	cout<<"Enter the number of data to be sorted from 1 to 1000 included"<<endl;
	cin>>data_num;
	
	int arr[data_num]={0};						//Array declaration
	int arrr[data_num+1]={0};
	
	if(data_num>=1 && data_num<=1000)
	{
		int iSecret,i;
		/* initialize random seed: */
		srand (time(NULL));
		
		/* generate secret number between 1 and 10: */
		
		if(data_num>20)
		{	
			if(sort_num == 1)
			{
				for(i=1;i<data_num+1;i++)
				{
					iSecret = rand();
					arrr[i] = iSecret;				//Random number is generated and assigned to array index
					cout<<iSecret<<" ";
				}
				cout<<endl;
				
				heap(arrr,data_num);
				
				for(i=1;i<data_num+1;i++)
				{
					cout<<arrr[i]<<" ";
				}				
			}
			else if(sort_num == 2)
			{
				for(i=0;i<data_num;i++)
				{
					iSecret = rand()%1000;
					arr[i] = iSecret;				//Random number is generated and assigned to array index
					cout<<iSecret<<" ";
				}
				cout<<endl;
				
				radix(arr,data_num);
				
				for(i=0;i<data_num;i++)
				{
					cout<<arr[i]<<" ";
				}		
			}
			else
			{
				cout<<"Please choose 1 for exchange sort, 2 for insertion sort, 3 for merge sort, 4 for quick sort"<<endl;
			}
		}
		else
		{	
			if(sort_num == 1)
			{
				for(i=1;i<data_num+1;i++)
				{
					iSecret = rand() % 15;
					arrr[i] = iSecret;						//Random number assigned to array
					int j;
					
					for(j=0;j<iSecret;j++)
					{
						cout<<"*";							//Inital graph of numbers to be sorted
					}
					cout<<endl;
				}
				cout<<endl<<endl;
				heap_graph(arrr,data_num);
			}
			else if(sort_num == 2)
			{
				for(i=0;i<data_num;i++)
				{
					iSecret = rand() % 15;
					arr[i] = iSecret;						//Random number assigned to array
					int j;
					
					for(j=0;j<iSecret;j++)
					{
						cout<<"*";							//Inital graph of numbers to be sorted
					}
					cout<<endl;
				}
				cout<<endl<<endl;
				radix_graph(arr,data_num);
			}
			else
			{
				cout<<"Please choose 1 for exchange sort, 2 for insertion sort, 3 for merge sort, 4 for quick sort"<<endl;
			}
		}
	}
	else
	{
		cout<<"Input data should be in between 1 to 1000 included."<<endl;
	}
	return 0;
}

