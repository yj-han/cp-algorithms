#include <bits/stdc++.h>

using namespace std;

struct SuffixAuto {
    struct State {
        int len, link;
        int next[26];
        State(int _len = 0, int _link = -1) : len(_len), link(_link) {
            memset(next, -1, sizeof(next));
        }
    };

    vector<State> states;
    int last;

    SuffixAuto() {}

    SuffixAuto(const string &s) {
        init(s);
    }

    inline int state(int len = 0, int link = -1) {
        states.emplace_back(len, link);
        return states.size() - 1;
    }

    void init(const string &s) {
        states.reserve(2 * s.size());
        last = state();
        for (char c : s) {
            extend(c);
        }
    }

    void extend(char _c) {
        int c = _c - 'a';
        int cur = state(states[last].len + 1), p = last;
        while (p != -1 && states[p].next[c] == -1) {
            states[p].next[c] = cur;
            p = states[p].link;
        }

        if (p == -1) {
            states[cur].link = 0;
        } else {
            int q = states[p].next[c];
            if (states[p].len + 1 == states[q].len) {
                states[cur].link = q;
            } else {
                int C = state(states[p].len + 1, states[q].link);
                copy(states[q].next, states[q].next + 26, states[C].next);
                while (p != -1 && states[p].next[c] == q) {
                    states[p].next[c] = C;
                    p = states[p].link;
                }
                states[q].link = states[cur].link = C;
            }
        }
        last = cur;
    }
};

