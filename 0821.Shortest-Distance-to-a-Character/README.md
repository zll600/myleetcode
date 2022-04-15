# [821. Shortest Distance to a Character](https://leetcode.com/problems/shortest-distance-to-a-character/)

Given a string `s` and a character `c` that occurs in `s`, return *an array of integers* `answer` *where* `answer.length == s.length` *and* `answer[i]` *is the **distance** from index* `i` *to the **closest** occurrence of character* `c` *in* `s`.

The **distance** between two indices `i` and `j` is `abs(i - j)`, where `abs` is the absolute value function.

 

**Example 1:**

```
Input: s = "loveleetcode", c = "e"
Output: [3,2,1,0,1,0,0,1,2,2,1,0]
Explanation: The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
The closest occurrence of 'e' for index 0 is at index 3, so the distance is abs(0 - 3) = 3.
The closest occurrence of 'e' for index 1 is at index 3, so the distance is abs(1 - 3) = 2.
For index 4, there is a tie between the 'e' at index 3 and the 'e' at index 5, but the distance is still the same: abs(4 - 3) == abs(4 - 5) = 1.
The closest occurrence of 'e' for index 8 is at index 6, so the distance is abs(8 - 6) = 2.
```

**Example 2:**

```
Input: s = "aaab", c = "b"
Output: [3,2,1,0]
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s[i]` and `c` are lowercase English letters.
- It is guaranteed that `c` occurs at least once in `s`.

## 题目大意

给定一个字符串 `s` 和一个字符 `c`，返回一个长度和字符串长度相等的数组 `answer`，数组中的每个元素都是与当前最近的 `s` 中的 `c` 的最近位置，


### Solution 1:

````c++
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        const int len = s.size();
        // 保留最小值，初始化为最大值
        vector<int> answers(len, 10001);
        for (int i = 0; i < len; ++i) {
            if (s[i] != c) {
                continue;
            }

            // 从每个对应位置开始向两边扩展，保留最小值
            answers[i] = 0;
            int left = i - 1;
            while (left >= 0 && s[left] != c) {
                answers[left] = min(answers[left], i - left);
                --left;
            }

            int right = i + 1;
            while (right < len && s[right] != c) {
                answers[right] = min(answers[right], right - i);
                ++right;
            }
        }

        return answers;
    }
};
````
