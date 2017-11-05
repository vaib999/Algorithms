#include<iostream>
#include<stack>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

brute_knapsack(int W,int n,int weight[],int benefit[],int index[])
{
	int global_benefit = 0,global_weight = 0,local_weight,local_benefit,i,j,k,taken;
	
	int size = pow(2, n);
	stack<int> global_items;
	for(i = 0; i < size; i++)
	{
		local_weight = 0;
		local_benefit = 0;
		
		stack<int> items;
		
		for(j = 0; j < n; j++)
		{
			if(i & (1<<j))
			{
				k = index[j];
				items.push(k);
				local_weight = 	local_weight + weight[k];
				local_benefit = local_benefit + benefit[k];
			}
			
			if(local_weight>W)
			{
				break;
			}
		}

		if(local_benefit>global_benefit && local_weight<=W)
		{
			global_benefit = local_benefit;
			global_weight = local_weight;
			global_items = items;
		}

	}
	
	cout<<"Total Benefit="<<global_benefit<<endl;
	cout<<"Total weight="<<global_weight<<endl;
	
	while(!global_items.empty())
	{
		int temp = global_items.top();
		global_items.pop();
		
		cout<<" weight="<<weight[temp];
		cout<<" benefit="<<benefit[temp];
		cout<<endl;
	}
}
int main()
{
	//Brute Force
	
	int W,n,i,j;
	
	n = rand() % 8 + 4;
	cout<<"Number of items="<<n<<endl;
	
	int weight[n],benefit[n],index[n];
	
	for(i=0;i<n;i++)
	{
		weight[i] = rand() % 20 + 5;
		cout<<" weight"<<i<<"="<<weight[i];
		benefit[i] = rand() % 30 + 10;
		cout<<" benefit"<<i<<"="<<benefit[i];
		index[i] = i;
	}

	for(i=0;i<n;i++)
	{
		W = W + weight[i];
	}
	
	W = (W*6)/10;
	cout<<"Maximum Weight = "<<W<<endl;
    
    brute_knapsack(W,n,weight,benefit,index);
    
    //Brute Force
	return 0;
}
