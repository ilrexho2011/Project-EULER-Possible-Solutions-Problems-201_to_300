#include <stdio.h>
#include <math.h>


#define N 100000
#define LIMITR (N*5000)

#define PN 500000
int prime_search[PN+1];
int prime_t[PN/5];
int primen=0;

int prime5[PN/5];
int primen5=0;
int prime52[PN/5][2];

double answer = 0;

typedef struct _Point {
  int x;
  int y;
} Point;

Point pp[100000];
int pn;


void make_primetable();
void calc_radius0 ();
void calc_radius(int nth, int min, int r);
void calc_point(int nth, int r);
int comp_pp(Point *a, Point *b);
void search_tri();
void merge_ppoint(int nth);

void decompose_prime5();


int main(int argc, char **argv) {
  int i;

  make_primetable();

  for (i=1; i<primen; i++) {
    if (LIMITR < prime_t[i])
      break;
    if (prime_t[i] % 4 == 1)
      prime5[primen5++] = prime_t[i];
  }

  decompose_prime5();

  calc_radius0();

  printf ("answer: %.4f  (%.7f)\n", answer, answer);
}

void decompose_prime5() {
  int i, j;
  int d, dsq;

  for (i=0; i<primen5; i++) {
    for (j=1; j<prime5[i]; j++) {
      d = prime5[i]-j*j;
      dsq = sqrt(d);
      if (d == dsq*dsq) {
	prime52[i][0] = j;
	prime52[i][1] = dsq;
	break;
      }
    }
  }
}

int ii[20];
int iif[20];

// nth src/trg n element
int pset[20][2][10][2];
int ppoint[20][10000][2];
int ppointn[20];

void calc_radius0 () {
  int i;
  long long int nr;
  int trg, src;
  int nth = 0;
  int tmp;

  ii[0] = 0; // 5
  {
    nr = prime5[ii[0]];

    pset[0][1][0][0] = prime52[ii[0]][0];
    pset[0][1][0][1] = prime52[ii[0]][1];
    
    for (iif[0]=1;; iif[0]++) {
      ppointn[0] = iif[0]/2+1;
      for (i=0; i<ppointn[0]; i++) {
	ppoint[0][i][0] = pset[0][iif[0]%2][i][0];
	ppoint[0][i][1] = pset[0][iif[0]%2][i][1];
	//	printf ("(%d %d)", ppoint[0][i][0],ppoint[0][i][1]);
      }
      //      printf ("\n");

      calc_radius(1, 1, nr);

      if (iif[0]!=1)
	calc_point(0, nr);

      nr *= prime5[ii[0]];
      if (nr > LIMITR)
	break;

      src = iif[0]%2;
      trg = 1-src;
      if (iif[0]==1) {
	pset[0][0][0][0] = 0;
	pset[0][0][0][1] = prime5[ii[0]];
	i = 1;
      } else {
	for (i=0; i<(iif[0]+1)/2; i++) {
	  pset[0][trg][i][0] *= prime5[ii[0]];
	  pset[0][trg][i][1] *= prime5[ii[0]];
	}
      }
	tmp = pset[0][src][iif[0]/2][0]*prime52[ii[0]][0]+pset[0][src][iif[0]/2][1]*prime52[ii[0]][1];
	if (tmp % prime5[ii[0]]) {
	  pset[0][trg][i][0] = tmp;
	  pset[0][trg][i][1] = abs(pset[0][src][iif[0]/2][0]*prime52[ii[0]][1]-pset[0][src][iif[0]/2][1]*prime52[ii[0]][0]);
	} else {
	  pset[0][trg][i][0] = abs(pset[0][src][iif[0]/2][0]*prime52[ii[0]][0]-pset[0][src][iif[0]/2][1]*prime52[ii[0]][1]);
	  pset[0][trg][i][1] = pset[0][src][iif[0]/2][0]*prime52[ii[0]][1]+pset[0][src][iif[0]/2][1]*prime52[ii[0]][0];
	}
    }
  }

}

void calc_radius(int nth, int min, int r) {
  int i;
  long long int nr;
  int trg, src;
  int tmp;

  long long int limitrn;

  limitrn = LIMITR/r;

  for (ii[nth]=min; ii[nth]<primen5; ii[nth]++) {

    if (prime5[ii[nth]] > limitrn)
      return;

    nr = prime5[ii[nth]]*(long long int)r;

    pset[nth][1][0][0] = prime52[ii[nth]][0];
    pset[nth][1][0][1] = prime52[ii[nth]][1];
    
    for (iif[nth]=1;; iif[nth]++) {
      merge_ppoint(nth);
      calc_point(nth, nr);
      calc_radius(nth+1, ii[nth]+1, nr);

      nr *= prime5[ii[nth]];
      if (nr > LIMITR)
	break;

      src = iif[nth]%2;
      trg = 1-src;
      if (iif[nth]==1) {
	pset[nth][0][0][0] = 0;
	pset[nth][0][0][1] = prime5[ii[nth]];
	i=1;
      } else {
	for (i=0; i<(iif[nth]+1)/2; i++) {
	  pset[nth][trg][i][0] *= prime5[ii[nth]];
	  pset[nth][trg][i][1] *= prime5[ii[nth]];
	}
      }
      tmp = pset[nth][src][iif[nth]/2][0]*prime52[ii[nth]][0]+pset[nth][src][iif[nth]/2][1]*prime52[ii[nth]][1];
      if (tmp % prime5[ii[nth]]) {
	pset[nth][trg][i][0] = tmp;
	pset[nth][trg][i][1] = abs(pset[nth][src][iif[nth]/2][0]*prime52[ii[nth]][1]-pset[nth][src][iif[nth]/2][1]*prime52[ii[nth]][0]);
      } else {
	pset[nth][trg][i][0] = abs(pset[nth][src][iif[nth]/2][0]*prime52[ii[nth]][0]-pset[nth][src][iif[nth]/2][1]*prime52[ii[nth]][1]);
	pset[nth][trg][i][1] = pset[nth][src][iif[nth]/2][0]*prime52[ii[nth]][1]+pset[nth][src][iif[nth]/2][1]*prime52[ii[nth]][0];
      }
    }
  }

}

void calc_point(int nth, int r) {
  int i;
  long long int r2;
  long long int d;
  int x, y;
  int xmax;

  pn = 0;

  // duplicate mirror images
  for (i=0; i<ppointn[nth]; i++) {
    pp[pn].x = ppoint[nth][i][0];
    pp[pn++].y = ppoint[nth][i][1];
    pp[pn].x = ppoint[nth][i][0];
    pp[pn++].y = -ppoint[nth][i][1];
    pp[pn].x = ppoint[nth][i][1];
    pp[pn++].y = ppoint[nth][i][0];
    pp[pn].x = -ppoint[nth][i][1];
    pp[pn++].y = ppoint[nth][i][0];
    if (ppoint[nth][i][0]) {
      pp[pn].x = -ppoint[nth][i][0];
      pp[pn++].y = ppoint[nth][i][1];
      pp[pn].x = -ppoint[nth][i][0];
      pp[pn++].y = -ppoint[nth][i][1];
      pp[pn].x = ppoint[nth][i][1];
      pp[pn++].y = -ppoint[nth][i][0];
      pp[pn].x = -ppoint[nth][i][1];
      pp[pn++].y = -ppoint[nth][i][0];
    }
  }

  qsort (pp, pn, sizeof(Point), comp_pp);
  search_tri();
}

int comp_pp(Point *a, Point *b) {
  if (a->x == b->x)
    return 0;
  else if (a->x < b->x)
    return -1;
  else
    return 1;
}

//search triangle
void search_tri() {
  int i, j, k, ktmp;
  long long int tmp;
  int x3, y3, xk;
  double p2, p;
  for (i=0; i<pn-2; i++) {
    if (pp[i].x >=2)
      break;
    j = i+1;
    k = pn-1;
    while (j<k) {
      x3 = pp[i].x + pp[j].x + pp[k].x;
      if (x3 > 5)
	k--;
      else if (x3 < 5)
	j++;
      else {// (x3 == 5)
	xk = pp[k].x;
	ktmp = k;
	while(xk == pp[ktmp].x) {
	  if (ktmp <= j)
	    break;
	  y3 = pp[i].y + pp[j].y + pp[ktmp].y;
	  if (y3 == 0) {
	    // get answer
	    tmp = (pp[i].x - pp[j].x);
	    tmp *= tmp;
	    p2 = tmp;
	    tmp = (pp[i].y - pp[j].y);
	    tmp *= tmp;
	    p2 += tmp;
	    p = sqrt(p2);
	    tmp = (pp[i].x - pp[ktmp].x);
	    tmp *= tmp;
	    p2 = tmp;
	    tmp = (pp[i].y - pp[ktmp].y);
	    tmp *= tmp;
	    p2 += tmp;
	    p += sqrt(p2);
	    tmp = (pp[j].x - pp[ktmp].x);
	    tmp *= tmp;
	    p2 = tmp;
	    tmp = (pp[j].y - pp[ktmp].y);
	    tmp *= tmp;
	    p2 += tmp;
	    p += sqrt(p2);
	    if (p <= N) {
	      printf (">> (%d %d) (%d %d) (%d %d) ", pp[i].x, pp[i].y, pp[j].x, pp[j].y, pp[ktmp].x, pp[ktmp].y);
	      answer += p;
	      printf ("p %f %.7f\n", p, answer);
	    }
	  }
	  ktmp--;
	}
	j++;
      }
    }
    
  }

}

void make_primetable() {
  int i, j;
  int SQRN = sqrt(PN);

  primen = 0;
  
  prime_t[0] = 2;
  primen++;
  prime_t[1] = 3;
  primen++;

  for (i=5; i<=SQRN; i+=2) { // sqrt(SQRN)
    if (i%3==0)
      continue;
    if (!prime_search[i/3]) {
      // prime
      prime_t[primen] = i;
      for (j=i; j<PN; j += (i+i)) {
	if (j%3==0)
	  continue;
        prime_search[j/3] = primen;
      }
      primen++;
    }
  }

  for (; i<=PN; i+=2) {
    if (i%3==0)
      continue;
    if (!prime_search[i/3]) {
      prime_search[i/3] = primen;
      prime_t[primen++] = i;
    }
  }

  printf("prime %d %d  PN: %lld\n", primen, prime_t[primen-1], PN);
}

//pset[nth][iif[nth]%2][iif[nth]/2+1][] * ppoint[nth-1][- ppointn[nth-1]][]
void merge_ppoint(int nth) {
  int i;
  int j;
  int tmp1, tmp2, tmp3, tmp4;

  ppointn[nth] = 0;
  for (i=0; i<ppointn[nth-1]; i++) {
    for (j=0; j<iif[nth]/2+1; j++) {
      if (pset[nth][iif[nth]%2][j][0]==0) {
	ppoint[nth][ppointn[nth]][0] = ppoint[nth-1][i][0] * pset[nth][iif[nth]%2][j][1];
	ppoint[nth][ppointn[nth]][1] = ppoint[nth-1][i][1] * pset[nth][iif[nth]%2][j][1];
	ppointn[nth]++;
      } else if (ppoint[nth-1][i][0]==0) {
	ppoint[nth][ppointn[nth]][0] = pset[nth][iif[nth]%2][j][0] * ppoint[nth-1][i][1];
	ppoint[nth][ppointn[nth]][1] = pset[nth][iif[nth]%2][j][1] * ppoint[nth-1][i][1];
	ppointn[nth]++;
      } else {
	tmp1 = ppoint[nth-1][i][0] * pset[nth][iif[nth]%2][j][0];
	tmp2 = ppoint[nth-1][i][1] * pset[nth][iif[nth]%2][j][1];
	tmp3 = ppoint[nth-1][i][0] * pset[nth][iif[nth]%2][j][1];
	tmp4 = ppoint[nth-1][i][1] * pset[nth][iif[nth]%2][j][0];
	ppoint[nth][ppointn[nth]][0] = tmp1 + tmp2;
	ppoint[nth][ppointn[nth]][1] = abs(tmp3 - tmp4);
	ppointn[nth]++;
	ppoint[nth][ppointn[nth]][0] = abs(tmp1 - tmp2);
	ppoint[nth][ppointn[nth]][1] = tmp3 + tmp4;
	ppointn[nth]++;
      }
    }
  }
}