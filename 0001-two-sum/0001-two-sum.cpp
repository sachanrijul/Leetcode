class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;  // value -> index

        for (int i = 0; i < nums.size(); i++) {
            int needed = target - nums[i];

            // Have we already seen the required value?
            if (mp.find(needed) != mp.end()) {
                return {mp[needed], i};
            }

            // Store current value and its index
            mp[nums[i]] = i;
        }

        return {};
    }
};