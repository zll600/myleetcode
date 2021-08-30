# [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)

## 题目

Given an integer array `bloomDay`, an integer `m` and an integer `k`.

We need to make `m` bouquets. To make a bouquet, you need to use `k` **adjacent flowers** from the garden.

The garden consists of `n` flowers, the `ith` flower will bloom in the `bloomDay[i]` and then can be used in **exactly one** bouquet.

Return *the minimum number of days* you need to wait to be able to make `m` bouquets from the garden. If it is impossible to make `m` bouquets return **-1**.

 

**Example 1:**

```
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let's see what happened in the first three days. x means flower bloomed and _ means flower didn't bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
```

**Example 2:**

```
Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.
```

**Example 3:**

```
Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here's the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
```

**Example 4:**

```
Input: bloomDay = [1000000000,1000000000], m = 1, k = 1
Output: 1000000000
Explanation: You need to wait 1000000000 days to have a flower ready for a bouquet.
```

**Example 5:**

```
Input: bloomDay = [1,10,2,9,3,8,4,7,5,6], m = 4, k = 2
Output: 9
```

 

**Constraints:**

- `bloomDay.length == n`
- `1 <= n <= 10^5`
- `1 <= bloomDay[i] <= 10^9`
- `1 <= m <= 10^6`
- `1 <= k <= n`

## 题目大意

整数数组 bloomDay 的第 i th 个元素表示这朵花第几天才能开花，整数 m 表示要多少束花，整数 k 表示没束花有多少个，

制作一束花，要必须从花园里取连续的 k 朵。花园中有 n 朵花，请你返回从花园中制作 m 束花需要的最少的天数。如果不能制作 m 束花，返回 -1；

## 解题思路

* 这道题目可以用 “二分搜索”来解决，二分搜索的区间为[0, max_day]（这里我认为还可以再缩小，不过因为二分本身的效率比较高，所以也可以不用缩小），找到满足条件的最少的天数，也就是第一个可以满足 m 束花的解。Check函数判断为 true 的条件是：从左向右便利数组，如果当前的花可以在当前天数开放，则计入，满足有连续的 k 朵开放的花，则可以递增 花的束数，如果可以制作 m 束花，则返回true，

## 代码

`````c++
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int size = bloomDay.size();
        if (m > size / k) {
            return -1;
        }
        /*
        int lo = 0;
        int hi = 0;
        for (int i : bloomDay) {
            if (i > hi) {
                hi = i;
            }
        }*/
        
        int lo = INT_MAX;
        int hi = INT_MIN;
        for (int i : bloomDay) {
            if (i > hi) {
                hi = i;
            }
            if (i < lo) {
                lo = i;
            }
        }
        
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (Check(bloomDay, mid, m, k)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }
    
 private:
    /*
    static bool Check(vector<int>& bloomDay, int days, int m, int k) {
        int flowers = 0;
        int bouquets = 0;
        
        for (int d : bloomDay) {
            if (d > days) { // 不连续
                flowers = 0;
            } else {
                ++flowers;
                if (flowers == k) { // 可以制作一束花，
                    ++bouquets;
                    flowers = 0;
                }
            }
        }
        
        return bouquets >= m;
    }*/
    
    static bool Check(vector<int>& bloomDay, int days, int m, int k) {
        int flowers = 0;
        int bouquets = 0;
        
        for (int d : bloomDay) {
            if (d > days) {
                flowers = 0;
            } else {
                if (++flowers == k) {
                    if (++bouquets >= m) {
                        return true;
                    }
                    flowers = 0;
                }
            }
        }
        
        return false;
    }
};
`````

