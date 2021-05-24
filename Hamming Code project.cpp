

#include<bits/stdc++.h>
using namespace std;

int regular_bit[120];
int regular_received[120];


int improved_bit[120];
int improved_received[120];




int regular_method_parity(int arr[],int n, int sz)
{
    int l=0,cnt=0;

    for(int i=0; i<sz; i++)///for finding parity bit
    {
        int j=pow(2,i);
        int sum=0,track=0;
        int limit=sz+n;

        int k=j;

        while(k<=limit)
        {
            if(track==0)
            {
                for(int c=k; c<k+j && c<=limit; c++)/// operation
                {
                    cnt++;
                    if(arr[c]!=-1)
                    {
                        sum+=arr[c];

                    }

                }

                track=1;

            }
            else
            {
                track=0;
            }


            k=k+j;
        }

        if(sum%2!=0)
        {
            arr[j]=1;
        }
        else
        {
            arr[j]=0;
        }

    }
    return cnt;

}

int improved_get_parity(int arr[],int n, int sz)
{
    int cnt=0;
    int l=n+1;

    for(int i=0; i<sz; i++)///for the starting
    {
        int j=pow(2,i) ;

        int sum=0,track=0,limit,k;

        if(j<=n)
        {
            limit=n;
            k=j;
        }
        else
        {

            limit=n+sz-1;
            k=n+1;

        }


        while(k<=limit)///for parity's operation
        {


            if(track==0)
            {
                for(int c=k; c<k+j && c<=limit; c++)/// operation
                {
                    sum=sum + arr[c];
                    cnt++;
                }

                track=1;

            }
            else
            {
                track=0;
            }

            k=k+j;

        }

        if(sum%2!=0)
        {
            arr[l]=1;
            l++;
        }
        else
        {
            arr[l]=0;
            l++;
        }

    }

    return cnt;
}


int binary_to_decimal(int arr[], int s)
{
    int dec=0;

    for(int i=0; i<s; i++)
    {
        dec+=arr[i]*pow(2,i);
    }
    if(dec==0)
    {
        cout<<"no error\n";
    }
    else
    {
        cout<<"The bit error at position : "<<dec<<endl;

    }
    return dec;

}


int parity_count(int n )
{
    int p=0,sz=0;
    while(true)
    {

        if(pow(2,p)>=n+p+1)
        {
            break;
        }
        else
        {
            p++;
            sz++;
        }

    }
    return sz;
}


void bit_correction(int dec,int arr[] )
{

    if(arr[dec]==0)
    {
        arr[dec]=1;
    }
    else
    {
        arr[dec]=0;
    }
}


int main()
{
    cout<<"////////////////////////  ERROR DETECTION AND CORRECTION BY HAMMING CODE  \\\\\\\\\\\\\\\\\\\\\\\\\ " <<endl;
    cout<<endl<<":::::::::::::CLASSIC HAMMING CODE:::::::::::::"<<endl<<endl;
    int n;
    cout<<"Enter the bit size: ";
    cin>>n;

    int sz=parity_count(n);






    ///SENDING BITS/////////////////////////////

    ///Allocating parity bits
    for(int i=0; i<sz; i++)
    {
        int j=pow(2,i);

        regular_bit[j]=-1;

    }

    ///Allocating bits
    cout<<"\nEnter sending message: ";
    for(int i=sz+n; i>=1; i--)
    {
        if(regular_bit[i]!=-1)
        {
            cin>>regular_bit[i];
        }
    }

    cout<<"Allocated as(regular): ";
    for(int i=sz+n; i>=1; i--)
    {
        cout<<regular_bit[i]<<" ";
    }
    cout<<"\nHere -1 means parity positions";

    cout<<endl;

    regular_method_parity(regular_bit,n,sz);


    cout<<"Sending message with redundancy bits: ";
    for(int i=sz+n; i>=1; i--)
    {
        cout<<regular_bit[i]<<" ";
    }






    ///RECEIVED BITS////////////////////////////////////////

    ///Allocating parity bits
    for(int i=0; i<sz; i++)
    {
        int j=pow(2,i);

        regular_received[j]=-1;

    }
    ///Allocating bits
    cout<<"\n\nEnter receive message: ";
    for(int i=sz+n; i>=1; i--)
    {
        if(regular_received[i]!=-1)
        {
            cin>>regular_received[i];
        }
    }
    cout<<"Allocated as(regular): ";
    for(int i=sz+n; i>=1; i--)
    {
        cout<<regular_received[i]<<" ";
    }

    cout<<endl;


    int cnt=regular_method_parity(regular_received,n,sz);




    ///parity compare
    int regular_p_status[sz+1];
    int s=0;
    for(int i=0; i<sz; i++)
    {
        int j=pow(2,i);

        if(regular_bit[j]!=regular_received[j])
        {
            regular_p_status[s]=1;
            s++;

        }
        else
        {
            regular_p_status[s]=0;
            s++;
        }

    }
    cout<<"\nBinary position: \n ";
    for(int i=s-1; i>=0; i--)
    {

        cout<<regular_p_status[i]<<" ";

    }
    cout<<endl;

    int dec=binary_to_decimal(regular_p_status, s);


    bit_correction(dec,regular_received);///bit correction






    cout<<"\nThe corrected received message: ";
    int c=sz-1;

    int it=n+sz;

    while(it>=1)
    {
        int j=pow(2,c);
        if(j==it)
        {
            it--;
            c--;
        }
        else
        {
            cout<<regular_received[it]<<" ";
            it--;

        }

    }

    cout<<endl<<"Thus a total of " <<cnt<<" bits are involved in the process of Hamming bits calculations. "<<endl<<endl<<endl;




    cout<<endl<<":::::::::::::IMPROVED HAMMING CODE:::::::::::::"<<endl<<endl;

    for(int i=sz+n; i>n; i--)///for redundancy bits
    {
        improved_bit[i]=-1;
    }

    cout<<"\nEnter sending message: ";
    for(int i=n; i>=1; i--)
    {
        cin>>improved_bit[i];
    }


    cout<<"Allocated as(improved): ";
    for(int i=n+sz; i>=1; i--)
    {
        cout<<improved_bit[i]<<" ";
    }
    cout<<"\nHere -1 means parity positions";


    improved_get_parity(improved_bit,n,sz);///function call

    cout<<"\nSending message with redundancy bits: ";
    for(int i=n+sz; i>=1; i--)
    {
        cout<<improved_bit[i]<<" ";
    }







    cout<<"\n\nEnter received message: ";
    for(int i=sz+n; i>n; i--)///for redundancy bits
    {
        improved_received[i]=-1;
    }


    for(int i=n; i>=1; i--)
    {
        cin>>improved_received[i];
    }

    int cnt2=improved_get_parity(improved_received,n,sz);///function call

    cout<<"Allocated as(improved): ";
    for(int i=n+sz; i>=1; i--)
    {
        cout<<improved_received[i]<<" ";
    }




    ///now parity comp
    int p_status[sz+1];

    int s2=0;
    for(int i=n+1; i<=sz+n; i++)
    {
        if(improved_bit[i]!=improved_received[i])
        {
            p_status[s2]=1;
            s2++;

        }
        else
        {
            p_status[s2]=0;
            s2++;
        }
    }



    cout<<"\n\nBinary position: \n ";
    for(int i=s2-1; i>=0; i--)
    {

        cout<<p_status[i]<<" ";

    }
    cout<<endl;


    int decimal=0;

    for(int i=0; i<s2; i++)
    {
        decimal+=p_status[i]*pow(2,i);
    }
    if(decimal==0)
    {
        cout<<"no error\n";
    }
    else
    {
        cout<<"The bit error at position : "<<decimal<<endl;

    }

    bit_correction(decimal,improved_received);



    cout<<"\nThe corrected received message: ";
    for(int i=n; i>=1; i--)
    {
        cout<<improved_received[i]<<" ";
    }
    cout<<endl<<"Thus a total of " <<cnt2+sz <<" bits are involved in the process of Hamming bits calculations. "<<endl;








}
















