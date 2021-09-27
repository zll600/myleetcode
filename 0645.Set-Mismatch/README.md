# [645. Set Mismatch](https://leetcode.com/problems/set-mismatch/)

## 题目

You have a set of integers `s`, which originally contains all the numbers from `1` to `n`. Unfortunately, due to some error, one of the numbers in `s` got duplicated to another number in the set, which results in **repetition of one** number and **loss of another** number.

You are given an integer array `nums` representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return *them in the form of an array*.

 

**Example 1:**

```
Input: nums = [1,2,2,4]
Output: [2,3]
```

**Example 2:**

```
Input: nums = [1,1]
Output: [1,2]
```

 

**Constraints:**

- `2 <= nums.length <= 104`
- `1 <= nums[i] <= 104`

## 题目大意

你有一个整数集合 s，初始时包括所有从 1 到 n 的整数，不幸的的是，由于一些错误，导致集合里面某一个元素复制了成了集合里面的另外一个元素的值，导致集合丢失了一个整数并且有一个元素重复

给定一个整数数组 nums 表示这个集合出错之后的状态，找出重复的那个数和丢失的那个数，并返回他们

## 解题思路

### 解法1（原地哈希）

这道题目和第 41 题比较像，可以利用 nums[i] = i + 1 的关系来将数组重新排序

然后在遍历一次数组，就可以找到答案

`````c++
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != nums[nums[i] - 1]) {  // 这里将每个数放到对应的位置上，
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) { // 找到第一个 索引与值不匹配的位置，返回
                return vector<int>({nums[i], i + 1});
            }
        }
        
        return vector<int>();
    }
};
`````

