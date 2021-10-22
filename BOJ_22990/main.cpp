#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int N_MAX = 200;
const int V_MAX = N_MAX * 2 + 2;
const ll INF = LLONG_MAX;

int n, m;

struct MCMF{
    struct Edge{
        int to; ll cap, flow, cost;
        Edge *rev;
        Edge(int to, ll cap, ll flow, ll cost): to(to), cap(cap), flow(flow), cost(cost){}
        void addFlow(ll flw){
            flow += flw;
            rev->flow -= flw;
        }
        ll left(){
            return cap - flow;
        }
    };

    int prv[V_MAX];
    ll dst[V_MAX];
    Edge* path[V_MAX];
    vector<Edge*> edges[V_MAX];
    
    void addEdge(int u, int v, ll c, ll cst){
        Edge *e1 = new Edge(v, c, 0, cst);
        Edge *e2 = new Edge(u, 0, 0, -cst);
        e1->rev = e2;
        e2->rev = e1;
        edges[u].push_back(e1);
        edges[v].push_back(e2);
    }
    
    bool SPFA(int start, int end){
        bool inQ[V_MAX] = {false};
        memset(prv, -1, sizeof(prv));
        memset(path, 0, sizeof(path));
        memset(dst, 0x3f, sizeof(dst));
        
        queue<int> q;
        q.push(start);
        dst[start] = 0;
        inQ[start] = true;
        
        while(!q.empty()){
            int now = q.front(); q.pop();
            inQ[now] = false;
            
            for (auto e: edges[now]){
                int next = e->to;
                if (e->left() > 0 && dst[next] > dst[now] + e->cost){
                    dst[next] = dst[now] + e->cost;
                    prv[next] = now;
                    path[next] = e;
                    if (!inQ[next]){
                        q.push(next);
                        inQ[next] = true;
                    }
                }
            }
        }
        
        return prv[end] != -1;
    }
    pll go(int start, int end){
        ll ans = 0, maxFlow = 0;
        while(SPFA(start, end)){
            ll minFlow = INF;
            for (int i = end; i != start; i = prv[i]){
                minFlow = min(minFlow, path[i]->left());
            }
            for (int i = end; i != start; i = prv[i]){
                path[i]->addFlow(minFlow);
                ans += minFlow * path[i]->cost;
            }
            maxFlow += minFlow;
        }
        return {maxFlow, ans};
    }
};


int main(){
    scanf("%d %d", &n, &m);
    
    MCMF mcmf;
    
    for (int i = 0; i < m; i++){
        int u, v; ll w;
        scanf("%d %d %lld", &u, &v, &w);
        mcmf.addEdge(u, v + N_MAX, 1, w);
    }
    
    for (int i = 1; i <= n; i++){
        mcmf.addEdge(0, i, 1, 0);
        mcmf.addEdge(i + N_MAX, V_MAX - 1, 1, 0);
    }
    
    pll res = mcmf.go(0, V_MAX - 1);
    
    if (res.first < n){
        printf("0\n");
        return 0;
    }
    printf("1\n%lld\n", res.second);
    for (int i = 1; i <= n; i++){
        for (auto e: mcmf.edges[i]){
            if (e->flow == 1){
                printf("%d %d\n", i, e->to - N_MAX);
            }
        }
    }
    
    
    return 0;
}
