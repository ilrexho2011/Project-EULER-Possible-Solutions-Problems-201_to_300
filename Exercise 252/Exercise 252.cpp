#include <stdio.h>
#define max 500
int x[max],y[max];
int spat[max][max][max],tri[max][max][max],line[max][max];

int maxarea=0;

int p[max];

// k collinear (strictly) between i and j ?
inline int between(int i, int j, int k) {
  if (spat[i][j][k]!=0) return 0;
  if (x[i]<x[j]) return x[i]<x[k]&&x[k]<x[j]; 
  if (x[i]>x[j]) return x[i]>x[k]&&x[k]>x[j]; 
  if (y[i]<y[j]) return y[i]<y[k]&&y[k]<y[j]; 
  if (y[i]>y[j]) return y[i]>y[k]&&y[k]>y[j]; 
  return 0;
}

void triangular_holes() {
  int i,j,k,l;
  for (i=0;i<max;i++) for (j=0;j<max;j++) for (k=0;k<max;k++) 
    tri[i][j][k]=(spat[i][j][k]>0);

  for (i=0;i<max;i++) for (j=i+1;j<max;j++) for (k=i+1;k<max;k++) {
    if (tri[i][j][k]) {
      for (l=0;l<max;l++)
        if (spat[i][j][l]>0 && spat[j][k][l]>0 && spat[k][i][l]>0) {
          tri[i][j][k]=0;
          //tri[j][k][i]=0;
          //tri[k][i][j]=0;
          break;
        }
      if (l==max); // todo: cancel all triangles that contain (i,j,k)
    }
  }
}

void add_triangle(int level, int area) {
  int i=p[0],j=p[1],k=p[level-1],l=p[level],m;
  if (line[i][l] || level==1)
    for (m=i+1;(p[level+1]=m)<max;m++) 
      if (tri[i][l][m] && spat[i][j][m]>0 && spat[k][l][m]>0)
        add_triangle(level+1,area+spat[i][l][m]);
  if (area>maxarea) {
    printf("area=%.1f\n",(maxarea=area)/2.0);
    maxarea=area;
  }
}


int main() {
  unsigned long long s=290797;
  int t, dx,dy, i,j,k,l;
  for (i=0;i<2*max;i++) {
    t=(s=(s*s)%50515093)%2000-1000;
    if (i%2) y[i/2]=t; else x[i/2]=t;
    if (i%2) printf("%d: (%d,%d)\n",i/2,x[i/2],y[i/2]);
  }
  for (i=0;i<max;i++) for (j=i;j<max;j++) {
    dx=x[j]-x[i];
    dy=y[j]-y[i];
    s=-dy*x[i]+dx*y[i];
    line[i][j]=line[j][i]=(i<j);
    for (k=0;k<max;k++) {
      spat[j][i][k]=-(spat[i][j][k]=-dy*x[k]+dx*y[k]-s);
      if (between(i,j,k)) line[i][j]=line[j][i]=0;
    }
  }
  
  triangular_holes();
  int ntri=0,ntri2=0; 
  for (i=0;i<max;i++) for (j=0;j<max;j++) for (k=0;k<max;k++) {
    ntri+=tri[i][j][k];
    if (i<j&&i<k) ntri2+=tri[i][j][k]; 
  }
  printf("%d triangular holes\n",ntri);
  printf("%d ordered triangular holes\n",ntri2);
  
  for (i=0;i<max;i++) for (j=i+1;j<max;j++) {
    p[0]=i;p[1]=j;add_triangle(1,0);
  }
}