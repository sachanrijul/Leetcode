class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1000000007;

        vector<vector<long long>> dp(k + 1, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        for (int j = 1; j <= k; j++) {
            long long sum = 0;

            for (int i = 1; i < n; i++) {
                sum = (sum + dp[j - 1][i - 1]) % MOD;
                dp[j][i] = (dp[j][i - 1] + sum) % MOD;
            }
        }

        return dp[k][n - 1];
    }
};