#include <iostream>
#include <algorithm>
using namespace std;

const double INF = (double)(1e12 * 4);
const int N_MAX = 4000;
const int B_MAX = 30;

int b, n;
double sum[N_MAX + 1];
double expo[N_MAX + 1];
double dp[N_MAX + 1][B_MAX + 1];

int main(){
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    
    cin >> b >> n;
    
    for (int i = 1; i <= n; i++){
        double x; cin >> x;
        sum[i] = sum[i - 1] + x;
        expo[i] = expo[i - 1] + x * x;
        for (int j = 0; j <= b; j++){
            dp[i][j] = INF;
        }
    }
    
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= b; j++){
            for (int k = 0; k < i; k++){
                if (dp[k][j - 1] == INF)
                    continue;
                double avg = (sum[i] - sum[k]) / (double)(i - k);
                double error = (expo[i] - expo[k]) - 2 * avg * (sum[i] - sum[k]) + avg * avg * (double)(i - k);
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + error);
            }
        }
    }
    
    cout << fixed;
    cout.precision(6);
    cout << dp[n][b] << "\n";
    
    return 0;
}
