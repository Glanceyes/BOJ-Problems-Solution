#include <iostream>
#include <algorithm>
using namespace std;

const int M_MAX = 300;
const int N_MAX = 300;

int m, n, ans;
int mat[M_MAX + 1][N_MAX + 1];
int sum[M_MAX + 1][N_MAX + 1];

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> m >> n;
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            cin >> mat[i][j];
        }
    }
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + mat[i][j];
        }
    }
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            for (int k = i; k >= 0; k--){
                for (int l = j; l >= 0; l--){
                    int temp = sum[i][j] - sum[i][l] - sum[k][j] + sum[k][l];
                    if (temp > 10){
                        break;
                    }
                    else if (temp == 10){
                        ans += 1;
                    }
                }
            }
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
