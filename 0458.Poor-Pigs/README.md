# [458. Poor Pigs](https://leetcode-cn.com/problems/poor-pigs/)

## 题目

There are `buckets` buckets of liquid, where **exactly one** of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have `minutesToTest` minutes to determine which bucket is poisonous.

You can feed the pigs according to these steps:

1. Choose some live pigs to feed.
2. For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets simultaneously and will take no time.
3. Wait for `minutesToDie` minutes. You may **not** feed any other pigs during this time.
4. After `minutesToDie` minutes have passed, any pigs that have been fed the poisonous bucket will die, and all others will survive.
5. Repeat this process until you run out of time.

Given `buckets`, `minutesToDie`, and `minutesToTest`, return *the **minimum** number of pigs needed to figure out which bucket is poisonous within the allotted time*.

 

**Example 1:**

```
Input: buckets = 1000, minutesToDie = 15, minutesToTest = 60
Output: 5
```

**Example 2:**

```
Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
Output: 2
```

**Example 3:**

```
Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
Output: 2
```

 

**Constraints:**

- `1 <= buckets <= 1000`
- `1 <= minutesToDie <= minutesToTest <= 100`

## 题目大意

这里有 buckets 桶饮料，其中只有一桶是有毒的，它们从外观看起来都一样。为了弄清楚哪只水桶含有毒药，你可以喂一些猪喝，通过观察猪是否会死进行判断。不幸的是，你只有 minutesToTest 分钟时间来确定哪桶液体是有毒的

你可以按照一下规则来喂猪
1. 选择一头活着的猪来喂，
2. 可以允许小猪同时饮用任意数量的桶中的水，并且该过程不需要时间。
3. 等待 minutesToDie，期间你不能喂猪，
4. 过了 minutesToDie 分钟后，所有喝到毒药的猪都会死去，其他所有猪都会活下来。
5. 重复这一过程，直到时间用完。

给你桶的数目 buckets ，minutesToDie 和 minutesToTest ，返回 在规定时间内判断哪个桶有毒所需的 最小 猪数 。

## 解题思路

这道题目中，每桶水只有有毒和无毒两种状态，每只猪在喝完水之后，也只有 活着或死亡两种状态，这里需要的 n 只猪每轮可以表示 minutesToTest / minutesToDie + 1 种状态，可以表示的状态需要大于 buckets ，

这道题目可以参考霜神的 [题解](https://leetcode.com/problems/poor-pigs/submissions/) ，以及这篇 [题解](https://leetcode-cn.com/problems/poor-pigs/solution/tong-ge-lai-shua-ti-la-k-jin-zhi-wen-ti-ha2ze/)

### Solution 1:



````c++
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int base = minutesToTest / minutesToDie + 1;
        return ceil(log10(buckets) / log10(base));
    }
};

````
