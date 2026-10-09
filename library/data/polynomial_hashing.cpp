#include <vector>
#include <string>

using namespace std;

/**
 * polynomial hashing
 * 
 * MOD = 1e9 + 9 is recommended
 * base = 2 for binary string
 * base = 31 for lowercase characters string
 * 2 versions available: vector<int> and string
 */

 const int MOD = 1e9 + 7;

long long compute_hash(vector<int>& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (int value : s) {
        hash_value = (hash_value + value * base_power) % MOD;
        base_power = base_power * base % MOD;
    }
    return hash_value;
}

long long compute_hash(const string& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (char c : s) {
        long long value = c -'a' + 1;
        hash_value = (hash_value + value* base_power) % MOD;
        base_power = base_power * base % MOD;
    }
    return hash_value;
}