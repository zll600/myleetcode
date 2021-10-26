# [717. 1-bit and 2-bit Characters](https://leetcode.com/problems/1-bit-and-2-bit-characters/)

## 题目

We have two special characters:

- The first character can be represented by one bit `0`.
- The second character can be represented by two bits (`10` or `11`).

Given a binary array `bits` that ends with `0`, return `true` if the last character must be a one-bit character.

 

**Example 1:**

```
Input: bits = [1,0,0]
Output: true
Explanation: The only way to decode it is two-bit character and one-bit character.
So the last character is one-bit character.
```

**Example 2:**

```
Input: bits = [1,1,1,0]
Output: false
Explanation: The only way to decode it is two-bit character and two-bit character.
So the last character is not one-bit character.
```

 

**Constraints:**

- `1 <= bits.length <= 1000`
- `bits[i]` is either `0` or `1`.

## 题目大意

我们有两种特殊的字符：

* 第一种字符可以用一位 0 表示
* 第二种字符可以被两个位表示(10 和 11)

现给一个由若干比特组成的字符串。问最后一个字符是否必定为一个一比特字符。给定的字符串总是由0结束。

## 解题思路

### Solution 1:

这种解法可以参考这篇题解：https://leetcode.com/problems/1-bit-and-2-bit-characters/

`````c++
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        const int size = bits.size();
        int i = 0;
        // 只匹配到倒数第一个字符
        while (i < size - 1) {
            // 如果是 1，直接跳两格
            if (bits[i] == 1) {
                ++i;
            }
            ++i;
        }
        
        // 如果最后停在 size - 1的位置上，说明最后一位是 0
        // 如果停在 size 位置上，说明最后一个位 0 是第二种情况
        return i == size - 1;
    }
};
`````

