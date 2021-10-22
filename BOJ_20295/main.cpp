#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

const int N_MAX = (int)1e5;
const int D_MAX = 20;

int n, m;
int kind[N_MAX + 1];
int cache[N_MAX + 1];
int depth[N_MAX + 1];
int dp[N_MAX + 1][D_MAX];
int bit[N_MAX + 1][D_MAX];

vector<int> edges[N_MAX + 1];

void swap(int& a, int &b){
    int temp = a; a = b; b = temp;
    return;
}

void dfs(int now, int parent){
    depth[now] = depth[parent] + 1;
    bit[now][0] |= cache[now];
    
    for (auto next: edges[now]){
        if (next != parent){
            dp[next][0] = now;
            bit[next][0] |= cache[now];
            dfs(next, now);
        }
    }
}

int lca(int a, int b){
    int ret = cache[a] | cache[b];
    if (depth[a] < depth[b]){
        swap(a, b);
    }
    
    int diff = depth[a] - depth[b];
    
    for (int i = 0; i < D_MAX && diff; i++, diff /= 2){
        if (diff % 2){
            ret |= bit[a][i];
            a = dp[a][i];
        }
    }
    
    if (a != b){
        for (int i = D_MAX - 1; i >= 0; i--){
            if (dp[a][i] != dp[b][i]){
                ret |= bit[a][i];
                ret |= bit[b][i];
                a = dp[a][i];
                b = dp[b][i];
                
            }
        }
        ret |= bit[a][0];
        ret |= bit[b][0];
    }
    
    return ret;
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> n;
    
    for (int i = 1; i <= n; i++){
        cin >> kind[i];
        cache[i] |= 1 << (kind[i] - 1);
    }
    
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    dfs(1, 0);
    
    for (int j = 1; j < D_MAX; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            bit[i][j] |= bit[i][j - 1];
            bit[i][j] |= bit[dp[i][j - 1]][j - 1];
        }
    }
    
    cin >> m;
    
    for (int i = 0, prev = 0; i < m; i++){
        int num, like;
        cin >> num >> like;
        if (i == 0){
            bool exist = false;
            for (int i = 1; i <= n; i++){
                if (kind[i] == like){
                    exist = true;
                    break;
                }
            }
            if (exist){
                cout << "PLAY\n";
            }
            else {
                cout << "CRY\n";
            }
            
        }
        else {
            int res = lca(num, prev);
            if (res & (1 << (like - 1))){
                cout << "PLAY\n";
            }
            else {
                cout << "CRY\n";
            }
        }
        prev = num;
    }
    
    return 0;
}
