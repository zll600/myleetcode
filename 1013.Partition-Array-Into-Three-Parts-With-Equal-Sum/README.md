#### [1013. Partition Array Into Three Parts With Equal Sum](https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/)

## 题目

Given an array of integers `arr`, return `true` if we can partition the array into three **non-empty** parts with equal sums.

Formally, we can partition the array if we can find indexes `i + 1 < j` with `(arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1]  == arr[j] + arr[j + 1] + ... + arr[arr.length - 1])`

 

**Example 1:**

```
Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
```

**Example 2:**

```
Input: arr = [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false
```

**Example 3:**

```
Input: arr = [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
```

 

**Constraints:**

- `3 <= arr.length <= 5 * 104`
- `-104 <= arr[i] <= 104`

## 题目大意

给定一个整数数组 `arr`，如果可以将这个数组划分为 *3个非空且总和相等* 的部分，返回 `True`

形式上，如果可以找出索引 `i + 1 < j` 且满足 `(arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length - 1])` 就可以将数组三等分

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/solution/java-shi-yong-shuang-zhi-zhen-by-sugar-31/)

### Solution 1: 找下标

这个解法不好理解的地方在  `res >= 3`，这里当时是因为 `[0, 0, 0, 0]` 这个case 没过，但这里肯定与 `sum ` 无关，所以只能考虑 `res`，

如果总和可以被 `3` 整除，那么如果可以划分出来的组大于 `3`，那么每组的和只能为 `0`，个人认为这里可以回比较男理解

````c++
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        // 先求和
        int sum = accumulate(arr.begin(), arr.end(), 0);
        // 如果不能被 3 整除直接返回 false
        if (sum % 3 != 0) {
            return false;
        }
        // 每个部分的和
        int target = sum / 3;

        // 可以划分的下标个数
        int res = 0;
        const int len = arr.size();
        int tmp = 0;
        for (int i = 0; i < len; ++i) {
            tmp += arr[i];
            if (tmp == target) {
                ++res;
                tmp = 0;
            }
        }

        // 注意这里是 >= ，否则不能解决 [0, 0, 0, 0] 等情况
        return res >= 3;
    }
};
````
