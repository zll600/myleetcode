# [275. H-Index II](https://leetcode.com/problems/h-index-ii/)

Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their `ith` paper and `citations` is sorted in an **ascending order**, return compute the researcher's `h`**-index**.

According to the [definition of h-index on Wikipedia](https://en.wikipedia.org/wiki/H-index): A scientist has an index `h` if `h` of their `n` papers have at least `h` citations each, and the other `n − h` papers have no more than `h` citations each.

If there are several possible values for `h`, the maximum one is taken as the `h`**-index**.

You must write an algorithm that runs in logarithmic time.

 

**Example 1:**

```
Input: citations = [0,1,3,5,6]
Output: 3
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had received 0, 1, 3, 5, 6 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
```

**Example 2:**

```
Input: citations = [1,2,100]
Output: 2
```

 

**Constraints:**

- `n == citations.length`
- `1 <= n <= 105`
- `0 <= citations[i] <= 1000`
- `citations` is sorted in **ascending order**.

## 题目大意

给定一位研究者论文被引用次数的数组（被引用次数是非负整数），数组已经按照升序排列。编写一个方法，计算出研究者的 h 指数。

h 指数的定义: “h 代表“高引用次数”（high citations），一名科研人员的 h 指数是指他（她）的 （N 篇论文中）至多有 h 篇论文分别被引用了至少 h 次。（其余的 N - h 篇论文每篇被引用次数不多于 h 次。）”

说明:

- 如果 h 有多有种可能的值 ，h 指数是其中最大的那个。

进阶：

- 这是 H 指数 的延伸题目，本题中的 citations 数组是保证有序的。 你可以优化你的算法到对数时间复杂度吗？

## 解题思路

这道题同 274题，这道题目多了有序的条件，同时数据量也更大了

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/h-index-ii/solution/gong-shui-san-xie-liang-chong-er-fen-ji-sovjb/

### 解法1

`````c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int left = 0;
        int right = citations.size();
        
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            
            if (Check(citations, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        return left;
    }
    
 private:
    bool Check(const vector<int>& citations, int mid) {
        int cnt = 0;
        for (int num : citations) {
            if (num >= mid) {
                ++cnt;
            }
        }
        
        return cnt >= mid;
    } 
};
`````

### 解法2

这里利用原数组的有序性，二分查找**第一个可以满足条件**的论文

这里的二分条件check 函数也利用了数组的有序性， mid 右边的所有论文都满足要求

`````c++、
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int size = citations.size();
        int left = 0;
        int right = size - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (citations[mid] >= size - mid) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return citations[right] >= size - right ? size - right : 0;
    }
};
`````

