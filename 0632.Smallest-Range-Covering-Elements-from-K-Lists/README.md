# [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

## 题目

You have `k` lists of sorted integers in **non-decreasing order**. Find the **smallest** range that includes at least one number from each of the `k` lists.

We define the range `[a, b]` is smaller than range `[c, d]` if `b - a < d - c` **or** `a < c` if `b - a == d - c`.

 

**Example 1:**

```
Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
```

**Example 2:**

```
Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]
```

 

**Constraints:**

- `nums.length == k`
- `1 <= k <= 3500`
- `1 <= nums[i].length <= 50`
- `-105 <= nums[i][j] <= 105`
- `nums[i]` is sorted in **non-decreasing** order.

## 题目大意

给定 `k` 个按照非降序排序的链表，找到 `k` 个链表中只有一个元素的最小区间

区间 `[a, b]` 小于 `[c, d]` 其中，`b - a < d - c` 或者 `a < c` 且 `b - a == d - c`

## 解题思路 

这道题目的关键在于，每个组都需要有至少一个数字在，所以我们要将数字和组的类别联系在一起，然后利用滑动窗口去找到包含所有组的数字的区间

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/solution/pai-xu-hua-chuang-by-netcan/)
或者 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0632.Smallest-Range-Covering-Elements-from-K-Lists/)

````c++
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // 将数字和所属的数组联系起来
        vector<pair<int, int>> records;

        const int nums_len = nums.size();
        for (int i = 0; i < nums_len; ++i) {
            for (int num : nums[i]) {
                records.push_back({num, i});
            }
        }

        // 按照数字的大小进行排序
        sort(records.begin(), records.end());

        vector<int> res;
        // 滑动窗口
        int low = 0, high = 0;
        int cnt = 0;
        // 每个数组中出现的而数字的频数
        unordered_map<int, int> freq;
        const int records_len = records.size();
        while (high < records_len) {
            // 如果之前频数为 0
            if (!freq[records[high].second]) {
                ++cnt;
            }
            ++freq[records[high].second];

            if (cnt == nums_len) {
                // 窗口收缩
                while (freq[records[low].second] > 1) {
                    --freq[records[low].second];
                    ++low;
                }

                // 更新结果
                if (res.empty()
                    || records[high].first - records[low].first < res.back() - res.front()
                    || (records[high].first - records[low].first == res.back() - res.front()
                       && records[low].first < res.front())) {
                    res = {records[low].first, records[high].first};
                }
            }
            // 扩大窗口
            ++high;
        }

        return res;
    }
};
````
