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
const int MAXD = 1005;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int LOG = 18;
const double EPS = 1e-9;
const double PI = 3.1415926535;
const int OFF = 1 << 17;
 
map <ll, int> node;
vector <pii> edges;
vector <int> G[MAXD];
int dist[MAXD];
bool used[MAXD];
ll arr[MAXN];
 
void bfs(int root, pii edge) {
    queue <int> Q;
 
    dist[root] = 0;
    Q.push(root);
 
    while(!Q.empty()) {
        int curr = Q.front();
        used[curr] = true;
        Q.pop();
 
        for(auto next : G[curr]) {
            if(edge.first == curr && edge.second == next)
                continue;
 
            if(edge.first == next && edge.second == curr)
                continue;
 
            if(used[next] == false) {
                dist[next] = dist[curr] + 1;
                used[next] = true;
                Q.push(next);
            }
        }
    }
}
 
void reset() {
    memset(dist, 0, sizeof(dist));
    memset(used, false, sizeof(used));
}
 
int main() {
    int n;
 
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
 
    for(int i = 0; i <= 60; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if((arr[j] & (1LL << i)) != 0) {
                cnt ++;
            }
        }
 
        if(cnt >= 3) {
            cout << 3 << endl;
            return 0;
        }
    }
 
    int node_marker = 0;
    for(int i = 0; i <= 60; i++) {
        ll node1 = -1, node2 = -1;
        for(int j = 0; j < n; j++) {
            if((arr[j] & (1LL << i)) != 0) {
                if(node1 == -1)
                    node1 = arr[j];
                else
                    node2 = arr[j];
            }
        }
 
        if(node1 == -1 || node2 == -1)
            continue;
 
        if(node[node1] == 0) {
            node_marker ++;
            node[node1] = node_marker;
        }
 
        if(node[node2] == 0) {
            node_marker ++;
            node[node2] = node_marker;
        }
 
        G[node[node1]].push_back(node[node2]);
        G[node[node2]].push_back(node[node1]);
        edges.push_back({node[node1], node[node2]});
    }
 
    int ans = INF;
    for(auto rem_edge : edges) {
        bfs(rem_edge.first, rem_edge);
 
        if(dist[rem_edge.second] != 0)
            ans = min(ans, dist[rem_edge.second] + 1);
        reset();
    }
 
    if(ans == INF) {
        cout << "-1" << endl;
        return 0;
    }
 
    cout << ans << endl;
 
    return 0;
}