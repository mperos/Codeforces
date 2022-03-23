#include <bits/stdc++.h>
 
using namespace std;
 
// Suffix Array O(n log n)
// koristimo O(n) counting sort umjesto implementiranog C++ sorta
 
void count_sort(vector <int> &p, vector <int> &c) {
    int n = p.size();
    vector <int> cnt(n);
    for(auto val : c) {
        cnt[val] ++;
    }
 
    vector <int> pos(n);
    pos[0] = 0;
    for(int i = 1; i < n; i++) {    // da znas u koje buckete koga stavljas
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
 
    vector <int> p_new(n);
    for(auto val : p) {
        int cls = c[val];
        p_new[pos[cls]] = val;
        pos[cls] ++;
    }
    p = p_new;
}
 
vector <int> lcp_construct(string &s, vector <int> &p) {
    int n = s.size();
    vector <int> rank(n);
    for(int i = 0; i < n; i++) {
        rank[p[i]] = i;
    }
 
    int h = 0;
    vector <int> lcp(n - 1);
    for(int i = 0; i < n - 1; i++) {    // iteriramo po duljini suffixa (rank[i] pokazuje mjesto u p-u)
        int j = p[rank[i] - 1];         // prethodni suffix
        while(i + h < n && j + h < n && s[i + h] == s[j + h]) { 
            h ++; 
        }
 
        lcp[rank[i] - 1] = h;
        if(h != 0) {
            h--;
        }
    }
 
    return lcp;
}
 
int main() {
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
 
    vector <int> p(n), c(n);
    vector <pair <char, int> > a(n);
    
    // k = 0
    for(int i = 0; i < n; i++) {
        a[i] = {s[i], i};
    }
 
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        p[i] = a[i].second;
    }
 
    c[p[0]] = 0;
    for(int i = 1; i < n; i++) {
        if(a[i].first == a[i - 1].first) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }
 
    int k = 0;
    while((1 << k) < n) {
        // k -> k + 1
        for(int i = 0; i < n; i++) {    // shift ulijevo (da desna polovica bude sortirana)
            p[i] = (p[i] - (1 << k) + n) % n;
        }
 
        count_sort(p, c);   // sortirano i po lijevoj polovici
 
        // update klase c
        vector <int> c_new(n);
        c_new[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair <int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair <int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
 
            if(prev == now) {
                c_new[p[i]] = c_new[p[i - 1]];
            } else {
                c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
        }
        c = c_new;
        k ++;
    }
 
    for(auto var : p) {
        cout << var << " ";
    } cout << endl;
 
    vector <int> lcp = lcp_construct(s, p);
    for(auto var : lcp) {
        cout << var << " ";
    } cout << endl;
}