#include<iostream>
#include <stdlib.h>  
#include <time.h> 
#include<vector>      
using namespace std;


//Function to add two vectors
vector<int> add(vector<int> A,vector<int> B)
{
	int A_len,B_len,new_size,carry,i,j,k,temp,num,zeros;
	
	A_len = A.size();
	B_len = B.size();
	
	if(A_len>B_len)				//If vector A is greater than vector B
	{
		new_size = A_len+1;
		
		zeros = A_len - B_len;
		
		vector<int> A_zero(A_len),B_zero(A_len);
		
		for(i=0;i<zeros;i++)
		{
			B_zero[i] = 0;
		}
		for(i=zeros;i<A_len;i++)
		{
			B_zero[i] = B[i-zeros];
		} 
		
		for(i=0;i<A.size();i++)
		{
			A_zero[i]  = A[i];
		}
		
		vector<int> arr(new_size,0); //New vector in which add result will be copied
		
		carry = 0;
		i=new_size-1,j=A.size()-1,k=A.size()-1;
		
		while(i>=1)
		{
			temp = A_zero[j] + B_zero[k] + carry;
			
			arr[i] = temp%10;
			carry = temp/10;
			
			i--,j--,k--;
		}
		arr[0] = carry;
		
		if(arr[0] == 0)
		{
			vector<int> new_arr(arr.size()-1);
			
			for(i=0;i<new_arr.size();i++)
			{
				new_arr[i] = arr[i+1];
			}
			
			return new_arr;
		}
		return arr;
	}
	else if(B_len>A_len)				//If vector B is greater than vector A
	{
		new_size = B_len+1;
		
		zeros = B_len - A_len;
		
		vector<int> B_zero(B_len),A_zero(B_len);
		
		for(i=0;i<zeros;i++)
		{
			A_zero[i] = 0;
		}
		for(i=zeros;i<B_len;i++)
		{
			A_zero[i] = A[i-zeros];
		} 
		
		for(i=0;i<B.size();i++)
		{
			B_zero[i]  = B[i];
		}
		
		vector<int> arr(new_size,0);
		
		carry = 0;
		i=new_size-1,j=B.size()-1,k=B.size()-1;
		
		while(i>=1)
		{
			temp = A_zero[j] + B_zero[k] + carry;
			
			arr[i] = temp%10;
			carry = temp/10;
			
			i--,j--,k--;
		}
		arr[0] = carry;
		
		if(arr[0] == 0)
		{
			vector<int> new_arr(arr.size()-1);
			
			for(i=0;i<new_arr.size();i++)
			{
				new_arr[i] = arr[i+1];
			}
			
			return new_arr;
		}
		return arr;
	}
	else						//If vector A and B are equal
	{
		vector<int> B_zero(B_len),A_zero(A_len);
		
		new_size = A.size()+1;
		
		for(i=0;i<A.size();i++)
		{
			A_zero[i] = A[i];
		}
		
		for(i=0;i<B.size();i++)
		{
			B_zero[i] = B[i];
		}
		
		vector<int> arr(new_size,0);
		
		carry = 0;
		i=new_size-1,j=A.size()-1,k=B.size()-1;
		
		while(i>0)
		{
			temp = A_zero[j] + B_zero[k] + carry;
			
			arr[i] = temp%10;
			carry = temp/10;
			
			i--,j--,k--;
		}
		arr[0] = carry;
		
		if(arr[0] == 0)
		{
			vector<int> new_arr(arr.size()-1);
			
			for(i=0;i<new_arr.size();i++)
			{
				new_arr[i] = arr[i+1];
			}
			return new_arr;
		}
		return arr;
	}
}

//Function to add zeros
vector<int> addzero(vector<int> A, int zeros)
{
	int size = A.size(),i;
	
	vector<int> temp(size + zeros);				//Initialization of Vector for adding zeros
	
	for(i=0;i<size;i++)
	{
		temp[i] = A[i];
	}
	for(int i=size;i<size+zeros;i++)
	{
		temp[i] = 0;							//Adding zeros
	}

	return temp;
}

//Simple multiplication
vector<int> mult(vector<int> A,vector<int> B)
{
	int e,num1,num2,i,digit,mod;
	
	e = 1;
	num1 = 0;
	for(i=A.size()-1;i>=0;i--)
	{
		num1 = num1 + e*A[i];			//Converting 1st vector to integer
		
		e = e*10;
	}
	
	e = 1;
	num2 = 0;
	for(i=B.size()-1;i>=0;i--)
	{
		num2 = num2 + e*B[i];			//Converting 2nd vector to integer
		
		e = e*10;
	}
	
	int big = max(A.size(),B.size());
	
	int array[2*big],j;
	
	int number = num1*num2;					//Multiplying those 2 numbers
	
	for (int i = 2*big-1; i >= 0; i--) 
	{
	    array[i] = number % 10;				//Converting number back to vector
	    number /= 10;
	}

	int start = 0;
	for(i=0,j=0;i<2*big;i++)
	{
		if(array[i]!=0)
		{
			start = i;
			break;
		}
	}

	int size = 2*big-start;
	
	vector<int> result(size);
	
	i=0,j=start;
	
	while(size--)
	{
		result[i]  = array[j];			//Finally copying number without leading zeros
		i++,j++;
	}

	return result;
}

//Main Function of Large Integer Multiplication
vector<int> prod(vector<int> u,vector<int> v)
{
	int u_len = u.size();
	int v_len = v.size();
	
	int i;

	int n,m,j;
	vector<int> C;
	
	n = max(u_len,v_len);
	
	if(n<=3)							//Base case when n is less than or equal to 3
	{
		C = mult(u,v);					//Normal multiplication
		return C;	
	}

		
	m = n/3;
	
	vector<int> x(u_len-(2*m)),y(m),z(m),a(v_len-(2*m)),b(m),c(m);//Vectors in which numbers are dividedand stored 
	
	i=0;
	j=0;
	while(i<u_len-(2*m))
	{
		x[j] = u[i];
		i++,j++;
	}
	
	i=u_len-(2*m);
	j=0;
	while(i<u_len-m)
	{
		y[j] = u[i];
		i++,j++;
	}
	
	i=u_len-m;
	j=0;
	while(i<u_len)
	{
		z[j] = u[i];
		i++,j++;
	}
	
	i=0;
	j=0;
	while(i<v_len-(2*m))
	{
		a[j] = v[i];
		i++,j++;
	}
	
	i=v_len-(2*m);
	j=0;
	while(i<v_len-m)
	{
		b[j] = v[i];
		i++,j++;
	}
	
	i=v_len-m;
	j=0;
	while(i<v_len)
	{
		c[j] = v[i];
		i++,j++;
	}
	
	vector<int> p1,p2,p3,p4,p5,p6,p7,p8,p9,a1,a2,a3,a4;
	
	p1 = prod(x,a);

	p2 = prod(x,b);

	p3 = prod(y,a);

	p4 = prod(x,c);

	p5 = prod(y,b);
	
	p6 = prod(z,a);
	
	p7 = prod(y,c);
	
	p8 = prod(z,b);
	
	p9 = prod(z,c);
	
	a1 = addzero(p1,4*m);
	
	a2 = addzero(add(p2,p3),3*m);
	
	a3 = addzero(add(add(p4,p5),p6),2*m);
	
	a4 = addzero(add(p7,p8),m);
	
	return add(add(add(add(a1,a2),a3),a4),p9);
}
int main()
{
	int n,i;
	
	cin>>n;
	
	vector<int> num1(n),num2(n),result;
	
	srand (time(NULL));
	
	num1[0] = rand() % 9 + 1;
	num2[0] = rand() % 9 + 1;
	
	for(i=1;i<n;i++)
	{
		num1[i] = rand() % 10;
		num2[i] = rand() % 10;

	}
	
	for(i=0;i<n;i++)
	{
		cout<<num1[i];
	}
	cout<<endl;
	for(i=0;i<n;i++)
	{
		cout<<num2[i];
	}
	cout<<endl;
	
	result = prod(num1,num2);
	
	for(i=0;i<result.size();i++)
	{
		cout<<result[i];
	}
	
	return 0;
}
