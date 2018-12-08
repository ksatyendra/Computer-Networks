#include<cstdlib>
#include<iostream>
#define Pipeline_Size 16
#define Max_No_of_Frames 1000
using namespace std;
class Head
{
    private:

    int Data[Max_No_of_Frames], Pipeline[Pipeline_Size], Bits_Sent,
        Bits_Received, No_of_bits_to_send;

    public:

    Head()
    {
        Bits_Sent=Bits_Received=0;
    }
    void Scan()
    {
        int No_of_Bits,No_of_Frames;
        cout<<"Enter the no of bits : ";
        cin>>No_of_Bits;
        No_of_Frames = 2<<(No_of_Bits-1);
        No_of_bits_to_send = No_of_Frames/2;
        for(int j=0, Frame_No=0 ; j<Max_No_of_Frames ; Frame_No%=No_of_Frames)
            Data[j++]=Frame_No++;
        Event_Send(No_of_Frames);
    }

    void Event_Send(int Frames_Send)
    {
        cout <<"\nSender Message :\n";
        for (int k=0,i=Bits_Sent ; i<Bits_Sent+No_of_bits_to_send ; )
        {
            Pipeline[k]=Data[i++];
            cout<<"\nFrame No. "<<Pipeline[k++]<<" is sent.";
        }
        Event_Receive(Frames_Send);
    }
    void  Event_Receive(int Frames_Received)
    {
         int Trans_Error,Lost_Index,Ack_Lost_Prob,Damage;
         bool cont;
         cout <<"\n\nReceiver Message :\n";
         Trans_Error = rand() % 5; // probability of transmission error = 1/5

         /* We have assumed if Trans_Error=0 then transmission error happened
         otherwise we received data correctly. */

         if(Trans_Error!=0)
         {
            for (int i=0 ; i<No_of_bits_to_send ; i++)
            {
                if (Bits_Received == Pipeline[i])
                {
                    cout <<"\nFrame No. "<<Pipeline[i]<<" is received correctly.";
                    ++Bits_Received;
                    Bits_Received%=Frames_Received;
                }
                else
                    cout << "\nDuplicate Frame No. "<<Pipeline[i]<<" is received thus discarded.";
            }
            Ack_Lost_Prob = rand() % 20;

            /* We have assumed if Ack_Lost_Prob is between 0 and 5 then acknowledgments
            are lost otherwise we received all acknowledgments correctly. */

            if (Ack_Lost_Prob>=0 && Ack_Lost_Prob<5)
            {
                cout << "\nAcknowledgment "<<Pipeline[Ack_Lost_Prob]<<" and all Acknowledgments after this are lost.";
                Bits_Sent = Pipeline[Ack_Lost_Prob];
            }
            else
                Bits_Sent=(Bits_Sent+No_of_bits_to_send)%Frames_Received;
         }
         else
         {
            Lost_Index=rand()%No_of_bits_to_send;

            // Lost_Index is the index of the frame being lost.

            for (int i = 0 ; i < Lost_Index ; i++)
            {
                if (Bits_Received == Pipeline[i])
                {
                    cout<<"\nFrame No. "<<Pipeline[i]<<" is received correctly.";
                    ++Bits_Received;
                    Bits_Received%=Frames_Received;
                }
                else
                    cout<<"\nDuplicate frame "<<Pipeline[i]<<" is received thus discarded.";
            }

            Damage = rand() % 2;
            // If Damage == 0 Frame damaged otherwise Frame lost.
            if(!Damage)
                cout <<"\nFrame No. "<<Pipeline[Lost_Index]<<" is damaged.";
            else
                cout <<"\nFrame No. "<<Pipeline[Lost_Index]<<" is lost.";
            for (int i=Lost_Index+1;i<No_of_bits_to_send; i++)
                cout << "\nFrame  No. "<<Pipeline[i]<<" is received thus discarded.";
            cout<<"\nSender's Timeout thus Resend the Frame.";
            Bits_Sent = Pipeline[Lost_Index];
         }
         cout << "\nEnter 1 to continue or 0 to abort : ";
         cin >> cont;
         if (cont == 1)
            Event_Send(Frames_Received);
         else
            exit(0);
    }
};
int  main()
{
    Head Go_Back_N;
    Go_Back_N.Scan();
}
