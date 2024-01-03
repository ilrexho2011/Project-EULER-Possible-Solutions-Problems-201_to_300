#include <stdio.h>
#define Ds 20
#define Ts 10
#define T 70
#define S 12
unsigned long long ans;
unsigned long long f[21];
void dfs(int count,int value,unsigned long long div,int l){
	int i,j;
	if(value>T)return ;
	if(value==T && count<Ts)return;
	if(count==Ds){
		if(value==T){
			ans+=f[Ds]/div;
		}
		return;
	}
	if(count==0){
		for(i=1;i<=S;i++){
			for(j=1;j<=Ds;j++){
				if(j<Ts){
					dfs(j,i*j,f[j],i);
				}else{
					dfs(j,i*Ts,f[j],i);
				}
			}
		}
		return ;
	}
	if(count<Ts){
		for(i=1;i<l;i++)
			for(j=1;j<=Ds-count;j++){
				if(count+j<Ts){
					dfs(count+j,value+i*j,div*f[j],i);
				}else{
					dfs(count+j,value+i*(Ts-count),div*f[j],i);
				}
			}
	}else{
		if(value!=T)return;
		for(i=1;i<l;i++)
			for(j=1;j<=Ds-count;j++)
				dfs(count+j,value,div*f[j],i);
	}
}

int main(){
	f[0]=1;
	int i;
	for(i=1;i<=Ds;i++)f[i]=f[i-1]*i;
	dfs(0,0,0,0);
	printf("%llu\n",ans);
	return 0;
}