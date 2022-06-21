# [[NOIP2001 普及组] 求先序排列](https://www.luogu.com.cn/problem/P1030)

## 题目描述

给出一棵二叉树的中序与后序排列。求出它的先序排列。（约定树结点用不同的大写字母表示，长度$  \le  8$）。

## 输入格式

$2$行，均为大写字母组成的字符串，表示一棵二叉树的中序与后序排列。

## 输出格式

$1$行，表示一棵二叉树的先序。

## 样例 #1

### 样例输入 #1

```
BADC
BDCA
```

### 样例输出 #1

```
ABCD
```

## 提示

**【题目来源】**

NOIP 2001 普及组第三题



### Solution 1:

这里注意是利用中序分割后的左右子树的长度来划分后序遍历的，注意不是下标，是长度，这道题目也可以只用下标来做

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
 	void Solve(const string& inorder, const string& postorder) {
		if (inorder.size() <= 0) {
			return;
		}
		char ch = postorder.back();
		cout << ch;
		int pos = inorder.find(ch);
		Solve(inorder.substr(0, pos), postorder.substr(0, pos));
		Solve(inorder.substr(pos + 1), postorder.substr(pos, inorder.size() - pos - 1));
	}  	
};

int main(void) {
	string inorder;
	string postorder;
	cin >> inorder;
	cin >> postorder;
	
	Solution obj;
	obj.Solve(inorder, postorder);
	
	return 0;
}
````

