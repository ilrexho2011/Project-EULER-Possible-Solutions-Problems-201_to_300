#include <iostream>
using namespace std;
__int64 finale(string s)
{
    bool flag=0;
    for(__int64 t=1;t<1000000000; t++)
    {
                __int64 n=t;
            for(__int64 i=s.length()-1; i>=0; i--)
            {
                    if(s[i]=='d')
                    {
                                 if(n%2)
                                 {
                                        //good
                                        n=(3*n+1)/2;
                                 }
                                 else
                                        break;
                    }
                    if(s[i]=='D')
                    {
                                 //everything is ok
                                 n*=3;
                    }
                    if(s[i]=='U')
                    {
                                 if((n-2)%4==0)
                                 {
                                        n=(3*n-2)/4;
                                 }
                                 else
                                        break;
                    }
                    if(i==0 && n>1000000)
                    {
                               if(n<0)
                                      return -1;
                            cout<<n<<"\t"<<t<<endl;
                            
//                             return n;
                    }
            }
    }
    return 0;
}

int main()
{
    cout<<finale("UDDDUdddDDUDDddDdDddDDUDDdUUDd");
    return 0;
}