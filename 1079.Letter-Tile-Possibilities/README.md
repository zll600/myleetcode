# [1079. Letter Tile Possibilities](https://leetcode.com/problems/letter-tile-possibilities/)

## 题目

You have `n` `tiles`, where each tile has one letter `tiles[i]` printed on it.

Return *the number of possible non-empty sequences of letters* you can make using the letters printed on those `tiles`.

**Example 1:**

```
Input: tiles = "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
```

**Example 2:**

```
Input: tiles = "AAABBC"
Output: 188
```

**Example 3:**

```
Input: tiles = "V"
Output: 1
```

 

**Constraints:**

- `1 <= tiles.length <= 7`
- `tiles` consists of uppercase English letters.

## 题目大意

给定一套活字字模，每个字模上都刻有一个字，返回你可以利用这些字模印出的非空字母序列的个数，字模由大写的英文字母组成，

## 解题思路

* 这道题目是一道 排列 + 组合的问题，组合是每次可以选 1，2，3，...n 个字符，排列是组内排列，

* 可以利用 回溯法来解决，将字符串放在一个字符数组中，联系第 47 题，不过这次需要的记录路径上的所有结果，不仅仅是叶子节点，而且不需要知道结果的内容，只需要知道内容即可，
* 可以建立一个字频统计，因为不需要知道具体的解的结果，只需要知道解的数目，

## 代码

````c++
// 解法一：暴力法
/*
class Solution {
public:
    int numTilePossibilities(string tiles) {
        vector<char> dict;
        dict.reserve(7);
        for (char c : tiles) {
            dict.push_back(c);
        }
        sort(dict.begin(), dict.end());
        vector<bool> used(tiles.size(), false);
        // Backtracking(dict, used);
        Backtracking(dict, used, 0);
        return res;
    }
    
 private:
    int res;
    // vector<int> path;
    
    
    void Backtracking(const vector<char>& dict, vector<bool>& used) {
        if (path.size() == dict.size()) {
            return;
        }
        
        int size = dict.size();
        for (int i = 0; i < size; ++i) {
            if (!used[i]) {
                if (i > 0 && dict[i - 1] == dict[i] && !used[i - 1]) {
                    continue;
                }
                
                path.push_back(dict[i]);
                ++res;
                used[i] = true;
                Backtracking(dict, used);
                used[i] = false;
                path.pop_back();
            }
        }
    }
    
    void Backtracking(const vector<char>& dict, vector<bool>& used, int idx) {
        if  (idx == dict.size()) {
            return;
        }
        
        int size = dict.size();
        for (int i = 0; i < size; ++i) {
            if (!used[i]) {
                if (i > 0 && dict[i - 1] == dict[i] && !used[i - 1]) {
                    continue;
                }
                
                //++idx;
                ++res;
                used[i] = true;
                Backtracking(dict, used, idx + 1);
                used[i] = false;
                //--idx;
            }
        }
    }
};*/


// 解法二：建立一个字频统计
class Solution {
 public:
    int numTilePossibilities(string tiles) {
        vector<int> freq(26);
        for (char c : tiles) {
            ++freq[c - 'A'];
        }
        
        return Backtracking(freq);
    }
    
 private:
    int Backtracking(vector<int>& freq) {
        int res = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) {
                continue;
            }
            
            ++res;
            --freq[i];
            res += Backtracking(freq);
            ++freq[i];
        }
        return res;
    }
};
````

