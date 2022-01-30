# [519. Random Flip Matrix](https://leetcode.com/problems/random-flip-matrix/)

## 题目

There is an `m x n` binary grid `matrix` with all the values set `0` initially. Design an algorithm to randomly pick an index `(i, j)` where `matrix[i][j] == 0` and flips it to `1`. All the indices `(i, j)` where `matrix[i][j] == 0` should be equally likely to be returned.

Optimize your algorithm to minimize the number of calls made to the **built-in** random function of your language and optimize the time and space complexity.

Implement the `Solution` class:

- `Solution(int m, int n)` Initializes the object with the size of the binary matrix `m` and `n`.
- `int[] flip()` Returns a random index `[i, j]` of the matrix where `matrix[i][j] == 0` and flips it to `1`.
- `void reset()` Resets all the values of the matrix to be `0`.

 

**Example 1:**

```
Input
["Solution", "flip", "flip", "flip", "reset", "flip"]
[[3, 1], [], [], [], [], []]
Output
[null, [1, 0], [2, 0], [0, 0], null, [2, 0]]

Explanation
Solution solution = new Solution(3, 1);
solution.flip();  // return [1, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
solution.flip();  // return [2, 0], Since [1,0] was returned, [2,0] and [0,0]
solution.flip();  // return [0, 0], Based on the previously returned indices, only [0,0] can be returned.
solution.reset(); // All the values are reset to 0 and can be returned.
solution.flip();  // return [2, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
```

 

**Constraints:**

- `1 <= m, n <= 104`
- There will be at least one free cell for each call to `flip`.
- At most `1000` calls will be made to `flip` and `reset`.

## 题目大意

给你一个 `m x n` 的二元矩阵 `matrix` ，且所有值被初始化为 `0` 。请你设计一个算法，随机选取一个满足 `matrix[i][j] == 0` 的下标 `(i, j)` ，并将它的值变为 `1` 。所有满足 `matrix[i][j] == 0` 的下标 `(i, j)` 被选取的概率应当均等

尽量最少调用内置的随机函数，并且优化时间和空间复杂度

实现 `Solution` 类：

- `Solution(int m, int n)` 使用二元矩阵的大小 `m` 和 `n` 初始化该对象
- `int[] flip()` 返回一个满足 `matrix[i][j] == 0` 的随机下标 `[i, j]` ，并将其对应格子中的值变为 `1`
- `void reset()` 将矩阵中所有的值重置为 `0`



## 解题思路

### Solution1: 哈希 + swap

这种解法可以参考这篇 [题解](https://leetcode-cn.com/problems/random-flip-matrix/solution/gong-shui-san-xie-note-bie-pian-yi-ti-sh-e6gi/)

一般的蓄水池抽样算法，都是操作一维数组，这道题目给的是二维的条件，所以可以考虑将二维化为一维来做，这里有个难点，就是反转后要维持一维空间的有效性

这种解法利用哈希表来将 二维数组转化为一位的连续空间，在一维上随机选取一个位置，然后将这个位置与有效空间的最后一个位置坐交换，保证前面的空间都是有效的
这里的复杂度分析可以借鉴三叶姐的题解，

````C++
class Solution {
public:
    Solution(int m, int n) : m_(m), n_(n), total_(m * n){
    }
    
    vector<int> flip() {
        // [0, total_) 范围内取值
        uniform_int_distribution<int> rand_(0, total_ - 1);
        int key = rand_(engine_);
        int val = key;
        if (data_.find(key) != data_.end()) {
            // 如果 key 存在在哈希表中，就取哈希表中的值
            val = data_[key];
        }
        
        // 将 key 与最右边的位置进行交换
        if (data_.find(total_ - 1) != data_.end()) {
            data_[key] = data_[total_ - 1];
        } else {
            data_[key] = total_ - 1;
        }
        
        // 更新映射
        data_.erase(total_ - 1);
        --total_;
        
        return {val / n_, val % n_}; 
    }
    
    void reset() {
        total_ = m_ * n_;
        data_.clear();
    }
 
 private:
    default_random_engine engine_; // 随机数引擎
    unordered_map<int, int> data_; // 哈希表
    int total_; // 始终维持有效的总数
    int m_; // 
    int n_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */
````

