 # [212. Word Search II](https://leetcode.com/problems/word-search-ii/)

## 题目

Given an `m x n` `board` of characters and a list of strings `words`, return *all words on the board*.

Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells** are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/07/search1.jpg)

```
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/07/search2.jpg)

```
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 12`
- `board[i][j]` is a lowercase English letter.
- `1 <= words.length <= 3 * 104`
- `1 <= words[i].length <= 10`
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are unique.

## 题目大意

给定一个m x n 的字符网格和一个字符串列表，返回出现在网格中的所有单词，

每个单词必须按照单词中字母出现的顺序通过网格中相邻的字母进行构建，相邻的字母可以是水平的也可以是垂直的，网格中每个字幕在一个单词中最多只能用一次，

## 解题思路

* 这道题可以和第 79 题一起做，
* 这道题目可以直接使用 79 题的答案，对每一个字符串进行搜索，但是时间复杂度特别高，
* 可以利用前缀树来做（留待实现）

## 代码

````
````

