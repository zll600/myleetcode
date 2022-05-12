# [1170. Compare Strings by Frequency of the Smallest Character](https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/)

## 题目

Let the function `f(s)` be the **frequency of the lexicographically smallest character** in a non-empty string `s`. For example, if `s = "dcce"` then `f(s) = 2` because the lexicographically smallest character is `'c'`, which has a frequency of 2.

You are given an array of strings `words` and another array of query strings `queries`. For each query `queries[i]`, count the **number of words** in `words` such that `f(queries[i])` < `f(W)` for each `W` in `words`.

Return *an integer array* `answer`*, where each* `answer[i]` *is the answer to the* `ith` *query*.

 

**Example 1:**

```
Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").
```

**Example 2:**

```
Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query both f("aaa") and f("aaaa") are both > f("cc").
```

 

**Constraints:**

- `1 <= queries.length <= 2000`
- `1 <= words.length <= 2000`
- `1 <= queries[i].length, words[i].length <= 10`
- `queries[i][j]`, `words[i][j]` consist of lowercase English letters.

## 题目大意

定义一个函数 f(s)，统计 s  中（按字典序比较）最小字母的出现频次 ，其中 s 是一个非空字符串。

例如，若 s = "dcce"，那么 f(s) = 2，因为字典序最小字母是 "c"，它出现了 2 次。

现在，给你两个字符串数组待查表 queries 和词汇表 words 。对于每次查询 queries[i] ，需统计 words 中满足 f(queries[i]) < f(W) 的 词的数目 ，W 表示词汇表 words 中的每个词。

请你返回一个整数数组 answer 作为答案，其中每个 answer[i] 是第 i 次查询的结果

## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1170.Compare-Strings-by-Frequency-of-the-Smallest-Character/)

这道题目我们先对 words 中没一项应用 f(s) 来求得对应的值保存为 wordsFunc，

然后对 queries 中没一项也应用 f(s) ，然后用这个值在 wordsFunc 中二分查找，找到第一个 大于等于的即可

这道题目第一次做没有想到可以利用二分查找来进行优化

````Go
func numSmallerByFrequency(queries []string, words []string) []int {
    wordsFunc := make([]int, len(words))
    for i, word := range words {
        wordsFunc[i] = countFunc(word)
    }

    sort.Ints(wordsFunc)
    res := make([]int, len(queries))

    for i, query := range queries {
        queryFreq := countFunc(query)
        res[i] = len(words) - sort.Search(len(words), func (i int) bool { return queryFreq < wordsFunc[i] })
    }

    return res
}

// 执行二分查找的过程
func countFunc(str string) int {
    cnt := [26]int{}
    for _, c := range str {
        cnt[c - 'a']++
    }

    i := 0
    for cnt[i] == 0 {
        i++
    }
    return cnt[i]
}
````
