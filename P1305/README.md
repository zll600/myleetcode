# [新二叉树](https://www.luogu.com.cn/problem/P1305)

## 题目描述

输入一串二叉树，输出其前序遍历。

## 输入格式

第一行为二叉树的节点数 $n$。($1 \leq n \leq 26$)

后面 $n$ 行，每一个字母为节点，后两个字母分别为其左右儿子。

空节点用 `*` 表示

## 输出格式

二叉树的前序遍历。

## 样例 #1

### 样例输入 #1

```
6
abc
bdi
cj*
d**
i**
j**
```

### 样例输出 #1

```
abdicj
```



### Solution 1

这里就是使用二叉树的先序遍历来构建二叉树，其实这里也可以用list 来存储，可能会更好一点

````c++
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
	void Solve(const vector<string>& nodes) {
		string ans = nodes[0];
		for (size_t i = 1; i < nodes.size(); ++i) {
			size_t pos = ans.find(nodes[i][0]);
			ans.replace(pos, 1, nodes[i]);
		}
		
		for (char c : ans) {
			if (c == '*') {
				continue;
			}
			cout << c;
		}
		cout << endl;
	}
};

int main(void) {
   	int n;
	cin >> n;
	vector<string> nodes(n);
	for (int i = 0; i < n; ++i) {
		cin >> nodes[i];
	}
	Solution obj;
	obj.Solve(nodes);
	
   return 0;
}
````



