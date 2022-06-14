# [1156. Swap For Longest Repeated Character Substring](https://leetcode.cn/problems/swap-for-longest-repeated-character-substring/)

## 题目

You are given a string `text`. You can swap two of the characters in the `text`.

Return *the length of the longest substring with repeated characters*.

 

**Example 1:**

```
Input: text = "ababa"
Output: 3
Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa" with length 3.
```

**Example 2:**

```
Input: text = "aaabaaa"
Output: 6
Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa" with length 6.
```

**Example 3:**

```
Input: text = "aaaaa"
Output: 5
Explanation: No need to swap, longest repeated character substring is "aaaaa" with length is 5.
```

 

**Constraints:**

- `1 <= text.length <= 2 * 104`
- `text` consist of lowercase English characters only.

## 题目大意

如果字符串中的所有字符都相同，那么这个字符串是单字符重复的字符串

给你一个字符串 `text`，你只能交换其中两个字符一次或者什么都不做，然后得到一些单字符重复的子串。返回其中最长的子串的长度

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/swap-for-longest-repeated-character-substring/solution/zhao-dao-mo-shi-jiu-hen-jian-dan-by-brya-x6k4/)

这种解法统计一种字符的频数，如果遇到不相同的字符，如果只有这个不相同的字符后面依旧是原来的字符，那么就可以通过一次交换来使得原来的字符继续连续，得到连续的字符之后，还需要判断这段连续的字符的频数是否等于这个字符的总频数，

如果小于这个字符的总频数，那么就还可以再次交换一次，使得当前连续的这一段字符数量增加

````c++
class Solution {
public:
    int maxRepOpt1(string text) {
        // 统计频数
        vector<int> freq(26, 0);
        for (char c : text) {
            ++freq[c - 'a'];
        }
        
        char cur = text[0];
        int cur_cnt = 1;
        
        int res = 1;
        const int len = text.size();
        for (int i = 1; i < len; ++i) {
            if (text[i] != cur) {
                // 如果遇到不相等的字符
                
                // 先跳过统计这个字符后面的连续的 cur 的数量
                int idx = i + 1;
                while (idx < len && text[idx] == cur) {
                    ++cur_cnt;
                    ++idx;
                }
                // 统计结束，如果得到的数量依然小于这个字符的总数量，则一定还可以交换一次加 1
                if (cur_cnt < freq[cur - 'a']) {
                    ++cur_cnt;
                }
                res = max(res, cur_cnt);
                
                // 重置计数
                cur_cnt = 1;
                cur = text[i];
            } else {
                ++cur_cnt;
            }
        }
        // 最后一个字符还没参与种种结果的更新，所以这里在比较一次
        if (cur_cnt > 1) {
            if (cur_cnt < freq[cur - 'a']) {
                ++cur_cnt;
            }
            res = max(res, cur_cnt);
        }
        return res;
    }
};
````

 
