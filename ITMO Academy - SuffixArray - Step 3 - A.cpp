#include <bits/stdc++.h>
 
using namespace std;
 
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
 
bool binarySearch(int lo, int hi, vector <int> &p, string &t, string &query) {
    if(hi >= lo) {
        int mid = lo + (hi - lo) / 2;
 
        string pref = t.substr(p[mid], min(query.size(), t.size() - p[mid])); 
 
        if(query == pref) {
            return true;
        } else if(query < pref) {
            return binarySearch(lo, mid - 1, p, t, query);
        } else {
            return binarySearch(mid + 1, hi, p, t, query);
        }
    }
 
    return false;
}
 
 
int main() {
    int n_queries;
    string text;
    cin >> text >> n_queries;
 
    vector <string> queries(n_queries);
    for(int i = 0; i < n_queries; i++) {
        cin >> queries[i];
    }
 
    text += "$";
    int n = text.size();
 
    vector <int> p(n), c(n);
    vector <pair <char, int> > a(n);
    
    // k = 0
    for(int i = 0; i < n; i++) {
        a[i] = {text[i], i};
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
 
    for(auto query : queries) {
        if(binarySearch(0, n - 1, p, text, query)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
 
    return 0;
}