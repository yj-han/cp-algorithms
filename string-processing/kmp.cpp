#include <iostream>
#include <vector>

using namespace std;
 
typedef vector<int> vi;

vi prefix_function(string s) {
    int n = s.size();
    vi pi(n);

    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j && s[i] != s[j])
            j = pi[j-1];
        
        if (s[i] == s[j])
            j++;
        
        pi[i] = j;
    }
    return pi;
}
