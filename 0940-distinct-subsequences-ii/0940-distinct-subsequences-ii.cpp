class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        vector<long long> dp(26, 0);
        long long total = 0;

        for (char c : s) {
            int x = c - 'a';

            long long add = (total + 1) % MOD;

            total = (total - dp[x] + add + MOD) % MOD;
            dp[x] = add;
        }

        return total;
    }
};