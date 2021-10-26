# [165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/)

## 题目

Given two version numbers, `version1` and `version2`, compare them.



Version numbers consist of **one or more revisions** joined by a dot `'.'`. Each revision consists of **digits** and may contain leading **zeros**. Every revision contains **at least one character**. Revisions are **0-indexed from left to right**, with the leftmost revision being revision 0, the next revision being revision 1, and so on. For example `2.5.33` and `0.1` are valid version numbers.

To compare version numbers, compare their revisions in **left-to-right order**. Revisions are compared using their **integer value ignoring any leading zeros**. This means that revisions `1` and `001` are considered **equal**. If a version number does not specify a revision at an index, then **treat the revision as `0`**. For example, version `1.0` is less than version `1.1` because their revision 0s are the same, but their revision 1s are `0` and `1` respectively, and `0 < 1`.

*Return the following:*

- If `version1 < version2`, return `-1`.
- If `version1 > version2`, return `1`.
- Otherwise, return `0`.

 

**Example 1:**

```
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation: Ignoring leading zeroes, both "01" and "001" represent the same integer "1".
```

**Example 2:**

```
Input: version1 = "1.0", version2 = "1.0.0"
Output: 0
Explanation: version1 does not specify revision 2, which means it is treated as "0".
```

**Example 3:**

```
Input: version1 = "0.1", version2 = "1.1"
Output: -1
Explanation: version1's revision 0 is "0", while version2's revision 0 is "1". 0 < 1, so version1 < version2.
```

**Example 4:**

```
Input: version1 = "1.0.1", version2 = "1"
Output: 1
```

**Example 5:**

```
Input: version1 = "7.5.2.4", version2 = "7.5.3"
Output: -1
```

 

**Constraints:**

- `1 <= version1.length, version2.length <= 500`
- `version1` and `version2` only contain digits and `'.'`.
- `version1` and `version2` **are valid version numbers**.
- All the given revisions in `version1` and `version2` can be stored in a **32-bit integer**.

## 题目大意

给定两个版本号，version1 和 version2 比较它们，

版本号由一个或者多个修订号组成，由 ' . '隔开，每个修订好由多个数字组成，可能包括前导 0，每个修订至少包含一个字符，修订号从索引 0开始，从左至右 

左边的修订号下标为 0 ，下一个修订号下标为 1，例如，`2.5.33` 和 `0.1` 都是有效的版本号。

比较版本号，从左至右一次比较他们的修订号，比较修订号时，只需要比较忽略前导 0 之后的整数值即可，这意味着，修订号 `1` 和修订号 `001` **相等**，如果版本号没有指定某个下标处的修订号，视这个修订号为0，例如，版本 `1.0` 小于版本 `1.1` ，因为它们下标为 `0` 的修订号相同，而下标为 `1` 的修订号分别为 `0` 和 `1` ，`0 < 1` 。

按照下列规则进行返回：

- If `version1 < version2`, return `-1`.
- If `version1 > version2`, return `1`.
- Otherwise, return `0`.

## 解题思路

### 解法1

最直接的方法就是，将版本号重新划分为 修订号，返回逐个比较修订号

因为 C++ 并没有直接诶分隔字符串的函数，所以这里利用 stringstream 来分割字符串，这个技巧是十分值得学习的。

这里放上一篇题解：https://leetcode-cn.com/problems/compare-version-numbers/solution/gong-shui-san-xie-jian-dan-zi-fu-chuan-m-xsod/

这种解法直接利用库函数 stoi 来进行数字的转化，所以代码实现的难度不高

`````c++
class Solution {
public:
    int compareVersion(string version1, string version2) {
        vector<string> strs1 = Split(version1, '.');
        vector<string> strs2 = Split(version2, '.');
        
        const int size1 = strs1.size();
        const int size2 = strs2.size();
        int idx1 = 0, idx2 = 0;
        // 逐个匹配
        while (idx1 < size1 || idx2 < size2) {
            // 如果没有指定的话，记作 0
            int num1 = idx1 < size1 ? stoi(strs1[idx1]) : 0;
            int num2 = idx2 < size2 ? stoi(strs2[idx2]) : 0;
            
            // 一旦不匹配直接返回
            if (num1 != num2) {
                return num1 > num2 ? 1 : -1;
            }
            // 移动下标
            ++idx1;
            ++idx2;
        }
        return 0;
    }
    
 private:
    // 拆分字符串
    vector<string> Split(const string& str, char delim) {
        vector<string> res;
        stringstream ss(str);
        string item = "";
        while (getline(ss, item, delim)) {
            res.push_back(item);   
        }
        
        return res;
    }
};
`````

### 解法2（双指针）

``````c++
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0;
        int j = 0;
        
        while (i < version1.size() || j < version2.size()) {
            // 得出修订号的整数形式
            int num1 = 0;
            while (i < version1.size() && version1[i] != '.') {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }
            
            int num2 = 0;
            while (j < version2.size() && version2[j] != '.') {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }
            
            // 比较修订号
            if (num1 != num2) {
                return num1 > num2 ? 1 : -1;
            }
            
            // 跳过 '.' 符号
            i++;
            j++;
        }
        
        return 0;
    }
};
``````

