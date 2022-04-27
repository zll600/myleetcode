# [870. Advantage Shuffle](https://leetcode.com/problems/advantage-shuffle/)

## 题目

You are given two integer arrays `nums1` and `nums2` both of the same length. The **advantage** of `nums1` with respect to `nums2` is the number of indices `i` for which `nums1[i] > nums2[i]`.

Return *any permutation of* `nums1` *that maximizes its **advantage** with respect to* `nums2`.

 

**Example 1:**

```
Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
Output: [2,11,7,15]
```

**Example 2:**

```
Input: nums1 = [12,24,8,32], nums2 = [13,25,32,11]
Output: [24,32,8,12]
```

 

**Constraints:**

- `1 <= nums1.length <= 105`
- `nums2.length == nums1.length`
- `0 <= nums1[i], nums2[i] <= 109`

## 题目大意

给定两个大小相等的数组 `A` 和 `B`，`A` 相对于 `B` 的优势可以用满足 `A[i] > B[i]` 的索引 `i` 的数目来描述。

返回 `A` 的任意排列，使其相对于 `B` 的优势最大化。

## 解题思路

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0870.Advantage-Shuffle/)

这里我们将 nums1 数组按照升序排序，因为题意中是与下标有关的，所以这里不能直接对 nums2 排序，所以这里对 nums2 的下标排序，

然后同时遍历 nums1 和 nums2 的有序下标数组，贪心的进行匹配，

这里处理 nums2 中暂时用不到的值的做法是存储在队列中，后面使用的时候再重新拿出来即可

````c++
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        // 对 nums1 按照升序排序
        sort(nums1.begin(), nums1.end());
        // nums2 按照升序将下标排序
        const int len = nums1.size();
        vector<int> idxes(len);
        for (int i = 0; i < len; ++i) {
            idxes[i] = i;
        }
        sort(idxes.begin(), idxes.end(), [&](int a, int b) {
            return nums2[a] < nums2[b];
        });


        vector<int> res(len);
        // 保存不能提供 advantage 的值，
        queue<int> useless;
        int idx1 = 0;
        for (int idx2 : idxes) {
            int cur = nums2[idx2];
            // cout << cur << endl;
            // 如果不能产生 advantage 就先存储起来
            while (idx1 < len && nums1[idx1] <= cur) {
                useless.push(nums1[idx1]);
                ++idx1;
            }

            // 如果有 大的就直接使用即可
            if (idx1 < len) {
                res[idx2] = nums1[idx1];
                ++idx1;
            } else {
                // 如果没有更大的，就使用之前存储起来的
                res[idx2] = useless.front();
                useless.pop();
            }
        }

        return res;
    }
};
````
