#include <bits/stdc++.h>

#include "../debug.h"

using namespace std;
/**
 * trie
 * 
 * arrays implementation for strings
 */

const int N = 100;
const int ALPHABET = 26;
const int MIN_CHAR = 'a'; // 'A' for uppercase

const int MAXNODES = ALPHABET * N;

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

void add(const string& s) {
    int node = 0;
    trie[node].cnt++;
    for (auto c : s) {
        int v = c - MIN_CHAR;
        if (trie[node].childs[v] == 0) {
            trie[node].childs[v] = nodeIte++;
        }
        node = trie[node].childs[v];
        trie[node].cnt++;
    }
    trie[node].end++;
}

// returns the number of strings that start with prefix s
int countPrefix(const string& s) {
    int node = 0;
    for (auto c : s) {
        int v = c - MIN_CHAR;
        if (trie[node].childs[v] == 0) {
            return 0;
        }
        node = trie[node].childs[v];
    }
    return trie[node].cnt;
}

// returns the number of strings exactly equal to s
int countExact(const string& s) {
    int node = 0;
    for (auto c : s) {
        int v = c - MIN_CHAR;
        if (trie[node].childs[v] == 0) {
            return 0;
        }
        node = trie[node].childs[v];
    }
    return trie[node].end;
}

// remove one (and only one) occurence of s from the trie
void erase(const string& s) {
    if (countExact(s) == 0) return; // check that the string exist in the trie
    int node = 0;
    trie[node].cnt--;
    for (auto c : s) {
        int v = c - MIN_CHAR;
        int par = node;
        node = trie[node].childs[v];
        trie[node].cnt--;
        if (trie[node].cnt == 0) {
            trie[par].childs[v] = 0;
        }
    }
    trie[node].end--;
}

int main() {
    add("toto");
    add("tototo");

    cout << countPrefix("toto") << '\n'; // 2
    cout << countExact("toto") << "\n\n"; // 1

    erase("tototo");

    cout << countPrefix("toto") << '\n'; // 1
    cout << countExact("toto") << "\n\n"; // 1

    return 0;
}