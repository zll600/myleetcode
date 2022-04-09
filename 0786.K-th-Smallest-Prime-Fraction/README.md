# [786. K-th Smallest Prime Fraction](https://leetcode.com/problems/k-th-smallest-prime-fraction/)

## 题目大意

You are given a sorted integer array `arr` containing `1` and **prime** numbers, where all the integers of `arr` are unique. You are also given an integer `k`.

For every `i` and `j` where `0 <= i < j < arr.length`, we consider the fraction `arr[i] / arr[j]`.

Return *the* `kth` *smallest fraction considered*. Return your answer as an array of integers of size `2`, where `answer[0] == arr[i]` and `answer[1] == arr[j]`.

 

**Example 1:**

```
Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.
```

**Example 2:**

```
Input: arr = [1,7], k = 1
Output: [1,7]
```

 

**Constraints:**

- `2 <= arr.length <= 1000`
- `1 <= arr[i] <= 3 * 104`
- `arr[0] == 1`
- `arr[i]` is a **prime** number for `i > 0`.
- All the numbers of `arr` are **unique** and sorted in **strictly increasing** order.
- `1 <= k <= arr.length * (arr.length - 1) / 2`

## 题目大意

给定一个已经排序的数组 `arr` 包含 `1` 和 素数 数字，`arr` 中的所有元素都是唯一的，给定一个整数 `k`，
对于每一个 `i` 和 `j`，其中 `0 <= i < j < arr.length`，我们构造一个分数 `arr[i] / arr[j]`
返回第 k 个最小分数，将答案按照一个大小为 2 的整数数组返回

## 解题思路

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0786.K-th-Smallest-Prime-Fraction/)

### Solution 1:


````c++
// 表示一个分数，也可以用一个 pair 来表示
struct Fraction {
    int molecule_;
    int denominator_;
    
    Fraction(int molecule, int denominator)
        : molecule_(molecule), denominator_(denominator) {}
};

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        const int len = arr.size();
        if (len == 0 || len * (len - 1) / 2 < k) {
            return {};
        }
        
        // 生成所有分数
        vector<Fraction> fractions;
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                fractions.push_back({arr[i], arr[j]});
            }
        }
        
        // 排序
        sort(fractions.begin(), fractions.end(), [](const Fraction& lhs, const Fraction& rhs) {
            return lhs.molecule_ * rhs.denominator_ < rhs.molecule_ * lhs.denominator_;
        });
        
        // 返回结果
        return {fractions[k - 1].molecule_, fractions[k - 1].denominator_};
    }
};
````

### Solution 2: BinarySearch

这里很巧妙的使用了真分数的特性，存在一个可以二分的区间 `[0, 1.0)`

然后这里因为浮点数的关系，所以不能使用边界条件来终止条件，所以在这里实际上使用了 cnt 来作为递归终止的条件

````c++
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        // 这里二分的范围是 [0.0, 1.0]
        double low = 0.0, high = 1.0;

        const int len = arr.size();
        while (true) {
            const double mid = (high + low) / 2;
            int p = 0, q = 1, j = 0;
            int cnt = 0;

            for (int i = 0; i < len; ++i) {
                // 统计大于 mid 的分数的个数
                while (j < len && 1.0 * arr[i] > mid * arr[j]) {
                    ++j;
                }
                // 统计小于 mid 的数的数目
                cnt += len - j;

                // 动态维护一个最大的分子值和分母值
                if (j < len && q * arr[i] > p * arr[j]) {
                    p = arr[i];
                    q = arr[j];
                }
            }

            if (cnt == k) {
                // 这里就是终止二分的条件
                return {p, q};
            } else if (cnt < k) {
                low = mid;
            } else {
                high = mid;
            }
        }

        return {};
    }
};
````
