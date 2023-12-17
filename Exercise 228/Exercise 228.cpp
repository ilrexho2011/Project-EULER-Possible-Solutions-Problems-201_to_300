#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	uint_fast32_t i, j, s, *phi;
	uint_fast64_t r;
	long long int a = 1864;
	long long int b = 1909;
	if (argc != 1
	 && (argc != 3
	  || argc == 3 && ((a = strtoll(argv[1], 0, 0)) < 3
		        || (b = strtoll(argv[2], 0, 0)) < a
		        || b > 4294967295
		        || errno)))
	{
		fprintf(stderr
			, "Usage: %s [a b]"
			  ", 3 <= a(1864) <= b(1909) <= 4294967295"
			  "\nCalculate edge#(sum_{k=a}^b P_k)."
			  "\n"
			, *argv);
		return EXIT_FAILURE;
	}
	if (a < (b+1) >> 1)
	{
		a = (b+1) >> 1;
	}
	s = b-a+1;
	phi = malloc(s*sizeof(uint_fast32_t));
	if (!phi)
	{
		fprintf(stderr, "Could not allocate enough dynamic memory.\n");
		return EXIT_FAILURE;
	}
	for (i = 1; i < s; i++)
	{
		phi[i] = i;
	}
	for (i = 2; i < s; i++)
	{
		if (phi[i] == i)
		{
			j = i;
			do
			{
				phi[j] -= phi[j]/i;
				j += i;
			}
			while (j < s);
		}
	}
	r = (a+b)*s/2;
	for (i = 1; i < s; i++)
	{
		r -= (b/i-(a+i-1)/i)*phi[i];
	}
	printf("%" PRIuFAST64 "\n", r);
	return EXIT_SUCCESS;
}