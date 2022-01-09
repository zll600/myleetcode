# [390. Elimination Game](https://leetcode-cn.com/problems/elimination-game/)

## 题目

You have a list `arr` of all integers in the range `[1, n]` sorted in a strictly increasing order. Apply the following algorithm on `arr`:

- Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
- Repeat the previous step again, but this time from right to left, remove the rightmost number and every other number from the remaining numbers.
- Keep repeating the steps again, alternating left to right and right to left, until a single number remains.

Given the integer `n`, return *the last number that remains in* `arr`.

 

**Example 1:**

```
Input: n = 9
Output: 6
Explanation:
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr = [2, 4, 6, 8]
arr = [2, 6]
arr = [6]
```

**Example 2:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `1 <= n <= 109`

## 题目大意

列表 `arr` 由在范围 `[1, n]` 中的所有整数组成，并按**严格递增**排序。对 `arr` 应用下述算法：

* 从左到右，删除第一个数字，然后每隔一个数字删除一个，直到到达列表末尾
* 重复上面的步骤，但这次是从右到左。也就是，删除最右侧的数字，然后剩下的数字每隔一个删除一个
* 不断重复这两步，从左到右和从右到左交替进行，直到只剩下一个数字

返回最后一个剩下的数字

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/elimination-game/solution/c-shu-xue-by-qian2-60yk/

这是一道数学 + 找规律的题目

### Solution 1:

这种解法要新开许多的数组，结果内存超出限制了

````c++
class Solution {
public:
    int lastRemaining(int n) {
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = i + 1;
        }
        
        bool left_to_right = true; // 维护遍历方向
        while (res.size() > 1) {
            const int len = res.size();
            vector<int> tmp(len / 2);
            if (left_to_right) {
                int idx = 0;
                // 从左边开始删
                for (int i = 1; i < len; i += 2) {
                    tmp[idx] = res[i];
                    ++idx;
                }
            } else {
                // 从右边开始删
                int idx = len / 2 - 1;
                for (int i = len - 2; i >= 0; i -= 2) {
                    tmp[idx] = res[i];
                    --idx;
                }
            }
            left_to_right = !left_to_right;
            swap(tmp, res);
        }
        
        return res.front();
    }
};
````

### Solution 2:

这里优化的内存使用，但是会超时

````c++
class Solution {
public:
    int lastRemaining(int n) {
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = i + 1;
        }
        
        bool left_to_right = true; // 维护遍历方向
        vector<int> tmp;
        while (res.size() > 1) {
            const int len = res.size();
            tmp.resize(len / 2);
            if (left_to_right) {
                int idx = 0;
                // 从左边开始删
                for (int i = 1; i < len; i += 2) {
                    tmp[idx] = res[i];
                    ++idx;
                }
            } else {
                // 从右边开始删
                int idx = len / 2 - 1;
                for (int i = len - 2; i >= 0; i -= 2) {
                    tmp[idx] = res[i];
                    --idx;
                }
            }
            left_to_right = !left_to_right;
            swap(tmp, res);
            tmp.clear();
        }
        
        return res.front();
    }
};
````

### Solution 3:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/elimination-game/solution/wo-hua-yi-bian-jiu-kan-dong-de-ti-jie-ni-k2uj/

```c++
class Solution {
public:
    int lastRemaining(int n) {
        int head = 1; // 指向首部位置
        bool left = true; // 从左到右
        int step = 1; // 步进
        
        while (n > 1) {
            if (left || n % 2 == 1) {
                // 这两种情况需要调整 head
                head += step;
            }
            step <<= 1;
            left = !left;
            n >>= 1;
        }
        
        return head;
    }
};
```

