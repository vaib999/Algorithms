#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

stack<int> items_dynamic;

vector<vector<int> > entries(int W,int n,vector<vector<int> > B,int w[])
{
	if(n<=1 || W-w[n-1]<=0)
	{
		return B;
	}

	B[n][W] = 1;
	B[n-1][W] = 1;
	B[n-1][W-w[n-1]] = 1;
	
	B = entries(W,n-1,B,w);
	B = entries(W-w[n-1],n-1,B,w);
	
	return B;	
}

vector<vector<int> > dynamic_knapsack(int W,int item,int weight[],int benefit[],vector<vector<int> > table)
{
	int i,j,k;
	
	for(i=0;i<=W;i++)
	{
		table[0][i] = 0;
	}
	
	for(k=1;k<=item;k++)
	{
		table[k][0] = 0;
		
		for(j=1;j<=W;j++)
		{
			if(table[k][j] == 1)
			{
				if(weight[k-1]<=j && (table[k-1][j-weight[k-1]] + benefit[k-1] > table[k-1][j]))
				{
					table[k][j] = table[k-1][j-weight[k-1]] + benefit[k-1];
				}
				else
				{
					table[k][j] = table[k-1][j];
				}
			}
		}
	}
	return table;
}

int main()
{
	
	//Dynamic Programming
	int W,n,i,j;
	
	n = rand() % 8 + 4;
	cout<<"Number of items="<<n<<endl;
    
    int weight[n],benefit[n];

	for(i=0;i<n;i++)
	{
		weight[i] = rand() % 20 + 5;
		cout<<" weight"<<i<<"="<<weight[i];
		benefit[i] = rand() % 30 + 10;
		cout<<" benefit"<<i<<"="<<benefit[i];
	}
	

	for(i=0;i<n;i++)
	{
		W = W + weight[i];
	}
	
	W = (W*6)/10;
	cout<<endl;
	cout<<"Maximum Weight = "<<W<<endl;
    
	vector<int> row(W+1);
    vector<vector<int> > B(n+1,row);
    
    vector<vector<int> > result(n+1,row);
    
	typedef pair<float, int> pair;
	priority_queue< pair, vector <pair> > pq;
	
	for(i=0;i<n;i++)
	{
		pq.push(make_pair((float)benefit[i]/(float)weight[i], i));
	}
	
	int w_new[n+1],p_new[n+1];
	
	for(i=0;i<n;i++)
	{
        int indx = pq.top().second;
        pq.pop();
        w_new[i] = weight[indx];
        p_new[i] = benefit[indx];
	}
    
    for(i=0;i<n+1;i++)
    {
    	for(j=0;j<W+1;j++)
    	{
    		B[i][j] = 0;
		}
	}
    
	result = entries(W,n,B,w_new);
	
	result = dynamic_knapsack(W,n,w_new,p_new,result);
	
    for(i=0;i<n+1;i++)
    {
    	for(j=0;j<W+1;j++)
    	{
    		cout<<result[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<"Maximum benefit = "<<result[i-1][j-1]<<endl;
	
	//Dynamic Programming
	
	return 0;
}
