#include <bits/stdc++.h>
using namespace std;

class SuffixArray {
private:
    string s;
    vector<int> suffix, rank, temp_rank, lcp;
    int sz;

    void make_suffix_array();
    void make_lcp();
    void update() { 
        make_suffix_array();
        make_lcp(); 
    }

public:
    SuffixArray(string& s) : s(s), sz(s.size()) { 
        update(); 
    }

    void change_string(string& s) { 
        s = s; 
        sz = s.size();
        update(); 
    }

    vector<int> get_suffix_array() { 
        return suffix; 
    }

    vector<int> get_lcp() { 
        return lcp; 
    }
};

void SuffixArray::make_suffix_array() {
    suffix.assign(sz, 0);
    rank.assign(sz + 1, -1);
    temp_rank.assign(sz + 1, -1);

    // ex) String = "banana" / Suffix = {0, 1, 2, 3, 4, 5}, Rank = {98, 97, 110, 97, 110, 97, -1}
    for (int i = 0; i < sz; i++) {
        suffix[i] = i;
        rank[i] = s[i];
    }

    for (int compare_length = 1; compare_length < sz; compare_length <<= 1) {
        auto cmp = [&](int x, int y) {
            if (rank[x] == rank[y])
                return rank[x + compare_length] < rank[y + compare_length];
            return rank[x] < rank[y];
        };

        sort(suffix.begin(), suffix.end(), cmp);
        temp_rank[suffix[0]] = 0;

        for (int i = 1; i < sz; i++) {
            if (cmp(suffix[i - 1], suffix[i]))
                temp_rank[suffix[i]] = temp_rank[suffix[i - 1]] + 1;
            else
                temp_rank[suffix[i]] = temp_rank[suffix[i - 1]];
        }
        rank = temp_rank;
    }
}

void SuffixArray::make_lcp() {
    lcp.assign(sz, 0);
    rank.assign(sz, 0);

    for (int i = 0; i < sz; i++)
        rank[suffix[i]] = i;

    int len = 0;
    for (int i = 0; i < sz; i++) {
        int curr_rank = rank[i];

        if (curr_rank > 0) {
            int j = suffix[curr_rank - 1];

            while (i+len < sz && j+len < sz && s[i+len] == s[j+len])
                len++;
            lcp[curr_rank] = len;

            if (len) {
                len--;
            }
        }
    }
}