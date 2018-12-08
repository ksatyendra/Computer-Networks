#include<iostream>
using namespace std;
char xor1(char a,char b)
{
	if(a!=b)
	{
		return '1';
	}
	else 
	return '0';
}
int main()
{
	string divsr,divdnd,quot,rem;
	cout<<"enter frame"; 
	cin>>divdnd;
	//cout<<"enter generator";
	//cin>>divsr;	
	divsr="10001000000100001";  //std crc16 x^16+x^12+x^5+x^2+1
	cout<<"standard crc 16 bit poly"<<divsr<<endl;
	int t=divdnd.length();
	for(int m=0;m<divsr.length()-1;m++)
	{
	  divdnd =	divdnd+'0';
	}
	string h=divdnd;
	int k=0,l=0;
 for(int j=0;j<=(divdnd.length()-divsr.length());j++) 
 {
   	if(divdnd[j]=='1')
   	{  quot[k++]='1';
   	   for(int i=0;i<divsr.length();i++)
         
		  {
		      divdnd[i+j]=xor1(divdnd[i+j],divsr[i]);
	      }
	}
	else
	{
		quot[k++]='0';		
	}
}
int p=0,m=divdnd.length()-divsr.length()+1;
for(int i=(divdnd.length()-divsr.length()+1);i<=divdnd.length();i++)
{
	h[m++]= xor1(divdnd[i],'0' );
}
cout<<"transmitted frame"<<" "<<h;
}
