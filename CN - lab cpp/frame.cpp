#include<iostream>
using namespace std;
struct frame
{
	string flag="01111110";
	string src_add,dest_add;
	string data;        
    string check_sum;	
	
}frm;
void get_data(frame& s)
{
	cout<<"enter data"<<endl; //4 bit data
	cin>>s.data;
	
}
void get_address(frame& s)
{
	cout<<"enter source add";
	cin>>s.src_add;
	cout<<"enter destn address";
	cin>>s.dest_add;
}
char xor1(char a,char b)
{
	if(a!=b)
	{
		return '1';
	}
	else 
	return '0';
}
void create_chksm(frame& s)
{
	string gen="1100000001111";   //crc12
	
	
	//int t=divdnd.length();
	for(int m=0;m<gen.length()-1;m++)
	{
	  s.data =	s.data+'0';
	}
	string h=s.data;
	int k=0,l=0;
 for(int j=0;j<=(s.data.length()-gen.length());j++) 
 {
   	if(s.data[j]=='1')
   	{  //quot[k++]='1';
   	   for(int i=0;i<gen.length();i++)
         
		  {
		      s.data[i+j]=xor1(s.data[i+j],gen[i]);
		     
	      }
	}
	else
	{
	//	quot[k++]='0';		
	}
   
}
int p=0,m=s.data.length()-gen.length()+1;
for(int i=(s.data.length()-gen.length()+1);i<=s.data.length();i++)
{
	h[m++]= xor1(s.data[i],'0' );
}
s.check_sum=h;

	
}
int main()
{
	get_data(frm);
	string t=frm.data;
	get_address(frm);
	create_chksm(frm);
	cout<<endl<<frm.flag<<" "<<frm.src_add<<" "<<frm.dest_add<<" "<<t<<" "<<frm.check_sum<<" "<<frm.flag;
}
