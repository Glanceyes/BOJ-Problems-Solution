#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, l;
vector<int> pos, interval;

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> n >> m >> l;
    
    int ans = l;
    pos.push_back(0);
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        pos.push_back(x);
    }
    pos.push_back(l);
    
    sort(pos.begin(), pos.end());
    
    for (int i = 0; i <= n; i++){
        interval.push_back(pos[i + 1] - pos[i]);
    }
    
    int left = 0, right = l;
    
    while(left <= right){
        int mid = (left + right) >> 1;
        // 이 최솟값이 최댓값으로 가능한지
        priority_queue<int, vector<int>, less<int>> pq;
        for (auto x: interval){
            pq.push(x);
        }
        
        for (int i = 0; i < m; i++){
            int now = pq.top();
            pq.pop();
            if (now >= mid){
                pq.push(mid);
                pq.push(now - mid);
            }
            else {
                break;
            }
        }
        
        int maxInterval = pq.top();

        if (maxInterval <= mid){
            right = mid - 1;
            ans = mid;
        }
        else {
            left = mid + 1;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
