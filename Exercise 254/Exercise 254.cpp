#include <iostream>
#include <vector>

using namespace std;

const int64_t NINEFACT=362880;

int64_t pow(int64_t base,int64_t exp)
{
    if(exp==1) return base;
    int64_t x,result;
    x=pow(base,exp/2);
    result=x*x;
    if(exp%2==1) result*=base;
    return result;
}

class factBaseComp // factorial base composition
{
    public:
    vector<int64_t> h;  // h(i) as defined in WriteLatex file
    int64_t digits;

    factBaseComp()
    {
        h.assign(9,0);
        digits=0;
    }

    factBaseComp(int64_t num)
    {
        int64_t i;
        digits=0;
        for(i=2;i<=9;i++)
        {
            h.push_back(num%i);
            digits+=h.back();
            num/=i;
        }
        h.push_back(num);
        digits+=num;
    }

    bool operator<(factBaseComp b)
    {
        int i;
        if(digits!=b.digits)
        {
            if(digits<b.digits) return true;
            return false;
        }
        for(i=0;i<9;i++) if(h[i]!=b.h[i])
        {
            if(h[i]>b.h[i]) return true;
            return false;
        }
        return false;
    }

};

int main()
{
    int64_t sum=3;  // includes i=1 and 2
    int64_t i,j,k,temp;
    vector<int64_t> f; // as in f(i)
    factBaseComp min,curr;
    for(i=72;i<=150;i++)
    {
        temp=(i%9+1)*pow(10,i/9)-1;
        for(j=2;j<=9;j++)
        {
            sum+=temp%j*(j-1);
            temp/=j;
        }
        sum+=temp*9;
    }
    f.assign(8,0);
    // cout << "checkpoint" << endl;
    for(i=3;i<=71;i++)
    {
        //cout << i << endl;
        // Start with smallest number whose digits sum to i
        for(j=1;j<=i/9;j++) f[8-j]=9;
        f[8-j]=i%9;
        while(j<8)
        {
            j++;
            f[8-j]=0;
        }
        temp=0;
        for(j=0;j<8;j++) temp=temp*10+f[j];
        min=factBaseComp(temp);
        do
        {
            // Now find the next smallest number
            j=7;
            while(f[j]==0) j--;
            temp=-1;
            do
            {
                temp+=f[j];
                j--;
                if(j<0) break;
            } while(f[j]==9);
            if(j<0) break;  // Next smallest number is too big
            f[j]++;
            for(k=1;k<=temp/9;k++) f[8-k]=9;
            f[8-k]=temp%9;
            k++;
            while((8-k)>j)
            {
                f[8-k]=0;
                k++;
            }
            temp=0;
            for(j=0;j<8;j++)
            {
                temp=temp*10+f[j];
             //   cout << f[j];
            }
            //cout << endl;
            // verify in bounds
            if(temp>min.digits*NINEFACT) break;
            curr=factBaseComp(temp);
            if(curr<min)
            {
                min=curr;
                if(min.digits==1) break;  // Can't do better than a single digit
            }
        } while(true);
        for(j=0;j<9;j++) sum+=(j+1)*min.h[j];
    }
    cout << sum << endl;
    return 0;
}