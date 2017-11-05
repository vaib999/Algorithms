#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

int C, profit, maxprofit = 0, num = 0, n,node = 0;
stack<int> items_backtrack;

int KWF2(int i,int w[],int p[],int weight,int profit)
{
	int bound = profit;
	int j;
	float x[n+1];
	float temp;
	
	for(j=i;j<=n;j++)
	{
		x[j] = 0;
	}

	while(weight<C && i<=n)
	{
		if(weight + w[i]<=C)
		{
			x[i] = 1;
			weight = weight + w[i];
			bound = bound + p[i];
		}
		else
		{
			x[i] = (C - weight);
			temp = p[i]/w[i];
			weight = C;
			bound = bound + temp*x[i];
		}
		i = i+1;
	}
	return bound;
}

bool promising(int i,int w[],int p[],int weight,int profit)
{
	if(weight>=C)
	{
		return false;
	}
	
	int bound = KWF2(i+1,w,p,weight,profit);
	
	cout<<endl;
	node++;
	cout<<" Node="<<node;
	cout<<" Profit="<<profit;
	cout<<" Weight="<<weight;
	cout<<" bound="<<bound;
	cout<<endl;
	
	return bound>maxprofit;
}

knapsack(int i,int profit,int weight,int bestset[],int include[],int w[],int p[])
{	
	if(weight<=C && profit>maxprofit)
	{
		maxprofit = profit;
		num = i;
		bestset = include;
	}
	
	if(promising(i,w,p,weight,profit))
	{	
		include[i+1] = 1;
		items_backtrack.push(i+1);
		knapsack(i+1,profit+p[i+1],weight+w[i+1],bestset,include,w,p);
		include[i+1] = 0;
		knapsack(i+1,profit,weight,bestset,include,w,p);
	}
}

int main()
{
	//Backtracking
	
	n = rand() % 8 + 4;
	cout<<"Number of items="<<n<<endl;
	
	int w[n+1],p[n+1],include[n+1],bestset[n+1];
	float d[n+1];
	
	int i;
	
	
	for(i=1;i<n+1;i++)
	{
		w[i] = rand() % 20 + 5;
		cout<<" weight"<<i<<"="<<w[i];
		p[i] = rand() % 30 + 10;
		cout<<" benefit"<<i<<"="<<p[i];
	}
	
	for(i=1;i<n+1;i++)
	{
		C = C + w[i];
	}
	
	C = (C*6)/10;
	cout<<"Maximum Weight = "<<C<<endl;
	
	typedef pair<float, int> pair;
	priority_queue< pair, vector <pair> > pq;
	
	for(i=1;i<n+1;i++)
	{
		pq.push(make_pair((float)p[i]/(float)w[i], i));
	}
	
	int w_new[n+1],p_new[n+1];
	
	for(i=1;i<n+1;i++)
	{
        int indx = pq.top().second;
        pq.pop();
        w_new[i] = w[indx];
        p_new[i] = p[indx];
	}

	knapsack(0,0,0,bestset,include,w_new,p_new);
	
	int finalweight = 0;
	while(!items_backtrack.empty())
	{
		int temp = items_backtrack.top();
		items_backtrack.pop();
		
		cout<<" weight="<<w_new[temp];
		finalweight = finalweight + w_new[temp];
		cout<<" benefit="<<p_new[temp];
		cout<<endl;
	}
	
	cout<<endl;
	cout<<"maxprofit="<<maxprofit<<endl;
	
	//Backtracking
	return 0;
}
/*
16
4
2
40
5
30
10
50
5
10
*/
/*
10
6
4
6
2
4
3
5
1
3
6
9
4
7
*/
