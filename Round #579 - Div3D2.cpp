#include <bits/stdc++.h>
 
#define F first
#define S second
#define MP make_pair
#define PB push_back
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
typedef pair < ll, ll > pll;
typedef vector < ll > vl;
 
const int MAXN = 2e5 + 500;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int LOG = 18;
const double EPS = 1e-9;
const double PI = 3.1415926535;
const int OFF = 1 << 17;
 
string s, t;
int pref[MAXN];
int suf[MAXN];
 
void preprocess() {
    int curr;
 
    curr = 0;
    pref[0] = 0;
    pref[s.size() + 1] = t.size();
    for(int i = 1; i <= s.size(); i++) {
        if(curr >= t.size())
            pref[i] = curr;
        else if(s[i - 1] == t[curr])
            curr ++;
        pref[i] = curr;
    }
 
    curr = 0;
    suf[0] = t.size();
    suf[s.size() + 1] = 0;
    reverse(t.begin(), t.end());
    for(int i = s.size(); i >= 1; i--) {
        if(curr >= t.size())
            suf[i] = curr;
        else if(s[i - 1] == t[curr])
            curr ++;
        suf[i] = curr;
    }
}
 
int binarySearch(int shift, int l, int r) {
    if(l >= r)
        return (l - shift + 1);
 
    int mid = (l + r) / 2;
 
    if(pref[shift - 1] + suf[mid + 1] >= t.size()) {
        if(pref[shift - 1] + suf[mid + 2] < t.size())
            return (mid - shift + 1);
        binarySearch(shift, mid + 1, r);
    }
    else
        binarySearch(shift, l, mid);
}
 
int main() {
    cin >> s >> t;
 
    if(s == t) {
        cout << 0 << endl;
        return 0;
    }
 
    preprocess();
    int ans = 0;
    for(int i = 1; i <= s.size(); i++)
        ans = max(ans, binarySearch(i, i, s.size()));
 
    cout << ans << endl;
 
    return 0;
}