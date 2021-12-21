# [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

## 题目

Given string num representing a non-negative integer `num`, and an integer `k`, return *the smallest possible integer after removing* `k` *digits from* `num`.

 

**Example 1:**

```
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
```

**Example 2:**

```
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
```

**Example 3:**

```
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
```

 

**Constraints:**

- `1 <= k <= num.length <= 105`
- `num` consists of only digits.
- `num` does not have any leading zeros except for the zero itself.

## 题目大意

给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

## 解题思路

最直观的思路就是遍历整个数，决定每一个位是否要删除，

这道题目有一个数学知识：对于两个数 123a456 和 123b456，如果 a > b， 那么数字 123a456 大于 数字 123b456，否则数字 123a456 小于等于数字 123b456。也就说，两个相同位数的数字大小关系取决于第一个不同的数的大小。

### Solution 1: Monotonic Stack

可以参考这篇题解：https://leetcode-cn.com/problems/remove-duplicate-letters/solution/yi-zhao-chi-bian-li-kou-si-dao-ti-ma-ma-zai-ye-b-4/

这种解法利用的是单调栈，维护一个单调递增的单调栈，让权重高的位的数的值小，整体的值就是最小

```c++
class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<char> sta; // 类似单调栈的结构
        const int len = num.size(); // 长度
        const int remain = len - k; // 理论上最终的长度
        if (remain <= 0) {
            return "0";
        }
        
        // 更新维护单调栈
        for (char digit : num) {
            while (k && sta.size() && sta.back() > digit) {
                sta.pop_back();
                --k;
            }
            sta.push_back(digit);
        }
        
        // 删除末尾多余的数
        while (sta.size() > remain) {
            sta.pop_back();
        }
        
        string res = ""; // 结果
        bool start = false;
        for (char c : sta) {
            // 跳过前导 0
            if (c != '0') {
                start = true;
            }
            if (start) {
                res += c;
            }
        }
        
        return res == "" ? "0" : res; // 如果跳过前导 0，可能会导致结果字符串为空
    }
};
```

### Solution 2:

这种解法，参考的是这篇题解这：https://leetcode-cn.com/problems/remove-k-digits/solution/wei-tu-jie-dan-diao-zhan-dai-ma-jing-jian-402-yi-d/

````c++
class Solution {
public:
    string removeKdigits(string num, int k) {
        const int len = num.size();
        if (k == len) {
            // 特殊情况需要特殊处理
            return "0";
        }
        
        vector<char> sta; // 这里使用数组来模拟单调递增的栈
        for (char c : num) {
            while (k > 0 && !sta.empty() && sta.back() > c) {
                // 当前元素小于栈顶元素时
                sta.pop_back();
                --k;
            }
            
            if (c != '0' || !sta.empty()) {
                // 这里的写法是为了避免前导 0
                sta.push_back(c);
            }
        }
        
        // 可能还没有删够
        while (k > 0 && !sta.empty()) {
            sta.pop_back();
            --k;
        }
        
        // 最终可能已经删完了，结果为空
        return sta.empty() ? "0" : string(sta.begin(), sta.end());
    }
};
````

