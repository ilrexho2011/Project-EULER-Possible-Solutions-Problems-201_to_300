#include <inttypes.h>
#include <iostream>


size_t const N=24;
int64_t const C=1<<(N-1);
int64_t const R2=C*C;


bool black(uint64_t x, uint64_t y)
{
	int64_t dx=int64_t(x)-C;
	int64_t dy=int64_t(y)-C;
	int64_t r2=dx*dx+dy*dy;
	return r2<=R2;
}


uint64_t bits(uint64_t x0, uint64_t x1, uint64_t y0, uint64_t y1)
{
	uint64_t xc=(x0+x1)/2;
	uint64_t yc=(y0+y1)/2;
	size_t b=black(x0, y0)+black(x0, y1-1)+black(x1-1, y0)+black(x1-1, y1-1)+black(xc, yc);
	if(b==5)
		return 2;
	else if(b==0)
		return 2;
	else
	{
		// split
		return 1
			+ bits(x0, xc, y0, yc)
			+ bits(xc, x1, y0, yc)
			+ bits(x0, xc, yc, y1)
			+ bits(xc, x1, yc, y1);
	}
}


int main()
{
	uint64_t r=bits(0, 1ull<<N, 0, 1ull<<N);
	std::cout << "N=" << N << ", r=" << r << "\n";
	return 0;
}
