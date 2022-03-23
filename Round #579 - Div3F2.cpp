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
 
const int MAXN = 1e5 + 500;
const int MAXD = 105;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int LOG = 18;
const double EPS = 1e-9;
const double PI = 3.1415926535;
const int OFF = 1 << 17;
 
vector <pii> pos_projects;
vector <pii> neg_projects;
int dp[MAXN][MAXD];
 
bool pos_cmp(pii x, pii y) {
    return (x.first < y.first);
}
 
bool neg_cmp(pii x, pii y) {
    return (x.first + x.second >= y.first + y.second);
}
 
int main() {
    int n, r, ai, bi;
 
    scanf("%d%d", &n, &r);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &ai, &bi);
        if(bi >= 0) {
            pos_projects.push_back({ai, bi});
        }
        else {
            neg_projects.push_back({ai, bi});
        }
    }
 
    sort(pos_projects.begin(), pos_projects.end(), pos_cmp);
    sort(neg_projects.begin(), neg_projects.end(), neg_cmp);
 
    int cnt = 0;
    for(auto pr : pos_projects) {
        if(r >= pr.first) {
            cnt ++;
            r = r + pr.second;
        }
    }
 
    dp[r][0] = 1;
    for(int item = 0; item < neg_projects.size(); item ++) {
        ai = neg_projects[item].first;
        bi = neg_projects[item].second;
        for(int rating = 0; rating <= 1e5; rating ++) {
            if(dp[rating][item] != 0) {
                if(rating + bi >= 0 && rating >= ai)
                    dp[rating + bi][item + 1] = max(dp[rating + bi][item + 1], dp[rating][item] + 1);
                dp[rating][item + 1] = max(dp[rating][item + 1], dp[rating][item]);
            }
        }
    }
 
    int ans = 0;
    for(int rating = 0; rating <= 1e5; rating ++)
        ans = max(ans, dp[rating][neg_projects.size()]);
 
    cout << ans + cnt - 1 << endl;
    return 0;
}