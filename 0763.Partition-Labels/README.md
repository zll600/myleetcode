# [763. Partition Labels](https://leetcode.com/problems/partition-labels/)

## 题目

You are given a string `s`. We want to partition the string into as many parts as possible so that each letter appears in at most one part.

Return *a list of integers representing the size of these parts*.

 

**Example 1:**

```
Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
```

**Example 2:**

```
Input: s = "eccbbbbdec"
Output: [10]
```

 

**Constraints:**

- `1 <= s.length <= 500`
- `s` consists of lowercase English letters.

## 题目大意

给定一个字符串`s`,将字符串分割为多个部分，要求每个字目指南只能出现在至多一个部分中，返回这些子串的长度

## 解题思路

利用滑动窗口，但有两个不同的方案

* 先记录下每个字母出现的频数，如果窗口中的字母的频数都减为0，则说明当前窗口满足条件，这个方法需要一个额外的数组来记录窗口内出现的字母种类数
* 先记录每个字母出现最后一次的距离，如果窗口的右边界大于等于当前窗口中所有出现国字母的最远距离，说明当前窗口满足条件
* 这道题目目前用c++没过，先用go，但思路相同

## 代码

````go
// 解法一
func partitionLabels(S string) []int {
	var lastIndexOf [26]int
	for i, v := range S {
		lastIndexOf[v-'a'] = i
	}

	var arr []int
	for start, end := 0, 0; start < len(S); start = end + 1 {
		end = lastIndexOf[S[start]-'a']
		for i := start; i < end; i++ {
			if end < lastIndexOf[S[i]-'a'] {
				end = lastIndexOf[S[i]-'a']
			}
		}
		arr = append(arr, end-start+1)
	}
	return arr
}

// 解法二
func partitionLabels1(S string) []int {
	visit, counter, res, sum, lastLength := make([]int, 26), map[byte]int{}, []int{}, 0, 0
	for i := 0; i < len(S); i++ {
		counter[S[i]]++
	}

	for i := 0; i < len(S); i++ {
		counter[S[i]]--
		visit[S[i]-'a'] = 1
		sum = 0
		for j := 0; j < 26; j++ {
			if visit[j] == 1 {
				sum += counter[byte('a'+j)]
			}
		}
		if sum == 0 {
			res = append(res, i+1-lastLength)
			lastLength += i + 1 - lastLength
		}
	}
	return res
}

````



