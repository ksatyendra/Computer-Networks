#include<iostream>
using namespace std;
int main()
{
	string s,m="";
	cout<<"enter string to destuff"<<endl;
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
		 	i=i+2;
		 	m+=s[i];
     	 }
    }
	cout<<"destuffed string"<<endl<<m<<endl;
}
