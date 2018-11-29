#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct complex{
	double r,i;
};

complex sum(complex,complex);
complex product(complex,complex);
complex conjugate(complex);
vector<vector<complex> > tensorgen(vector<vector<complex> >,vector<vector<complex> >);
vector<complex> tensor(vector<complex>,vector<complex>);
double modulous(complex);
void disp(complex);

int main()
{
	complex x,y;
	x.r=1;
	x.i=1;
	y=sum(x,x);
	disp(y);
	y=product(x,x);
	disp(y);
	y=conjugate(x);
	disp(y);
	cout<<modulous(x)<<endl;
	return 0;
}

//Helper function to display a complex number in a more readable fashion
void disp(complex x)
{
	if(x.i<0)
	{
		cout<<x.r<<x.i<<"i\n";
	}
	else
	{
		cout<<x.r<<"+"<<x.i<<"i\n";
	}
}

//Function to sum two complex numbers
//Returns the sum
complex sum(complex x,complex y)
{
	complex temp;
	temp.r=x.r+y.r;
	temp.i=x.i+y.i;
	return temp;
}


complex product(complex x,complex y)
{
	complex temp;
	double a,b,c,d;
	a=x.r*y.r;
	b=x.r*y.i;
	c=x.i*y.r;
	d=(-1)*x.i*y.i;
	temp.r=a+d;
	temp.i=b+c;
	return temp;
}

//Function to return the conjugate of a complex number
//Returns conjugate in complex form
complex conjugate(complex x)
{
	complex temp;
	temp.r=x.r;
	temp.i=x.i*(-1);
	return temp;
}

//Function to return modulous of a complex number
//Returns a double
double modulous(complex x)
{
	return sqrt((pow(x.r,2)+pow(x.i,2)));
}

vector<vector<complex> > tensorgen(vector<vector<complex> > x,vector<vector<complex> > y)
{
	int i=0,j=0,k=0;
	complex temp;
	vector<complex> temp1;
	vector<vector<complex> > thing;
	for(i=0;i<((x[0]).size()*(y[0]).size());i++)
	{
		temp1.push_back(temp);
	}
	for(i=0;i<x.size()*y.size();i++)
	{
		thing.push_back(temp1);
	}
	for(i=0;i<thing.size();i++)
	{
		for(j=0;j<x[0].size();j++)
		{
			//*********************************
			//Finish later if needed
			//*********************************
			for(k=0;k<y.size();k++)
			{
				//thing[i][j+k]=product();
			}
		}
	}
	return thing;
}

//Function specifically made for ket tensors
vector<complex> tensor(vector<complex> x,vector<complex> y)
{
	int i=0,j=0;
	complex temp1;
	vector<complex> temp;
	for(i=0;i<x.size()*y.size();i++)
	{
		temp.push_back(temp1);
	}
	for(i=0;i<x.size();i++)
	{
		for(j=0;j<y.size();j++)
		{
			temp[i+j]=product(x[i],y[j]);
		}
	}
	return temp;
}