# [1078. Occurrences After Bigram](https://leetcode.com/problems/occurrences-after-bigram/)

## 题目

Given two strings `first` and `second`, consider occurrences in some text of the form `"first second third"`, where `second` comes immediately after `first`, and `third` comes immediately after `second`.

Return *an array of all the words* `third` *for each occurrence of* `"first second third"`.

 

**Example 1:**

```
Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
Output: ["girl","student"]
```

**Example 2:**

```
Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]
```

 

**Constraints:**

- `1 <= text.length <= 1000`
- `text` consists of lowercase English letters and spaces.
- All the words in `text` a separated by **a single space**.
- `1 <= first.length, second.length <= 10`
- `first` and `second` consist of lowercase English letters.

## 题目大意

### Solution 1:

给出第一个词 `first` 和第二个词 `second`，考虑在某些文本 `text` 中可能以 `“first second third”` 形式出现的情况，其中 `second` 紧随 `first` 出现，`third` 紧随 `second` 出现

对于每种这样的情况，将第三个词 `“third”` 添加到答案中，并返回答案

## 解题思路：

### Solution 1:

这种解法，先将 text 分割为 words 列表，然后进行判断，选出符合条件的结果

````Go
func findOcurrences(text string, first string, second string) []string {
    res := make([]string, 0)
    
    // 先将 text 分解为 words list
    words := strings.Split(text, " ")
    if len(words) < 3 {
        return res
    }
    
    // 进行判断确定答案
    for i := 2; i < len(words); i++ {
        if words[i - 2] == first && words[i - 1] == second {
            res = append(res, words[i])
        }
    }
    
    return res
}
````
