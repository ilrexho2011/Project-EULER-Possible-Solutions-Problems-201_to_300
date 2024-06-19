#include <stdio.h>
#include <math.h>
#include <vector>
#include <utility>
#include <map>
using namespace std;
map< pair<vector<int>,int>,double> hashed;

double ffabs(int x)
{
  if(x<0)
    return -(double)x;
  else
    return (double)x;
}
int N;
int label[12];

vector <int> LARRY(vector <int> &a,int &n,int &there)
{
  vector <int> an;
    if(there)//reorder
	{
	  //printf("comes here\n");
	  an.push_back(n);
	  for(int i=0;i<a.size();i++)
	    if(a[i]!=n)
	      an.push_back(a[i]);
	}
      else
	{
	  //printf("sdfs\n");
	  an.push_back(n);
	  //printf("n=%d\n",n);
	  for(int i=0;i<min(4,(int)a.size());i++)
	    {
	      //printf("sdfs %d\n",a.size()-1);
	      an.push_back(a[i]);
	    }
	  // printf("sdfsdf\n");
	  
	}
    return an;
}

vector <int> ROBIN(vector <int> &b,int &n,int &there)
{
  vector <int> bn;

      if(there)//no change in order
	{
	  bn=b;
	}
      else
	{
	  bn.push_back(n);
	  for(int i=0;i<min(4,(int)b.size());i++)
	    bn.push_back(b[i]);
	}
      return bn;
      
}


void relabel(vector <int> &an,vector <int> &bn)
{
  
    
     for(int i=1;i<=10;i++)
	label[i]=-1;
      int ct=1;
      for(int i=0;i<an.size();i++)
	{
	  label[an[i]]=ct;
	  an[i]=(ct++);
	}
      for(int i=0;i<bn.size();i++)
	{
	  if(label[bn[i]]!=-1)
	    {
	      bn[i]=label[bn[i]];
	    }
	  else
	    {
	      label[bn[i]]=ct;
	      bn[i]=(ct++);
	    }
	}
}


double findit(vector <int> &a,vector <int> &b,int d,int Nm)
{
  pair<vector<int>,int> hashval= make_pair(b,((d+102)*102+Nm)*10+(int)(a.size()));
  if(hashed.find(hashval)!=hashed.end())
    return hashed[hashval];
 
  if(Nm==N)
    {
      return ffabs(d);
    }
  double retval=0;
  for(int n=1;n<=10;n++)
    {
      int sc1=0;int sc2=0;
    

      //see if n is there in a
      for(int i=0;i<a.size();i++)
	if(a[i]==n)
	  {
	    sc1=1;
	    break;
	  }
      for(int i=0;i<b.size();i++)
	if(b[i]==n)
	  {
	    sc2=1;
	    break;
	  }
      vector <int> an=LARRY(a,n,sc1);
      vector <int> bn=ROBIN(b,n,sc2);
      relabel(an,bn);
	  


      retval+=0.1*findit(an,bn,d+sc1-sc2,Nm+1);


    }
  hashed[hashval]=retval;
  return retval;
}

int main()
{


  printf("%1.10f\n",findit(a,b,0,0));
  
}