#include <iostream>
#include <vector>
#include <tuple>
#include <string.h>
#include <algorithm>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N_MAX = (int)1e5;

int n;
int p[N_MAX], q[N_MAX];
ll x[N_MAX], y[N_MAX];
ll tree[N_MAX * 4 + 1];

vector<int> idx1, idx2;
vector<pii> v;

bool cmp(pii& a, pii& b){
    if (a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

int getIdx1(int x){
    return (int)(lower_bound(idx1.begin(), idx1.end(), x) - idx1.begin() + 1);
}

int getIdx2(int x){
    return (int)(lower_bound(idx2.begin(), idx2.end(), x) - idx2.begin() + 1);
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

void updateTree(int node, int start, int end, int idx, ll val){
    if (start > idx || end < idx){
        return;
    }
    
    tree[node] += val;
    
    if (start == end){
        return;
    }
    
    int mid = start + (end - start) / 2;
    updateTree(node * 2, start, mid, idx, val);
    updateTree(node * 2 + 1, mid + 1, end, idx, val);
    
    return;
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> p[i];
        idx1.push_back(p[i]);
    }
    
    sort(idx1.begin(), idx1.end());
    idx1.erase(unique(idx1.begin(), idx1.end()), idx1.end());
    
    for (int i = 0; i < n; i++){
        cin >> q[i];
        idx2.push_back(q[i]);
    }
    
    sort(idx2.begin(), idx2.end());
    idx2.erase(unique(idx2.begin(), idx2.end()), idx2.end());
    
    for (int i = 0; i < n; i++){
        v.push_back({getIdx1(p[i]), getIdx2(q[i])});
    }
    
    sort(v.begin(), v.end(), cmp);
    
    for (int i = 0; i < n; i++){
        x[i] = getSum(1, 1, n, 1, v[i].second - 1);
        updateTree(1, 1, n, v[i].second, 1);
    }
    
    memset(tree, 0, sizeof(tree));
    
    for (int i = n - 1; i >= 0; i--){
        y[i] = getSum(1, 1, n, v[i].second + 1, n);
        updateTree(1, 1, n, v[i].second, 1);
    }
    
    ll ans = 0;
    for (int i = 0; i < n; i++){
        ans += x[i] * y[i];
    }
    
    cout << ans << "\n";
    
    return 0;
}
