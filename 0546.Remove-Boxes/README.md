# [546. Remove Boxes](https://leetcode-cn.com/problems/remove-boxes/)

## 题目

You are given several `boxes` with different colors represented by different positive numbers.

You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of `k` boxes, `k >= 1`), remove them and get `k * k` points.

Return *the maximum points you can get*.

**Example 1:**

```
Input: boxes = [1,3,2,2,2,3,4,3,1]
Output: 23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
```

**Example 2:**

```
Input: boxes = [1,1,1]
Output: 9
```

**Example 3:**

```
Input: boxes = [1]
Output: 1
```

 

**Constraints:**

- `1 <= boxes.length <= 100`
- `1 <= boxes[i] <= 100`

## 题目大意

给定一些用不同正整数表示的盒子，你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k * k 个积分。

返回你能得到的最大分数，

## 解题思路

这是一道区间 dp 的问题

这道题的存在**最优子结构**，该问题的最优解包含其子问题的最优解，

重叠子问题：题目是在求解大量重复的子问题

这道题目的难点在于如何做好状态转移，

这里我们每次操作都可以把原数组分为三部分，`[0, i - 1]` 是要删除部分的前面，`[i, j]` 是要删除的连续字符，`[j + 1, len - 1]` 是要删除部分的后面部分

### Solution 1: DFS



```c++
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        return RemoveBoxes(boxes, 0);
    }
    
 private:
    int RemoveBoxes(const vector<int>& boxes, int cur_sum) {
        const int len = boxes.size();
        int res = 0;
        if (len == 0) {
            return cur_sum;
        } else if (len == 1) {
            return cur_sum + 1 * 1;
        }
        
        // 循环不变量：
        // [0, i) 表示删除的前面
        // (j, len - 1] 表示删除的后面
        // [i, j] 表示要删除的部分
        int i = 0;
        while (i < len) {
            int cnt = 1;
            int j = i;
            while (j < len - 1 && boxes[j] == boxes[j + 1]) {
                ++cnt;
                ++j;
            }
            
            // 调整数组
            vector<int> left(boxes.begin(), boxes.begin() + i);
            vector<int> right(boxes.begin() + j + 1, boxes.end());
            left.insert(left.end(), right.begin(), right.end());
            // 递归
            int cur = RemoveBoxes(left, cur_sum + cnt * cnt);
            res = max(res, cur);
            i = j + 1;
        }
        
        return res;
    }
};
```

### Solution 2: 记忆化递归

这种解法依旧会超时

```c++
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        const int len = boxes.size();
        // 状态定义：移除 [left, right] 和 区间前面和 boxes[left] 一样的cnt 个数
        vector<vector<vector<int>>> memo(len, vector<vector<int>>(len, vector<int>(len, 0)));
        
        return RemoveBoxes(boxes, 0, len - 1, 0, memo);
    }
    
 private:
    int RemoveBoxes(const vector<int>& boxes, int left, int right, int cnt,
              vector<vector<vector<int>>>& memo) {
        if (left > right) {
            return 0;
        }
        if (memo[left][right][cnt] != 0) {
            return memo[left][right][cnt];
        }
        
        // 找出连续的数字，有 cnt + 1 个
        while (left < right && boxes[left] == boxes[left + 1]) {
            ++left;
            ++cnt;
        }
        
        // 直接移除连续的部分
        int scores = (cnt + 1) * (cnt + 1) + RemoveBoxes(boxes, left + 1, right, 0, memo);
        // 移除中间的部分
        for (int i = left + 1; i <= right; ++i) {
            if (boxes[i] == boxes[left]) {
                scores = max(scores,
                             RemoveBoxes(boxes, left + 1, i - 1, 0, memo)
                             + RemoveBoxes(boxes, i, right, cnt + 1, memo));
            }
        }
        memo[left][right][cnt] = scores;
        return scores;
    }
};
```

### Solution 3: dp

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/remove-boxes/solution/fei-di-gui-ban-qu-jian-dp-by-acw_weian/

状态定义：`dp[i][j][k]` 表示从`[i, j]`中移除颜色相同的盒子， `j`右边有`k`个和`boxes[j]`颜色相同的盒子

状态转移：

````java
class Solution {
    int[][][] dp = new int[105][105][105];
    public int removeBoxes(int[] a) {
        int n = a.length;
        for(int len = 1; len <= n; len++){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len - 1;
                for(int k = 0; k < n; k++){
                    dp[i][j][k] = Math.max(dp[i][j][k], (j - 1 < i ? 0: dp[i][j - 1][0]) + (k + 1) * (k + 1));
                    for(int t = i; t <= j - 1; t++){
                        if(a[t] == a[j]){
                            dp[i][j][k] = Math.max(dp[i][j][k], (t + 1 > j - 1 ? 0: dp[t + 1][j - 1][0]) +
                             dp[i][t][k + 1]);
                        }
                    }
                }
            }
        }
        return dp[0][n - 1][0];
    }
}
````

