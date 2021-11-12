# [68. Text Justification](https://leetcode-cn.com/problems/text-justification/)

## 题目

Given an array of strings `words` and a width `maxWidth`, format the text such that each line has exactly `maxWidth` characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces `' '` when necessary so that each line has exactly `maxWidth` characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified and no extra space is inserted between words.

**Note:**

- A word is defined as a character sequence consisting of non-space characters only.
- Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
- The input array `words` contains at least one word.

 

**Example 1:**

```
Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
```

**Example 2:**

```
Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified becase it contains only one word.
```

**Example 3:**

```
Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
```

 

**Constraints:**

- `1 <= words.length <= 300`
- `1 <= words[i].length <= 20`
- `words[i]` consists of only English letters and symbols.
- `1 <= maxWidth <= 100`
- `words[i].length <= maxWidth`

## 题目大意

给定一个字符串数组 words 和一个最大宽度 maxWidth，重新排版这个文本使得每一行恰有 maxWidth 个字符，而且是左右对齐的

你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 `' '` 填充，使得每行恰好有 *maxWidth* 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

## 解题思路

字符串类的题目还是细节比较多，这里主要就是空格的合理分配了

### Solution 1:

这种解法可以看这篇题解：https://leetcode.com/problems/text-justification/submissions/

这道题目还需要注意边界条件的处理，这道题目以后一定要自己在做一遍，

````c++
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int max_width) {
        vector<string> ans;
        int cnt = 0;
        int lo = 0;
        for (int i = 0; i < words.size(); ++i) {
            cnt += words[i].size() + 1;
            
            // 如果是最后一个单词或者，累计长度已经超过最大宽度，则需要进行填充
            if (i + 1 == words.size() || cnt + words[i + 1].size() > max_width) {
                ans.push_back(FillWords(words, lo, i, max_width, i + 1 == words.size()));
                lo = i + 1;  // 下一次开始
                cnt = 0;  // 清零计数
            }
        }
        
        return ans;
    }
    
 private:
    string FillWords(const vector<string>& words, int lo, int hi,
                     int max_width, bool last_line = false) {
        int word_cnt = hi - lo + 1;  // 单词的数量
        int space_cnt = max_width + 1 - word_cnt;  // 除去每个单词尾部的空格，最后一个需要特殊处理
        for (int i = lo; i <= hi; ++i) {
            space_cnt -= words[i].size();  // 除去每个单词的长度
        }
        
        int space_suffix = 1;  // 固定的每个单词后面接一个空格
        int space_avg = (word_cnt == 1) ? 1 : (space_cnt / (word_cnt - 1));  // 每个间隙平均的空格数
        int space_extra = (word_cnt == 1) ? 0 : (space_cnt % (word_cnt - 1));  // 每个间隙额外的空格数
        // space_avg + space_extra 才是需要分布的空格总数
        
        string ans = "";
        for (int i = lo; i < hi; ++i) {
            ans += words[i];  // 接上单词
            
            if (last_line) {
                // 如果是最后一行
                fill_n(back_inserter(ans), 1, ' ');  // 插入一个空格
                continue;
            }
            
            // 填入空格
            fill_n(back_inserter(ans), space_suffix + space_avg + (i - lo < space_extra), ' ');
        }
        ans += words[hi];  // 加上最后一个单词
        fill_n(back_inserter(ans), max_width - ans.size(), ' ');  // 加上所有空余的单词，
        return ans;
    }
};
````

