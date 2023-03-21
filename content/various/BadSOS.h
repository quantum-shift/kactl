/**
 * Author: BForBruteForce
 * License: CC0
 * Source: me
 * Description: Bad 2D SOS DP.
 * F[i] contains sum over all subsets of i
 * Status: tested
 */

using vll = vector<ll>;
struct BadSOS {
    vector<vll> dp;
    vll F;
    BadSOS(int n, vll& A) {
        dp.resize(1 << n, vll(n + 1));
        F.resize(1 << n);
        rep(m,0,1 << n) {
            dp[m][0] = A[m];
            rep(i,0,n) {
                dp[m][i+1]=dp[m][i]+((m >> i & 1) ? dp[m^(1 << i)][i] : 0);
            }
            F[m] = dp[m][n];
        }
    }
}