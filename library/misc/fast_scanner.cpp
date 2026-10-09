#include <bits/stdc++.h>

using namespace std;

/**
 * fast scanner
 * 
 * can be used to read integer instead of cin
 * 
 * it's faster and might be useful when the input size is around ~ 1e7
 */

struct FastScanner {
    static inline int gc() { return getchar(); }

    int nextInt() {
        int c = gc();
        while (c <= ' ') c = gc();
        int x = 0;
        while (c > ' ') {
            x = x * 10 + (c - '0');
            c = gc();
        }
        return x;
    }
};


int main() {
    FastScanner fs;
    int n = fs.nextInt();
    int m = fs.nextInt();
}