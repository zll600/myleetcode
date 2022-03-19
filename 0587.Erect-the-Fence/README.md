#### [587. Erect the Fence](https://leetcode-cn.com/problems/erect-the-fence/)

## 题目

You are given an array `trees` where `trees[i] = [xi, yi]` represents the location of a tree in the garden.

You are asked to fence the entire garden using the minimum length of rope as it is expensive. The garden is well fenced only if **all the trees are enclosed**.

Return *the coordinates of trees that are exactly located on the fence perimeter*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/24/erect2-plane.jpg)

```
Input: points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[3,3],[2,4],[4,2]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/24/erect1-plane.jpg)

```
Input: points = [[1,2],[2,2],[4,2]]
Output: [[4,2],[2,2],[1,2]]
```

 

**Constraints:**

- `1 <= points.length <= 3000`
- `points[i].length == 2`
- `0 <= xi, yi <= 100`
- All the given points are **unique**.

## 题目大意

给定一个数组 `trees`，其中 `trees[i] = [xi, yi]` 表示树在花园中的位置

由于安装费用十分昂贵，你的任务是先用最短的绳子围起所有的树。只有当所有的树都被绳子包围时，花园才能围好栅栏。

你需要找到正好位于栅栏边界上的树的坐标。

## 解题思路

这道题目真的很难，是一道计算几何的问题，可以参考这几篇题解

- https://leetcode-cn.com/problems/erect-the-fence/solution/mo-ao-tu-bao-suan-fa-by-moao-24t5/
- https://leetcode-cn.com/problems/erect-the-fence/solution/cpp-grahamqiu-tu-bao-gua-he-xiao-bai-by-zen-june/
- https://leetcode-cn.com/problems/erect-the-fence/solution/xiang-xi-ti-jie-by-fly-f/


### Solution 1:


````c++
class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        auto cross=[](vector<int>&a,vector<int>&b,vector<int>&c){
            return (b[0]-a[0])*(c[1]-b[1])-(b[1]-a[1])*(c[0]-b[0]);
        };
        int n=trees.size();
        if(n<3)return trees;
        sort(begin(trees),end(trees),[](auto&a,auto&b){
            return make_pair(a[0],a[1])<make_pair(b[0],b[1]);
        });
        vector<vector<int>>low;
        for(auto&p:trees){
            while(low.size()>1 && cross(low[low.size()-1],low[low.size()-2],p)<0)low.pop_back();
            low.push_back(p);
        }
        reverse(begin(trees),end(trees));
        vector<vector<int>>top;
        for(auto&p:trees){
            while(top.size()>1 && cross(top[top.size()-1],top[top.size()-2],p)<0)top.pop_back();
            top.push_back(p);
        }
        set<pair<int,int>>s;
        for(auto&p:low)s.insert(make_pair(p[0],p[1]));
        for(auto&p:top)s.insert(make_pair(p[0],p[1]));
        vector<vector<int>>ans;
        for(auto[x,y]:s)ans.push_back({x,y});
        return ans;
    }
};


````
