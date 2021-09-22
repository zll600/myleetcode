# [455. Assign Cookies](https://leetcode.com/problems/assign-cookies/)

## 题目

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child `i` has a greed factor `g[i]`, which is the minimum size of a cookie that the child will be content with; and each cookie `j` has a size `s[j]`. If `s[j] >= g[i]`, we can assign the cookie `j` to the child `i`, and the child `i` will be content. Your goal is to maximize the number of your content children and output the maximum number.

 

**Example 1:**

```
Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
```

**Example 2:**

```
Input: g = [1,2], s = [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.
```

 

**Constraints:**

- `1 <= g.length <= 3 * 104`
- `0 <= s.length <= 3 * 104`
- `1 <= g[i], s[j] <= 231 - 1`

## 题目大意

假设你是一个很棒的家长，你想要给你的孩子们一些饼干，但是你最多只能给每个孩子一块饼干

每个孩子都有一个胃口 g[i]，表示可以让这个孩子满足的最小大小的饼干，每个饼干都有一个大小 s[j]，如果 s[j] >= g[i]，我们可以将饼干 j 分给孩子 i，孩子 i 就可以得到满足，你的目标时尽可能让更多的孩子满足 

## 解题思路

这是一道很有名的贪心算法的题目，这道题的特点在于大的饼干可以满足胃口大的和胃口小的孩子，但是小的饼干只能满足胃口小的孩子，所以为了让更多的孩子满足，就要尽力让更多的饼干可以用的上，需要尽量把大的饼干分给胃口大的孩子

## 代码

````c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 将两个数组从大到小排序，
        sort(g.begin(), g.end(), cmp);
        sort(s.begin(), s.end(), cmp);
        
        int res = 0;
        int idx = 0;
        for (int i = 0; i < g.size(); ++i) {    // 注意这里必须是遍历胃口值，因为最大的饼干不能满足最大的胃口
            if (idx < s.size() && s[idx] >= g[i]) {
                ++idx;
                ++res;
            }
        }
        
        
        return res;
    }

 private:
    // 如果这个函数要多次使用，还是不要用 lamda 表达式了
    static bool cmp(int a, int b) {
        return a > b;
    }
    
};
````

