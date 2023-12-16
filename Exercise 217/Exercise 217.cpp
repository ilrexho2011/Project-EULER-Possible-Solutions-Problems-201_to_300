#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL>PII;
const int maxn = 150000000;
const int mod = 243*243*243;
const int level = 500;
int len,center;
LL dp[50][1024];
LL ANS[50][1024];
LL p[50],ret;
PII dfs(int pos,int sum,bool first){
    if(pos==0){
        return PII((sum==level),0);
    }
    if(~dp[pos][sum]){
        return PII(dp[pos][sum],ANS[pos][sum]);
    }
    int st=first?1:0;
    LL &ans=dp[pos][sum],&ret=ANS[pos][sum];
    ret=ans=0;

    int sign=0;
    for(int i=st;i<10;++i){
        if(len&1){
            sign=pos>center?1:-1;
        }else{
            if(pos^center){
                sign=pos>center?1:-1;
            }else{
                sign=0;
            }
        }
        PII tmp=dfs(pos-1,sum+sign*i,false);
        ans+=tmp.first;
        ret+=p[pos-1]*i*tmp.first+tmp.second;
        ans%=mod;
        ret%=mod;
    }
    return PII(ans,ret);
}
int main(){
    ios_base::sync_with_stdio(false);
    p[0]=1;
    for(int i=1;i<50;++i){
        p[i]=p[i-1]*10%mod;
    }
    LL ans=0,cnt=0;
    PII tmp;
    for(int i=1;i<48;++i){
        center=(i+1)>>1;
        len=i+1;
        memset(dp,-1,sizeof(dp));
        ret=0;
        tmp=dfs(i,level,true);
        cnt+=tmp.first;
        ans+=tmp.second;
        cnt%=mod;
        ans%=mod;
    }
    cout<<ans<<" "<<cnt<<endl;
    return 0;
}