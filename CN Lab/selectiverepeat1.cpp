#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<cstring>
#include<cmath>
using namespace std;
ifstream in;
ofstream out;
int c=-1,x,alen,blen,size,z1,count1=0,z=1,pr=-1,seq;
float success=0,trans=0;
int a1[200],b1[200],c1[200],d1[200],e1[200],rtt;
char ch1[100],ch2[100]="100000111",ch3[100]="1100000001111",a[200],crc[100];
struct node
{
	char data[200];
	int frame;
	int ack=-1;
	node *next;
};
struct timer
{
	int t;
	int r;
	timer *next;
};
struct node1  
{
	char data1[200];
	node1 *next;
};
node1 *backup,*backup1;
int process(char ch[200],int t);
int transmit(node *p,timer *q,int h,int count,node1 *q1,int count2);
node *start,*sf,*s,*sl,*p,*r;
timer *st,*st1;
void division(int a[100],int b[100])
{
	blen=strlen(ch1);
	for(int i=0;i<alen;i++)
	{
		if(a[i]==1)
			for(int j=0;j<alen+blen-1;j++)
			a[j]=a[j]^b[j];
		for(int k=alen+blen-2;k>0;k--)
		b[k]=b[k-1];
		b[0]=0;	
	}
}
void generatecrc(char ch[100])
{
	
	alen=strlen(ch);
	for(int i=0;i<alen;i++)
	{
		a1[i]=ch[i]-48;
		c1[i]=a1[i];
	}
	for(int i=0;ch1[i]!='\0';i++)
	{
		if(ch1[i]=='0')
			b1[i]=0;
		else
			b1[i]=1;
			e1[i]=b1[i];
	}
	blen=strlen(ch1);
	for(int i=0;i<blen-1;i++)
	a1[i+alen]=0;
    for(int j=0;j<alen;j++)
     {
     b1[j+blen]=0;
     e1[j+blen]=0;
 	}
		division(a1,b1);
	for(int i=alen;i<alen+blen-1;i++)
       {
		if(a1[i]==1)
		crc[i-alen]='1';
		else
		crc[i-alen]='0';
		}	
		//cout<<crc<<endl;	
}
void rotate(char a[100])
{
	x=strlen(a);
    for(int i=0;i<(x/2);i++)
    {
    char y=a[i];
    a[i]=a[x-i-1];
    a[x-i-1]=y;
	}
}
void insert(int i,char a[200])
{
	a[x+1]=NULL;
	for(int j=x-1;j>i;j--)
	a[j+1]=a[j];
	a[i+1]='0';
}
void framenumber(char a[200])
{
	switch(c)
	{	
	case 0:	strcat(a,"0000");break;
	case 1:	strcat(a,"1000");break;
	case 2:	strcat(a,"0100");break;
	case 3:	strcat(a,"1100");break;
	case 4:	strcat(a,"0010");break;
	case 5:	strcat(a,"1010");break;
	case 6:	strcat(a,"0110");break;
	case 7:	strcat(a,"1110");break;
	case 8:	strcat(a,"0001");break;
	case 9:	strcat(a,"1001");break;
	case 10:strcat(a,"0101");break;
	case 11:strcat(a,"1101");break;
	case 12:strcat(a,"0011");break;
	case 13:strcat(a,"1011");break;
	case 14:strcat(a,"0111");break;
	case 15:strcat(a,"1111");break;
	default:;
	}	
}
void bitstuffing(char a[200])
{
	generatecrc(a);
	//strcat(a," ");
	strcat(a,crc);
	if(c==15)
		c=-1;
		c++;
	int y=0,r=0,z;
	x=strlen(a);
	for(int i=0;i<x;i++)
	{
		if(a[i]=='1')
		y++;
		else 
		y=0;
		if(y==5)
		{
		insert(i,a);
		 x=strlen(a);
		y=0;
	   }
	}
	strcat(a,"01111110");
	rotate(a);
	framenumber(a);
	strcat(a,"01111110");
	rotate(a);
}
void destuffing1(char a[200])
{
	int j=0,i=0,q;
	for(i=0;i<strlen(a)-20;i++)
	{
		if(a[i+12]=='1')
		j++;
		else
		j=0;
		if(j==5)
		{
		for(q=i+12;a[q+1]!=NULL;q++)
		a[q+1]=a[q+2];
		a[q]=NULL;
		j=0;
		}	
	}
}
int errordetection(char a[200])
{

	//cout<<"\n check point 2 "<<a;
	destuffing1(a);
//	cout<<"\n check point 3 "<<a;
	int j=0,i=0;
	for(i=0;i<=strlen(a)-20;i++,j++)
	{
		
		d1[j]=a[i+12]-48;
	}
/*	cout<<"checking i "<<i;
	cout<<"  "<<strlen(a);*/
	alen=j;
	/*cout<<endl;
	cout<<"\n check point 4 ";
    for(int i=0;i<j;i++)
    cout<<d1[i];*/
    for(int i=0;i<strlen(ch1);i++)
    e1[i]=ch1[i]-48;
    blen=strlen(ch1);
    for(int i=blen;i<alen;i++)
    e1[i]=0;
    cout<<endl;
   
      /*for(int i=0;i<alen;i++)
      cout<<e1[i];
      cout<<"\n alen is"<<alen<<"   "<<blen;*/
     alen=alen-blen+1;
	division(d1,e1);
	cout<<"\n remainder is";
	for(int i=alen;i<alen+blen-1;i++)
	cout<<d1[i];
	x=0;
	for(int i=alen;i<alen+blen-1;i++)
	{
	if(d1[i]==1)
    x++;
    }
    if(x==0)
    {
    cout<<"\n no error in received data \n";
    return 1;
    }
    else
    cout<<"\n error in received data";
    return 0;
}
void print(char a[200])
{
	if(pr==15)
	pr=-1;
	pr++;
	int qw=0;
	for(int i=0;i<4;i++)
	qw=qw+((a[11-i]-48)*pow(2,i));
	if(pr==qw)
	{
	char a2[200];
	int j=0;
	for(int i=0;i<=strlen(a)-20-strlen(ch1);i++,j++)
	{
		
		a2[j]=a[i+12];
	}
	a2[j]=NULL;
	out<<a2;
	}
	else
	{
		pr--;
	cout<<"\n duplicate packet discarded";
	}
}
int  process(char a[200],int t)
{
	int k=rand()%100;
	if(k<70)
	cout<<"\n errorless channel";
	else
	{
		cout<<"\n erroneous channel";
		k=rand()%100;
		if(k>50)
		{
			//cout<<"paclet lost";
			t=100;
			return 0;
		}
		else
		{
			k=rand()%(strlen(a)-20);
	 		if(a[k+12]=='1')
			a[k+12]='0';
    		else
			a[k+12]='1';
		}
	}
	return 1;
}
int  receiver(node *p,timer *q,int j,int h)
{
	if(j==1)	//packet does not lost
  	{
  		int y=0;
  		if(p->frame==r->frame)
  		y=errordetection(p->data);
  		else
  		{
  			cout<<"\n  waiting for packet "<<r->frame<<" discard packet";
  			cout<<"\n nack received for frame "<<r->frame;
  			return r->frame;
  		//	return -1;
  		}
  		if(y==1) //no error
  		{
  				success++;
  			if(r->next!=NULL)
  			r=r->next;
  			print(p->data);
  			int k=rand()%100;
    		if(k<20)
    		{
    		cout<<"\n ack lost";
    		return 16;
    		q->r=1000;
    		}
    		else
    		{
    			count1=0;
    		//	cout<<"\n enter the time taken for transmission and reception ";
    		q->t=rand()%50;
    		q->r=rand()%50;
    		if((q->t+q->r)>rtt)
    		cout<<"\n ack delayed";
    		}	
  		}
		else
		{	//error in received data
  		q->r=1000;
		  count1=0;	
  		}
	  }
  	else
  	{
  	cout<<"\n packet lost";
  	q->t=1000;
  	count1=0;
  	}
  	if((q->t+q->r)>rtt)
  	{
  		//cout<<"\n time out";
  		return -1;
  	}
  	else
  	{
  		//success++;
  	cout<<"\n ack received for frame "<<p->frame;
  	rtt=rand()%1000;
  	node *w=start;
  	while(w!=p)
  	{
  		w->ack=1;
  		w=w->next;
  	}
     while(sf->frame!=r->frame)
  	{
  		if(sl->next!=NULL)
  		{
			sl=sl->next;
			sf=sf->next;
			st1=st1->next;
			backup=backup->next;
			cout<<"\n window slides";
		}
		else
		break;
	}
	z=1;
	count1=0;
  	return 16;
  	}	
}
int  transmit(node *p,timer *q,int h,int count,node1 *q1,int count2)
{
if(p!=NULL)
  {
  //	cin>>z;
  	trans++;
	for(int i=0;i<strlen(q1->data1);i++)
	p->data[i]=q1->data1[i];
	cout<<"\n transmitting frame "<<p->frame<<"    "<<p->data;
	int j=process(p->data,q->t);
	 h=receiver(p,q,j,h);
	 if((h==16))
	 p->ack=1;
	 if((h!=16)&&(count!=0)&&(h!=-1))
	 {
	 	p=sf;
	 	while((p->frame!=h))//&&(p->next!=NULL))
	 	p=p->next;
	 }
	 if(h!=16)
	 count++;
	 else
	 count=0;
	 if((p!=sl)&&((count<=1)||(h==-1)))
	 transmit(p->next,q->next,h,count,q1->next,0);
	 else
	 {
	 if(sl->next!=NULL)
   	cout<<"\n time out";
   	}
	 if((p->ack!=1)&&(count==1))
	 transmit(p,q,1,0,q1,0);
}
}
void input(char a[200])
{
	int i=0;
	for(i=0;i<seq;i++)
	{
	
	in>>a[i];
		if(in.eof())
     break;
	}
	a[i]=NULL;
}
int main()
{
	//out.open("data to be transmitted.txt");
	for(int i=0;i<1000;i++)
	z=rand()%2;
	//out.close();
	cout<<"\n enter the frame size";
	cin>>seq;
	int t;
	cout<<" \n select crc  1.crc-8  2.crc-12";
	cin>>t;
	if(t==1)
	for(int i=0;i<=strlen(ch2);i++)
	ch1[i]=ch2[i];
	else
	for(int i=0;i<=strlen(ch3);i++)
	ch1[i]=ch3[i];
	cout<<"\n enter the window size";
	cin>>size;
	in.open("data to be transmitted.txt");
	out.open("received data.txt");
	t=size-1;
	start=new node;
	backup=new node1;
	backup1=backup;
	input(start->data);	//in>>start->data;
//	cout<<"\n actual data"<<start->data;
		bitstuffing(start->data);
		for(int i=0;i<=strlen(start->data);i++)
		backup->data1[i]=start->data[i];
		backup->next=NULL;
//	cout<<"\n data to be transmitted "<<start->data;
	start->frame=c;
	start->next=NULL;
	sf=start;
	st=new timer;
	st->next=NULL;
	st1=st;
	while(!in.eof())
	{	
	 p=new node;
	 node1 *q=new node1;
		input(p->data);
		if(p->data[0]==NULL)	
		break;	//in>>p->data;
//	cout<<"\n actual data"<<p->data;
		bitstuffing(p->data);
//	cout<<"\n data to be transmitted"<<p->data;
for(int i=0;i<=strlen(p->data);i++)
		q->data1[i]=p->data[i];
		q->next=NULL;
		backup->next=q;
		backup=backup->next;
	p->frame=c;
	p->next=NULL;
	start->next=p;
	start=start->next;
	timer *st2=new timer;
	st2->next=NULL;
	st->next=st2;
	st=st->next;
	}
	st=st1;
	start=sf;
	s=sf;
	sl=s;
	backup=backup1;
	r=s;
	start=sf;
	for(int i=0;i<t;i++)
	{
	sl=sl->next;
	st1=st1->next;
	backup=backup->next;
	}
	rtt=rand()%1000;
	transmit(s,st,1,0,backup1,0);
	cout<<"\n throughput is "<<(success/trans);
	return 0;
}
