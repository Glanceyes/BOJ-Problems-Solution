#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int m, n, k;
vector<pii> treasure;
set<int> s;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> m >> n >> k;
    
    for (int i = 0; i < k; i++){
        int a, b; cin >> a >> b;
        treasure.push_back({a, b});
    }
    sort(treasure.begin(), treasure.end());
    
    s.insert(0);
    
    for (int i = 0; i < k; i++){
        int y = -treasure[i].second;
        auto iter = s.lower_bound(y);
        if (iter == s.end()){
            s.insert(y);
        }
        else {
            s.erase(iter);
            s.insert(y);
        }
    }
    cout << s.size() << "\n";
}
