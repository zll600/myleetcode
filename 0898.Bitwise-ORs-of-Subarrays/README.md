# [898. Bitwise ORs of Subarrays](https://leetcode.com/problems/bitwise-ors-of-subarrays/)

## 题目

We have an array `arr` of non-negative integers.

For every (contiguous) subarray `sub = [arr[i], arr[i + 1], ..., arr[j]]` (with `i <= j`), we take the bitwise OR of all the elements in `sub`, obtaining a result `arr[i] | arr[i + 1] | ... | arr[j]`.

Return the number of possible results. Results that occur more than once are only counted once in the final answer

 

**Example 1:**

```
Input: arr = [0]
Output: 1
Explanation: There is only one possible result: 0.
```

**Example 2:**

```
Input: arr = [1,1,2]
Output: 3
Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.
```

**Example 3:**

```
Input: arr = [1,2,4]
Output: 6
Explanation: The possible results are 1, 2, 3, 4, 6, and 7.
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `0 <= nums[i] <= 109`

##  题目大意

我们有一个非负整数数组 `arr`。对于每个（连续的）子数组 `sub = [arr[i], arr[i+1], …, arr[j]] （ i <= j）` ，我们对 `sub` 中的每个元素进行按位或操作，获得结果 arr[i] | arr[i+1] | … | arr[j]。

返回可能结果的数量。（多次出现的结果在最终答案中仅计算一次。）

## 解题思路



### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0898.Bitwise-ORs-of-Subarrays/)

每次遍历到一个新的数的时候，我们要做两件事

- 其自身可以形成一个子数组
- 其可以接在已经存在子数组后面

````c++
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> res;
        unordered_set<int> cache;

        for (int num : arr) {
            unordered_set<int> tmp;
            // 将自己加入到此次遍历的集合中
            tmp.insert(num);

            // 与上一次遍历产生的集合的所有值做 或 运算
            for (int n : cache) {
                tmp.insert(n | num);
            }

            // 做交换
            cache.swap(tmp);
            // 将此次遍历的结果加入到结果集合中
            for (int n : cache) {
                res.insert(n);
            }
        }

        return res.size();
    }
};
````
