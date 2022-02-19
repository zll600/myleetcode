# [373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)

## 题目

You are given two integer arrays `nums1` and `nums2` sorted in **ascending order** and an integer `k`.

Define a pair `(u, v)` which consists of one element from the first array and one element from the second array.

Return *the* `k` *pairs* `(u1, v1), (u2, v2), ..., (uk, vk)` *with the smallest sums*.

 

**Example 1:**

```
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
```

**Example 2:**

```
Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
```

**Example 3:**

```
Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [[1,3],[2,3]]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]
```

 

**Constraints:**

- `1 <= nums1.length, nums2.length <= 105`
- `-109 <= nums1[i], nums2[i] <= 109`
- `nums1` and `nums2` both are sorted in **ascending order**.
- `1 <= k <= 1000`

## 题目大意

给定两个按照升序排序的数组 nums1 和 nums2和一个整数 k，

定义一个数对 `(u, v)` 分别从第一个数组和第二个数组中各取出一个元素，

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/find-k-pairs-with-smallest-sums/solution/zui-da-dui-he-zui-xiao-dui-shi-xian-by-m-c1mj/)

### Solution 1:

这种解法是一利用一个大顶堆来保存前 k 最小的数，这里添加了一个剪枝，不然这道题是过不了的，

````c++
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.first + lhs.second < rhs.first + rhs.second;
        };
        
        const int len1 = nums1.size();
        const int len2 = nums2.size();
        if (1L * len1 * len2 < k) {
            k = len1 * len2;
        }
        
        // 这里使用一个大顶堆来做，维护前 k 最小的组合
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < len1; ++i) {
            for (int j = 0; j < len2; ++j) {
                // 这里这个剪枝很重要，
                // 因为数组本身是有序的，所以我们只需要在前面找够 k 个就可以，
                if (i * j > k && heap.size() == k) {
                    break;
                }
                if (heap.size() < k) {
                    heap.emplace(make_pair(nums1[i], nums2[j]));
                } else if (nums1[i] + nums2[j] < heap.top().first + heap.top().second) {
                    heap.pop();
                    heap.emplace(make_pair(nums1[i], nums2[j]));
                }
            }
        }
        
        // 逆序写入数组中
        vector<vector<int>> res(k, vector<int>(2));
        for (int i = k - 1; i >= 0; --i) {
            res[i][0] = heap.top().first;
            res[i][1] = heap.top().second;
            heap.pop();
        }
        
        return res;
    } 
};
````

### Solution 2:

使用小顶堆来做，这里建议画图来做，也可以去看上面的题思路，

```````C++
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        const int len1 = nums1.size();
        const int len2 = nums2.size();
        if (1L * len1 * len2 < k) {
            k = len1 * len2;
        }
        
        // 实现小顶堆
        auto cmp = [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return nums1[lhs.first] + nums2[lhs.second] > nums1[rhs.first] + nums2[rhs.second];
        };
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
        // 先向 heap 中加入 k 个元素
        for (int i = 0; i < k; ++i) {
            heap.emplace(make_pair(i, 0));
        }
        
        vector<vector<int>> res;
        // 如果数目不够，且堆没有空，
        while (k-- > 0 && !heap.empty()) {
            auto item = heap.top(); // 取最小的
            heap.pop(); // 弹出最小的
            // 加入结果集中
            res.emplace_back(vector<int>({nums1[item.first], nums2[item.second]}));
            
            if (item.second < len2 - 1) {
                // 入队新
                heap.push({item.first, item.second + 1});
            }
        }
        
        return res;
    }
};
```````

