# [670. Maximum Swap](https://leetcode-cn.com/problems/maximum-swap/)

## 题目

You are given an integer `num`. You can swap two digits at most once to get the maximum valued number.

Return *the maximum valued number you can get*.

 

**Example 1:**

```
Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
```

**Example 2:**

```
Input: num = 9973
Output: 9973
Explanation: No swap.
```

 

**Constraints:**

- `0 <= num <= 10^8`

## 题目大意

给定一个整数 `num`，你可以最多可以交换一次两位数，来得到最大值，

返回你可以得到的最大的数

## 解题思路

这道题目的关键就是从高位向低位找，找到第一个较小的数，和后面最后一个最大的数做交换，这个最大的数，需要尽量靠后，

可以参考 [这篇题解](https://leetcode-cn.com/problems/maximum-swap/solution/2021316-zui-da-jiao-huan-quan-chang-zui-ery0x/)

### Solution 1:


````c++
class Solution {
public:
    int maximumSwap(int num) {
        // 将整数转化为字符串数组
        string str = to_string(num);
        
        const int len = str.size();
        // 向将高位交换为最大的
        for (int i = 0; i < len; ++i) {
            // 从后向前遍历，找到一个最大的值
            int idx = len - 1;
            for (int j = idx - 1; j > i; --j) {
                if (str[j] > str[idx]) {
                    idx = j;
                }
            }
            
            // 如果这个值大于当前高位，则交换，然后退出
            if (str[idx] > str[i]) {
                swap(str[idx], str[i]);
                break;
            }
        }
        
        return stoi(str);
    }
};
````
