# [388. Longest Absolute File Path](https://leetcode-cn.com/problems/longest-absolute-file-path/)

## 题目

Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:

![img](https://assets.leetcode.com/uploads/2020/08/28/mdir.jpg)

Here, we have `dir` as the only directory in the root. `dir` contains two subdirectories, `subdir1` and `subdir2`. `subdir1` contains a file `file1.ext` and subdirectory `subsubdir1`. `subdir2` contains a subdirectory `subsubdir2`, which contains a file `file2.ext`.

In text form, it looks like this (with ⟶ representing the tab character):

```
dir
⟶ subdir1
⟶ ⟶ file1.ext
⟶ ⟶ subsubdir1
⟶ subdir2
⟶ ⟶ subsubdir2
⟶ ⟶ ⟶ file2.ext
```

If we were to write this representation in code, it will look like this: `"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"`. Note that the `'\n'` and `'\t'` are the new-line and tab characters.

Every file and directory has a unique **absolute path** in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by `'/'s`. Using the above example, the **absolute path** to `file2.ext` is `"dir/subdir2/subsubdir2/file2.ext"`. Each directory name consists of letters, digits, and/or spaces. Each file name is of the form `name.extension`, where `name` and `extension` consist of letters, digits, and/or spaces.

Given a string `input` representing the file system in the explained format, return *the length of the **longest absolute path** to a **file** in the abstracted file system*. If there is no file in the system, return `0`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/28/dir1.jpg)

```
Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
Output: 20
Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/08/28/dir2.jpg)

```
Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
Output: 32
Explanation: We have two files:
"dir/subdir1/file1.ext" of length 21
"dir/subdir2/subsubdir2/file2.ext" of length 32.
We return 32 since it is the longest absolute path to a file.
```

**Example 3:**

```
Input: input = "a"
Output: 0
Explanation: We do not have any files, just a single directory named "a".
```

 

**Constraints:**

- `1 <= input.length <= 104`
- `input` may contain lowercase or uppercase English letters, a new line character `'\n'`, a tab character `'\t'`, a dot `'.'`, a space `' '`, and digits.

### 题目大意

假设有一个同时存储文件和目录的文件系统。下图展示了文件系统的一个示例：



这里将 `dir` 作为根目录中的唯一目录。`dir` 包含两个子目录 `subdir1` 和 `subdir2` 。`subdir1` 包含文件 `file1.ext` 和子目录 `subsubdir1`；`subdir2` 包含子目录 `subsubdir2`，该子目录下包含文件 `file2.ext` 。

在文本格式中，如下所示(⟶表示制表符)：

`````
dir
⟶ subdir1
⟶ ⟶ file1.ext
⟶ ⟶ subsubdir1
⟶ subdir2
⟶ ⟶ subsubdir2
⟶ ⟶ ⟶ file2.ext
`````

如果是代码表示，上面的文件系统可以写为 `"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" `。`'\n'` 和 `'\t'` 分别是换行符和制表符。

文件系统中的每个文件和文件夹都有一个唯一的 绝对路径 ，即必须打开才能到达文件/目录所在位置的目录顺序，所有路径用 `'/'` 连接。上面例子中，指向 `file2.ext` 的绝对路径是 `"dir/subdir2/subsubdir2/file2.ext"` 。每个目录名由字母、数字和/或空格组成，每个文件名遵循 `name.extension` 的格式，其中名称和扩展名由字母、数字和/或空格组成。

给定一个以上述格式表示文件系统的字符串 input ，返回文件系统中 指向文件的最长绝对路径 的长度。 如果系统中没有文件，返回 0。



### 解题思路

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/longest-absolute-file-path/solution/388-cchao-100de-jian-dan-yi-dong-de-zhi-pcfuk/

这种解法的主要思路如下

* 使用 `'\n'`来划分不同的层级，使用 `'\t'`，来划分第几层，
* 使用 `'.'`来确认是否是文件，
* 遇到文件再更新最大长度，

```c++
class Solution {
public:
    int lengthLongestPath(string input) {
        // 给末尾添加一个 '\n'，为了处理逻辑上的统一
        input.push_back('\n');
        
        vector<int> levels(100); // 存储每一层的长度
        bool is_file = false; // 是否是文件
        int res = 0; // 最终结果
        int len = 0; // 作为每一层的长度
        int cur_level = 0; // 当前是第几层
        
        for (char c : input) {
            if (c == '\t') {
                ++cur_level; // 有几个制表符，就代表第几层，这里从第 0 层开始
            } else if (c == '\n') {
                levels[cur_level] = len; // 存储当前层的长度
                
                if (is_file) {
                    // 如果是文件的话，更新最大长度
                    int max_len = 0;
                    for (int i = 0; i <= cur_level; ++i) {
                        max_len += levels[i];
                    }
                    // 这里是为了加上分割符 '/'
                    res = max(res, max_len + cur_level);
                }
                // 重置参数
                cur_level = 0;
                len = 0;
                is_file = false;
            } else {
                if (c == '.') {
                    // 只有文件才有扩展名
                    is_file = true;
                }
                ++len;
            }
        }
        
        return res;
    }
};
```

### Solution 2: 利用栈来做

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/longest-absolute-file-path/solution/cstackwen-jian-zui-chang-jue-dui-lu-jing-kds6/

这里用栈来模拟 DFS，难点在于目录的出栈那里，这里可以自己打印看一下，

* 用栈记录当前目录

* 每次统计当前目录或文件所在层数

* 如果栈中元素大雨当前层数， 则持续出栈到栈中元素数量等于当前层数，

  

````c++
class Solution {
public:
    int lengthLongestPath(string input) {
        stack<string> strs; // 只存储目录
        string cur = ""; // 解析当前部分
        bool is_file = false; // 是否是文件
        int res = 0; // 最终结果
        int len = 0; // 当前路径
        int dir_len = 0; // 目录的长度
        const int size = input.size();
        
        int i = 0, j = 0; // i 是下标，j 是 '\t' 的数量，表示第几层
        while (i < size) {
            while (i < size && input[i] != '\n') {
                // 解析一段的字符串
                cur.push_back(input[i]);
                if (input[i] == '.') {
                    // 如果有扩展名，就是文件
                    is_file = true;
                }
                ++i;
            }
            
            if (is_file) {
                // 如果是文件
                int err = strs.size() - j;
                for (int k = 0; k < err; ++k) {
                    // 先达到文件所在的目录
                    dir_len -= strs.top().length() + 1;
                    strs.pop();
                }
                
                len = dir_len + cur.length(); // 这里不用加分隔符 '/'
                res = max(res, len);
                // 重置
                cur.clear();
                is_file = false;
            } else {
                // 如果是目录
                // cout << strs.size() << " --- ";
                int err = strs.size() - j;
                // cout << dir_len << " --- " << j << endl;
                for (int k = 0; k < err; ++k) {
                    dir_len -= strs.top().length() + 1;
                    strs.pop();
                }
                strs.push(cur); // 目录入栈
                dir_len += strs.top().length() + 1; // 这里要加上分割符 '/'
                // 重置
                cur.clear();
            }
            
            if (i >= input.size()) {
                // 解析完成，结束
                break;
            }
            
            ++i; // 跳过 '\n'
            j = 0; // 重置
            while (input[i] == '\t') {
                // 解析制表符
                ++i;
                ++j;
            }
        }
        return res;
    }
};
````



