# [71. Simplify Path](https://leetcode.com/problems/simplify-path/)

## 题目

Given a string `path`, which is an **absolute path** (starting with a slash `'/'`) to a file or directory in a Unix-style file system, convert it to the simplified **canonical path**.

In a Unix-style file system, a period `'.'` refers to the current directory, a double period `'..'` refers to the directory up a level, and any multiple consecutive slashes (i.e. `'//'`) are treated as a single slash `'/'`. For this problem, any other format of periods such as `'...'` are treated as file/directory names.

The **canonical path** should have the following format:

- The path starts with a single slash `'/'`.
- Any two directories are separated by a single slash `'/'`.
- The path does not end with a trailing `'/'`.
- The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period `'.'` or double period `'..'`)

Return *the simplified **canonical path***.

 

**Example 1:**

```
Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
```

**Example 2:**

```
``Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
```

**Example 3:**

```
Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
```

**Example 4:**

```
Input: path = "/a/./b/../../c/"
Output: "/c"
```

 

**Constraints:**

- `1 <= path.length <= 3000`
- `path` consists of English letters, digits, period `'.'`, slash `'/'` or `'_'`.
- `path` is a valid absolute Unix path.

## 题目大意

给定一个字符串，表示一个 Unix 文件的绝对路径，将其转换为一个更加简洁的规范路径

在Unix 文件系统中`'.'`表示当前目录，`'..'`表示当前目录的上一级目录，任何连续的多重斜线（ie. `'//'`）被视为一个单独的斜线(ie. `'/'`)，对于这个题目，任何其他格式的点（如：`'...'`）都被视为文件名或者目录名。

一个规范的路径必须满足如下条件：

* 字符串以`‘/’`开头
* 任意两个目录以`'/'`分隔
* 最后一个目录名（如果存在）**不能** 以 `'/'` 结尾。
* 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 `'.'` 或 `'..'`）。

返回简化后得到的规范路径名

## 解题思路

用一个 Vector 来模拟路径，用 ‘/‘ 来分隔path，

* 如果时`"."`或者`""，则直接跳过`
* 如果不是“..” ,就将当前目录名推入数组
* 如果是 ".." 且数组不为空，则删掉上一次推入的目录名

## 代码

````c++
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> strs;
        string cur = "";
        stringstream ss(path);
        
        while (getline(ss, cur, '/')) {
            if (cur != "." && cur != "") {
                if (cur != "..") {
                    strs.push_back(cur);
                } else if (!strs.empty()){
                    strs.pop_back();
                }
            }
        }
        
        if (!strs.empty()) {
            string res = "";
            for (string str : strs) {
                res += "/";
                res += str;
            }
            return res;
        }
        
        return "/";
    }
};
````

