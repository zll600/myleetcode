# [823. Binary Trees With Factors](https://leetcode.com/problems/binary-trees-with-factors/)

## 题目

Given an array of unique integers, `arr`, where each integer `arr[i]` is strictly greater than `1`.

We make a binary tree using these integers, and each number may be  used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.

Return *the number of binary trees we can make*. The answer may be too large so return the answer **modulo** `109 + 7`.

 

**Example 1:**

```
Input: arr = [2,4]
Output: 3
Explanation: We can make these trees: [2], [4], [4, 2, 2]
```

**Example 2:**

```
Input: arr = [2,4,5,10]
Output: 7
Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
```

 

**Constraints:**

- `1 <= arr.length <= 1000`
- `2 <= arr[i] <= 109`
- All the values of `arr` are **unique**.

## 题目大意

给定一个含有不重复数字的数组，数组中的元素都严格大于 1，

我们用这些整数狗在一棵二叉树，其中每个数字可以使用任意次，每个非叶子节点的值都是其孩子节点的值的乘积，返回我们可以构造的二叉树，结果可能很大

## 解题思路


### Solution 1: DFS

先将数组排序，然后列出所有所有可能形成的 乘积对，用 map 做缓存，方便查找


````c++
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        // 先排序
        sort(arr.begin(), arr.end());
        // 存入一个集合中，方便查找
        unordered_set<int> arr_set(arr.begin(), arr.end());

        const int len = arr.size();
        unordered_map<int, vector<pair<int, int>>> dict;
        for (int i = 0; i < len; ++i) {
            // 这里起点从 i 开始，每个数最多使用两次
            for (int j = i; j < len && 1LL * arr[i] * arr[j] <= arr.back(); ++j) {
                // 构造一个 key
                int key = arr[i] * arr[j];
                // 如果不存在，跳过
                if (arr_set.find(key) == arr_set.end()) {
                    continue;
                }

                dict[key].push_back({arr[i], arr[j]});
            }
        }

        int ans = 0;
        for (int num : arr_set) {
            ans = (ans + DFS(num, dict)) % mod_;
        }
        return ans;
    }

 private:
    const int mod_ = 1e9 + 7;

    int DFS(int key, const unordered_map<int, vector<pair<int, int>>>& dict) {

        // 初始化为 1，这颗树只有一个根节点的情况
        int res = 1;
        if (dict.find(key) != dict.end()) {
            for (const pair<int,int>& item : dict.at(key)) {
                int x = DFS(item.first, dict);
                int y = DFS(item.second, dict);

                long long tmp = 1LL * x * y;
                // 这里注意，如果左右孩子不相等，则交换之后可以形成新树
                if (item.first != item.second) {
                    tmp *= 2;
                }
                res = (res + tmp) % mod_;
            }
        }
        return res;
    }
};
````
