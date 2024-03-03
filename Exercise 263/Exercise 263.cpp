#include<iostream>
#include<vector>

using namespace std;

#define REP(i, n) for(int i=0;i<n;i++)

typedef long long Int;

vector<Int> pi;

const Int PMAX=10000000ll;

void make_pi(){
    pi.push_back(2);
    for(Int n=3;n<PMAX;n+=2){
        const int s=pi.size();
        bool found=false;
        REP(i, s){
            Int p=pi[i];
            if(p*p>n)break;
            if(n%p==0){
                found=true;
                break;
            }
        }
        if(not found){
            pi.push_back(n);
        //    cout<<n<<endl;
        }
    }
}

bool is_prac(Int n){
    Int s=1;
    if(n%2!=0)return false;
    while(n%2==0){
        Int s1=1;
        while(n%2==0){
            n/=2;
            s1*=2;
            s1+=1;
        }
        s*=s1;
    }
    for(int i=1;i<pi.size();i++){
        if(n==1)return true;
        const Int p=pi[i];
        if(p>s)return false;
        if(n%p==0){
            Int s1=1;
            while(n%p==0){
                n/=p;
                s1*=p;
                s1+=1;
            }
            s*=s1;
        }
    }
    if(n>1){
        //n:prime
        if(n>s)return false;
        else return true;
    }
}

const Int MAX=1000000000000ll;

bool is_prime(const Int n){
    for(int i=0;;i++){
        const Int p=pi[i];
        if(p*p>n)return true;
        if(n%p==0)return false;
    }
}

int main(){
    make_pi();
    Int s=0;
    int ct=0;
    for(Int n=20;n<=MAX;n+=20){
        if(is_prac(n-8) and is_prac(n-4) and is_prac(n) 
            and is_prac(n+4) and is_prac(n+8)){
            cout<<"prac: "<<n<<endl;
            if(is_prime(n-9) and is_prime(n-3) and
                is_prime(n+3) and is_prime(n+9)){
                if((not is_prime(n-7) and (not is_prime(n-5))
                    and (not is_prime(n-1)) and (not is_prime(n+1))
                    and (not is_prime(n+5)) and (not is_prime(n+7)))){
                    s+=n;
                    ct++;
                    cout<<"complete: "<<n<<" "<<s<<" "<<ct<<endl;
                }
            }
        }
    }
    return 0;
}