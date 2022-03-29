# [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)

## 题目

Given an array of strings `words` and an integer `k`, return *the* `k` *most frequent strings*.

Return the answer **sorted** by **the frequency** from highest to lowest. Sort the words with the same frequency by their **lexicographical order**.

 

**Example 1:**

```
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.
```

**Example 2:**

```
Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words, with the number of occurrence being 4, 3, 2 and 1 respectively.
```

 

**Constraints:**

- `1 <= words.length <= 500`
- `1 <= words[i] <= 10`
- `words[i]` consists of lowercase English letters.
- `k` is in the range `[1, The number of **unique** words[i]]`

 

**Follow-up:** Could you solve it in `O(n log(k))` time and `O(n)` extra space?

## 题目大意

给定一个字符串数组 `words` 和一个整数 `k`，返回出现频数最高的 `k` 个字符串

结果按照频数从高到低排序，频数相同的字符串按照字典序排序

## 解题思路

这道题目的难点就在于需要将字符串和字符串出现的频数做一个绑定，实现的方式不止一种

### Solution 1:

这种解法使用 pair 来做一个绑定，然后利用 vector 来排序

````c++
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // 先统计每个字符串出现的频数
        unordered_map<string, int> freqs;
        for (const string& word : words) {
            ++freqs[word];
        }

        // 这里将字符串和其出现的频数做一个绑定
        vector<pair<string, int>> records(freqs.begin(), freqs.end());
        // 对已经建立好的集合进行排序
        sort(records.begin(), records.end(),
             [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
                 if (lhs.second != rhs.second) {
                     // 按照频数的降序
                     return lhs.second > rhs.second;
                 } else {
                     // 频数相同按照字典序
                     return lhs.first < rhs.first;
                 }
             });

        // 这里直接取够所有的即可
        const int len = records.size();
        vector<string> res;
        // 这里遍历的上界要注意，这道题目有说明，如果没有说明需要考虑到
        for (int i = 0; i < min(k, len); ++i) {
            res.push_back(records[i].first);
        }

        return res;
    }
};
````
