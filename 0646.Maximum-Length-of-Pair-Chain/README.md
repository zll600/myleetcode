# [646. Maximum Length of Pair Chain](https://leetcode-cn.com/problems/maximum-length-of-pair-chain/)

You are given an array of `n` pairs `pairs` where `pairs[i] = [lefti, righti]` and `lefti < righti`.

A pair `p2 = [c, d]` **follows** a pair `p1 = [a, b]` if `b < c`. A **chain** of pairs can be formed in this fashion.

Return *the length longest chain which can be formed*.

You do not need to use up all the given intervals. You can select pairs in any order.

 

**Example 1:**

```
Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].
```

**Example 2:**

```
Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
```

 

**Constraints:**

- `n == pairs.length`
- `1 <= n <= 1000`
- `-1000 <= lefti < righti <= 1000`

## 题目大意

出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。

现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。

给定一个数对集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。

## 解题思路


### Solution 1:

这里先放上一个错误的解法

按照 上限和下限的 升序进行排序，但是一下用例是过不了的: `[[-6,9],[1,6],[8,10],[-1,4],[-6,-2],[-9,8],[-5,3],[0,3]]`

````c++
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[0] != rhs[0] ? lhs[0] < rhs[0] : lhs[1] < rhs[1];
        });
        
        int res = 1;
        const int len = pairs.size();
        int bound = pairs[0][1];
        for (int i = 1; i < len; ++i) {
            cout << bound << " --- " << pairs[i][0] << endl;
            if (pairs[i][0] > bound) {
                ++res;
                bound = pairs[i][1];
            }
        }
        
        return res;
    }
};

### Solution 2: 

这里其实只需要关注 上界即可，就可以结局上一种解法中存在的问题了,

````c++
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            // 因为每一对其实内部都是升序的，所以这里排序我们只需要关注 上界 即可
            return lhs[1] < rhs[1];
        });

        int res = 1;
        const int len = pairs.size();
        int bound = pairs[0][1];
        for (int i = 1; i < len; ++i) {
            // cout << bound << " --- " << pairs[i][0] << endl;
            if (pairs[i][0] > bound) {
                ++res;
                bound = pairs[i][1];
            }
        }

        return res;
    }
};
````
