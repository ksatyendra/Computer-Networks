#include<iostream>
#include<cstdio>
#define MAX_SIZE 100
using namespace std;
void Scan_Data(bool *Source,int &Source_Size)
{
    // for scanning the Frame and Generator into respective variables
    char c=getchar();
	Source_Size=0;
	while(c!='\n')
    {
        Source[Source_Size++]=c=='0'?0:1;
        c=getchar();
    }
}

void Display_Result(bool *Source,int Source_Size)
{
    // to display the contents of Frame
    for(int i=0;i<Source_Size;i++)
        cout<<Source[i];
    cout<<endl;
}

void Display_CheckSum(bool *Hold,int Gen_Size,int flag)
{
    for(int i=flag+1;i<Gen_Size+flag;i++)
        cout<<Hold[i%Gen_Size];
}

int main() // 11010110111100101011100111011001
{
    bool *Frame,*Generator,*Hold;
    int Frame_Size,Gen_Size,i,j,flag;
    Frame=new bool[MAX_SIZE];
    Hold=new bool[MAX_SIZE];
    Generator=new bool[MAX_SIZE];	// x^16+x^12+x^5+x^0  10001000000100001
    cout<<"\nEnter Frame : ";
    Scan_Data(Frame,Frame_Size);    // Scannimg Frame
    cout<<"\nEnter Generator : ";
    Scan_Data(Generator,Gen_Size);  // Scannimg Generator
    for(int i=0;i<Gen_Size-1;i++)   // insterting Gen_Size-1 0's at end of Frame
        Frame[Frame_Size++]=0;
    for(i=0;Frame[i]!=Generator[0];) // when Hold < Generator
        i++;
    while(i<Gen_Size)   // load Hold with initial data
        Hold[i]=Frame[i++];
    flag=0;
    for(j=Gen_Size;j<Frame_Size;)
    {
        // Display_Result(Hold,Gen_Size);
        int k;
        for(i=flag,k=1;k<Gen_Size;i++)  // XORing Generator with dividend(i.e., Hold)
            Hold[i%Gen_Size]=Hold[(i+1)%Gen_Size]^Generator[k++];
        Hold[i%Gen_Size]=Frame[j++];
        // Display_Result(Hold,Gen_Size);
        while(Hold[flag%Gen_Size]!=Generator[0] && j<Frame_Size) // when Hold < Generator
            Hold[flag%Gen_Size]=Frame[j++],flag++;
    }
    for(j=Frame_Size-Gen_Size;j<Frame_Size;flag++) // XORing remainder with dividend(i.e., Frame)
        Frame[j++]^=Hold[flag%Gen_Size];
    cout<<"\nTransmitted Frame : ";
    Display_Result(Frame,Frame_Size);   // displaying resulting data
    cout<<"\nCheck Sum : ";
    Display_CheckSum(Hold,Gen_Size,flag);   // displaying check sum
    cout<<endl;
}
