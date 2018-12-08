#include<iostream>
#include<cstdlib>
#define Max_No_Frames 15
using namespace std;

struct Frame
{
 int index;
 int data;
 int Fault;
};			// Frame Structure

Frame frame;
bool MODE;		// Mode 0 denotes SENDER mode and 1 denotes RECEIVER mode
int Connection=1,Time_Out=3,i=0;
int Data_Set[Max_No_Frames+1]={54,46,67,61,546,44,93,53,65,78,94,24,200,332,65,10};

void SEND_from_network_layer(int *buffer)
{	// SEND_ in function name denotes sender side
   *buffer= Data_Set[i++];			// Data is fetched from network layer
}

void REC_to_network_layer(int *buffer)
{
 cout<<"Frame Data "<<*buffer<<" is recieved. And Acknowledgment is Sent. [Receiver]\n";
 if(i>Max_No_Frames)          //if all frames received then disconnect
   Connection=0, cout<<"Connection Closed.\n";
}

void REC_from_physical_layer(Frame *buffer)
{
 *buffer = frame;	// receiver takes data from physical layer
}

void SEND_to_physical_layer(Frame *s)
{
 s->Fault = rand()%8;  //Fault=0 means error and non zero means no error
 frame = *s;           //probability of error = 1/8
}

enum Event_Type
{
    FRAME_SIGNAL,	// frame is there
    ERROR,			// frame is damaged when frame.fault=0
    TIMEOUT,		// acknowledgment not received
    NO_EVENT		// nothing happens
};

void wait_for_event_sender(Event_Type * e)
{
 static int Counter=0;	// to count the timeout
 if(MODE==0)	//when sender mode
  {
   Counter++;
   if(Counter==Time_Out)	//TIMEOUT happened
   {
        *e = TIMEOUT, Counter=0;;
        cout<<"Acknowledgment is not received, TIMEOUT. [Sender]\n";
        return;
   }

   if(!frame.Fault)		//	when frame is damaged ERROR
        *e = ERROR;
   else
        *e = FRAME_SIGNAL,  Counter=0; 		// otherwise frame
  }
}

void wait_for_event_receiver(Event_Type * e)
{
 if(MODE==1)	//when receiver mode
  {
   if(!frame.Fault)
     *e = ERROR;
   else
     *e = FRAME_SIGNAL;
  }
}

void SENDER()
{
 static int Frame_No_to_Send=0; //next frame no to send
 static Frame s;
 int buffer;
 Event_Type event;		//event holder
 static int flag=0;

 if(flag==0)	// only for first frame (since we started from sender mode)
 {
  SEND_from_network_layer(&buffer);		//data fetching from network layer(sender side)
  s.data = buffer;
  s.index = Frame_No_to_Send;	// next frame index
  cout<<"Frame No "<<s.index<<" and Data "<<s.data<<" is sent. [Sender]\n";
  MODE=1;		// receiver mode
  SEND_to_physical_layer(&s);
  flag = 1;
 }

 wait_for_event_sender(&event);

 if(MODE==0)	// when sender mode
  {
   if(event==FRAME_SIGNAL)
    {
      SEND_from_network_layer(&buffer);	//data fetching from network layer(sender mode)
      s.index = ++Frame_No_to_Send;
      s.data = buffer;
      cout<<"Frame No "<<s.index<<" and Data "<<s.data<<" is sent. [Sender]\n";
      MODE=1;
      SEND_to_physical_layer(&s); //data sent to physical layer
    }

	if(event==TIMEOUT)
    {
      cout<<"Resending the Frame. [Sender]\n";
      MODE=1;
      SEND_to_physical_layer(&s);	//data sent to physical layer
    }
  }
}

void RECEIVER()
{
 static int frame_in=0; // frame_in is the expected value of frame no.
 Frame A,B;
 Event_Type E;

 wait_for_event_receiver(&E);

 if(MODE==1)
  {
   if(E==FRAME_SIGNAL)
    {
     REC_from_physical_layer(&A);	// data received from physical layer (receiver mode)
     if(A.index==frame_in)
     {
       REC_to_network_layer(&A.data); // data sent to network layer (receiver side)
       ++frame_in;
     }

	 else
       cout<<"Reacknowledgment is sent. [Receiver]\n";
     MODE=0, SEND_to_physical_layer(&B); // Acknowledgment is received send next frame
    }

	if(E==ERROR)
    {
      cout<<"Frame is Damaged. [Receiver]\n";
      MODE=0;     //frame is damaged Sender should send it again.
    }
  }
}
int main()
{
 while(Connection)
 {
   SENDER();
   RECEIVER();
 }
}
