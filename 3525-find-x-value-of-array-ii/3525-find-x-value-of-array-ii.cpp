class Solution {
public:
    static const int MAXK = 5;

    struct Node {
        int prod;
        array<int, MAXK> cnt;

        Node() {
            prod = 1;
            cnt.fill(0);
        }
    };

    int k;
    vector<Node> tree;

    Node mergeNodes(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        for (int r = 0; r < k; r++) {
            res.cnt[r] = a.cnt[r];
        }

        for (int r = 0; r < k; r++) {
            int nr = (a.prod * r) % k;
            res.cnt[nr] += b.cnt[r];
        }

        return res;
    }

    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();
        int size = 1;

        while (size < n) {
            size <<= 1;
        }

        tree.resize(2 * size);

        for (int i = 0; i < n; i++) {
            int r = nums[i] % k;
            tree[size + i].prod = r;
            tree[size + i].cnt[r] = 1;
        }

        for (int i = size - 1; i >= 1; i--) {
            tree[i] = mergeNodes(tree[i << 1], tree[i << 1 | 1]);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            int pos = size + index;
            tree[pos] = Node();

            int r = value % k;
            tree[pos].prod = r;
            tree[pos].cnt[r] = 1;

            pos >>= 1;

            while (pos >= 1) {
                tree[pos] = mergeNodes(tree[pos << 1], tree[pos << 1 | 1]);
                pos >>= 1;
            }

            int l = size + start;
            int rr = size + n;

            Node left;
            Node right;

            while (l < rr) {
                if (l & 1) {
                    left = mergeNodes(left, tree[l]);
                    l++;
                }

                if (rr & 1) {
                    --rr;
                    right = mergeNodes(tree[rr], right);
                }

                l >>= 1;
                rr >>= 1;
            }

            Node res = mergeNodes(left, right);
            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};