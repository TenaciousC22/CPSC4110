#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//struct to represent a complex number
//r = real value
//i = imaginary coefficient
struct complex{
	double r,i;
};

//these are just really useful to have available
complex zero,one;
vector<complex> ketone,ketzero;

//Function prototypes
void init();
vector<complex> hadamard(vector<complex>);
vector<complex> hadamardMagnum(vector<complex>);
vector<complex> deutsch();
vector<complex> toffoli(vector<complex>,vector<complex>,vector<complex>);
vector<complex> cnot(vector<complex>,vector<complex>);
complex sum(complex,complex);
complex product(complex,complex);
complex coproduct(complex,double);
complex conjugate(complex);
vector<vector<complex> > tensorgen(vector<vector<complex> >,vector<vector<complex> >);
vector<complex> tensor(vector<complex>,vector<complex>);
double modulous(complex);
void disp(complex);


//C-NOT arrays for use in C-NOT and Toffoli functions and the hadamard function
complex fourbyfour[4][4];
complex eightbyeight[8][8];
complex hada[2][2];

int main()
{
	//initilize global variables and other useful stuff
	init();
	int option=20,n,m,o;
	complex x,y;
	vector<complex> a,b,test;
	x.r=1;
	x.i=1;
	a=ketzero;
	b=ketone;
	while(option!=4)
	{
		cout<<"\nChoose an option:"<<endl;
		cout<<"1: CNOT"<<endl;
		cout<<"2: Toffoli"<<endl;
		cout<<"3: Deutsche's "<<endl;
		cout<<"4: CNOT test\n";
		cout<<"5: Toffoli test\n";
		cout<<"6: Exit";
		std::cin>>option;
		cin.clear();
		if (option==1){
			cout<<"Enter your 2-bit binary input with a space after each"<<endl;
			std::cin>>n>>m;
			cout<<endl;
			cin.clear();
			if (n==0&&m==0){cnot(a,a);}
			if (n==0&&m==1){cnot(a,b);}
			if (n==1&&m==0){cnot(b,a);}
			if (n==1&&m==1){cnot(b,b);}
			cout<<endl;
		}
		else if (option==2){
			cout<<"Enter your 3-bit binary input"<<endl;
			std::cin>>n>>m>>o;
			cout<<endl;
			cin.clear();
			if (n==0&&m==0&&o==0){toffoli(a,a,a);}
			if (n==0&&m==0&&o==1){toffoli(a,a,b);}
			if (n==0&&m==1&&o==0){toffoli(a,b,a);}
			if (n==0&&m==1&&o==1){toffoli(a,b,b);}
			if (n==1&&m==0&&o==0){toffoli(b,a,a);}
			if (n==1&&m==0&&o==1){toffoli(b,a,b);}
			if (n==1&&m==1&&o==0){toffoli(b,b,a);}
			if (n==1&&m==1&&o==1){toffoli(b,b,b);}
			cout<<endl;
		}
		else if (option==3){
			cout<<endl;
			deutsch();
		}
		else if(option==4){
			cnot(ketzero,ketzero);
			cout<<endl;
			cnot(ketzero,ketone);
			cout<<endl;
			cnot(ketone,ketzero);
			cout<<endl;
			cnot(ketone,ketone);
			cout<<endl;
		}
		else if(option==5){
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
		}
		else if(option==6){
			cout<<"Invalid Entry\n";
		}
	}
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
	//why am I even bothering to comment this
	complex temp;
	temp.r=x.r+y.r;
	temp.i=x.i+y.i;
	return temp;
}

//returns the product of two complex numbers
complex product(complex x,complex y)
{
	//multiply everything together
	complex temp;
	double a,b,c,d;
	a=x.r*y.r;
	b=x.r*y.i;
	c=x.i*y.r;
	d=(-1)*x.i*y.i;
	//add that shiznit
	temp.r=a+d;
	temp.i=b+c;
	//return to sender
	return temp;
}

//returns product of a complex number and a coefficient
complex coproduct(complex x, double y)
{
	x.r=x.r*y;
	x.i=x.i*y;
	return x;
}
//Function to return the conjugate of a complex number
//Returns conjugate in complex form
complex conjugate(complex x)
{
	//find and return the conjugate
	complex temp;
	temp.r=x.r;
	temp.i=x.i*(-1);
	return temp;
}

//Function to return modulous of a complex number
//Returns a double
double modulous(complex x)
{
	//take a guess at what  this does
	return sqrt((pow(x.r,2)+pow(x.i,2)));
}

//returns full tensored vector for c-not, if you just want the affected ket change the return value to 'y' NOTE: this only works if you are using |0> and |1> 
vector<complex> cnot(vector<complex> x,vector<complex> y)
{
	//initilize stuff
	int decode;
	vector<complex> temp,ret;
	//make the return value the right size
	for(int i=0;i<4;i++){
		ret.push_back(zero);
	}
	//get the tensor product of x and y
	temp=tensor(x,y);
	for(int i=0;i<4;i++)
	{
		//yep, that's a thing
		ret[i]=sum(sum(product(fourbyfour[0][i],temp[0]),product(fourbyfour[1][i],temp[1])),sum(product(fourbyfour[2][i],temp[2]),product(fourbyfour[3][i],temp[3])));
	}
	//modify the affected ket and display results
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
	//return full vector
	return ret;
}

//Returns the full tenosr form for a toffoli gate, if you want it to return just the affected bit, change the return value to 'z' NOTE: this only works if you are using |0> and |1>
vector<complex> toffoli(vector<complex> x,vector<complex> y,vector<complex> z)
{
	//initilize temporary varibales
	int decode;
	vector<complex> temp, ret;
	for(int i=0;i<8;i++)
	{
		ret.push_back(zero);
	}
	//create the tensor product for matrix multiplication
	temp=tensor(x,y);
	temp=tensor(temp,z);
	//matrix multiplication
	for(int i=0;i<8;i++)
	{
		//trust me, it works
		ret[i]=sum(sum(sum(product(eightbyeight[0][i],temp[0]),product(eightbyeight[1][i],temp[1])),sum(product(eightbyeight[2][i],temp[2]),product(eightbyeight[3][i],temp[3]))),sum(sum(product(eightbyeight[4][i],temp[4]),product(eightbyeight[5][i],temp[5])),sum(product(eightbyeight[6][i],temp[6]),product(eightbyeight[7][i],temp[7]))));
	}
	//modify affected ket and display results
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

//take a guess at what this does
vector<complex> deutsch()
{
	//build Uf
	complex uf[4][4];
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			uf[i][j]=zero;
		}
	}
	double a,b,c,d;
	vector<complex> temp,ret,top,bot;
	complex x,y;
	cout<<"Input Uf, line by line, in the format a b c d where a, b, c, and d are 1 or 0\n";
	for(int i=0;i<4;i++)
	{
		cin>>a>>b>>c>>d;
		uf[0][i].r=a;
		uf[1][i].r=b;
		uf[2][i].r=c;
		uf[3][i].r=d;
	}
	//set up kets and entangle then tensor them
	top=ketzero;
	bot=ketone;
	top=hadamard(top);
	bot=hadamard(bot);
	temp=tensor(top,bot);
	//matrix multiplication
	for(int i=0;i<4;i++)
	{
		ret.push_back(sum(sum(product(uf[0][i],temp[0]),product(uf[1][i],temp[1])),sum(product(uf[2][i],temp[2]),product(uf[3][i],temp[3]))));
	}
	//output results
	if(ret[1].r<0&&ret[3].r<0)
	{
		cout<<"Uf is constant\n";
	}
	else
	{
		cout<<"Uf is balanced\n";
	}
	//tbh not sure why I do this, but it can't hurt
	return ret;
}

//this does not work, but I also don't think i need to make it work
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

//Function specifically made for 1-D vectors
vector<complex> tensor(vector<complex> x,vector<complex> y)
{
	//initilize stuff
	int i=0,j=0;
	vector<complex> temp;
	for(i=0;i<static_cast<int>(x.size())*static_cast<int>(y.size());i++)
	{
		//make temp the right size
		temp.push_back(zero);
	}
	for(i=0;i<x.size();i++)
	{
		for(j=0;j<y.size();j++)
		{
			//assign values to the tensor product
			temp[(i*2)+j]=product(x[i],y[j]);
		}
	}
	//done, return tensor product
	return temp;
}


//this just initilizes all our varibles for use
void init()
{
	//initilize generic complex values and vectors
	zero.r=0;
	zero.i=0;
	one.r=1;
	one.i=0;
	ketone.push_back(zero);
	ketone.push_back(one);
	ketzero.push_back(one);
	ketzero.push_back(zero);
	int i,j;
	//create 4X4 and 8X8 c-not matricies
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
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			if(j==1&&i==1)
			{
				hada[i][j]=coproduct(one,-1);
			}
			else
			{
				hada[i][j]=one;
			}
		}
	}
}

//Function to entangle a ket
vector<complex> hadamard(vector<complex> x)
{
	//build the return vector
	vector<complex> ret;
	for(int i=0;i<2;i++)
	{
		ret.push_back(zero);
	}
	//matrix multiplication and root 2ing
	for(int i=0;i<2;i++)
	{
		ret[i]=sum(product(hada[0][i],x[0]),product(hada[1][i],x[1]));
		ret[i]=coproduct(ret[i],1/sqrt(2));
	}
	//return the new thing
	return ret;
}


//I'm so tired I've resorted to condom jokes
vector<complex> hadamardMagnum(vector<complex> x)
{
	//build the 4 by 4 hadamard matrix
	complex neg=coproduct(one,-1);
	vector<complex> ret;
	complex hadamardXL[4][4]={
		{one,one,one,one},
		{one,neg,one,neg},
		{one,one,neg,neg},
		{one,neg,neg,one}
	};
	//matrix multiplication and root 2ing
	for(int i=0;i<4;i++)
	{
		ret.push_back(sum(sum(product(hadamardXL[0][i],x[0]),product(hadamardXL[1][i],x[1])),sum(product(hadamardXL[2][i],x[2]),product(hadamardXL[3][i],x[3]))));
		ret[i]=coproduct(ret[i],1/sqrt(2));
	}
	//return the new thing
	return ret;
}