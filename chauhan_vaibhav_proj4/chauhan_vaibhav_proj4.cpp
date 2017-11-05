#include<iostream>
#include<queue>
#include<stack>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
using namespace std;

class Edge
{
	public:	
		int start;
		int end;
		int weight;	
};

void union3(int repx,int repy ,int Set[], int height[])
{
	if(height[repx] == height[repy])
	{
		height[repx]++;
		Set[repy] = repx;
	}
	else
	{
		if(height[repx]>height[repy])
		{
			Set[repy] = repx;
		}
		else
		{
			Set[repx] = repy;
		}
	}
}

int find3(int x, int Set[])
{	
	int root = x;
	
	while(root!=Set[root])
	{
		root = Set[root];
	}
	
	int node = x;
	
	while(node!=root)
	{
		int parent = Set[node];
		Set[node] = root;
		node = parent;
	}
	
	return root;
}

void kruskal(int n)
{
	int d[n+1][n+1],temp,i,j,k;
	
	int edges = 0;
	
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<i+1;j++)
		{
			if(i == j)
			{
				d[i][j] = 0;
			}
			else
			{
				temp = rand() % 10 + 1;
				
				d[i][j] = temp;
				d[j][i] = temp;
				edges++;
			}
		}
	}
	
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			cout<<d[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	Edge e[edges];	//All edge list
	
	int count = 0;
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<i+1;j++)
		{
			if(d[i][j] != 0)
			{
				Edge temp;
				temp.start = i;
				temp.end = j;
				temp.weight = d[i][j];		//Initializing edge weight
				
				e[count] = temp;
				count++;
			}
		}
	}
	
	Edge t;
	
	for(i=0;i<edges;i++)
	{
		for(j=i+1;j<edges;j++)
		{
			if(e[i].weight>e[j].weight)
			{
				t = e[i];
				e[i] = e[j];			//Sorting edges according to their weight
				e[j] = t;
			}
		}
	}
	
	stack <Edge> preset;
	
	for(i=edges-1;i>=0;i--)
	{
		preset.push(e[i]);			//Stack of edges
	}
	
	int Set[n+1],height[n+1] = {0};
	
	for(i=1;i<n+1;i++)
	{
		Set[i] = i;			//Set array
	}
	
	int ucomp,vcomp;
	
	stack <Edge> postset;
	for(i=0;i<edges;i++)
	{
		ucomp = find3(e[i].start,Set);
		vcomp = find3(e[i].end,Set);
		
		if(ucomp != vcomp)
		{
			postset.push(e[i]);			//Adding edge to final set
			union3(ucomp,vcomp,Set,height);
		}
	}
	
	while(!postset.empty())
	{
		cout<<postset.top().start<<" <----> "<<postset.top().end<<" "<<endl;	//Printing edges
		postset.pop();
	}
}

void prim(int n)
{
	int d[n][n],temp,i,j,k;
	
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
				
				d[i][j] = temp;
				d[j][i] = temp;
			}
		}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<d[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	int postset[n]; // Final set
	int weight[n];   // Weight array
	
	bool preset[n];  // Set with vertex left
	
	for (int i = 0; i < n; i++)
	{
		weight[i] = 10000;	// Initializing wights to large number
		preset[i] = false;	//Nothing is in the starting set
	}
	
	int first = 0; //First vertex
	
	weight[0] = 0;     // First Vertex weight initialization
	postset[0] = -1; // First vertex included in final set
	
	typedef pair<int, int> pair;
	priority_queue< pair, vector <pair> , greater<pair> > pq;
	
    pq.push(make_pair(0, first));
    weight[first] = 0;
 
	for (int temp = 0; temp < n-1; temp++)
	{
        int j = pq.top().second;	//Selecting Minimum weight vertex
        pq.pop();
		
		preset[j] = true;	//Vertex chosen
	
		for (int i = 0; i < n; i++)
		{
			if (d[j][i] && preset[i] == false && d[j][i] <  weight[i])
		    {
		  		postset[i]  = j;	//Vertex added to final set
				weight[i] = d[j][i];
				pq.push(make_pair(weight[i], i));	
		    }		     
		}
	}
	
    for (int i = 1; i < n; ++i)
    {
    	cout<<postset[i]+1<<" <---> "<<i+1<<endl;	//Print edges
	}
}

int main()
{
	srand (time(NULL));
	
	int n;
	
	n = rand() % 6 + 5;
	
	int choice;
	
	cout<<"Select 1 for Prim's Algorithm or 2 for Kruskal's Algorithm: ";
	cin>>choice;
	
	if(choice == 1)
	{
		prim(n);
	}
	else if(choice == 2)
	{
		kruskal(n);
	}
	else
	{
		cout<<"Wrong choice. Run program again!!!";
	}
	
	return 0;
}
