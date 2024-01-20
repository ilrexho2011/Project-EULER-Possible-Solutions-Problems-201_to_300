#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<numeric>

using namespace std;

int bits[16];
int ubit[16];

//how the position is numbered:
//low 2 bytes denote where red (0) and blue (1) squares are positioned
//hi 2 bytes where is empty cell
//empty cell is considered to be red

const int N = 16*256*256;

const int L = 76;
const int R = 82;
const int U = 85;
const int D = 68;

const int MS = 0xCCCC;
const int MT = 0x5A5A;

inline void setbit(int& n, int b, bool v){
        if (v) n |= bits[b];
        else n &= ubit[b];
}

inline bool getbit(int n, int b){
        return (n & bits[b]);
}

int genL(int pos){
        int p = pos >> 16;
        if ((p&3) == 3) return 0;

        pos = pos & 0xffff;
        setbit(pos, p, getbit(pos, p+1));
        p++;
        setbit(pos, p, 0);

        pos |= (p << 16);
        return pos;
}

int genR(int pos){
        int p = pos >> 16;
        if ((p&3) == 0) return 0;

        pos = pos & 0xffff;
        setbit(pos, p, getbit(pos, p-1));
        p--;
        setbit(pos, p, 0);

        pos |= (p << 16);
        return pos;
}

int genU(int pos){
        int p = pos >> 16;
        if (p > 11) return 0;

        pos = pos & 0xffff;
        setbit(pos, p, getbit(pos, p + 4));
        p += 4;
        setbit(pos, p, 0);

        pos |= (p << 16);
        return pos;
}

int genD(int pos){
        int p = pos >> 16;
        if (p < 4) return 0;

        pos = pos & 0xffff;
        setbit(pos, p, getbit(pos, p - 4));
        p -= 4;
        setbit(pos, p, 0);

        pos |= (p << 16);
        return pos;
}



set<int>* a;

map<int, set<int> >  *nxt, *curr;

int checksum(int m, int c = 0){
       long long C = 243;
       C *= c;
       C += m;
       C %= 100000007;
       return C;
}


bool move(){
        static int cc =0;
        bool res = false;

        while(curr->size()){
                int k = (curr->begin())->first;
                set<int>& K = (curr->begin())->second;

                int t = genL(k);
                if (t == MT) res = true;
                if (t && a[t].size() == 0 && curr->count(t) == 0)
                        for (auto z = K.begin(); z != K.end(); z++)
                                (*nxt)[t].insert(checksum(L, *z));

                t = genR(k);
                if (t == MT) res = true;
                if (t && a[t].size() == 0 && curr->count(t) == 0)
                         for (auto z = K.begin(); z != K.end(); z++)
                                (*nxt)[t].insert(checksum(R, *z));

                t = genU(k);
                if (t == MT) res = true;
                if (t && a[t].size() == 0 && curr->count(t) == 0)
                        for (auto z = K.begin(); z != K.end(); z++)
                                (*nxt)[t].insert(checksum(U, *z));

                t = genD(k);
                if (t == MT) res = true;
                if (t && a[t].size() == 0 && curr->count(t) == 0)
                        for (auto z = K.begin(); z != K.end(); z++)
                                (*nxt)[t].insert(checksum(D, *z));

                a[k] = (*curr)[k];
                curr->erase(k);
        }

        map<int, set<int> >* t = nxt;
        nxt = curr;
        curr = t;

        cerr << "Round " << ++cc << " " << res << endl;
        return res;

}

int main(){
        a = new set<int> [N];
        a[MS].insert(0);

        nxt = new map<int, set<int> >;
        curr = new map<int, set<int> >;
        (*curr)[MS].insert(0);

        bits[0] = 1; ubit[0] =0xfffe;
        for (int i = 1; i < 16; i++){
                bits[i] = bits[i-1]*2;
                ubit[i] = 0xffff - bits[i];
        }

        while(!move());

        cerr << (*curr)[MT].size() << endl;
        cerr << accumulate((*curr)[MT].begin(), (*curr)[MT].end(), 0ll) << endl;
}