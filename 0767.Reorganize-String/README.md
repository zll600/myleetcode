# [767. Reorganize String](https://leetcode.com/problems/reorganize-string/)

## 题目

Given a string `s`, rearrange the characters of `s` so that any two adjacent characters are not the same.

Return *any possible rearrangement of* `s` *or return* `""` *if not possible*.

 

**Example 1:**

```
Input: s = "aab"
Output: "aba"
```

**Example 2:**

```
Input: s = "aaab"
Output: ""
```

 

**Constraints:**

- `1 <= s.length <= 500`
- `s` consists of lowercase English letters.

## 题目大意

给定一个字符串 `s`，重新排列 `s` 中的字符，使得相邻的字符不相同

返回 任意可能的排列，如果不可能，返回 `""`

## 解题思路



### Solution 1: Priority_queue

这种是我自己的解法，不过会超时

````c++
class Solution {
public:
    string reorganizeString(string s) {
        // 统计频数
        vector<int> freq(26, 0);
        for (char c : s) {
            ++freq[c - 'a'];
        }
        
        // 将频数转存到 堆中
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < 26; ++i) {
            // 只加入频数不为 0 的
            if (freq[i] != 0) {
                pq.push({freq[i], 'a' + i});
            }
        }
        
        pair<int, char> data1 = pq.top();
        pq.pop();
        pair<int, char> data2 = pq.top();
        pq.pop();
        
        string res = "";
        while (!pq.empty() || (data1.first != 0 && data2.first != 0)) {
            res += data1.second;
            --data1.first;
            if (data1.first == 0 && !pq.empty() ) {
                data1 = pq.top();
                pq.pop();
            }
            
            res += data2.second;
            --data2.first;
            if (data2.first == 0 && !pq.empty()) {
                data2 = pq.top();
                pq.pop();
            }
        }
        
        if (res.back() != data1.second && data1.first == 1) {
            res += data1.second;
            --data1.first;
        }
        if (res.back() != data2.second && data2.first == 1) {
            res += data2.second;
            --data2.first;
        }
        
        if (data1.first == 0 && data2.first == 0) {
            return res;
        }
        
        return "";
    }
};
````

### Solution 2:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0767.Reorganize-String/)

这种解法有一下小细节需要注意，详情可以参考注释

````c++
class Solution {
public:
    string reorganizeString(string s) {
        // 先统计频数
        vector<int> freq(26, 0);
        for (char c : s) {
            ++freq[c - 'a'];
        }

        // 入队
        const int s_len = s.size();
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < 26; ++i) {
            // 这里是一个剪枝
            if (freq[i] > (s_len + 1) / 2) {
                return "";
            }
            // 只将频数大于 0 的加入堆中
            if (freq[i] > 0) {
                pq.push({freq[i], 'a' + i});
            }
        }

        // 这里利用队列先进先出的特性
        queue<pair<int, char>> other;
        string res = "";
        while(!pq.empty() || other.size() > 1) {
            if (other.size() > 1) {
                // 这里如果是 等于 1，那么会一直输出最大的值
                auto cur = other.front();
                other.pop();
                // 这里只将大于 0 的重新入堆
                if (cur.first > 0) {
                    pq.push(cur);
                }
            }
            if (!pq.empty()) {
                auto cur = pq.top();
                pq.pop();
                res += cur.second;
                --cur.first;
                other.push(cur);
            }
        }

        return res;
    }
};
`````
