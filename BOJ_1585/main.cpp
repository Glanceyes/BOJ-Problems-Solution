#include <cstdio>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

const int N_MAX = 50;
const int V_MAX = N_MAX * 2 + 2;
const int INF = 0x3f3f3f3f;

int n, t, f;
int prv[V_MAX + 2];
int dst[V_MAX + 2];
int in[N_MAX + 2];
int out[N_MAX + 2];
int cap[V_MAX + 2][V_MAX + 2];
int flw[V_MAX + 2][V_MAX + 2];
int cst[V_MAX + 2][V_MAX + 2];
vector<int> edges[V_MAX + 2];

int SPFA(int start, int end){
    int flow = 0, ans = 0;
    bool inQ[V_MAX] = { false };
    while(1){
        memset(prv, -1, sizeof(prv));
        memset(dst, 0x3f, sizeof(dst));
        memset(inQ, false, sizeof(inQ));
        
        queue<int> q; q.push(start);
        dst[start] = 0; inQ[start] = true;
        
        while(!q.empty()){
            int now = q.front(); q.pop();
            inQ[now] = false;
            
            for (auto next: edges[now]){
                if (cap[now][next] > flw[now][next] && dst[next] > dst[now] + cst[now][next]){
                    dst[next] = dst[now] + cst[now][next];
                    prv[next] = now;
                    if (!inQ[next]){
                        q.push(next);
                        inQ[next] = true;
                    }
                }
            }
        }
        
        if (prv[end] == -1) break;
        
        int minFlow = INF;
        for (int i = end; i != start; i = prv[i]){
            minFlow = min(minFlow, cap[prv[i]][i] - flw[prv[i]][i]);
        }
        
        for (int i = end; i != start; i = prv[i]){
            ans += minFlow * cst[prv[i]][i];
            flw[prv[i]][i] += minFlow;
            flw[i][prv[i]] -= minFlow;
        }
        
        flow += minFlow;
    }
    
    if (flow < n){
        return -1;
    }
    
    return (ans > 0) ? ans : (-ans);
}

int main(){
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++){
        scanf("%d", &in[i]);
    }
    
    for (int i = 1; i <= n; i++){
        scanf("%d", &out[i]);
    }
    
    scanf("%d %d", &t, &f);
    
    for (int i = 1; i <= n; i++){
        cap[0][i] = 1;
        edges[0].push_back(i);
        edges[i].push_back(0);
        for (int j = 1; j <= n; j++){
            int diff = out[j] - in[i];
            // 도로를 통과하는 데 적어도 1초는 걸림
            if (diff < 1){
                continue;
            }
            // 차가 과속을 한 경우
            if (diff < t){
                int cost = min(f, (t - diff) * (t - diff));
                cst[i][j + N_MAX] = cost;
                cst[j + N_MAX][i] = -cost;
            }
            cap[i][j + N_MAX] = 1;
            edges[i].push_back(j + N_MAX);
            edges[j + N_MAX].push_back(i);
        }
    }
    
    for (int i = 1; i <= n; i++){
        cap[i + N_MAX][V_MAX - 1] = 1;
        edges[i + N_MAX].push_back(V_MAX - 1);
        edges[V_MAX - 1].push_back(i + N_MAX);
    }
    
    int minCost = SPFA(0, V_MAX - 1);
    
    for (int i = 0; i < V_MAX; i++){
        for (int j = 0; j < V_MAX; j++){
            flw[i][j] = 0;
            cst[i][j] = -cst[i][j];
        }
    }
    
    int maxCost = SPFA(0, V_MAX - 1);

    if (minCost == -1 || maxCost == -1){
        printf("-1\n");
    }
    else {
        printf("%d %d\n", minCost, maxCost);
    }
    
    return 0;
}
