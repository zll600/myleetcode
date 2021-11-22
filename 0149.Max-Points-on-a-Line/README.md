# [149. Max Points on a Line](https://leetcode-cn.com/problems/max-points-on-a-line/)

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane, return *the maximum number of points that lie on the same straight line*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/25/plane1.jpg)

```
Input: points = [[1,1],[2,2],[3,3]]
Output: 3
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/25/plane2.jpg)

```
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
```

 

**Constraints:**

- `1 <= points.length <= 300`
- `points[i].length == 2`
- `-104 <= xi, yi <= 104`

## 题目大意

给你一个数组 `points` ，其中 `points[i] = [xi, yi]` 表示 **X-Y** 平面上的一个点。求最多有多少个点在同一条直线上。

 ## 解题思路

这道题我采用的办法是，利用两点确定一条直线，算出该条直线的斜率，然后后面再用其他的点进行判断

这篇题解讲的很清楚：https://leetcode-cn.com/problems/max-points-on-a-line/solution/gong-shui-san-xie-liang-chong-mei-ju-zhi-u44s/ ，另外这篇题解的评论回答了很多问题，也值得好好看看，

### Solution 1:TLE

3 层循环枚举所有可能，不过会超时，另外这里使用乘法来代替除法，因为除法存在精度问题

````c++
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        const int len = points.size();
        if (len < 3) {
            return len;
        }
        
        int ans = 0;
        for (int i = 0; i < len; ++i) {
            vector<int> first = points[i];
            for (int j = i + 1; j < len; ++j) {
                vector<int> second = points[j];
                int cnt = 2;  // 两点确定一条直线
                for (int k = j + 1; k < len; ++i) {
                    vector<int> third = points[k];
                    int part1 = (second[1] - first[1]) * (third[0] - second[0]);
                    int part2 = (third[1] - second[1]) * (second[0] - first[0]);
                    if (part1 == part2) {
                        ++cnt;
                    }
                }
                
                ans = max(ans, cnt);
            }
        }
        
        return ans;
    }
};
````

### Solution 2:

````c++
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        const int len = points.size();
        if (len < 3) {
            return len;
        }
        
        int ans = 0;
        for (int i = 0; i < len; ++i) {
            unordered_map<string, int> cache;
            
            int max_val = 0; // 这里只需要最大值，所以用哈希表就可以
            for (int j = i + 1; j < len; ++j) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int a = x1 - x2, b = y1 - y2;
                int k = gcd(a, b); // 求得最大公约数，可以保证 key 的唯一性
                string key = to_string(a / k) + '_' + to_string(b / k); // 构造 key
                ++cache[key];
                max_val = max(max_val, cache.at(key));
            }
            
            ans = max(ans, max_val + 1); // max_val 中保存的是节点对，所以这里要 + 1
        }
        
        return ans;
    }
    
 private:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};
````

