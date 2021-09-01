# [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)

## 题目

The **next greater element** of some element `x` in an array is the **first greater** element that is **to the right** of `x` in the same array.

You are given two **distinct 0-indexed** integer arrays `nums1` and `nums2`, where `nums1` is a subset of `nums2`.

For each `0 <= i < nums1.length`, find the index `j` such that `nums1[i] == nums2[j]` and determine the **next greater element** of `nums2[j]` in `nums2`. If there is no next greater element, then the answer for this query is `-1`.

Return *an array* `ans` *of length* `nums1.length` *such that* `ans[i]` *is the **next greater element** as described above.*

 

**Example 1:**

```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
```

**Example 2:**

```
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.
```

 

**Constraints:**

- `1 <= nums1.length <= nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 104`
- All integers in `nums1` and `nums2` are **unique**.
- All the integers of `nums1` also appear in `nums2`.

 

**Follow up:** Could you find an `O(nums1.length + nums2.length)` solution?

## 题目大意

数组中 x 的下一个更大的元素，是 x 右边第一个比 x 大的元素，

给定两个**下标从0开始且不含重复元素**的数组 nums1 和 nums2，其中 nums1 是 nums2 的子集，针对 nums1 中的每个数组中的元素，要求在 nums2 数组中找出比 nums1 数组中下一个更大的元素，nums2 中元素之间的顺序保持不变。如果找到了就输出这个值，如果找不到就输出 -1。

## 解题思路

* 这道题目是可以利用单调栈来解决的。
* 可以暴力，不过会超时

## 代码

````c++
class Solution {
public:
    // 解法一：记录nums1中元素在 nums2 中的位置，然后遍历
    /*
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<int> res;
        
        unordered_map<int, int> record;
        for (int i = 0; i < len2; ++i) {
            record.insert(make_pair(nums2[i], i));  // 插入值使用insert，更新值使用[]
        }
        
        for (int i = 0; i < len1; ++i) {
            bool flag = false;
            for (int j = record[nums1[i]]; j < len2; ++j) {
                if (nums2[j] > nums1[i]) {
                    res.push_back(nums2[j]);
                    flag = true;
                    break;
                }
            }
            
            if (flag == false) {
                res.push_back(-1);
            }
        }
        
        return res;
    }*/
    
    // 解法二：利用单调栈，
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> record;
        stack<int> sta;
        
        int size = nums2.size();
        for (int i = 0; i < size; ++i) {
            while (!sta.empty() && nums2[i] > sta.top()) {
                record.insert(make_pair(sta.top(), nums2[i]));
                sta.pop();
            }
            sta.push(nums2[i]);
        }
        
        while (!sta.empty()) {
            record.insert(make_pair(sta.top(), -1));
            sta.pop();
        }
        
        vector<int> res;
        for (int i : nums1) {
            res.push_back(record[i]);
        }
        return res;
    }
    
    // 解法三：暴力解，能过但是效率堪忧
    /*
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        
        int len1 = nums1.size();
        int len2 = nums2.size();
        for (int i = 0; i < len1; ++i) {
            int j = 0;
            for (; j < len2; ++j) {
                if (nums2[j] == nums1[i]) {
                    break;
                }
            }
            
            for (; j < len2; ++j) {
                if (nums2[j] > nums1[i]) {
                    res.push_back(nums2[j]);
                    break;
                }
            }
            if (j == len2) {
                res.push_back(-1);
            }
        }
        
        return res;
    }*/
};
````

