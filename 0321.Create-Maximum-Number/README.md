# [321. Create Maximum Number](https://leetcode-cn.com/problems/create-maximum-number/)

## 题目

You are given two integer arrays `nums1` and `nums2` of lengths `m` and `n` respectively. `nums1` and `nums2` represent the digits of two numbers. You are also given an integer `k`.

Create the maximum number of length `k <= m + n` from digits of the two numbers. The relative order of the digits from the same array must be preserved.

Return an array of the `k` digits representing the answer.

 

**Example 1:**

```
Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
Output: [9,8,6,5,3]
```

**Example 2:**

```
Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
Output: [6,7,6,0,4]
```

**Example 3:**

```
Input: nums1 = [3,9], nums2 = [8,9], k = 3
Output: [9,8,9]
```

 

**Constraints:**

- `m == nums1.length`
- `n == nums2.length`
- `1 <= m, n <= 500`
- `0 <= nums1[i], nums2[i] <= 9`
- `1 <= k <= m + n`

## 题目大意

给定两个长度分别为 m 和 n 的数组 num1 和 num 2，num1 和 num2 分别代表两个数字，也给定一个整数 k，从两个数组中创造一个长度为 k <= m + n的数，选择的数必须保持原来在数组中的顺序，

## 解题思路

这道题的解法，可以联系第 316 题，不过这里涉及到需要从两个数组中做出选择，直接的想法就是 两个数组中都取最大，然后拼接为最大，就可以达到全局最大，

所以这里其实是多了一个分别从两个数组中取总共 k 个数，然后拼接到一起的步骤，剩下的是就是求单调递减的单调栈了

### Solution 1:

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/create-maximum-number/solution/tu-jie-suan-fa-zhe-ge-dan-diao-zhan-bu-yi-ban-by-t/

这里的比较函数是我没想到的，写的真的不错，可以学习，

````c++
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        const int len1 = nums1.size();
        const int len2 = nums2.size();
        int start = max(0, k -len2), end = min(len1, k);
        vector<int> res(k, 0);
        for (int i = start; i <= end; ++i) {
            // i 表示从 sta1 中选择的数的数目
            vector<int> sta1 = GetMonStack(nums1, i);
            vector<int> sta2 = GetMonStack(nums2, k - i);
            vector<int> tmp = MergeMonStack(sta1, sta2);
            if (Cmp(tmp, 0, res, 0) > 0) {
                // 更新最终的结果
                res.swap(tmp);
            }
        }
        return res;
    }
    
 private:
    // 这里需要注意比较的顺序
    // 合并时的比较函数
    int Cmp(const vector<int>& sta1, int idx1, const vector<int>& sta2, int idx2) {
        const int len1 = sta1.size();
        const int len2 = sta2.size();
        while (idx1 < len1 && idx2 < len2) {
            // 比较当前元素，选择较大的元素，
            // 如果相等，判断后面的
            int tag = sta1[idx1++] - sta2[idx2++];
            if (tag != 0) {
                return tag;
            }
        }
        
        // 这里用长度做判断，那个先遍历完
        return (len1 - idx1) - (len2 - idx2);
    }
    
    // 从数组中求出单调栈
    vector<int> GetMonStack(const vector<int>& nums, const int len) {
        vector<int> sta;
        int drop_num = nums.size() - len; // 需要删除的数的数目
        for (int num : nums) {
            // 这里需要的是单调递减的单调栈
            while (!sta.empty() && sta.back() < num && drop_num > 0) {
                sta.pop_back();
                --drop_num;
            }
            
            if (sta.size() < len) {
                // 如果单调栈还没满，继续加
                sta.push_back(num);
            } else {
                // 否则视为删除一个数
                --drop_num;
            }
        }
        
        return sta;
    }
    
    // 合并两个单调栈
    vector<int> MergeMonStack(const vector<int>& sta1, const vector<int>& sta2) {
        const int len1 = sta1.size();
        const int len2 = sta2.size();
        if (len1 == 0) {
            return sta2;
        }
        if (len2 == 0) {
            return sta1;
        }
        
        vector<int> res(len1 + len2);
        int idx1 = 0, idx2 = 0;
        for (int i = 0; i < len1 + len2; ++i) {
             if (Cmp(sta1, idx1, sta2, idx2) > 0) {
                 res[i] = sta1[idx1++];
             } else {
                 res[i] = sta2[idx2++];
             }
        }
        return res;
    }
};
````





