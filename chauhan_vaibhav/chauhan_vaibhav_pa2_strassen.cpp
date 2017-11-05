#include<iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<vector>
#include <limits.h>
#include <math.h> 
using namespace std;

//Normal matrix multiplication for base case
vector<vector<int> > mult(vector<vector<int> > A,vector<vector<int> > B)
{
	vector<int> row(A.size());
    vector<vector<int> > mul(A.size(),row);
    int i,j,k,sum = 0;
    
	for(i=0;i<A.size();i++)
	{
		for(j=0;j<B.size();j++)
		{
			for(k=0;k<A.size();k++)
			{
				sum = sum + A[i][k]*B[k][j];
			}
			mul[i][j] = sum;
			sum = 0;
		} 
	}
	return mul;
}

//Adding two vectors
vector<vector<int> > add(vector<vector<int> > A,vector<vector<int> > B, int size)
{
	vector<int> row(size);
    vector<vector<int> > temp(size,row);
    int i,j;
    
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			temp[i][j] = A[i][j] + B[i][j];
		}
	}
	return temp;
}

//Subtracting two vectors
vector<vector<int> > sub(vector<vector<int> > A,vector<vector<int> > B, int size)
{
	vector<int> row(size);
    vector<vector<int> > temp(size,row);
    int i,j;
    
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			temp[i][j] = A[i][j] - B[i][j];
		}
	}
	return temp;
}

//Main strassen algorithm
vector<vector<int> > strassen(int n,vector<vector<int> > A,vector<vector<int> > B,vector<vector<int> > C)
{
	if(n<=128)						//Base Case
	{
		C = mult(A,B);
		
		return C;
	}
	
	vector<int> row(n/2);
	//Two matrix divided into 8 matrix
    vector<vector<int> > a_11(n/2,row),a_12(n/2,row),a_21(n/2,row),a_22(n/2,row),b_11(n/2,row),b_12(n/2,row),b_21(n/2,row),b_22(n/2,row);
	vector<vector<int> > m1(n/2,row),m2(n/2,row),m3(n/2,row),m4(n/2,row),m5(n/2,row),m6(n/2,row),m7(n/2,row);
	int i,j,k,l;
	
	//1st sub matrix of 1st matrix
	for(i=0,k=0;i<n/2;k++,i++)
	{
		for(j=0,l=0;j<n/2;l++,j++)
		{
			a_11[k][l] = A[i][j]; 
		}
	}
	
	//2nd sub matrix of 1st matrix
	for(i=n/2,k=0;i<n;k++,i++)
	{
		for(j=0,l=0;j<n/2;l++,j++)
		{
			a_12[k][l] = A[i][j];
		}
	}
	
	//3rd sub matrix of 1st matrix
	for(i=0,k=0;i<n/2;k++,i++)
	{
		for(j=n/2,l=0;j<n;l++,j++)
		{
			a_21[k][l] = A[i][j]; 
		}
	}
	
	//4th sub matrix of 1st matrix
	for(i=n/2,k=0;i<n;k++,i++)
	{
		for(j=n/2,l=0;j<n;l++,j++)
		{
			a_22[k][l] = A[i][j]; 
		}
	}
	
	//1st sub matrix of 2nd matrix
	for(i=0,k=0;i<n/2;k++,i++)
	{
		for(j=0,l=0;j<n/2;l++,j++)
		{
			b_11[k][l] = B[i][j]; 
		}
	}
	
	//2nd sub matrix of 2nd matrix
	for(i=n/2,k=0;i<n;k++,i++)
	{
		for(j=0,l=0;j<n/2;l++,j++)
		{
			b_12[k][l] = B[i][j]; 
		}
	}
	
	//3rd sub matrix of 2nd matrix
	for(i=0,k=0;i<n/2;k++,i++)
	{
		for(j=n/2,l=0;j<n;l++,j++)
		{
			b_21[k][l] = B[i][j]; 
		}
	}
	
	//4th sub matrix of 2nd matrix
	for(i=n/2,k=0;i<n;k++,i++)
	{
		for(j=n/2,l=0;j<n;l++,j++)
		{
			b_22[k][l] = B[i][j]; 
		}
	}
	
	m1 = strassen(n/2,add(a_11,a_22,n/2),add(b_11,b_22,n/2),m1);

	m2 = strassen(n/2,add(a_21,a_22,n/2),b_11,m2);

	m3 = strassen(n/2,a_11,sub(b_12,b_22,n/2),m3);

	m4 = strassen(n/2,a_22,sub(b_21,b_11,n/2),m4);

	m5 = strassen(n/2,add(a_11,a_12,n/2),b_22,m5);

	m6 = strassen(n/2,sub(a_21,a_11,n/2),add(b_11,b_12,n/2),m6);

	m7 = strassen(n/2,sub(a_12,a_22,n/2),add(b_21,b_22,n/2),m7);
	
    vector<vector<int> > c_00(n/2,row),c_01(n/2,row),c_10(n/2,row),c_11(n/2,row);
    
	c_00 = add(sub(add(m1,m4,n/2),m5,n/2),m7,n/2);
	c_01 = add(m3,m5,n/2);
	c_10 = add(m2,m4,n/2);
	c_11 = add(sub(add(m1,m3,n/2),m2,n/2),m6,n/2);
	
	//Putting together result in third matrix
	for(i=0,k=0;i<n/2;i++,k++)
	{
		for(j=0,l=0;j<n/2;j++,l++)
		{
			C[k][l] = c_00[i][j]; 
		}
	}
	
	for(i=0,k=n/2;i<n/2;k++,i++)
	{
		for(j=0,l=0;j<n/2;l++,j++)
		{
			C[k][l] = c_01[i][j];  
		}
	}

	for(i=0,k=0;i<n/2;k++,i++)
	{
		for(j=0,l=n/2;j<n/2;l++,j++)
		{
			C[k][l] = c_10[i][j]; 
		}
	}
	
	for(i=0,k=n/2;i<n/2;k++,i++)
	{
		for(j=0,l=n/2;j<n/2;l++,j++)
		{
			C[k][l] = c_11[i][j];  
		}
	}

	return C;
}

int main()
{
	int n,i,j,k,sum = 0;

	int iSecret;

	srand (time(NULL));
	
	cin>>n;

    vector<int> row(n);
    vector<vector<int> > matrix1(n,row),matrix2(n,row),pout(n,row);
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			iSecret = rand() % int(sqrt(INT_MAX/n));
			matrix1[i][j] = iSecret;
			iSecret = rand() % int(sqrt(INT_MAX/n));
			matrix2[i][j] = iSecret;
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<matrix2[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<matrix1[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	pout = strassen(n,matrix1,matrix2,matrix2);
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<pout[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}


