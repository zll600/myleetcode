# [228. Summary Ranges](https://leetcode.com/problems/summary-ranges/)

## 题目

You are given a **sorted unique** integer array `nums`.

Return *the **smallest sorted** list of ranges that **cover all the numbers in the array exactly***. That is, each element of `nums` is covered by exactly one of the ranges, and there is no integer `x` such that `x` is in one of the ranges but not in `nums`.

Each range `[a,b]` in the list should be output as:

- `"a->b"` if `a != b`
- `"a"` if `a == b`

 

**Example 1:**

```
Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: The ranges are:
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
```

**Example 2:**

```
Input: nums = [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: The ranges are:
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"
```

**Example 3:**

```
Input: nums = []
Output: []
```

**Example 4:**

```
Input: nums = [-1]
Output: ["-1"]
```

**Example 5:**

```
Input: nums = [0]
Output: ["0"]
```

 

**Constraints:**

- `0 <= nums.length <= 20`
- `-231 <= nums[i] <= 231 - 1`
- All the values of `nums` are **unique**.
- `nums` is sorted in ascending order.

## 题目大意

给定一个已经排好序且没有重复数字的数组，返回准确覆盖数组中所有元素的最小范围，也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。

列表中的每个区间范围 [a,b] 应该按如下格式输出：

- “a->b” ，如果 a != b
- “a” ，如果 a == b

## 解题思路

这道题简化一下，就是确定多个连续的区间，这里利用区间升序且没有重复元素还是比较好解决的

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0200~0299/0228.Summary-Ranges/

具体就是滑动窗口遍历即可，注意区间的移动

````c++
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        const int len = nums.size();
        if (len == 0) { // 边界情况
            return vector<string>();
        }
        vector<string> res;
        int left = 0;
        int right = 0;
        
        // cout << len << endl;
        while (left < len) {
            string str = to_string(nums[left]); // 先放入区间的左端点
            // 向右扩容
            while (right + 1 < len && nums[right] + 1 == nums[right + 1]) {
                ++right;
            }
            if (right != left) {
                // 如果区间左右端点不相等，则说明是一个区间
                str += "->" + to_string(nums[right]);
            }
            
            // cout << left << "----" << right << endl;
            left = right + 1; // 更新边界
            right = left; // 右边也需要更新，忘记更新会死循环
            
            res.push_back(str);
        }
        
        return res;
    }
};
````



