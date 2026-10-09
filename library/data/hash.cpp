#include <vector>
#include <queue>
#include <cstdint>
#include <unordered_map>
#include <iostream>
#include <chrono>

const int INF32 = 1e9 + 10;

using namespace std;

/**
 * custom hash function to avoid to get hacked
 * 
 * based on http://xorshift.di.unimi.it/splitmix64.c
 * can be used in unordered_map: unordered_map<int, int, custom_hash>
 */

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    unordered_map<int, int, custom_hash> mp;

    mp[1] = 3;
    mp[3] = 5;

    for (auto [key, val] : mp) {
        cout << key << ": " << val << '\n';
    }


    return 0;
}