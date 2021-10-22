#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int N_MAX = 5000;
const ll MOD = (ll)1e9 + 7;

int n, m;
int parent[N_MAX + 1];
ll sum[N_MAX + 1];
ll dp[N_MAX + 1][N_MAX + 1];

int find(int x){
    if (x != parent[x]){
        return parent[x] = find(parent[x]);
    }
    return x;
}

void merge(int x, int y){
    x = find(x); y = find(y);
    if (x != y){
        parent[y] = x;
    }
    return;
}

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++){
        parent[i] = i;
    }
    
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++){
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * j;
            dp[i][j] %= MOD;
        }
    }
    
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++){
            sum[i] += dp[i][j];
            sum[i] %= MOD;
        }
    }
    
    for (int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        merge(x, y);
        
        int cnt = 0;
        for (int j = 1; j <= n; j++){
            if (parent[j] == j){
                cnt += 1;
            }
        }
        cout << sum[cnt] % MOD << "\n";
    }
    return 0;
}
