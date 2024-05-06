#include <iostream>
#include <algorithm>
#include <map>
#include <climits>

typedef unsigned uint;
typedef long long llong;
typedef unsigned long long ullong;

static const uint
	cNumDigits = 16;

static const llong
	cVoid = LLONG_MIN + 1; // a special "don't care" value

// A vararray-like class of fixed size
template<class T, size_t N> struct valtuple
{
	static const size_t size = N;
	typedef T value_type;

	T & operator[](int i) { return m_data[i]; }
	T operator[](int i) const { return m_data[i]; }

	bool operator==(const valtuple & other) const
	{
		for (size_t i = 0; i < N; i++)
			if (m_data[i] != other.m_data[i])
				return false;
		return true;
	}

	bool operator<(const valtuple & other) const
	{
		for (size_t i = 0; i < N; i++)
		{
			if (m_data[i] < other.m_data[i])
				return true;
			if (m_data[i] > other.m_data[i])
				return false;
		}
		return false;
	}

	bool operator!=(const valtuple & other) const { return !(*this == other); }
	bool operator<=(const valtuple & other) const { return !(other < *this); }
	bool operator> (const valtuple & other) const { return  (other < *this); }
	bool operator>=(const valtuple & other) const { return !(*this < other); }

	T m_data[N];
};
template<class T, size_t N> valtuple<T,N> operator+(const valtuple<T,N> & a, const valtuple<T,N> & b)
{
	valtuple<T,N> r;
	for (size_t i = 0; i < N; i++)
		r[i] = a[i] + b[i];
	return r;
}

template<class T1, class T2, size_t N> valtuple<T1,N> operator+(const valtuple<T1,N> & a, T2 t)
{
	valtuple<T1,N> r;
	for (size_t i = 0; i < N; i++)
		r[i] = a[i] + t;
	return r;
}
template<class T1, class T2, size_t N> valtuple<T2,N> operator+(T1 t, const valtuple<T2,N> & a) { return a + t; }

template<class T, size_t N> valtuple<T,N> operator*(const valtuple<T,N> & a, const valtuple<T,N> & b)
{
	valtuple<T,N> r;
	for (size_t i = 0; i < N; i++)
		r[i] = a[i] * b[i];
	return r;
}

template<class T1, class T2, size_t N> valtuple<T1,N> operator*(const valtuple<T1,N> & a, T2 t)
{
	valtuple<T1,N> r;
	for (size_t i = 0; i < N; i++)
		r[i] = a[i] * t;
	return r;
}
template<class T1, class T2, size_t N> valtuple<T2,N> operator*(T1 t, const valtuple<T2,N> & a) { return a * t; }

template<class T> valtuple<T, 2> make_valtuple(T t1, T t2) { valtuple<T,2> s = { t1, t2 }; return s; }
template<class T> valtuple<T, 3> make_valtuple(T t1, T t2, T t3) { valtuple<T,3> s = { t1, t2, t3 }; return s; }

template<size_t N, class T> valtuple<T, N> fill_valtuple(T t) { valtuple<T,N> s; for(size_t i = 0; i < N; i++) s[i] = t; return s; }



int main()
{
	llong total = 1;
	for (uint n = 1; n < cNumDigits; n++)
		total *= 10;

	for (int thisRoot = 1; thisRoot < 10; thisRoot++)
	{
		typedef valtuple<llong, 9> llval;
		typedef std::map<llval, ullong> CombiMap;
		CombiMap combis;
		llval roots = { }; // roots that we're evaluating
		for (int i = 0; i < thisRoot; i++)
			roots[i] = -thisRoot + i;

		// initialize combinations with a single digit (by starting at 1, we exclude all the polynomials with root 0)
		for (int d = 1; d < 10; d++)
		{
			if (d % thisRoot == 0)
			{
				llval key = { };
				for (int i = 0; i < thisRoot; i++)
					key[i] = d;
				combis[key] = 1;
			}
		}

		// now add all digits
		llval powers = roots;
		for (uint n = 1; n < cNumDigits; n++)
		{
			llval nextPowers = powers * roots;
			CombiMap addCombis;
			for (int d = 0; d < 10; d++) // for each digit, add new possible sums with that digit to the map
			{
				llval b = powers * d;
				for (CombiMap::iterator it = combis.begin(); it != combis.end(); ++it)
				{
					if ((b[0] + it->first[0]) % nextPowers[0] == 0)
					{
						llval key = b + it->first;
						for (int i = 1; i < thisRoot; i++)
						{	// combine roots that are no longer possible
							if (b[i] == cVoid || key[i] % nextPowers[i] != 0)
								key[i] = cVoid;
						}
						addCombis[key] += it->second;
					}
				}
			}
			combis.swap(addCombis);
			powers = nextPowers;
		}

		// count all (not yet counted) polynomials
		llval min = { 0, LLONG_MIN }, max = { 0, LLONG_MAX };
		CombiMap::iterator begin = combis.lower_bound(min), end = combis.upper_bound(max);
		for (CombiMap::iterator it = begin; it != end; ++it)
		{
			bool ok = true;
			for (int i = 1; i < thisRoot; i++)
			{
				if (!it->first[i])
				{
					ok = false;
					break;
				}
			}
			if (ok)
				total += it->second;
		}
	}
	std::cout << "answer: " << total << std::endl;
}