#### [1286. Iterator for Combination](https://leetcode.cn/problems/iterator-for-combination/)

## 题目

Design the `CombinationIterator` class:

- `CombinationIterator(string characters, int combinationLength)` Initializes the object with a string `characters` of **sorted distinct** lowercase English letters and a number `combinationLength` as arguments.
- `next()` Returns the next combination of length `combinationLength` in **lexicographical order**.
- `hasNext()` Returns `true` if and only if there exists a next combination.

 

**Example 1:**

```
Input
["CombinationIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[["abc", 2], [], [], [], [], [], []]
Output
[null, "ab", true, "ac", true, "bc", false]

Explanation
CombinationIterator itr = new CombinationIterator("abc", 2);
itr.next();    // return "ab"
itr.hasNext(); // return True
itr.next();    // return "ac"
itr.hasNext(); // return True
itr.next();    // return "bc"
itr.hasNext(); // return False
```

 

**Constraints:**

- `1 <= combinationLength <= characters.length <= 15`
- All the characters of `characters` are **unique**.
- At most `104` calls will be made to `next` and `hasNext`.
- It is guaranteed that all calls of the function `next` are valid.



### 题目大意

请你设计一个迭代器类 CombinationIterator ，包括以下内容：

    CombinationIterator(string characters, int combinationLength) 一个构造函数，输入参数包括：用一个 有序且字符唯一 的字符串 characters（该字符串只包含小写英文字母）和一个数字 combinationLength 。
    函数 next() ，按 字典序 返回长度为 combinationLength 的下一个字母组合。
    函数 hasNext() ，只有存在长度为 combinationLength 的下一个字母组合时，才返回 true



### 解题思路

类似 *组合* 题目，在构造函数中，构造所有可能的结果，这样至于构造函数的时间复杂度较高，next 和 hasnext 函数的世间复杂度都是 O(1)

### Solution 1: DFS



````c++
class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {
        string path;
        DFS(characters, 0, path, combinationLength);
    }
    
    string next() {
        string ans = std::move(combinations_.front());
        combinations_.pop();
        return ans;
    }
    
    bool hasNext() {
        return !combinations_.empty();
    }
    
 private:
    queue<string> combinations_;
    
    void DFS(const string& characters, int idx, string& path, int combination_len) {
        if (path.size() == combination_len) {
            combinations_.push(path);
            return;
        }
        
        const int len = characters.size();
        for (int i = idx; i < len; ++i) {
            path.append(1, characters[i]);
            DFS(characters, i + 1, path, combination_len);
            path.pop_back();
        }
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
````

