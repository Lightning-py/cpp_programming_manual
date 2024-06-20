#include <iostream>
#include <set>
#include <string>
#include <vector>

typedef unsigned long long ull;


int GetDistinctSubstring (std::string a) {
    std::set<ull> substrings_set;

    ull k   = 33;
    ull mod = 10e9 + 7;

    for (int i = 0; i < a.size (); ++i) {
        int sum   = 0;
        int k_pow = 1;

        for (int j = i; j < a.size (); ++j) {
            sum = (sum + ((a[j] - 'a' + 1) * k_pow) % mod) % mod;
            k_pow *= k;
            substrings_set.insert (sum);
        }
    }

    return substrings_set.size ();
}


int main () {
    std::string a = "ahah";

    std::cout << GetDistinctSubstring (a) << std::endl;

    return 0;
}