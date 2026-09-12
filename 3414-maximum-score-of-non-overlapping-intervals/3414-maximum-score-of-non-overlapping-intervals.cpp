class Solution {
public:
    struct State {
        long long score = 0;
        int len = 0;
        array<int, 4> ids{};
    };

    bool lexSmaller(const State& a, const State& b) {
        for (int i = 0; i < min(a.len, b.len); i++) {
            if (a.ids[i] != b.ids[i]) {
                return a.ids[i] < b.ids[i];
            }
        }
        return a.len < b.len;
    }

    State better(const State& a, const State& b) {
        if (a.score != b.score) {
            return a.score > b.score ? a : b;
        }

        return lexSmaller(a, b) ? a : b;
    }

    State addInterval(State state, int id, long long weight) {
        state.score += weight;
        state.ids[state.len++] = id;
        sort(state.ids.begin(), state.ids.begin() + state.len);
        return state;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        for (int i = 0; i < n; i++) {
            intervals[i].push_back(i);
        }

        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            if (a[1] != b[1]) {
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });

        vector<int> ends(n);

        for (int i = 0; i < n; i++) {
            ends[i] = intervals[i][1];
        }

        vector<array<State, 5>> dp(n + 1);

        for (int i = 1; i <= n; i++) {
            int l = intervals[i - 1][0];
            int weight = intervals[i - 1][2];
            int id = intervals[i - 1][3];

            int p = lower_bound(
                ends.begin(),
                ends.begin() + i - 1,
                l
            ) - ends.begin();

            for (int j = 1; j <= 4; j++) {
                State skip = dp[i - 1][j];
                State take = addInterval(dp[p][j - 1], id, weight);

                dp[i][j] = better(skip, take);
            }
        }

        State answer = dp[n][0];

        for (int j = 1; j <= 4; j++) {
            answer = better(answer, dp[n][j]);
        }

        return vector<int>(
            answer.ids.begin(),
            answer.ids.begin() + answer.len
        );
    }
};