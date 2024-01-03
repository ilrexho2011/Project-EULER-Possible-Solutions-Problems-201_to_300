#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>

using namespace std;

using frozenset = const unordered_set<unsigned long long>;

constexpr auto S0 =  14025256UL;
constexpr auto SEQ_MOD =  20300713UL;


void fill_vector_with_cumulative_digits_sum(unsigned long s, vector<unsigned long long> &partial_sum) {
    auto rem = s;
    auto num_digits = static_cast<int>(log10(s));
    unsigned long factor = powl(10, num_digits);
    while (rem) {
        auto digit_and_remainder = ldiv(rem, factor);
        partial_sum.push_back(partial_sum.back() + digit_and_remainder.quot);
        rem = digit_and_remainder.rem;
        factor /= 10;
    }
}


vector<unsigned long long> calc_partial_sums() {
    vector<unsigned long long> partial_sum;
    partial_sum.push_back(0);
    auto s = S0;
    do {
        fill_vector_with_cumulative_digits_sum(s, partial_sum);
        s = (s * s) % SEQ_MOD;
    } while (s != S0);
    return partial_sum;
}


class PSum {
public:
    unsigned long long sum(unsigned long sum_upto) const {
        const auto num_recurrent_sums_and_remainder = ldiv(sum_upto, _period);
        const auto recurrent_sum = _sum(_period);
        return recurrent_sum * num_recurrent_sums_and_remainder.quot + _sum(num_recurrent_sums_and_remainder.rem);
    }

private:
    const vector<unsigned long long> _partial_sums = calc_partial_sums();
    frozenset _partial_sums_set = frozenset(cbegin(_partial_sums), end(_partial_sums));
    const size_t _N = _partial_sums.size() - 1;
    const unsigned long _period = _partial_sums.back();

    unsigned long _p(unsigned long k) const {
        for (size_t offset = 0; offset < _N; ++offset) {
            if (_partial_sums_set.count((k + _partial_sums[offset]) % _period))
                return offset + 1;
        }
        return 0;
    }

    unsigned long long _sum(unsigned long sum_upto) const {
        auto answer = 0ULL;
        for (auto i = 1UL; i <= sum_upto; ++i) {
            answer += _p(i);
        }
        return answer;
    }
};


int main() {
    const auto start = chrono::steady_clock::now();
    const PSum p;
    const auto init_time = chrono::steady_clock::now();
    const auto result = p.sum(2 * powl(10, 15));
    const auto end = chrono::steady_clock::now();
    cout << "Result is " << result << endl;
    cout << "Init took " << chrono::duration_cast<chrono::milliseconds>(init_time - start).count() << "ms" << endl;
    cout << "Sum took " << chrono::duration_cast<chrono::milliseconds>(end - init_time).count() << "ms" << endl;
    return 0;
}