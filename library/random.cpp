#include <bits/stdc++.h>
// #include <random>

using namespace std;

/**
 * custom hash function to avoid to get hacked
 * 
 * based on http://xorshift.di.unimi.it/splitmix64.c
 * 
 * Usage:
 *  - unordered_map: unordered_map<int, int, custom_hash>
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

/**
 * Random generators based on Mersenne Twister 19937
 * 
 * Versions:
 *  - 32-bit output: mt19937 rng(seed)
 *  - 64-bit output: mt19937_64 rng(seed)
 * 
 * Initialization:
 *  - fix seed: mt19937 rng(seed)
 *  - random seed: mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
 * 
 * U ~ Uniform([a, b]):
 *  - int u = a + rng() % (b - a + 1)
 *  - uniform_int_distribution<int> dist(a, b);
 *    int u = dist(rng)
 * 
 * For most problems, it is enough to use:
 *    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
 *    int u = rng() % n
 */

using namespace std;

void mersenneTwister32() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //mt19937 rng32(42);
    for (int i = 0; i < 10; i++) {
        cout << rng() % 10 << '\n';
    }
}

void mersenneTwister32Uniform() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        cout << dist(rng) << '\n';
    }
}

void mersenneTwister64() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    //mt19937_64 rng32(42);
    for (int i = 0; i < 10; i++) {
        cout << rng() % 10 << '\n';
    }
}

int main() {

    unordered_map<int, int, custom_hash> map;

    cout << "Mersenne Twister 32-bit output:\n";
    mersenneTwister32();
    cout << "Mersenne Twister Uniform 32-bit output:\n";
    mersenneTwister32Uniform();
    cout << "Mersenne Twister 64-bit output:\n";
    mersenneTwister64();

    return 0;
}