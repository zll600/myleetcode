# [859. Buddy Strings](https://leetcode.com/problems/buddy-strings/)

## 题目

Given two strings `s` and `goal`, return `true` *if you can swap two letters in* `s` *so the result is equal to* `goal`*, otherwise, return* `false`*.*

Swapping letters is defined as taking two indices `i` and `j` (0-indexed) such that `i != j` and swapping the characters at `s[i]` and `s[j]`.

- For example, swapping at indices `0` and `2` in `"abcd"` results in `"cbad"`.

 

**Example 1:**

```
Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
```

**Example 2:**

```
Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.
```

**Example 3:**

```
Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.
```

 

**Constraints:**

- `1 <= s.length, goal.length <= 2 * 104`
- `s` and `goal` consist of lowercase letters.

## 题目大意

给定连个字符串 `s` 和 `goal`,返回 `true` 如果你能交换 `s` 中的两个字符使其等于 `goal`,否则,返回 `false`,

交换字母的定义是：取两个下标 i 和 j （下标从 0 开始）且满足 i != j ，接着交换 s[i] 和 s[j] 处的字符

- 例如, 交换下标 `0` 和 `2` 的字符, `"abcd"` 结果是 `"cbad"`

## 解题思路

这道题根据题目给定的用力来看,必须要考虑字符串相同和字符串不相同两种情况,

- 如果字符串相同, 则字符串中必须出现重复字符
- 如果字符串不相同,则必须有两个位置的字符串在交换位置之后相同

### Solution 

这种解法可以参考 [这篇题解](https://leetcode.com/problems/buddy-strings/submissions/)

````c++
class Solution {
public:
    bool buddyStrings(string s, string goal) {
        const int len1 = s.size();
        const int len2 = goal.size();
        
        if (len1 != len2 || len1 <= 1) {
            // 如果长度不相等或者长度小于 2,直接返回
            return false;
        }
        
        if (s == goal) {
            // 如果两个字符串相等,必须存在相等字符
            unordered_set<char> freq;
            for (int i = 0; i < len1; ++i) {
                if (freq.find(s[i]) != freq.end()) {
                    return true;
                }
                freq.insert(s[i]);
            }
            return false;
        } else {
            // 如果两个字符串不相等,必须存在两个位置可以互换
            int first = -1, second = -1;
            
            for (int i = 0; i < len1; ++i) {
                if (s[i] != goal[i]) {
                    if (first == -1) {
                        first = i;
                    } else if (second == -1) {
                        second = i;
                    } else {
                        return false;
                    }
                }
            }
            
            return second != -1 && s[first] == goal[second] && s[second] == goal[first];
        }
        
        return false;
    }
};
````
