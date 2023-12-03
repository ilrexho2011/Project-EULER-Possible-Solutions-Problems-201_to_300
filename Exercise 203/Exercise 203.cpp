#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>

using namespace std;
typedef unsigned long long uint64;

class GreaterThan
{
	public :
		GreaterThan(unsigned val) : cmpVal(val){}
		bool operator()(pair<unsigned,unsigned> elem)
		{
			return elem.second > cmpVal;
		}
	private :
		unsigned cmpVal;
};

void buildTable(vector<map<unsigned,unsigned> >&);

int main()
{
	const unsigned MAX_ROW = 51;
	set<uint64> squareFreeNums;
	vector<map<unsigned,unsigned> > primeFactorizTable(MAX_ROW);
	
	buildTable(primeFactorizTable);
	squareFreeNums.insert(1);
	
	for (unsigned row = 2; row < MAX_ROW; ++row) {
		map<unsigned, unsigned> primeFactoriz;
		uint64 pascalTriElem = 1;
		
		for (unsigned col = 1; 2*col <= row; ++col) {
			map<unsigned,unsigned> numerFact(primeFactorizTable[row + 1 - col]), 
			                       denomFact(primeFactorizTable[col]); 
			
			pascalTriElem = (pascalTriElem*(row + 1 - col))/col;
			
			for (map<unsigned,unsigned>::iterator expItr = numerFact.begin();
			 	 expItr != numerFact.end(); ++expItr)
			{
				primeFactoriz[expItr->first] += expItr->second;
			}
			for (map<unsigned,unsigned>::iterator expItr = denomFact.begin();
			 	 expItr != denomFact.end(); ++expItr)
			{
				primeFactoriz[expItr->first] -= expItr->second;
			}

			if (find_if(primeFactoriz.begin(), primeFactoriz.end(), GreaterThan(1)) == 
				primeFactoriz.end())
			{
				squareFreeNums.insert(pascalTriElem);
			}
		}
	}
	cout << accumulate(squareFreeNums.begin(), squareFreeNums.end(), 0ULL);
}

void buildTable(vector<map<unsigned,unsigned> >& primeFactorizTable)
{
	for (unsigned i = 2; i < primeFactorizTable.size(); ++i) { 
		unsigned n = i;
		for (unsigned p = 2; p*p <= n && n > 1; p == 2 ? p = 3 : p += 2) { 
			if (n % p == 0) {
		    	primeFactorizTable[i][p]++; 
				n /= p;
		        while (n % p == 0) { 
		        	primeFactorizTable[i][p]++;
		            n /= p; 
		        }
			}   
		}
		if (n > 1)
			primeFactorizTable[i][n]++;
	}
}