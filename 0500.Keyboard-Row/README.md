# [500. Keyboard Row](https://leetcode.com/problems/keyboard-row/)



Given an array of strings `words`, return *the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below*.

In the **American keyboard**:

- the first row consists of the characters `"qwertyuiop"`,
- the second row consists of the characters `"asdfghjkl"`, and
- the third row consists of the characters `"zxcvbnm"`.

![img](https://assets.leetcode.com/uploads/2018/10/12/keyboard.png)

 

**Example 1:**

```
Input: words = ["Hello","Alaska","Dad","Peace"]
Output: ["Alaska","Dad"]
```

**Example 2:**

```
Input: words = ["omk"]
Output: []
```

**Example 3:**

```
Input: words = ["adsdf","sfd"]
Output: ["adsdf","sfd"]
```

 

**Constraints:**

- `1 <= words.length <= 20`
- `1 <= words[i].length <= 100`
- `words[i]` consists of English letters (both lowercase and uppercase). 

## 大意

给定一个单词列表，只返回可以使用在键盘同一行的字母打印出来的单词。键盘如上图所示

