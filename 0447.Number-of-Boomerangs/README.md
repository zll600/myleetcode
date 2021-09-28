# [447. Number of Boomerangs](https://leetcode.com/problems/number-of-boomerangs/)

You are given `n` `points` in the plane that are all **distinct**, where `points[i] = [xi, yi]`. A **boomerang** is a tuple of points `(i, j, k)` such that the distance between `i` and `j` equals the distance between `i` and `k` **(the order of the tuple matters)**.

Return *the number of boomerangs*.

 

**Example 1:**

```
Input: points = [[0,0],[1,0],[2,0]]
Output: 2
Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
```

**Example 2:**

```
Input: points = [[1,1],[2,2],[3,3]]
Output: 2
```

**Example 3:**

```
Input: points = [[1,1]]
Output: 0
```

 

**Constraints:**

- `n == points.length`
- `1 <= n <= 500`
- `points[i].length == 2`
- `-104 <= xi, yi <= 104`
- All the points are **unique**.

## 题目大意

给定平面上有 n 个互不相同的 points，其中 points[i] = [xi, yi]，一个回旋镖是一个由(i, j, k) 组成的三元组，其中 i 到 j 和 i 到k 的距离相等（与顺序相关）

返回回旋镖的数目

## 解题思路

这道题如果用暴力解法来做的话，需要三层循环，时间复杂度会比较高（不会算，以后一定要好好学），所以可以优化的地方就在于如何减少循环嵌套的层数。

### 解法1（利用哈希）

这道题目求的三元组，按照三数之和的做法，我们可以利用缓存来减少一层循环

`````c++
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); i++) {
            unordered_map<int, int> cache;  // 用距离作 key，用到当前位置距离为 key 的点的数目
            for (int j = 0; j < points.size(); j++) {
                if (i == j) {  // 跳过自己
                    continue;
                }
                
                cache[Calc(points[i], points[j])]++;
            }
            
            for (auto& it : cache) {  // 这里求一次距离相等的点的排列
                res += it.second * (it.second - 1);
            }
        }
        
        return res;
    }
    
 private:
    // 如果要开根，可能会带来误差，这里直接用平方和来做 key
    int Calc(const vector<int>& points_a, const vector<int>& points_b) {
        int x = points_a[0] - points_b[0];
        int y = points_a[1] - points_b[1];
        
        return x * x + y * y;
    }
};
`````

