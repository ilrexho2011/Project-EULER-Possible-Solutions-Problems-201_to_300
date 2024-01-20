#include<bits/stdc++.h>

#define MAX 100000
#define ll long long

using namespace std;

bool sieveprime[MAX/2+5];
ll prime[9600];

void precalc_prime()
{
	int MAX_2=MAX/2+3,k=1;
	
	for(int i=1;i<=MAX_2;i++)
		sieveprime[i]=0;
	
	for(int i=3;i*i<MAX;i+=2)
		if(!sieveprime[i/2])
			for(int j=i*i;j<=MAX;j+=2*i)
				sieveprime[j/2]=1;
				
	prime[0]=2;
	for(int i=3;i<MAX;i+=2) if(!sieveprime[i/2]) prime[k++]=i;
}

bool comp(ll a,ll b) { return a>b;}

ll kkkk;
ll mem[15][2];

ll check(ll x)
{
	if(x==2) return 1; if(x%2==0) return 0;
	if(x<MAX){
		 if(!sieveprime[x/2]) return 1;
		 else return 0;
	}
	int k=-1;
	while(prime[++k]*prime[k]<=x) if(x%prime[k]==0) return 0;
	return 1;
}

void solve(ll prev,ll start,ll end,ll *list)
{
	if(start==end){
		if(check(prev+1)) list[kkkk++]=prev; return;
	}
	ll x=1;
	for(int i=0;i<=mem[start][1];i++){
		solve(prev*x,start+1,end,list);
		x*=mem[start][0];
	}
}

void get_divisor_list(ll *list,ll n)
{
	int k=-1,curr=-1;
	for(int i=0;i<10;i++) mem[i][1]=0;
	
	while(prime[++k]*prime[k]<=n){
		if(n%prime[k]==0) mem[++curr][0]=prime[k];
		while(n%prime[k]==0){
			n/=prime[k];mem[curr][1]++;
		}
	}
	if(n!=1){
		mem[++curr][0]=n;mem[curr][1]++;
	}
	curr++;kkkk=0;
	solve(1,0,curr,list);
	sort(list,list+kkkk,comp);
}

struct node
{
	map<ll,bool> present;
	vector<ll> inverse_list;
	
	void add(ll x){
		if(present[x]) return;
		
		present[x]=1;
		inverse_list.push_back(x);
	}
	
	void arrange(){
		sort(inverse_list.begin(),inverse_list.end());
	}
} ;

map< ll , node > memoise;
map< ll , bool > store;

node empty;

void precomp()
{
	precalc_prime();
	node inv1,inv2;
	inv1.add(1); inv1.add(2); inv2.add(3); inv2.add(4); inv2.add(6);
	memoise[1]=inv1; memoise[2]=inv2;
	empty.add(-1);
}

node find(ll n)
{
	if(n<=2) return memoise[n];
	if(n%2!=0) return empty;
	if(store[n]) return memoise[n];
	
	node mainans;
	
	ll list[2000];
	get_divisor_list(list,n);
	ll cnt=kkkk;
	
	for(ll i=0;i<cnt;i++){
		ll p=list[i]+1,cpp=p,d=p-1;
		
		while(n%d==0){
			
			node ans;
			if(d!=1){
				
				ans=find(n/d);
				if(ans.inverse_list[0]==-1) {d*=p;cpp*=p;continue;}
				else{
					ll s=ans.inverse_list.size();
					for(ll j=0;j<s;j++)
						if(__gcd(ans.inverse_list[j],p)==1) mainans.add(cpp*ans.inverse_list[j]);
				}
			}
			cpp*=p;d*=p;
		}
	}
	
	if(mainans.inverse_list.empty()) memoise[n]=empty;
	else memoise[n]=mainans;
	store[n]=1;
	return memoise[n];
}

int main()
{
	precomp();
	node ans=find(6227020800LL);
	ans.arrange();
	cout<<ans.inverse_list[149999];
}