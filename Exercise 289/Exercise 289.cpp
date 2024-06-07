#include<stdio.h>
#include<string.h>
#define rows 6 
#define cols 10 
#define mod 10000000000ll

char stars[14][8],starscount=0/*14*/;
char tops[2][8]={{3,-1,-1,0,-1,6,5,-1},{6,-1,-1,5,-1,3,0,-1}};
char bottoms[2][8]={{-1,2,1,-1,7,-1,-1,4},{-1,7,4,-1,2,-1,-1,1}};
char op[rows+1][8];
long long int columnscount=0;
char lefts[1<<(rows-1)][4*rows];
char rights[1<<(rows-1)][4*rows];
char parts[200][4*rows];
int leftscount=0,rightscount=0,partscount=0;
int pmat[200][200];
long long int p1[200],p2[200];

create_stars(int todo,char*c,char lastx){
  int x,y;
  if(todo==0){
    memcpy(stars[starscount++],c,8);
    return;
  }
  x=lastx+1;while(c[x]!=-1)x++;for(y=x+1;y<8&&(c[y]==-1);y+=2){
    c[x]=y;c[y]=x;
    create_stars(todo-1,c,x);
    c[x]=-1;c[y]=-1;
  }
}
create_lefts(int todo,char*l,char lastx){
  int x,y;
  if(todo==0){
    memcpy(lefts[leftscount++],l,4*rows);
    return;
  }
  x=lastx+1;while(l[x]!=-1)x++;for(y=x+1;y<2*rows&&(l[y]==-1);y+=2){
    l[x]=y;l[y]=x;
    if(y>x+1){l[y-2]=y-1;l[y-1]=y-2;}
    create_lefts(todo-1-(y-x-1)/2,l,x);
    l[x]=-1;l[y]=-1;
  }
  for(x;x<=y;x++)l[x]=-1;
}
create_parts(int todo,char*p,char lastx){
  int x,y;
  if(todo==0){
    memcpy(parts[partscount++],p,4*rows);
    return;
  }
  x=lastx+1;while(p[x]!=-1)x++;

  for(y=x+1;y<2*rows&&(p[y]==-1);y+=2){
    p[x]=y;p[y]=x;
    create_parts(todo-1,p,x);
    p[x]=-1;p[y]=-1;
  }
}
create_column(){
  int i,j,from,to,dist=0;
  char column[4*rows],p[4*rows];
  for(i=0;i<4*rows;i++)column[i]=-1;
  for(i=0;i<4*rows;i++)if(column[i]==-1){
    j=i;if(j>=2*rows)j-=2*rows;
    j=(j+1)/2;
    if(j==0)from=0;else if(j==rows)from=7;else from=(i&1)?0:7;
    if(i>=2*rows)from=(from==0)?3:4;
    while(1){
      to=op[j][from];
      dist+=2;
      if(to==5||to==6){from=7-to;j++;}
      else if(to==1||to==2){from=7-to;j--;}
      else break;
    }
    j=2*j-(to==0||to==3);if(j<0)j++;if(j==2*rows)j--;
    if(to==3||to==4)j+=2*rows;
    column[i]=j;
    column[j]=i;
    if(i==j)break;
  }
  if(dist==8*rows){
    columnscount++;
    for(i=0;i<partscount;i++){
      if(apply_column_to_left(column,parts[i],p)){
        int k=find_part(p);
        if(k==-1){printf("HM\n");fflush(stdout);}
        pmat[k][i]++;
      }
    }
  }
}
create_operators(int pos){
  char (*choice)[8],choicecount,i;
  if(pos>rows){create_column();return;}
  if (pos==0){choice=tops;choicecount=2;}
  else if (pos<rows){choice=stars;choicecount=starscount;}
  else {choice=bottoms;choicecount=2;}
  for(i=0;i<choicecount;i++) {
    memcpy(op[pos],choice[i],8);
    if(pos>0){
      if(op[pos-1][5]==6&&op[pos][1]==2)continue;
    }
    create_operators(pos+1);
  }
}
apply_column_to_left(char*c, char*l,char*p){
  char x,y,i;
  for(i=0;i<2*rows;i++){p[i]=c[i];p[i+2*rows]=-1;}
  for(i=2*rows;i<4*rows;i++){
    x=i;while(x>=2*rows){x=c[l[x-2*rows]+2*rows];if(x==i)return 0;/*loop*/}
    y=c[i];while(y>=2*rows)y=c[l[y-2*rows]+2*rows];
    p[x]=y;
    p[y]=x;
  }
  return 1;
}
match_left_right(char*l,char*r){
  char i=0,steps=0;
  while(++steps){
    i=l[r[i+2*rows]-2*rows];
    if(!i)return(steps==rows);
  }
}
find_part(char *p){
  int i,j,ok=1;
  for(i=0;i<partscount;i++){
    ok=1;
    for(j=0;j<2*rows;j++)
      if(p[j]!=parts[i][j]){ok=0;break;}
    if(ok) return i;
  }
  return -1;
}

int main() {
  char c[8],l[4*rows],*r;
  int i,j,k;
  long long int solutions=0;
  for(i=0;i<8;i++)c[i]=-1;
  for(i=0;i<4*rows;i++)l[i]=-1;
  create_stars(4,c,-1);
  printf("%d stars\n",starscount);
  create_lefts(rows,l,-1);
  printf("%d lefts\n",leftscount);
  for(i=0;i<4*rows;i++)l[i]=-1;
  create_parts(rows,l,-1);
  printf("%d parts\n",partscount);

  for(i=0;i<leftscount;i++){
    r=rights[rightscount++];
    for(j=0;j<2*rows;j++)r[j]=-1;
    for(j=0;j<2*rows;j++)r[j+2*rows]=lefts[i][j]+2*rows;
  }

  for(i=0;i<100;i++)for(j=0;j<100;j++)pmat[i][j]=0;

  create_operators(0);
  printf("%lld columns\n",columnscount);

  for(i=0;i<partscount;i++){p1[i]=0;p2[i]=0;}

  for(i=0;i<leftscount;i++)
    p1[find_part(lefts[i])]++;

  for(i=0;i<cols-1;i++){
    for(j=0;j<partscount;j++){
      p2[j]=0;
      for(k=0;k<partscount;k++){
        p2[j]+=pmat[j][k]*p1[k];
        while(p2[j]>mod)p2[j]-=mod;
      }
    }
    for(j=0;j<partscount;j++)p1[j]=p2[j];
  }

  solutions=0;
  for(i=0;i<partscount;i++)for(j=0;j<rightscount;j++)
    if (match_left_right(parts[i],rights[j])) {
      solutions+=p1[i];
      while(solutions>mod)solutions-=mod;
    }
  printf("%lld solutions\n",solutions);
}