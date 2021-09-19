# [721. Accounts Merge](https://leetcode.com/problems/accounts-merge/)

## 题目

Given a list of `accounts` where each element `accounts[i]` is a list of strings, where the first element `accounts[i][0]` is a name, and the rest of the elements are **emails** representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails **in sorted order**. The accounts themselves can be returned in **any order**.

 

**Example 1:**

```
Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Explanation:
The first and second John's are the same person as they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
```

**Example 2:**

```
Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
```

 

**Constraints:**

- `1 <= accounts.length <= 1000`
- `2 <= accounts[i].length <= 10`
- `1 <= accounts[i][j] <= 30`
- `accounts[i][0]` consists of English letters.
- `accounts[i][j] (for j > 0)` is a valid email.

## 题目大意

给定一个列表 accounts，列表的每项元素是一个字符串列表，accouts[i] 的第一项是姓名，剩下的都是表示该账户的邮箱，

现在我们想合并一些账户，如果这些账户中由一些共同的邮箱，我们可以认为这些账户属于同一个人。因为不同的人可以由相同的名字，即使两个账户有同样的名字，这两个账户也不一定属于同一个人，一个人初始可以任意数量的账户，但是所有账户的名字，相同，

合并账户后，按照以下格式返回账户：每个账户的第一个元素都是名称，其余元素是按照字幕顺序的邮箱地址，

## 解题思路

* 这道题就是要将数组中有相同邮箱的行连通到一起，因此可以使用并查集来进行解决，
* 这里初始化每一行（每个账户）一个连通分量，遍历账户下的邮箱，如果没有出现在其他账户，继续，如果出现过其他账户，将两个账户连通，
* ##

## 代码

`````c++
class UF {
 public:
    UF(int n) {
        parent_.resize(n);
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
        }
    }
    
    int Find(int p) {
        while (p != parent_[p]) {
            parent_[p] = parent_[parent_[p]];
            p = parent_[p];
        }
        return p;
    }
    
    bool Connected(int p, int q) {
        return Find(p) == Find(q);
    }
    
    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);
        
        if (proot == qroot) {
            return;
        }
        parent_[proot] = qroot;
    }
    
 private:
    vector<int> parent_;
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> email;   // 这里保存的行id，和对应邮箱的映射
        int n = accounts.size();
        UF uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < accounts[i].size(); ++j) {
                string str = accounts[i][j];
                
                if (email.find(str) == email.end()) {
                    email.insert(make_pair(str, i));    // 如果没有出现，就添加到映射中
                } else {
                    uf.Union(i, email.at(str)); // 如果出现过就进行连通
                }
            }
        }
        
        vector<vector<string>> res;
        // 这里保存用户的 id，和与之关联的所有邮箱
        // 不能使用名称，因为名称可能会出现重复
        unordered_map<int, vector<string>> cache;
        for (auto& [k, v] : email) {
            cache[uf.Find(v)].emplace_back(k);
        }
        
        for (auto& [k, v] : cache) {
            sort(v.begin(), v.end());
            vector<string> tmp(1, accounts[k][0]);  // 插入名字，利用id进行索引
            tmp.insert(tmp.end(), v.begin(), v.end());
            res.emplace_back(tmp);
        }
        
        return res;
    }
};
`````



