#### [553. Optimal Division](https://leetcode-cn.com/problems/optimal-division/)

## 题目

You are given an integer array `nums`. The adjacent integers in `nums` will perform the float division.

- For example, for `nums = [2,3,4]`, we will evaluate the expression `"2/3/4"`.

However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.

Return *the corresponding expression that has the maximum value in string format*.

**Note:** your expression should not contain redundant parenthesis.

 

**Example 1:**

```
Input: nums = [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant, since they don't influence the operation priority. So you should return "1000/(100/10/2)".
Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2
```

**Example 2:**

```
Input: nums = [2,3,4]
Output: "2/(3/4)"
```

**Example 3:**

```
Input: nums = [2]
Output: "2"
```

 

**Constraints:**

- `1 <= nums.length <= 10`
- `2 <= nums[i] <= 1000`
- There is only one optimal division for the given iput.

## 题目大意

给定一组正整数，相邻的整数之间会进行浮点出发运算，
* 例如: [2,3,4] -> 2/3/4

但是，你可以在任意位置添加任意数目的括号，来改变算数的优先级。你需要找出怎么添加括号，才能得到最大的结果，并且返回相应的字符串格式的表达式。你的表达式不应该含有冗余的括号。



## 解题思路

这里的思路就是 让被除数尽可能的大，让除数尽可能的小，除数累积的越多，越小


### Solution 1: Math



````c++
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return to_string(nums[0]);
        }

        if (len == 2) {
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        }

        string res = to_string(nums[0]) + "/(";
        for (int i = 1; i < len; ++i) {
            res += to_string(nums[i]) + "/";
        }
        res.back() = ')';

        return res;
    }
};
````
