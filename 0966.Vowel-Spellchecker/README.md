# [966. Vowel Spellchecker](https://leetcode.com/problems/vowel-spellchecker/)

## 题目

Given a `wordlist`, we want to implement a spellchecker that converts a query word into a correct word.

For a given `query` word, the spell checker handles two categories of spelling mistakes:

- Capitalization: If the query matches a word in the wordlist (

  case-insensitive

  ), then the query word is returned with the same case as the case in the wordlist. 	

  - Example: `wordlist = ["yellow"]`, `query = "YellOw"`: `correct = "yellow"`
  - Example: `wordlist = ["Yellow"]`, `query = "yellow"`: `correct = "Yellow"`
  - Example: `wordlist = ["yellow"]`, `query = "yellow"`: `correct = "yellow"`

- Vowel Errors: If after replacing the vowels 

  ```
  ('a', 'e', 'i', 'o', 'u')
  ```

   of the query word with any vowel individually, it matches a word in the wordlist (

  case-insensitive

  ), then the query word is returned with the same case as the match in the wordlist. 

  - Example: `wordlist = ["YellOw"]`, `query = "yollow"`: `correct = "YellOw"`
  - Example: `wordlist = ["YellOw"]`, `query = "yeellow"`: `correct = ""` (no match)
  - Example: `wordlist = ["YellOw"]`, `query = "yllw"`: `correct = ""` (no match)

In addition, the spell checker operates under the following precedence rules:

- When the query exactly matches a word in the wordlist (**case-sensitive**), you should return the same word back.
- When the query matches a word up to capitlization, you should return the first such match in the wordlist.
- When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
- If the query has no matches in the wordlist, you should return the empty string.

Given some `queries`, return a list of words `answer`, where `answer[i]` is the correct word for `query = queries[i]`.

 

**Example 1:**

```
Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
```

**Example 2:**

```
Input: wordlist = ["yellow"], queries = ["YellOw"]
Output: ["yellow"]
```

 

**Constraints:**

- `1 <= wordlist.length, queries.length <= 5000`
- `1 <= wordlist[i].length, queries[i].length <= 7`
- `wordlist[i]` and `queries[i]` consist only of only English letters.

### 题目大意

在给定单词列表 `wordlist` 的情况下，我们希望实现一个拼写检查器，将查询单词转换为正确的单词。

对于给定的查询单词 `query`，拼写检查器将会处理两类拼写错误：

-   大小写：如果查询匹配单词列表中的某个单词（不区分大小写），则返回的正确单词与单词列表中的大小写相同。
        例如：wordlist = [“yellow”], query = “YellOw”: correct = “yellow”
        例如：wordlist = [“Yellow”], query = “yellow”: correct = “Yellow”
        例如：wordlist = [“yellow”], query = “yellow”: correct = “yellow”
-   元音错误：如果在将查询单词中的元音（‘a’、‘e’、‘i’、‘o’、‘u’）分别替换为任何元音后，能与单词列表中的单词匹配（不区分大小写），则返回的正确单词与单词列表中的匹配项大小写相同。
        例如：wordlist = [“YellOw”], query = “yollow”: correct = “YellOw”
        例如：wordlist = [“YellOw”], query = “yeellow”: correct = "” （无匹配项）
        例如：wordlist = [“YellOw”], query = “yllw”: correct = "” （无匹配项）

此外，拼写检查器还按照以下优先级规则操作：

- 当查询 *完全匹配* 单词列表中的某个单词（区分大小写）时，应返回相同的单词。
- 当查询匹配到 *大小写* 问题的单词时，您应该返回单词列表中的第一个这样的匹配项。
- 当查询匹配到 *元音错误* 的单词时，您应该返回单词列表中的第一个这样的匹配项。
- 如果该查询在单词列表中 *没有匹配项*，则应返回空字符串。

给出一些查询 `queries`，返回一个单词列表 `answer`，其中 `answer[i]` 是由查询 `query = queries[i]` 得到的正确单词。

## 解题思路

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0966.Vowel-Spellchecker/)

这道题目使用 `map` 来保存 `3` 组映射，分别代表完全匹配，变化大小写后匹配，变化元音字母之后匹配

- 这里注意 变化大小写和元音字母之后可能存在多对一的情况，这里之保存第一个，

这里其实也不太能说服自己，但是目前可以通过所有的 case 

`````c++
class Solution {
public:
    vector<string> spellchecker(vector<string>& word_list, vector<string>& queries) {
        // 完全匹配
        unordered_set<string> words_perfect(word_list.begin(), word_list.end());
        // 小写字母
        unordered_map<string, string> words_cap;
        // 元音匹配
        unordered_map<string, string> words_vowel;
        for (const string& word : word_list) {
            words_perfect.insert(word);
            
            // 注意这里可能会产生多对一的关系，所以只保存第一个即可
            string word_low = Tolower(word);
            if (words_cap.find(word_low) == words_cap.end()) {
                words_cap[word_low] = word;    
            }
            
            // 同上
            string word_low_vowel = Devowel(word_low);
            // cout << word_low_vowel << " --- "; 
            if (words_vowel.find(word_low_vowel) == words_vowel.end()) {
                words_vowel[word_low_vowel] = word;    
            }
        }
        // cout << endl;
        
        vector<string> res;
        for (const string& query : queries) {
            auto it = words_perfect.find(query);
            if (it != words_perfect.end()) {
                res.push_back(*it);
                continue;
            }
            
            string query_low = Tolower(query);
            auto iter = words_cap.find(query_low);
            if (iter != words_cap.end()) {
                res.push_back(iter->second);
                continue;
            }
            
            string query_low_vowel = Devowel(query_low);
            // cout << query_low_vowel << " --- ";
            iter = words_vowel.find(query_low_vowel);
            if (iter != words_vowel.end()) {
                res.push_back(iter->second);
                continue;
            }
            
            res.push_back("");
        }
        
        return res;
    }
    
 private:
    // 转化为小写
    string Tolower(const string& word) {
        string res = "";
        for (char c : word) {
            res += tolower(c);
        }
        return res;
    }
    
    // 对元音字符做处理
    string Devowel(const string& word) {
        string res = word;
        for (char& c : res) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                c = '*';
            }
        }
        
        return res;
    }
};
````
