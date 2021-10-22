#include <cstdio>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

const int N_MAX = 50;
const int V_MAX = 50 + 2;
const int INF = 0x3f3f3f3f;

int n, p;
int num[N_MAX + 1][N_MAX + 1];

struct MCMF{
    struct Edge{
        int to, cap, flow, cost;
        Edge *rev;
        Edge(int to, int cap, int flow, int cost): to(to), cap(cap), flow(flow), cost(cost){}
        void addFlow(int flw){
            flow += flw;
            rev->flow -= flw;
        }
        int left(){
            return cap - flow;
        }
    };

    int prv[V_MAX];
    int dst[V_MAX];
    Edge* path[V_MAX];
    vector<Edge*> edges[V_MAX];
    
    void addEdge(int u, int v, int c, int cst){
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
    int go(int start, int end){
        int ans = 0;
        while(SPFA(start, end)){
            int minFlow = INF;
            for (int i = end; i != start; i = prv[i]){
                minFlow = min(minFlow, path[i]->left());
            }
            for (int i = end; i != start; i = prv[i]){
                path[i]->addFlow(minFlow);
                ans += minFlow * path[i]->cost;
            }
        }
        return -ans;
    }
};

int main(){
    scanf("%d %d", &n, &p);
    MCMF mcmf;
    
    for (int i = 1; i < n; i++){
        for (int j = i + 1; j <= n; j++){
            scanf("%d", &num[i][j]);
        }
    }
    
    for (int i = 1; i < n; i++){
        for (int j = i + 1; j <= n; j++){
            int fare; scanf("%d", &fare);
            mcmf.addEdge(i, j, num[i][j], -fare);
        }
    }
    
    for (int i = 1; i < n; i++){
        mcmf.addEdge(i, i + 1, INF, 0);
    }
    mcmf.addEdge(0, 1, p, 0);
    mcmf.addEdge(n, V_MAX - 1, p, 0);
    
    printf("%d\n", mcmf.go(0, V_MAX - 1));
    return 0;
}
