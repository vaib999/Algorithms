#include<iostream>
#include <time.h>
#include <stdlib.h>
#include<vector>
using namespace std;

//Function to print intermediate nodes for shortest paths
void path(vector<vector<int> > arr,int a,int b)
{
	if(arr[a][b] != 0)
	{
		path(arr,a,arr[a][b]);		
		cout<<"v"<<arr[a][b]<<" ";	//Print Intermediate Node
		path(arr,arr[a][b],b);
		
		return;
	}
	else
	{
		return;		//Return if no shorter path is there
	}
}

//Floyd Algorithm
void floyd(int n)
{
	int d[n][n],temp,i,j,k;
	
	vector<int> row(n);
	vector<vector<int> > p(n,row);
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<i+1;j++)
		{
			if(i == j)
			{
				d[i][j] = 0;
			}
			else
			{
				temp = rand() % 10 + 1;
				
				d[i][j] = temp;		//Assigning random weights between nodes
				d[j][i] = temp;
			}
		}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			p[i][j] = 0;	//Initializing matrix to store intermediate nodes
		}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<d[i][j]<<" "; //Print random matrix that is generated
		}
		cout<<endl;
	}
	cout<<endl;
	
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(d[i][j]>d[i][k] + d[k][j])	//If there is some other intermediate node then update distance and node name
				{
					d[i][j] = d[i][k] + d[k][j];	
					p[i][j] = k;
				}
			}
		}
	}
	
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i != j)
			{
				cout<<endl;
				cout<<"v"<<i<<" ";
				path(p,i,j);	//Function call to print intermediate node 
				cout<<"v"<<j<<" ";
				cout<<d[i][j];
				cout<<endl;
			}
		}
		cout<<endl;
	}
}

int main()
{
	srand (time(NULL));
	
	int n;
	
	n = rand() % 6 + 5;
	
	floyd(n);
	
	return 0;
}
