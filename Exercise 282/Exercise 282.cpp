typedef uint64_t ull;

template<typename ULL>
ULL gcd(ULL a, ULL b) {
    while( b ) { ULL m=b; b=a%b; a=m; }
    return a;
}

// bitmasks for fastlog2
static const ull b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000LL, 0xFFFFFFFF00000000LL};
// shift widths for fastlog2
static const unsigned int S[] = {1, 2, 4, 8, 16, 32};

// quick way to find integral log2
template <typename T>
int fastlog2( T num ) {
    int r=0;
    if( sizeof(T) >=8 ) {
        if( num & b[5] ) {
            num >>= S[5];
            r |= S[5];
        }
    }
    if( sizeof(T) >= 4 ) {
        if( num & b[4] ) {
            num >>= S[4];
            r |= S[4];
        }
    }
    for( int i=3; i>=0; --i ) {
        if( num & b[i] ) {
            num >>= S[i];
            r |= S[i];
        }
    }
    return r;
}

// very basic base^num%mod
template <typename ULL>
ULL powmod_2( ULL base, ULL num, ULL mod ) {
    ULL nom=base;
    while( --num>0 ) {
        nom *= base;
        nom %= mod;
    }
    return nom;
}

// optimized base^num%mod
template <typename ULL>
ULL powmod( ULL base, ULL num, ULL mod ) {
    if( num==0 )
        return 1;
    if( base==0 )
        return 0;

    int logB = fastlog2(base)+1;
//    int logN = fastlog2(num)+1;

    // b^x should fit nicely into ULL/2
    ULL x = 8*sizeof(ULL)/logB/3;

    if( num<= x ) {
        return powmod_2( base, num, mod );
    }
    ULL b = powmod_2( base, x, mod );

    ULL res=1;
    while( num>=x ) {
        res *= b;
        res %= mod;
        num -= x;
    }
    switch( num ) {
        case 0:
            return res;
        case 1:
            return (res*base)%mod;
        default:
            return (res*powmod_2( base, num, mod ))%mod;
    }
}