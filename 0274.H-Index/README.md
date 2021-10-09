

# [274. H-Index](https://leetcode.com/problems/h-index/)

## 题目

Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their `ith` paper, return compute the researcher's `h`**-index**.

According to the [definition of h-index on Wikipedia](https://en.wikipedia.org/wiki/H-index): A scientist has an index `h` if `h` of their `n` papers have at least `h` citations each, and the other `n − h` papers have no more than `h` citations each.

If there are several possible values for `h`, the maximum one is taken as the `h`**-index**.

 

**Example 1:**

```
Input: citations = [3,0,6,1,5]
Output: 3
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
```

**Example 2:**

```
Input: citations = [1,3,1]
Output: 1
```

 

**Constraints:**

- `n == citations.length`
- `1 <= n <= 5000`
- `0 <= citations[i] <= 1000`

## 题目大意

给定一个整数数组 citations 其中 citations[i] 表示该研究者的第 i 篇论文被引用的次数，计算研究者的 h指数

一个科学家的 h 指数是他的 n 篇论文中有 h 篇被引用了至少 h 次，其他 n - h 篇没有被引用 h 次

如果有很多可能的值，返回其中最大的一个

##  解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/h-index/solution/er-fen-cai-lun-wen-pian-shu-java-by-liwe-zoh7/

这道题目的就是找 h 篇被引用了至少 h 次的论文，

### 解法1（二分查找）

这里用二分查找来确定论文引用的次数，这个次数的范围在[0, len] 之间，我们需要找到的满足条件中的最大的一个，



````c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // 这里 h 的取值范围就是 [0, citations.size()]
        int left = 0;
        int right = citations.size();
        
        while (left < right) {
            // int mid = (left + right + 1) / 2;
            int mid = left + (right - left + 1) / 2;  // 这里这样写更好，可以避免溢出， + 1是为了避免死循环
            
            int cnt = 0;
            for (int it : citations) {  // 统计出现次数大于等于 mid 的论文的书目
                if (it >= mid) {
                    ++cnt;
                }
            }
            
            if (cnt >= mid) { // 此时的mid 只是可能满足，我们要找到的的满足条件的最后一个，也就是最大的
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        return left;
    }
};
````

### 解法2（桶计数）

这种解法，使用桶来做计数，因为被引用次数多的论文总是会被计入

`````c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int size = citations.size();
        vector<int> buckets(size + 1);  // 用桶来计数，因为最终结果的次数一定在 [0, size]之间，决定桶的数目
        for (int num : citations) {
            if (num >= size) {  // 被引用次数大于等于 size的都放在 size 中，
                ++buckets[size];
            } else {
                ++buckets[num];
            }
        }
        
        int cnt = 0;
        for (int i = size; i >= 0; --i) {  // 找到第一个满足的答案
            cnt += buckets[i];
            if (cnt >= i) {
                return i;
            }
        }
        
        return 0;
    }
};
`````

### 解法3（排序）

排序后，后面的论文总是满足要求的，只需要不断增大引用次数即可，直到遇到 第一个引用次数小于要求的论文，这个过程中，不断增大需要引用的次数，而文章的引用次数却越来越低，这样总会终止，此时，返回满足要求的文章的数量就是答案

`````c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());  // 按引用次数从小到大排序
        
        int size = citations.size();
        int res = 0;
        for (int i = size - 1; i >= 0; --i) {
            if (citations[i] >= size - i) {  // 如果当前的引用次数大于等于最小被引用的次数，即满足条件
                ++res;
            } else {
                break;
            }
        }
        
        return res;
    }
};
`````

