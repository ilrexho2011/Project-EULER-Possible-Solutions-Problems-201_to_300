#include<iostream>
using namespace std;

long long MOD = 1000000000LL;
long long S[630][630] , T[630][630] , tem[630][630];

void TT()
{
    for(int i = 0 ; i < 552 ; i++)
        for(int j = 0 ; j < 552 ; j++)
        {
            tem[i][j] = 0;
            for(int k = 0 ; k < 552 ; k++)
                tem[i][j] = (tem[i][j] + T[i][k] * T[k][j]) % MOD;
        }
    for(int i = 0 ; i < 552 ; i++)
        for(int j = 0 ; j < 552 ; j++)
            T[i][j] = tem[i][j];
}

void ST()
{
    for(int i = 0 ; i < 552 ; i++)
        for(int j = 0 ; j < 552 ; j++)
        {
            tem[i][j] = 0;
            for(int k = 0 ; k < 552 ; k++)
                tem[i][j] = (tem[i][j] + S[i][k] * T[k][j]) % MOD;
        }
    for(int i = 0 ; i < 552 ; i++)
        for(int j = 0 ; j < 552 ; j++)
            S[i][j] = tem[i][j];
}

void power(long long b)
{
    while(b)
    {
        if(b % 2 == 1)
            ST();
        TT();
        b /= 2;
    }
}

int main()
{
    memset(S , 0 , sizeof(S));
    memset(T , 0 , sizeof(T));
    for(int i = 0 ; i < 576 ; i++)
        S[i][i] = 1;
    for(int left = 0 ; left < 23 ; left ++)
        for(int sum = 0 ; sum <= 23 ; sum ++)
        {
            for(int i = 0 ; i <= 9 ; i++)
                if(sum + i <= 23)
                    T[left * 24 + sum][((left * 10 + i) % 23) * 24 + sum + i] ++;
        }
    power(3138428376721LL);
    cout<<S[0][23]<<endl;
    return 0;
}