# [756. Pyramid Transition Matrix](https://leetcode.com/problems/pyramid-transition-matrix/)

You are  stacking blocks to form a pyramid. Each block has a color, which is  represented by a single letter. Each row of blocks contains **one less block** than the row beneath it and is centered on top.

To make the pyramid aesthetically pleasing, there are only specific **triangular patterns** that are allowed. A triangular pattern consists of a **single block** stacked on top of **two blocks**. The patterns are given as a list of three-letter strings `allowed`, where the first two characters of a pattern represent the left and  right bottom blocks respectively, and the third character is the top  block.

- For example, `"ABC"` represents a triangular pattern with a `'C'` block stacked on top of an `'A'` (left) and `'B'` (right) block. Note that this is different from `"BAC"` where `'B'` is on the left bottom and `'A'` is on the right bottom.

You start with a bottom row of blocks `bottom`, given as a single string, that you **must** use as the base of the pyramid.

Given `bottom` and `allowed`, return `true` *if you can build the pyramid all the way to the top such that **every triangular pattern** in the pyramid is in* `allowed`*, or* `false` *otherwise*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/26/pyramid1-grid.jpg)

```
Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
Output: true
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 3), we can build "CE" on level 2 and then build "E" on level 1.
There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/08/26/pyramid2-grid.jpg)

```
Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
Output: false
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 4), there are multiple ways to build level 3, but trying all the possibilites, you will get always stuck before building level 1.
```

 

**Constraints:**

- `2 <= bottom.length <= 6`
- `0 <= allowed.length <= 216`
- `allowed[i].length == 3`
- The letters in all input strings are from the set `{'A', 'B', 'C', 'D', 'E', 'F'}`.
- All the values of `allowed` are **unique**.

## 题目大意

你正在把积木堆成金字塔。每个块都有一个颜色，用一个字母表示。每一行的块比它下面的行 *少一个块* ，*并且居中*。

为了使金字塔美观，只有特定的 *三角形图案* 是允许的。一个三角形的图案由 *两个块* 和叠在上面的 *单个块* 组成。模式是以三个字母字符串的列表形式 `allowed` 给出的，其中模式的前两个字符分别表示左右底部块，第三个字符表示顶部块。

- 例如，`"ABC"` 表示一个三角形图案，其中一个 `“C”` 块堆叠在一个 `'A'` 块(左)和一个 `'B'` 块(右)之上。请注意，这与 `"BAC"` 不同，`"B"` 在左下角，`"A"` 在右下角。

你从底部的一排积木 `bottom` 开始，作为一个单一的字符串，你 必须 使用作为金字塔的底部。

在给定 bottom 和 allowed 的情况下，如果你能一直构建到金字塔顶部，使金字塔中的 每个三角形图案 都是允许的，则返回 true ，否则返回 false 。

## 解题思路

### Solution 1: DFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0756.Pyramid-Transition-Matrix/)

这里就是递归的构建每一层的 `bottom`，如果下一层的 bottom 已经构建成功，就切换到新的 bottom，然后继续开始构造

这里构造每一层 bottom，也是在遍历和使用 alloweds 中的每个合法的三角进行匹配

````c++
class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& alloweds) {
        // key bottom --> val: top
        unordered_map<string, vector<char>> pyramids;
        for (const string& allowed : alloweds) {
            pyramids[allowed.substr(0, 2)].push_back(allowed.back());
        }
        
        return DFS(bottom, "", pyramids);
    }
    
 private:
    bool DFS(const string& bottom, const string& above,
             const unordered_map<string, vector<char>>& pyramids) {
        // 递归终止
        if (bottom.size() == 2 && above.size() == 1) {
            return true;
        }
        // 如果 above 已经构建完成，用 above 替换 bottom
        if (bottom.size() == above.size() + 1) {
            return DFS(above, "", pyramids);
        }
        
        // 遍历所有可能的组合
        const string base = std::move(bottom.substr(above.size(), 2));
        auto it = pyramids.find(base);
        if (it != pyramids.end()) {
            for (char allow : it->second) {
                // 一旦找到就直接返回
                if (DFS(bottom, above + allow, pyramids)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
````
