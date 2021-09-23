# [179. Largest Number](https://leetcode.com/problems/largest-number/)

## 题目

Given a list of non-negative integers `nums`, arrange them such that they form the largest number.

**Note:** The result may be very large, so you need to return a string instead of an integer.

 

**Example 1:**

```
Input: nums = [10,2]
Output: "210"
```

**Example 2:**

```
Input: nums = [3,30,34,5,9]
Output: "9534330"
```

**Example 3:**

```
Input: nums = [1]
Output: "1"
```

**Example 4:**

```
Input: nums = [10]
Output: "10"
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 109`

## 题目大意

给定一个非负整数数组，排列它们使他们组成最大的数，

因为结果可能会很大，你需要返回一个字符串

## 解题思路

这道题也是一道贪心题，我先放一篇题解，这证明我是真的不会，以后一定要补上：https://leetcode-cn.com/problems/largest-number/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-vn86e/

这里将数字排序的条件是 a + b  > b + a

## 代码

`````c++
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (int num : nums) {
            strs.push_back(to_string(num));
        }
        
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) -> bool {
            return a + b > b + a;
        });
        
        string res = "";
        for (string str : strs) {
            res += str;
        }
        
        //  这里需要处理前导 0 的情况
        if (res[0] == '0') {
            return "0";
        }
        
        return res;
    }
};
`````

