#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N_MAX = (int)1e5;
const int D_MAX = 20;

int n, m, num;
int in[N_MAX + 1];
int out[N_MAX + 1];
int depth[N_MAX + 1];
int tree[N_MAX * 4 + 1];
int dp[N_MAX + 1][D_MAX];

vector<int> edges[N_MAX + 1];

void swap(int& a, int &b){
    int temp = a; a = b; b = temp;
    return;
}

void dfs(int now, int parent){
    in[now] = (++num);
    depth[now] = depth[parent] + 1;
    
    for (auto next: edges[now]){
        if (next != parent){
            dp[next][0] = now;
            dfs(next, now);
        }
    }
    
    out[now] = num;
}

int lca(int a, int b){
    if (depth[a] < depth[b]){
        swap(a, b);
    }
    
    int diff = depth[a] - depth[b];
    
    for (int i = 0; i < D_MAX && diff; i++, diff /= 2){
        if (diff % 2){
            a = dp[a][i];
        }
    }
    
    if (a != b){
        for (int i = D_MAX - 1; i >= 0; i--){
            if (dp[a][i] != dp[b][i]){
                a = dp[a][i]; b = dp[b][i];
            }
        }
        a = dp[a][0];
    }
    
    return a;
}

void update(int node, int start, int end, int idx, int val){
    if (idx < start || idx > end) return;
    
    tree[node] += val;
    
    if (start == end){
        return;
    }
    
    int mid = start + (end - start) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);
    return;
}

int query(int node, int start, int end, int left, int right){
    if (left > end || right < start){
        return 0;
    }
    if (left <= start && end <= right){
        return tree[node];
    }
    
    int mid = start + (end - start) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> n >> m;
    
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    dfs(1, 0);
    
    for (int j = 1; j < D_MAX; j++) {
            for (int i = 1; i <= n; i++) {
                if (dp[i][j - 1] != -1) {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                }
            }
        }
    
    for (int i = 0; i < m; i++){
        char c; int u, v;
        cin >> c >> u >> v;
        
        int x;
        if (c == 'P'){
            x = lca(u, v);
            update(1, 1, n, in[u], 1);
            update(1, 1, n, in[v], 1);
            update(1, 1, n, in[x], -2);
        }
        else if (c == 'Q'){
            if (in[u] < in[v]){
                x = v;
            }
            else {
                x = u;
            }
            
            cout << query(1, 1, n, in[x], out[x]) << "\n";
        }
    }
    
    return 0;
}
