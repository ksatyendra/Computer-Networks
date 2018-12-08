#include<iostream>
using namespace std;
int main()
{
	string s,m="";
	cout<<"enter string to stuff";
	cin>>s;
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
}
