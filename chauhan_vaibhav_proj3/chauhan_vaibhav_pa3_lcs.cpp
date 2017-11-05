#include<iostream>
#include<string>
using namespace std;

void lcs_length(string x,string y)
{
	int m,n,i,j;
	
	m = x.length();
	n = y.length();
	
	int c[m+1][n+1];
	char b[m+1][n+1];
	
	for(i=0;i<m+1;i++)
	{
		for(j=0;j<n+1;j++)
		{
			c[i][j] = 0;	//Initializing dp matrix
		}
	}
	
	for(i=0;i<m+1;i++)
	{
		c[i][0] = 0;		//Initializing 1st row with 0 values
	}
	
	for(j=0;j<n+1;j++)
	{
		c[0][j] = 0;		//Initializing 1st column with 0 values
	}
	
	for(i=1;i<m+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(x[i-1] == y[j-1])	//If character in both string are equal
			{
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = 'd';
			}
			else
			{
				if(c[i-1][j] >= c[i][j-1])	//If upper cell value is bigger
				{
					c[i][j] = c[i-1][j];
					b[i][j] = 'u';
				}
				else				//If left cell value is bigger
				{
					c[i][j] = c[i][j-1];
					b[i][j] = 'l';
				}
			}
		}
	}
	
	i=m;
	j=n;
	
	string temp;
	
	while(i!=0 && j!=0)
	{
		if(b[i][j] == 'd')
		{
			temp = temp + x[i-1];		//Temporary string container to print LCS
			i=i-1;
			j=j-1;
		}
		else if(b[i][j] == 'u')
		{
			i=i-1;
		}
		else if(b[i][j] == 'l')
		{
			j=j-1;
		}
	}
	
	//Print LCS
	for(i=temp.length()-1;i>=0;i--)
	{
		cout<<temp[i];
	}
	cout<<endl;
	
	return;
}

int main(int argc, char *argv[])
{
	string str1 = argv[1];
	string str2 = argv[2];
	
	lcs_length(str1,str2);
	
	return 0;
}
