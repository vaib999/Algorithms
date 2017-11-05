#include<iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


void exchangeSort(int size,int * arr)
{
	int i,j,temp;
	
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(arr[i]>arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];    //swap
				arr[j] = temp;
			}
		}
	}
	
	for(i=0;i<size;i++)
	{
		cout<<arr[i]<<" ";			//Final Sorted Array
	}
}

//Exchange Sort Graph
void exchangeSortGraph(int size,int * arr)
{
	int i,j,k,l,temp;
	
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(arr[i]>arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];		//Swap
				arr[j] = temp;
			}
			
			for(k=0;k<size;k++)
			{
				for(l=0;l<arr[k];l++)
				{
					cout<<"*";	
				}
				cout<<endl;
			}
			cout<<endl;
		}
	}
}

void insertionSort(int ar_size, int *  ar) 
{
	int i,j,k,temp;
	
	for(i=1;i<=ar_size-1;i++)
	{
		int value = ar[i];
		int hole = i;
		
		while(hole>0 && ar[hole-1]>value)
		{
			ar[hole] = ar[hole-1];
			hole = hole-1;						//Shifting the array to right so that lowest value can be placed
		}										//where hole is created.
		ar[hole] = value;
	}
	for(k=0;k<ar_size;k++)
	{
		cout<<ar[k]<<" ";
	}
}

//Insertion Sort Graph
void insertionSortGraph(int ar_size, int *  ar) 
{
	int i,j,k,l,temp;
	
	for(i=1;i<=ar_size-1;i++)
	{
		int value = ar[i];
		int hole = i;
		
		while(hole>0 && ar[hole-1]>value)
		{
			ar[hole] = ar[hole-1];
			hole = hole-1;
		}
		ar[hole] = value;
		
		for(k=0;k<ar_size;k++)
		{
			for(l=0;l<ar[k];l++)
			{
				cout<<"*";	
			}
			cout<<endl;
		}
		cout<<endl;
	}
}

void merge(int left[],int right[],int a[],int left_size,int right_size)
{
	int i,j,k;
	
	i = 0,j = 0, k = 0;
	
	while(i<left_size && j<right_size)
	{
		if(left[i]<=right[j])
		{
			a[k] = left[i];					//Copying left sorted array to original array
			i = i+1;
		}
		else
		{
			a[k] = right[j];				//Copying right sorted array to original array
			j = j+1;
		}
		k = k+1;
	}
	
	while(i<left_size)
	{
		a[k] = left[i];
		k++;								//Copying the remaining left array to original array
		i++;
	}

	while(j<right_size)
	{
		a[k] = right[j];					//Copying the remaining right array to original array
		k++;
		j++;
	}
}

void mergeSort(int array[],int length)
{	
	int mid,i;
	
	if(length < 2)						//Base case
	{
		return ;
	}
	
	mid = length/2;
	
	int left[mid],right[length-mid];		//Two temporary arrays
	
	for(i=0;i<mid;i++)
	{
		left[i] = array[i];					//Copying left half to left array
	}
	
	for(i=mid;i<length;i++)
	{
		right[i-mid] = array[i];			//Copying right half to right array
	}
	
	mergeSort(left,mid);					//Sort left array
	mergeSort(right,length-mid);			//Sort right array
	merge(left,right,array,mid,length-mid); //Merging the two sorted array
}

void mergeSortGraph(int array[],int length)
{	
	int mid,i;
	
	if(length < 2)
	{
		return ;
	}
	
	mid = length/2;
	
	int left[mid],right[length-mid];
	
	for(i=0;i<mid;i++)
	{
		left[i] = array[i];
	}
	
	for(i=mid;i<length;i++)
	{
		right[i-mid] = array[i];
	}
	
	mergeSortGraph(left,mid);
	mergeSortGraph(right,length-mid);
	merge(left,right,array,mid,length-mid);
	
	for(i=0;i<length;i++)
	{
		for(int j=0;j<array[i];j++)
		{
			cout<<"*";			
		}
		cout<<endl;
	}
	cout<<endl;
}

int partition(int *a,int start,int end)
{
	srand (time(NULL));
	int diff = end-start;
	int iSecret = rand()%diff + start;			//Random number generated for choosing pivot
	
	int pivot = a[iSecret];						//Pivot item chosen
	int pIndex = start;
	int i,temp;
	
	temp = a[end];
	a[end] = a[iSecret];						//Exchanging end item with pivot item
	a[iSecret] = temp;
	
	i=start;
	while(i<end)
	{
		if(a[i]<pivot)
		{
			temp = a[i];
			a[i] = a[pIndex];					//If an item is smaller than pivot then exchange it with pivot index 
			a[pIndex] = temp;					//and increment pivot index
			pIndex++;
		}
		i++;
	}
	temp = a[end];
	a[end] = a[pIndex];							//Swap end elemnet that is pivot with Pivot index item.
	a[pIndex] = temp;
		
	return pIndex;
}

void quickSort(int *a,int start,int end,int c_size)
{
	if(start<end)
	{
		int i;
		
		int pIndex = partition(a,start,end);			//Partition Index returned by partition function
		
		quickSort(a,start,pIndex-1,c_size);				//Quick sort: starting item to partition index - 1
		quickSort(a,pIndex+1,end,c_size);				//Quick sort: partition index + 1 to end
	}
}

void quickSortGraph(int *a,int start,int end,int c_size)
{
	if(start<end)
	{
		int i,j;
		
		int pIndex = partition(a,start,end);
		
		for(i=0;i<c_size;i++)
		{
			for(j=0;j<a[i];j++)
			{
				cout<<"*";	
			}
			cout<<endl;
		}
		cout<<endl;		
		
		quickSort(a,start,pIndex-1,c_size);
		quickSort(a,pIndex+1,end,c_size);	
	}
}

int main()
{
	int sort_num,data_num;
	cout<<"Enter 1 for exchange sort, 2 for insertion sort, 3 for merge sort, 4 for quick sort"<<endl;
	cin>>sort_num;
	cout<<"Enter the number of data to be sorted from 1 to 1000 included"<<endl;
	cin>>data_num;
	
	int arr[data_num]={0};						//Array declaration
	
	if(data_num>=1 && data_num<=1000)
	{
		int iSecret,i;
		/* initialize random seed: */
		srand (time(NULL));
		
		/* generate secret number between 1 and 10: */
		
		if(data_num>20)
		{
			for(i=0;i<data_num;i++)
			{
				iSecret = rand();
				arr[i] = iSecret;				//Random number is generated and assigned to array index
				cout<<iSecret<<" ";
			}
			cout<<endl;
			
			if(sort_num == 1)
			{
				exchangeSort(data_num,arr);
			}
			else if(sort_num == 2)
			{
				insertionSort(data_num, arr);
			}
			else if(sort_num == 3)
			{
				mergeSort(arr,data_num);
				for(int i=0;i<data_num;i++)
				{
					cout<<arr[i]<<" ";
				}
			}
			else if(sort_num == 4)
			{
				quickSort(arr,0,data_num-1,data_num);
				for(int i=0;i<data_num;i++)
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
			cout<<endl;
			
			if(sort_num == 1)
			{
				exchangeSortGraph(data_num,arr);
			}
			else if(sort_num == 2)
			{
				insertionSortGraph(data_num, arr);
			}
			else if(sort_num == 3)
			{
				mergeSortGraph(arr,data_num);
			}
			else if(sort_num == 4)
			{
				quickSortGraph(arr,0,data_num-1,data_num);
				for(int i=0;i<data_num;i++)
				{
					for(int j=0;j<arr[i];j++)
					{
						cout<<"*";
					}
					cout<<endl;
				}
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
