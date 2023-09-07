#include <iostream>
#include <vector>

using namespace std;
 
typedef vector<int> vi;

const int oo = 1 << 25;
const int ALPHABET = 256;

struct node {
    int start, end, slink;
    int next[ALPHABET];

    int edge_length(int pos) {
        return min(end, pos + 1) - start;
    }
};


