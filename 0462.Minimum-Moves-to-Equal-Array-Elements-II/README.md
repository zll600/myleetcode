# [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

## 题目

Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.

In one move, you can increment or decrement an element of the array by `1`.

Test cases are designed so that the answer will fit in a **32-bit** integer.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
```

**Example 2:**

```
Input: nums = [1,10,2,9]
Output: 16
```

 

**Constraints:**

- `n == nums.length`
- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

## 题目大意

给定一个大小为 n 的整数数组，返回使数组所有元素相等的最小移动次数，每一次移动，你可以对选定的元素 +1 或者 -1，

## 解题思路

这道题可以联系第 453 题，不过既然这道题可以 +1 也可以 -1，那么这道题就可以想到应该从两边向中间靠，那么就应该取中位数或者平均数，

最终道题选择的是中位数，所以先排序，然后遍历数组，将每个元素和中位数求差即可

### Solution 1:

这种解法，可以参考霜神的题解来做：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0462.Minimum-Moves-to-Equal-Array-Elements-II/

````c++
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        const int size = nums.size();
        int moves = 0;
        int mid = size / 2;
        
        // 排序取中位数
        sort(nums.begin(), nums.end());
        
        for (int num : nums) {
            moves += abs(num - nums[mid]);
        }
        
        return moves;
    }
};c
````

