#include<iostream>
#include<cstdio>
#include<cstdlib>
#define MAX_SIZE 100
using namespace std;
int main()
{
	bool Source[MAX_SIZE];
	int size=0,ptr=0;
	char c;
	cout<<"Enter the data to destuff :\n";
	c=getchar();
	while(c!='\n')
    {
        if(ptr==5)
        {
            if(c=='1')
            {
                cout<<"\nError Message : This is not correct stuffed data.";
                cout<<"As stuffed data should have 0 after five 1's\n";
                exit(-1);
            }
            ptr=0;
            c=getchar();
        }
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
