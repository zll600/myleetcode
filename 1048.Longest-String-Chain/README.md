# [1048. Longest String Chain](https://leetcode.com/problems/longest-string-chain/)

## 题目

You are given an array of `words` where each word consists of lowercase English letters.

`wordA` is a **predecessor** of `wordB` if and only if we can insert **exactly one** letter anywhere in `wordA` **without changing the order of the other characters** to make it equal to `wordB`.

- For example, `"abc"` is a **predecessor** of `"abac"`, while `"cba"` is not a **predecessor** of `"bcad"`.

A **word chain** is a sequence of words `[word1, word2, ..., wordk]` with `k >= 1`, where `word1` is a **predecessor** of `word2`, `word2` is a **predecessor** of `word3`, and so on. A single word is trivially a **word chain** with `k == 1`.

Return *the **length** of the **longest possible word chain** with words chosen from the given list of* `words`.

 

**Example 1:**

```
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
```

**Example 2:**

```
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].
```

**Example 3:**

```
Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
```

 

**Constraints:**

- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 16`
- `words[i]` only consists of lowercase English letters.

## 题目大意


### Solution 1: DP

这种解法可以参考这 [这篇题解](https://leetcode-cn.com/problems/longest-string-chain/solution/1048-cjian-dan-yi-dong-de-dong-tai-gui-h-x0ji/)

这里 

- 定义：dp[i] 表示以当前位置结尾的 字符串链最长为多长
- 初始化：初始化为 1,每个位置自身都可以构成一个字符串链
- 状态转移：排序之后每个位置可以尝试从之前的位置转移而来, `dp[i] = max(dp[i], dp[j] + 1)`

在填充数组的过程中更新最大值即可


````Go
func longestStrChain(words []string) int {
    // 先排序
    sort.Slice(words, func(i, j int) bool {
        return len(words[i]) < len(words[j])
    })

    res := 1
    // dp[i] 表示以 i 位置结尾有多少个连续的
    dp := make([]int, len(words))
    for i := 0; i < len(words); i++ {
        // 初始为 1
        dp[i] = 1
        for j := 0; j < i; j++ {
            if isPredecessor(words[i], words[j]) {
                dp[i] = max(dp[i], 1 + dp[j])
            }
        }
        // fmt.Println(words[i], "---", dp[i])
        res = max(res, dp[i])
    }
    return res
}

func max(a, b int) int {
    if a < b {
        return b
    }
    return a
}

// 判断两个字符串是否相等
func isPredecessor(long, short string) bool {
    if len(long) != len(short) + 1 {
        return false
    }

    i, j := 0, 0
    isMismatch := false

    for i < len(long) && j < len(short) {
        if long[i] != short[j] {
            if isMismatch {
                return false
            }
            isMismatch = true
            i++
            continue
        }
        i++
        j++
    }
    return true
}
````
