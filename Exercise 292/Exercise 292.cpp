#include<iostream>
#include<map>
#define N 120
using namespace std;

int sqrt[10000];
int z;
long long ans = 0;

map <int , long long> MEM;

struct vector
{
    int x , y , len , type;
    int operator *(vector u)
    {
        return x * u.y - y * u.x;
    }
}V[10000];

int gcd(int a , int b)
{
    if(a * b == 0)
        return a + b;
    return gcd(b , a % b);
}

int cmp(const void *a , const void *b)
{
    vector A = *(vector*)a;
    vector B = *(vector*)b;
    if(A.type != B.type)
        return A.type - B.type;
    return - (A * B);
}

int hash(int a , int b , int c , int d , int e)
{
    int ret = 0;
    a += N;
    b += N;
    e --;
    ret += a * (2 * N + 1) * (N + 1) * (z + 1) * 3;
    ret += b * (N + 1) * (z + 1) * 3;
    ret += c * (z + 1) * 3;
    ret += d * 3;
    ret += e;
    return ret;
}

long long f(int x , int y , int leftsum , int lastuse , int diff)
{
    if(leftsum < 0)
        return 0;
    if(diff > 3)
        diff = 3;
    if(x * x + y * y > leftsum * leftsum)
        return 0;
    if(x == 0 && y == 0)
    {
        if(diff == 3)
            return 1;
        return 0;
    }
    else
    {
        int H = hash(x , y , leftsum , lastuse , diff);
        if(MEM.count(H))
            return MEM[H];
        long long ret = 0;
        for(int i = lastuse ; i <= z ; i++)
            ret += f(x + V[i].x , y + V[i].y , leftsum - V[i].len , i , diff + (i > lastuse));
        MEM[H] = ret;
        return ret;
    }
}

int main()
{
    memset(sqrt , 0 , sizeof(sqrt));
    for(int i = 1 ; i <= N / 2 ; i++)
        sqrt[i * i] = i;
    z = 0;
    for(int i = -(N / 2) ; i <= N / 2 ; i++)
        for(int j = -(N / 2) ; j <= N / 2 ; j++)
            if(sqrt[i * i + j * j] && gcd(abs(i) , abs(j)) == 1)
            {
                z++;
                V[z].x = i;
                V[z].y = j;
                V[z].len = sqrt[i * i + j * j];
                if(j < 0)
                    V[z].type = 4;
                if(j > 0)
                    V[z].type = 2;
                if(j == 0)
                {
                    if(i > 0)
                        V[z].type = 1;
                    if(i < 0)
                        V[z].type = 3;
                }
            }
    qsort(V + 1 , z , sizeof(V[0]) , cmp);
    for(int i = 1 ; i <= z ; i++)
        ans += f(V[i].x , V[i].y , N - V[i].len , i , 1);
    cout<<ans<<endl;
    return 0;
}