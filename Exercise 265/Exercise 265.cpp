#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    unsigned long int n,sum1=67108865,sum2=0,sum3=0;
    int d[32],test[32],check=2,check2,check3=0;
    d[0]=d[1]=d[2]=d[3]=d[4]=0,d[31]=d[5]=1; 
    for(unsigned long int i=1;i<=33554431;i++)
    {
        n=i;
        while(n!=0)
        {
            if(n%2==1)
            { check++; }
            n=n/2;
        }
        if(check==16)
        {
            n=i;
            for(int j=6;j<=30;j++)
            {
                d[j]=n%2;
                n=n/2;
            }
            for(int k=2;k<=31;k++)
            { test[k]=1; }
            test[16]=0;
            for(int l=2;l<=30;l++)
            {
                check2=d[l]+d[(l+1)%32]*2+d[(l+2)%32]*4+d[(l+3)%32]*8+d[(l+4)%32]*16;
                test[check2]--;
            }    
            for(int m=2;m<=30;m++)
            {
                if(test[m]!=0)
                { check3++; }
            }
            if(check3==0)
            {
                for(int q=6;q<=30;q++)
                {
                    sum1=sum1+d[q]*int(pow(2.0,31.0-double(q)));
                }
                sum2=sum2+sum1;
                sum1=67108865;
                sum3=sum3+sum2/1000000000;
                sum2=sum2%1000000000; 
            }
            check3=0;
        }
        check=2;
    }
    cout<<"result = "<<sum3<<" 10^9 + "<<sum2<<endl;
    system("pause");
    return 0;
}    