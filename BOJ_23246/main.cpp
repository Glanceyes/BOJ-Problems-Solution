#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;
using pp = pair<int, pair<int, int>>;

int n;
vector<pp> v;

int main(){
    cin >> n;

    for (int i = 0; i < n; i++){
        int b, p, q, r;
        cin >> b >> p >> q >> r;
        v.push_back({p * q * r, {p + q + r, b}});
    }
    
    sort(v.begin(), v.end());
    
    for (int i = 0; i < 3; i++){
        cout << v[i].second.second << " ";
    }
    cout << "\n";
    
    return 0;
}
