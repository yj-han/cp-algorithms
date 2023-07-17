#include <bits/stdc++.h>
using namespace std;

const int K = 26;

struct Trie {
    Trie* t[K];
    bool end;

    Trie() {
        memset(t, 0, sizeof(t));
        end = false;
    }

    ~Trie() {
        for (int i = 0; i < K; i++) {
            if (t[i]) delete t[i];
        }
    }

    void insert(string& s, int idx) {
        if (idx == s.length()) {
            end = true;
            return;
        }
        if (!t[s[idx]-'a']) {
            t[s[idx]-'a'] = new Trie();
        }
        t[s[idx]-'a']->insert(s, idx+1);
    }

    bool solve(string& s, int idx) {
        if (idx == s.length()) return false;
        if (!t[s[idx]-'a']) return false;
        if (t[s[idx]-'a']->end) return true;
        return t[s[idx]-'a']->solve(s, idx+1);
    }
};