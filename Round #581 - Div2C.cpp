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
 
const int MAXN = 105;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int LOG = 18;
const double EPS = 1e-9;
const double PI = 3.1415926535;
const int OFF = 1 << 17;
 
int dist[MAXN];
int min_dist[MAXN][MAXN];
vector <int> G[MAXN];
vector <int> path;
 
void bfs(int u) {
    for(int i = 0; i < MAXN; i++)
        dist[i] = 0;
 
    queue<int> Q;
    Q.push(u);
    while(!Q.empty()) {
        int v = Q.front();
        Q.pop();
 
        for(auto w : G[v]) {
            if(dist[w] == 0) {
                dist[w] = dist[v] + 1;
                Q.push(w);
            }
        }
    }
    dist[u] = 0;
}
 
int main() {
    int N, M, m;
    string s;
 
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        cin >> s;
        for(int j = 0; j < s.size(); j++)
            if(s[j] == '1')
                G[i].push_back(j + 1);
    }
 
    scanf("%d", &M);
    for(int i = 0; i < M; i++) {
        scanf("%d", &m);
        path.push_back(m);
    }
 
    for(int i = 1; i <= N; i++) {
        bfs(i);
        for(int j = 1; j <= N; j++)
            min_dist[i][j] = dist[j];
    }
 
    int curr = 0;
    vector<int> ans;
    ans.push_back(path[curr]);
    while(curr < M - 1) {
        for(int i = min(M - curr - 1, 100); i >= 1; i--) {
            if(min_dist[path[curr]][path[curr + i]] == i) {
                ans.push_back(path[curr + i]);
                curr = curr + i;
                break;
            }
        }
    }
 
    cout << ans.size() << endl;
    for(auto v : ans)
        cout << v << " ";
    cout << endl;
 
    return 0;
}