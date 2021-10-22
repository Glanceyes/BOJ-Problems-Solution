#include <iostream>
#include <vector>
#include <tuple>
#include <string.h>
#include <algorithm>
using namespace std;
using ppi = pair<pair<int, int>, int>;
using ll = long long;

const int N_MAX = (int)1e5 * 2;
const ll MOD = (ll)1e9 + 7;

struct Coordinate{
    int cx, cy, idx;
    
    Coordinate(int cx, int cy, int idx): cx(cx), cy(cy), idx(idx){}
    
    bool operator<(const Coordinate& u) const{
        if (cx == u.cx){
            return cy < u.cy;
        }
        return cx < u.cx;
    }
};

int n;
ll tree[N_MAX * 4 + 1];
int x[N_MAX], y[N_MAX];
ll l[N_MAX], r[N_MAX];

vector<Coordinate> star;

bool cmp(Coordinate& a, Coordinate& b){
    if (a.cx == b.cx){
        return a.cy > b.cy;
    }
    return a.cx < b.cx;
}

int getIdx(vector<int>& v, int val){
    return (int)(lower_bound(v.begin(), v.end(), val) - v.begin() + 1);
}

void updateTree(int node, int start, int end, int idx, ll val){
    if (start > idx || end < idx){
        return;
    }
    
    tree[node] += val;
    
    if (start != end){
        int mid = start + (end - start) / 2;
        updateTree(node * 2, start, mid, idx, val);
        updateTree(node * 2 + 1, mid + 1, end, idx, val);
    }
    return;
}

ll getSum(int node, int start, int end, int left, int right){
    if (left > end || right < start){
        return 0;
    }
    
    if (left <= start && end <= right){
        return tree[node];
    }
    
    int mid = start + (end - start) / 2;
    return getSum(node * 2, start, mid, left, right) + getSum(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    vector<int> nx, ny;
    
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> x[i] >> y[i];
        nx.push_back(x[i]);
        ny.push_back(y[i]);
    }
    
    sort(nx.begin(), nx.end());
    sort(ny.begin(), ny.end());
    
    nx.erase(unique(nx.begin(), nx.end()), nx.end());
    ny.erase(unique(ny.begin(), ny.end()), ny.end());
    
    for (int i = 0; i < n; i++){
        star.push_back(Coordinate(getIdx(nx, x[i]), getIdx(ny, y[i]), 0));
    }
    
    sort(star.begin(), star.end());
    
    for (int i = 0; i < n; i++){
        star[i].idx = i;
    }
    
    for (int i = 0; i < n; i++){
        l[star[i].idx] = getSum(1, 1, n, star[i].cy + 1, n);
        updateTree(1, 1, n, star[i].cy, 1);
    }
    
    memset(tree, 0, sizeof(tree));
    sort(star.begin(), star.end(), cmp);
    
    for (int i = n - 1; i >= 0; i--){
        r[star[i].idx] = getSum(1, 1, n, star[i].cy + 1, n);
        updateTree(1, 1, n, star[i].cy, 1);
    }
    
    ll ans = 0;
    
    for (int i = 0; i < n; i++){
        ans += l[i] * r[i];
        ans %= MOD;
    }
    cout << ans << "\n";
    
    return 0;
}
