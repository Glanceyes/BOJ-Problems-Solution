#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

ll n;

int main(){
    scanf("%lld", &n);
    
    ll res = 1;
    
    while(n){
        if (n % 2){
            res *= 2;
        }
        n /= 2;
    }
    
    printf("%lld\n", res);
    
    return 0;
}
