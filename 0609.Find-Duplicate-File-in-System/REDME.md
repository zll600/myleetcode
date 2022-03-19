# [609. Find Duplicate File in System](https://leetcode.com/problems/find-duplicate-file-in-system/)

## 题目

Given a list `paths` of directory info, including the directory path, and all the files with contents in this directory, return *all the duplicate files in the file system in terms of their paths*. You may return the answer in **any order**.

A group of duplicate files consists of at least two files that have the same content.

A single directory info string in the input list has the following format:

- `"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"`

It means there are `n` files `(f1.txt, f2.txt ... fn.txt)` with content `(f1_content, f2_content ... fn_content)` respectively in the directory "`root/d1/d2/.../dm"`. Note that `n >= 1` and `m >= 0`. If `m = 0`, it means the directory is just the root directory.

The output is a list of groups of duplicate file paths. For each  group, it contains all the file paths of the files that have the same  content. A file path is a string that has the following format:

- `"directory_path/file_name.txt"`

 

**Example 1:**

```
Input: paths = ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root 4.txt(efgh)"]
Output: [["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
```

**Example 2:**

```
Input: paths = ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)"]
Output: [["root/a/2.txt","root/c/d/4.txt"],["root/a/1.txt","root/c/3.txt"]]
```

 

**Constraints:**

- `1 <= paths.length <= 2 * 104`
- `1 <= paths[i].length <= 3000`
- `1 <= sum(paths[i].length) <= 5 * 105`
- `paths[i]` consist of English letters, digits, `'/'`, `'.'`, `'('`, `')'`, and `' '`.
- You may assume no files or directories share the same name in the same directory.
- You may assume each given directory info represents a unique  directory. A single blank space separates the directory path and file  info.

 

**Follow up:**

- Imagine you are given a real file system, how will you search files? DFS or BFS?
- If the file content is very large (GB level), how will you modify your solution?
- If you can only read the file by 1kb each time, how will you modify your solution?
- What is the time complexity of your modified solution? What is the  most time-consuming part and memory-consuming part of it? How to  optimize?
- How to make sure the duplicated files you find are not false positive?

## 题目大意

给定一个目录信息列表，包括目录路径和目录中有内容的文件，返回所有重复文件的路径，你可以按照任意顺序返回

一组重复的文件至少含有两个文件内容相同的文件：

一个但文件的目录的信息表示如下：

- `"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"`

这意味着有 `n` 个文件 `(f1.txt, f2.txt ... fn.txt)`  的内容分别是 `(f1_content, f2_content ... fn_content)` 在目录 `root/d1/d2/.../dm` 下。注意：`n>=1 且 m>=0`。如果 `m=0`，则表示该目录是 *根目录*。

该输出是重复文件路径组的列表。对于每个组，它包含具有相同内容的文件的所有文件路径。文件路径是具有下列格式的字符串：`"directory_path/file_name.txt"`

## 题目大意


### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0609.Find-Duplicate-File-in-System/)

这里的难点在于分隔字符串，我们利用哈希表来做统计，最后再筛选即可


````c++
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        // 这里按照文件的内容进行分类
        unordered_map<string, vector<string>> records;
        // 这里的难点在于分隔字符串
        for (const auto& path : paths) {
            vector<string> parts;
            Split(path, parts);
            string dir = parts[0];

            const int len = parts.size();
            for (int i = 1; i < len; ++i) {
                int idx = parts[i].find_first_of("(", 0);
                string content = parts[i].substr(idx + 1, parts[i].size() - idx - 1);
                records[content].push_back(dir + "/" + parts[i].substr(0, idx));
            }
        }

        vector<vector<string>> res;
        for (const auto& record : records) {
            // 这里我们只记录长度大于 2 的
            if (record.second.size() >= 2) {
                res.push_back(record.second);
            }
        }

        return res;
    }

 private:
    // 分隔字符串
    void Split(const string& str, vector<string>& tokens, string delim = " ") {
        tokens.clear();
        int start = str.find_first_not_of(delim, 0);
        int pos = str.find_first_of(delim, start);
        while (start != string::npos || pos != string::npos) {
            tokens.push_back(std::move(str.substr(start, pos - start)));
            start = str.find_first_not_of(delim, pos);
            pos = str.find_first_of(delim, start);
        }
    }
};
````
