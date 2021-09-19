# [765. Couples Holding Hands](https://leetcode.com/problems/couples-holding-hands/) 

## 题目

There are `n` couples sitting in `2n` seats arranged in a row and want to hold hands.

The people and seats are represented by an integer array `row` where `row[i]` is the ID of the person sitting in the `ith` seat. The couples are numbered in order, the first couple being `(0, 1)`, the second couple being `(2, 3)`, and so on with the last couple being `(2n - 2, 2n - 1)`.

Return *the minimum number of swaps so that every couple is sitting side by side*. A swap consists of choosing any two people, then they stand up and switch seats.

 

**Example 1:**

```
Input: row = [0,2,1,3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
```

**Example 2:**

```
Input: row = [3,2,0,1]
Output: 0
Explanation: All couples are already seated side by side.
```

 

**Constraints:**

- `2n == row.length`
- `2 <= n <= 30`
- `n` is even.
- `0 <= row[i] < 2n`
- All the elements of `row` are **unique**.

## 题目大意

有 n 对情侣，坐在 一排2n 个座位上，想要牵手，

人和座位用一个数组 row 来表示，row[i]表示坐在第 i 个座位的人的 ID ，情侣们按顺序编号，第一队情侣是(0, 1)，第二对情侣是 (2, 3)，最后一对情侣是(2n - 1, 2n - 2),

返回使每对情侣可以坐在一起的最少交换次数，一次交换可以指定任意两人，让他们站起来交换座位，

## 解题思路

* 对于那些交错的情侣来说，交换次数就好似连通分量大小减1，于是问题就转化为了，求连通分量的数目
* 我们将每对情侣作为单位，对于情侣对（0，1）而言，编号为0，推广得到情侣对(i, i + 1)， 编号 i / 2,
* 如果有 k 对情侣坐错了位置，需要交换 k - 1次，才能让情侣牵手，

## 代码

`````c++
class UF {
 public:
    UF(int n) : count_(n) {
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
    
    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);
        
        if (proot == qroot) {
            return;
        }
        
        parent_[proot] = qroot;
        --count_;
    }
    
    int count() {
        return count_;   
    }
    
 private:
    vector<int> parent_;
    int count_;
};

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int size = row.size();
        UF uf(size / 2);    // 用并查集表示有 n 对情侣，
        
        for (int i = 0; i < size / 2; ++i) {    // 凑成所有对情侣，并且将交叉情侣也连接起来，篇
            uf.Union(row[2 * i] / 2, row[2 * i + 1] / 2);
        }
        
        return size / 2 - uf.count();
    }
};
`````

