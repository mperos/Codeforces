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
 
vector <int> arr;
int used[MAXN];
 
int main() {
    int n, x;
 
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        arr.push_back(x);
    }
 
    sort(arr.begin(), arr.end());
    for(auto x : arr) {
        if(x == 1) {
            if(used[x] == 0)
                used[x] = 1;
            else if(used[x + 1] == 0)
                used[x + 1] = 1;
        }
        else {
            if(used[x - 1] == 0)
                used[x - 1] = 1;
            else if(used[x] == 0)
                used[x] = 1;
            else if(used[x + 1] == 0)
                used[x + 1] = 1;
        }
    }
 
    int ans = 0;
    for(int i = 1; i < MAXN; i++)
        ans += used[i];
 
    cout << ans << endl;
 
    return 0;
}
