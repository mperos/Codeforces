#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    string s;
    cin >> s;
    s += "$";
 
    int n = s.size();
    vector <int> p(n);    // redoslijed dosad izgrađenih stringova
    vector <int> c(n);    // klasa ekvivalencije kojoj pripada trenutno izgrađeni stringovi
 
    // k = 0
    vector <pair <char, int> > a(n);
    for(int i = 0; i < n; i++) {
        a[i] = {s[i], i};           // inicijaliziranje za svaki znak
    }
 
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        p[i] = a[i].second;
    }
 
    c[p[0]] = 0;                    // inicijaliziranje prve po redu klase
    for(int i = 1; i < n; i++) {    // odredivanje kojoj klasi ekvivalencije string pripada
        if(a[i].first == a[i - 1].first) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }
 
    // k -> k + 1
    int k = 0;
    while((1 << k) < n) {           // analogno kao u prvom komadu samo smo string podijelili na L i D
        vector < pair < pair <int, int>, int > > a(n); 
        for(int i = 0; i < n; i++) {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};  
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
        k++;
    }
 
    for(int i = 0; i < n; i++) {
        cout << p[i] << " ";
    } cout << endl;
}