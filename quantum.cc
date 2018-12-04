#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct complex{
	double r,i;
};

complex zero,one;
vector<complex> ketone,ketzero;

void cnotinit();
vector<complex> toffoli(vector<complex>,vector<complex>,vector<complex>);
vector<complex> cnot(vector<complex>,vector<complex>);
complex sum(complex,complex);
complex product(complex,complex);
complex conjugate(complex);
vector<vector<complex> > tensorgen(vector<vector<complex> >,vector<vector<complex> >);
vector<complex> tensor(vector<complex>,vector<complex>);
double modulous(complex);
void disp(complex);

complex fourbyfour[4][4];
complex eightbyeight[8][8];

int main()
{
	cnotinit();
	complex x,y;
	vector<complex> a,b,test;
	x.r=1;
	x.i=1;
	ketone.push_back(zero);
	ketone.push_back(one);
	ketzero.push_back(one);
	ketzero.push_back(zero);
	a=ketzero;
	b=ketone;
	cnot(ketzero,ketzero);
	cout<<endl;
	cnot(ketzero,ketone);
	cout<<endl;
	cnot(ketone,ketzero);
	cout<<endl;
	cnot(ketone,ketone);
	cout<<endl;
	toffoli(a,a,a);
	cout<<endl;
	toffoli(a,a,b);
	cout<<endl;
	toffoli(a,b,a);
	cout<<endl;
	toffoli(a,b,b);
	cout<<endl;
	toffoli(b,a,a);
	cout<<endl;
	toffoli(b,a,b);
	cout<<endl;
	toffoli(b,b,a);
	cout<<endl;
	toffoli(b,b,b);
	cout<<endl;
	return 0;
}

//Helper function to display a complex number in a more readable fashion
void disp(complex x)
{
	if(x.i<0)
	{
		cout<<x.r<<x.i<<"i";
	}
	if(x.i==0)
	{
		cout<<x.r;
	}
	else
	{
		cout<<x.r<<"+"<<x.i<<"i";
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

//returns affected ket vector
vector<complex> cnot(vector<complex> x,vector<complex> y)
{
	int xoff,yoff,decode;
	vector<complex> temp,ret;
	for(int i=0;i<4;i++){
		ret.push_back(zero);
	}
	temp=tensor(x,y);
	if(x[0].r==1){xoff=0;}
	else{xoff=1;}
	if(y[0].r==1){yoff=0;}
	else{yoff=1;}
	temp[(xoff*2)+yoff].r=1;
	for(int i=0;i<4;i++)
	{
		ret[i]=sum(sum(product(fourbyfour[0][i],temp[0]),product(fourbyfour[1][i],temp[1])),sum(product(fourbyfour[2][i],temp[2]),product(fourbyfour[3][i],temp[3])));
	}
	for(int i=0;i<4;i++)
	{
		if(ret[i].r==1){decode=i;}
		disp(ret[i]);
		cout<<endl;
	}
	if(decode==3){
		y=ketone;
	}
	else if(decode==2){
		y=ketzero;
	}
	return ret;
}

//returns the affected qubit
vector<complex> toffoli(vector<complex> x,vector<complex> y,vector<complex> z)
{
	int xoff,yoff,zoff,decode;
	vector<complex> temp, ret;
	for(int i=0;i<8;i++)
	{
		ret.push_back(zero);
	}
	temp=tensor(x,y);
	temp=tensor(temp,z);
	if(x[0].r==1){xoff=0;}
	else{xoff=1;}
	if(y[0].r==1){yoff=0;}
	else{yoff=1;}
	if(z[0].r==1){zoff=0;}
	else{zoff=1;}
	temp[(xoff*4)+(yoff*2)+zoff]=one;
	for(int i=0;i<8;i++)
	{
		//trust me, it works
		ret[i]=sum(sum(sum(product(eightbyeight[0][i],temp[0]),product(eightbyeight[1][i],temp[1])),sum(product(eightbyeight[2][i],temp[2]),product(eightbyeight[3][i],temp[3]))),sum(sum(product(eightbyeight[4][i],temp[4]),product(eightbyeight[5][i],temp[5])),sum(product(eightbyeight[6][i],temp[6]),product(eightbyeight[7][i],temp[7]))));
	}
	for(int i=0;i<8;i++)
	{
		if(ret[i].r==1){decode=i;}
		disp(ret[i]);
		cout<<endl;
	}
	if(decode=8){
		z=ketone;
	}
	else if(decode=7){
		z=ketzero;
	}
	return ret;
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

//Function specifically made for ket tensors********Currently doesn't work
vector<complex> tensor(vector<complex> x,vector<complex> y)
{
	int i=0,j=0;
	vector<complex> temp;
	for(i=0;i<static_cast<int>(x.size())*static_cast<int>(y.size());i++)
	{
		temp.push_back(zero);
	}
	for(i=0;i<x.size();i++)
	{
		for(j=0;j<y.size();j++)
		{
			temp[(i*2)+j]=product(x[i],y[j]);
		}
	}
	return temp;
}

void cnotinit()
{
	zero.r=0;
	zero.i=0;
	one.r=1;
	one.i=0;
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			fourbyfour[i][j]=zero;
			if((i==1&&j==1)||(i==0&&j==0)||(i==2&&j==3)||(i==3&&j==2))
			{
				fourbyfour[i][j]=one;
			}
		}
	}
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			eightbyeight[i][j]=zero;
			if((i==1&&j==1)||(i==0&&j==0)||(i==2&&j==2)||(i==3&&j==3)||(i==4&&j==4)||(i==5&&j==5)||(i==6&&j==7)||(i==7&&j==6))
			{
				eightbyeight[i][j]=one;
			}
		}
	}
}