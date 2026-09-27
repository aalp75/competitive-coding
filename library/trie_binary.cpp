#include <bits/stdc++.h>

#include "../debug.h"

using namespace std;

/**
 *  Note: the pointer implementation of a Trie is probably easier to understand 
 *  but in competitive programming it's better to use the array implementation 
 *  to avoid dynamic memory allocation that can cause TLE (living on the heap) 
 *  and MLE (memory leak)
 */

/**
 * trie
 * 
 * arrays implementation for binary number
 */

const int N = 100;
const int ALPHABET = 2;
const int B = 30; // bit-length

const int MAXNODES = ALPHABET * B * N;

struct Node {
    int cnt;
    int end;
    int childs[ALPHABET];

    Node() : cnt(0), end(0) {
        for (int i = 0; i < ALPHABET; i++) {
            childs[i] = 0;
        }
    }

    void reset() {
        cnt = 0;
        end = 0;
        for (int i = 0; i < ALPHABET; i++) {
            childs[i] = 0;
        }
    }
};

Node trie[MAXNODES];
int nodeIte = 1;

void clear() {
    for (int i = 0; i <= nodeIte; i++) {
        trie[i].reset();
    }
    nodeIte = 1;
}

void add(int x) {
    int node = 0;
    trie[node].cnt++;
    for (int b = B; b >= 0; b--) {
        int p2 = 1 << b;
        if (x & p2) {
            if (trie[node].childs[1] == 0) {
                trie[node].childs[1] = nodeIte++;
            }
            node = trie[node].childs[1];
        }
        else {
            if (trie[node].childs[0] == 0) {
                trie[node].childs[0] = nodeIte++;
            }
            node = trie[node].childs[0];
        }
        trie[node].cnt++;
    }
    trie[node].end++;
}

// compute the maximum XOR with s possible
// it assumes that the trie is not empty
// otherwise it will return 0
int computeXor(int x) {
    int node = 0;
    int res = 0;
    for (int b = B; b >= 0; b--) {
        int p2 = 1 << b;
        if (x & p2) {
            if (trie[node].childs[0] != 0) {
                node = trie[node].childs[0];
                res |= p2;
            }
            else {
                node = trie[node].childs[1];
            }
        }
        else {
            if (trie[node].childs[1] != 0) {
                node = trie[node].childs[1];
                res |= p2;
            }
            else {
                node = trie[node].childs[0];
            }
        }
    }
    return res;
}

// find the k-th smaller values x ^ e among all elements e
int findkth(int x, int k) {
    int node = 0;
    int res = 0;
    for (int b = B; b >= 0; b--) {
        int p2 = 1 << b;
        int pref = trie[node].childs[0];
        int opp = trie[node].childs[1];
        if (p2 & x) swap(pref, opp);

        int cnt = 0;
        if (pref != 0) {
            cnt = trie[pref].cnt;
        }
        if (k <= cnt) {
            node = pref;
        }
        else {
            k -= cnt;
            res |= p2;
            node = opp;
        }
    }
    return res;
}   

// remove one (and only one) occurence of s from the trie
// it assumes that the number x is in the trie
void erase(int x) {
    int node = 0;
    trie[node].cnt--;
    for (int b = B; b >= 0; b--) {
        int p2 = 1 << b;
        int par = node;
        int bit = (x & p2) ? 1 : 0;

        node = trie[node].childs[bit];

        trie[node].cnt--;
        if (trie[node].cnt == 0) {
            trie[par].childs[bit] = 0;
        }
    }
    trie[node].end--;
}

int main() {
    add(3);
    add(5);
    add(7);
    add(8);

    cout << computeXor(11) << '\n'; // 14

    erase(7);
    
    cout << computeXor(8) << '\n'; // 13

    cout << findkth(3, 2) << '\n'; // 

    return 0;
}