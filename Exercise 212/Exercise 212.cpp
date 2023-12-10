#include <inttypes.h>
#include <iostream>
#include <vector>


size_t const N=50000;


struct fibo
{
	fibo(): k(1) {}

	uint64_t operator() ()
	{
		uint64_t r;
		if(55<k)
		{
			uint64_t f1=f[(k-24)%64];
			uint64_t f2=f[(k-55)%64];
			r=(f1+f2)%M;
		}
		else
		{
			uint64_t k3m=k*k%M*k%M;
			r=(100003+ M-(200003*k%M)%M+ 300007*k3m%M)%M;
		}
		f[k%64]=r;
		++k;
		return r;
	}

	static uint64_t const M=1000000;
	uint64_t k;
	uint64_t f[64];
} F;


struct cube_t
{
	size_t x0, y0, z0;
	size_t x1, y1, z1;
} cubes[N];


bool overlaps(size_t a0, size_t a1, size_t b0, size_t b1)
{
	return a0<b1 && b0<a1;
}


bool intersects(cube_t const &a, cube_t const &b)
{
	return overlaps(a.x0, a.x1, b.x0, b.x1)
		&& overlaps(a.y0, a.y1, b.y0, b.y1)
		&& overlaps(a.z0, a.z1, b.z0, b.z1);
}


// works from the back of f, can safely remove f[i]
void split(cube_t const &a, std::vector<cube_t> &f, size_t i)
{
	if(intersects(a, f[i]))
	{
		if(f[i].x0<a.x0)
		{
			cube_t c(f[i]);
			c.x1=a.x0;
			f.push_back(c);
			f[i].x0=a.x0;
		}
		if(a.x1<f[i].x1)
		{
			cube_t c(f[i]);
			c.x0=a.x1;
			f.push_back(c);
			f[i].x1=a.x1;
		}

		if(f[i].y0<a.y0)
		{
			cube_t c(f[i]);
			c.y1=a.y0;
			f.push_back(c);
			f[i].y0=a.y0;
		}
		if(a.y1<f[i].y1)
		{
			cube_t c(f[i]);
			c.y0=a.y1;
			f.push_back(c);
			f[i].y1=a.y1;
		}

		if(f[i].z0<a.z0)
		{
			cube_t c(f[i]);
			c.z1=a.z0;
			f.push_back(c);
			f[i].z0=a.z0;
		}
		if(a.z1<f[i].z1)
		{
			cube_t c(f[i]);
			c.z0=a.z1;
			f.push_back(c);
			f[i].z1=a.z1;
		}

		f.erase(f.begin()+i);
	}
}


size_t add(cube_t const &c, size_t n)
{
	std::vector<cube_t> f;
	f.push_back(c);
	for(size_t i=0; i<n; ++i)
	{
		cube_t const &ci=cubes[i];
		if(intersects(c, ci))
			for(size_t j=f.size(); j--;)
				// may remove f[j] and append disjunct non-intersecting fragments
				split(ci, f, j);
	}

	// disjunct fragments
	size_t a=0;
	for(size_t i=0; i<f.size(); ++i)
	{
		cube_t const &fi=f[i];
		a+=(fi.x1-fi.x0)*(fi.y1-fi.y0)*(fi.z1-fi.z0);
	}
	return a;
}


int main()
{
	uint64_t r=0;
	for(size_t n=0; n<N; ++n)
	{
		cube_t &c=cubes[n];
		c.x0=F()%10000;
		c.y0=F()%10000;
		c.z0=F()%10000;
		c.x1=c.x0+1+F()%399;
		c.y1=c.y0+1+F()%399;
		c.z1=c.z0+1+F()%399;
		r+=add(c, n);
	}
	std::cout << r << "\n";
	return 0;
}