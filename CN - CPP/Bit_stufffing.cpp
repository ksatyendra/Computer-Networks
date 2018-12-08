#include<iostream>
#include<cstdio>
#define MAX_SIZE 100
using namespace std;
int main()
{
	bool Source[MAX_SIZE];
	int size=0,ptr=0;
	char c;
	cout<<"Enter original data to stuff :\n";
	c=getchar();
	while(c!='\n')
    {
        if(ptr==5)
            ptr=0,Source[size++]=0;
        if(c=='1')
            ptr++,Source[size++]=1;
        else
            ptr=0,Source[size++]=0;
        c=getchar();
    }
	for(int i=0;i<size;)
        cout<<Source[i++];
    cout<<endl;
}
