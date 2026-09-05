class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<long long> prefixMax(n);
        prefixMax[0] = nums[0];

        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], (long long)nums[i]);
        }

        long long suffixMin = nums[n - 1];
        int answer = -1;

        for (int i = n - 1; i >= 0; i--) {
            suffixMin = min(suffixMin, (long long)nums[i]);

            if (prefixMax[i] - suffixMin <= k) {
                answer = i;
            }
        }

        return answer;
    }
};