#include<iostream>
using namespace std;

struct data
{
	string str;
	string quot;
	string dup_str;
	string src_add;
	int ack=0;
} data1;
void from_ntwrk_layer(data&);
void to_physical_layer(data&);
void from_physical_layer(data&);
void to_ntwrk_layer(data& );
void stuff(string);
void sender(data&);
void receiver(data&);
string stuff(string);
string stuff(string s)
{
	string m="";
	//cout<<"enter string to stuff";
	//cin>>s;
	int count=0,k=0;
	for(int i=0;i<s.length();i++)
	{   
	   if(s[i]=='0')
	   {
	   count=0;m+=s[i];
       }
		if(s[i]=='1')
		 {
		count++;m+=s[i];
        	}
		if(count==5)
		 {
		 	count=0;
		 	m+='0';
     	 }
    }
	cout<<"stuffed string"<<endl<<m;
return m;
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
string runcrc(string& divdnd)
{
	string divsr,quot,rem;
//	cout<<"enter frame"; 
//	cin>>divdnd;
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
//cout<<"transmitted frame"<<" "<<h;
divdnd=h;
}
void from_ntwrk_layer(data& info)
{
	cout<<"enter data";
	cin>>info.str;
}
void to_physical_layer(data& info)
{
	info.str=(info.str);
	cout<<"stuffed string"<<" "<<data1.str;
	info.quot=runcrc(info.str);
	cout<<"string after crc"<<" "<<data1.str;
}
void from_physical_layer(data& info)
{
		info.quot=runcrc(info.str);
	if(info.quot=="0000000000000000" && info.src_add=="110011" )
	{
		data1.ack='1';
		cout<<" acknowledgement sent";
	
	destuff(info.str);
    }
    else 
    {
    	cout<<"acknowledgmnt not sent";
    	data1.ack=0;
	}
}
void to_ntwrk_layer(data& info)
{
  cout<<"receiver received data:"<<info.str<<" from src address: "	<<info.src_add<<endl;
}
void sender(data& str)
{
	from_ntwrk_layer(str);
	to_physical_layer(str);	
}
void receiver(data& str)
{
	from_physical_layer(str);
	to_ntwrk_layer(str);
}
int main()
{
	sender(data1);
	sleep(1);
	receiver(data1);
}
