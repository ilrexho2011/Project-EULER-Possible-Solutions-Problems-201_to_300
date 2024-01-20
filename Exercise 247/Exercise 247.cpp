#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <sys/types.h>

using namespace std;

class SUH                           // Square Under Hyperbola (y = 1/x)
{
    public:
        double x0;
        double y0;
        double side;
        unsigned nleft, nbelow;
        SUH(const double& x0, const double& y0,
            unsigned nleft, unsigned nbelow)
            : x0(x0), y0(y0), side(0.0),
            nleft(nleft), nbelow(nbelow)
        {
            double B = x0 - y0;
            double y = (-B + sqrt(B*B + 4.0))/2.0;
            //double x = y + B;
            side = y - y0;
        }

};

bool
operator<(const SUH& a, const SUH& b)
{
    return  a.side > b.side ||
        a.side == b.side && (a.x0 < b.x0 ||
        a.x0 == b.x0 && a.y0 < b.y0);
}


const unsigned tdepth = 3;

int
main(int argc, char **argv)
{
    double min_side = 1.0;
    {
        set<SUH> s;
                                    // this primes the set
        s.insert(SUH(1.0, 0.0, 0, 0));
        set<SUH> t = s;             // something to build on
                                    // get correct indexes
        for (unsigned i=1; i<=2*tdepth; i++)
        {
            set<SUH> u;
            for (set<SUH>::iterator it = t.begin(); it!=t.end(); ++it)
            {
                u.insert(SUH(it->x0, it->y0 + it->side,
                    it->nleft, it->nbelow + 1));
                u.insert(SUH(it->x0 + it->side, it->y0,
                    it->nleft + 1, it->nbelow));
            }
            for (set<SUH>::iterator it = u.begin(); it!=u.end(); ++it)
            {
                s.insert(*it);
            }
            t = u;
        }
        ulong acc = 0;
        for (set<SUH>::iterator it = s.begin(); it!=s.end(); ++it)
        {
                                    // index correct
            if (tdepth==it->nleft && tdepth==it->nbelow)
            {
                ++acc;
                if (min_side > it->side)
                {
                                    // find smallest one with index
                    min_side = it->side;
                }
            }
        }
        cout << "There are " << acc
            << " squares with index (" << tdepth << "," << tdepth << ")" << endl;
        cout << "The smallest has a side of: " << min_side << endl;
        cout.flush();
    }
    // now we need to find out how many are bigger, to get the sequence number
    {
        priority_queue<SUH> pq;
        pq.push(SUH(1.0, 0.0, 0, 0));
        ulong acc = 0;
        while (0!=pq.size())
        {
            acc++;
            SUH t0 = pq.top();
            pq.pop();
            SUH tu = SUH(t0.x0, t0.y0 + t0.side, t0.nleft, t0.nbelow + 1);
            if (min_side <= tu.side)
            {
                pq.push(tu);
            }
            SUH tr = SUH(t0.x0 + t0.side, t0.y0, t0.nleft + 1, t0.nbelow);
            if (min_side <= tr.side)
            {
                pq.push(tr);
            }
        }
        cout << "S(" << acc << ") is the one." << endl;
    }
    return 0;
}