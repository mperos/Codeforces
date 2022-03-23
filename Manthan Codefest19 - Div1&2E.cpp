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
 
const int MAXN = 1e6 + 500;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int LOG = 18;
const double EPS = 1e-9;
const double PI = 3.1415926535;
const int OFF = 1 << 20;
 
int arr[MAXN], offset;
int maxi_tree[2 * OFF];
ll tree[2 * OFF];
ll prop[2 * OFF];
 
void refresh(int i) {
    if(prop[i] == 0)
        return;
 
    tree[i] = tree[i] + prop[i];
    if(i < offset) {
        prop[2 * i] += prop[i];
        prop[2 * i + 1] += prop[i];
    }
    prop[i] = 0;
}
 
void update(int i, int l, int r, int ql, int qr, ll val) {
    if(ql > qr)
        return;
 
    refresh(i);
    if(ql <= l && r <= qr) {
        prop[i] = prop[i] + val;
        refresh(i);
        return;
    }
 
    if(r < ql || qr < l)
        return;
 
    update(2 * i, l, (l + r) / 2, ql, qr, val);
    update(2 * i + 1, (l + r) / 2 + 1, r, ql, qr, val);
}
 
void fill_tree(int i) {
    refresh(i);
    if(i >= offset)
        return;
 
    fill_tree(2 * i);
    fill_tree(2 * i + 1);
}
 
void update_maxi(int i, int l, int r, int ql, int qr, int val) {
    if(ql <= l && r <= qr) {
        maxi_tree[i] = max(maxi_tree[i], val);
        return;
    }
 
    if(r < ql || qr < l)
        return;
 
    update_maxi(2 * i, l, (l + r) / 2, ql, qr, val);
    update_maxi(2 * i + 1, (l + r) / 2 + 1, r, ql, qr, val);
}
 
void fill_maxi_tree(int i) {
    if(i >= offset)
        return;
 
    maxi_tree[2 * i] = max(maxi_tree[2 * i], maxi_tree[i]);
    maxi_tree[2 * i + 1] = max(maxi_tree[2 * i + 1], maxi_tree[i]);
 
    fill_maxi_tree(2 * i);
    fill_maxi_tree(2 * i + 1);
}
 
void preprocess(int n) {
    for(int i = 0; i <= 21; i++) {
        if((1 << i) > n) {
            offset = (1 << i);
            break;
        }
    }
 
    for(int i = 1; i < 2 * offset; i++)
        maxi_tree[i] = -INF;
}
 
void reset() {
    for(int i = 1; i < 2 * offset; i++)
        maxi_tree[i] = -INF;
}
 
void check() {
    cout << "MAXI_TREE: " << endl;
    for(int j = offset; j < 2 * offset; j++)
        cout << maxi_tree[j] << " ";
    cout << endl;
}
 
void check1() {
    cout << "TREE: " << endl;
    for(int j = offset; j < 2 * offset; j++)
        cout << tree[j] << " ";
    cout << endl;
}
 
int main() {
    int n, w, len;
 
    scanf("%d", &n);
    scanf("%d", &w);
    preprocess(w);
    for(int i = 0; i < n; i++) {
        scanf("%d", &len);
        for(int j = 1; j <= len; j++)
            scanf("%d", &arr[j]);
 
        if(2 * len - 1 <= w) {
            int m;
            int L = len;
            int R = w - len + 1;
            int L0 = len + 1;
            int R0 = w - len;
 
            m = -INF;
            for(int j = 1; j < L; j++) {
                m = max(m, arr[j]);
                if(j <= R0)
                    update(1, 1, offset, j, j, max(0, m));
                else
                    update(1, 1, offset, j, j, m);
            }
 
            m = -INF;
            for(int j = w; j > R; j--) {
                m = max(m, arr[j - w + len]);
                if(j >= L0)
                    update(1, 1, offset, j, j, max(0, m));
                else
                    update(1, 1, offset, j, j, m);
            }
 
            m = -INF;
            for(int j = 1; j <= len; j++)
                m = max(m, arr[j]);
 
            if(L0 <= R0) {
                update(1, 1, offset, L, R, max(0, m));
            }
 
            else {
                if(L0 <= R && L <= R0) {
                    update(1, 1, offset, L0, R, max(0, m));
                    update(1, 1, offset, L, R0, max(0, m));
                    update(1, 1, offset, R0 + 1, L0 - 1, m);
                }
                else {
                    update(1, 1, offset, L, R, m);
                }
            }
        }
 
        else {
            update_maxi(1, 1, offset, len + 1, w, 0);
            update_maxi(1, 1, offset, 1, w - len, 0);
 
            for(int j = 1; j <= len; j++) {
                update_maxi(1, 1, offset, j, j + w - len, arr[j]);
            }
 
            fill_maxi_tree(1);
            for(int j = 1; j <= w; j++)
                update(1, 1, offset, j, j, maxi_tree[j + offset - 1]);
 
            reset();
        }
    }
 
    fill_tree(1);
    for(int i = offset; i < offset + w; i++)
        cout << tree[i] << " ";
    cout << endl;
 
    return 0;
}
 