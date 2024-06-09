package problems;

import java.math.BigInteger;
import java.util.BitSet;
import java.util.Random;

public class PE291 {
	
	public static long f(long n) {
		return n*n + (n+1)*(n+1);
	}
	
	public static void main(String[] args) {
		long N = 5000000000000000L;

		// prime sieve
		int max = (int)Math.sqrt(N);
		BitSet sieve = new BitSet(max+1);
		for (int p=2; p<=Math.sqrt(max); p++) {
			if (sieve.get(p)) continue;
			for (int pk=2*p; pk<=max; pk+=p) sieve.set(pk);
		}
		
                // second sieve
		int max2 = (int) (-2 + Math.sqrt(4+8*(N-1)))/4;
		BitSet sieve2 = new BitSet(max2+1);
		for (int p=3; p<=max; p++) {
			if (sieve.get(p)) continue;
			
			long inv = inverse(4, p);
			long sqrt = sqrtmod(2*p-4, p);
			if (sqrt==0) continue;
			
			long n1 = ((-2+sqrt)*inv) % p; if (n1<0) n1+=p;
			long n2 = ((-2-sqrt)*inv) % p; if (n2<0) n2+=p;
			
			if (f(n1)==p) n1+=p;
			if (f(n2)==p) n2+=p;
			
			for (;n1<=max2;n1+=p) sieve2.set((int)n1);
			for (;n2<=max2;n2+=p) sieve2.set((int)n2);

		}
		
		
		int count = 0;
		for (int n=1; n<=max2; n++) {
			if (sieve2.get(n)) continue;
			count++;
		}
		System.out.println(count);
	}


	public static long mulmod(long a, long b, long p) {
		// should generally watch out for overflow
		long n =  (a*b)%p;
		return n;
	}
	
	public static long powmod(long a, long k, long p) {
		a %= p;
		long res = 1;
		while (k>0) {
			if ((k&1)==1) res = (res*a) % p;
			a = (a*a) % p;
			k>>=1;
		}
		return res;
	}

	   public static int jacobi(long a, long m) {
	      int t=1;
	      long z;
	      a%=m;
	      while(a!=0) {
	         while((a&1)==0) {
	            a>>=1;
	            if((m&7)==3 || (m&7)==5) t=-t;
	         }
	         z=a; a=m; m=z;
	         if((a&3)==3 && (m&3)==3) t=-t;
	         a%=m;
	      }
	      if(m==1) return t;
	      return 0;
	   }
	   
	   static Random random = new Random();
	   // assume a>=0
	   public static long sqrtmod(long a,long p) {
	      if(p==2) return a&1;
	      a%=p;
	      if(jacobi(a,p)!=1) return 0; /* no square root */
	      int p8=(int)(p&7);
	      if(p8==3 || p8==5 || p8==7) {
	         if((p8&3)==3) return powmod(a,(p+1)/4,p);
	         long x=powmod(a,(p+3)/8,p);
	         long c=mulmod(x,x,p);
	         return c==a?x:mulmod(x,powmod(2,(p-1)/4,p),p);
	      }
	      int alpha=0;
	      long s=p-1;
	      while((s&1)==0) { s>>=1; alpha++; }
	      long r=powmod(a,(s+1)/2,p);
	      long r2a=mulmod(r,powmod(a,(s+1)/2-1,p),p);
	      long n=1;
	      do {
	         n=random.nextLong()%(p-2)+2;
	         if (n<0) n+=p;
	      }while(jacobi(n,p)!=-1);
	      long b=powmod(n,s,p);
	      long J=0;
	      for(int i=0;i<alpha-1;i++) {
	         long c=powmod(b,2*J,p);
	         c=mulmod(r2a,c,p);
	         c=powmod(c,1L<<(alpha-i-2),p);
	         if(c==p-1) J+=1L<<i;
	      }
	      return mulmod(r,powmod(b,J,p),p);
	   }
	   
	// assuming gcd(a, mod) == 1
	public static long inverse(long a,long mod) {
		long b=mod,x=0,y=1,t,q,lastx=1,lasty=0;
		while(b!=0) {
			q=a/b;
			t=a; a=b; b=t%b;
			t=x; x=lastx-q*x; lastx=t;
			t=y; y=lasty-q*y; lasty=t;
		}
		return a==1?(lastx%mod+mod)%mod:0;
	}

}