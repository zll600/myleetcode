# [825. Friends Of Appropriate Ages](https://leetcode.com/problems/friends-of-appropriate-ages/)

## 题目

There are `n` persons on a social media website. You are given an integer array `ages` where `ages[i]` is the age of the `ith` person.

A Person `x` will not send a friend request to a person `y` (`x != y`) if any of the following conditions is true:

- `age[y] <= 0.5 * age[x] + 7`
- `age[y] > age[x]`
- `age[y] > 100 && age[x] < 100`

Otherwise, `x` will send a friend request to `y`.

Note that if `x` sends a request to `y`, `y` will not necessarily send a request to `x`. Also, a person will not send a friend request to themself.

Return *the total number of friend requests made*.

 

**Example 1:**

```
Input: ages = [16,16]
Output: 2
Explanation: 2 people friend request each other.
```

**Example 2:**

```
Input: ages = [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
```

**Example 3:**

```
Input: ages = [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
```

 

**Constraints:**

- `n == ages.length`
- `1 <= n <= 2 * 104`
- `1 <= ages[i] <= 120`

## 题目大意

在社交媒体网站上有 `n` 个用户。给你一个整数数组 `ages` ，其中 `ages[i]` 是第 `i` 个用户的年龄。

如果下述任意一个条件为真，那么用户 `x` 将不会向用户 `y（x != y）` 发送好友请求：

- ages[y] <= 0.5 * ages[x] + 7
- ages[y] > ages[x]
- ages[y] > 100 && ages[x] < 100

否则，`x` 将会向 `y` 发送一条好友请求。注意，如果 `x` 向 `y` 发送一条好友请求，`y` 不必也向 `x` 发送一条好友请求。另外，用户不会向自己发送好友请求。

返回在该社交媒体网站上产生的好友请求总数

## 解题思路

这到题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0825.Friends-Of-Appropriate-Ages/)

### Solution 1: Bruce Force(TLE)

暴力解法，枚举所有的可能，然后累加结果即可

````c++
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        const int len = ages.size();

        // 加个缓存
        unordered_map<int, int> cache;
        int res = 0;
        for (int i = 0; i < len; ++i) {
            auto it = cache.find(ages[i]);
            if (it != cache.end()) {
                res += it->second;
            }

            int cnt = 0;
            for (int j = 0; j < len; ++j) {
                if (i == j) {
                    continue;
                }

                if (!NotSend(ages, i, j)) {
                    ++cnt;
                }
            }
            cache[ages[i]] = cnt;

            res += cnt;
        }
        return res;
    }

 private:
    bool NotSend(const vector<int>& ages, int x, int y) {
        return ages[y] <= ages[x] / 2 + 7
            || ages[y] > ages[x]
            || ages[y] > 100 && ages[x] < 100;
    }
};
````

### Solution 2: Sort + Two Pointers

将题目条件整理一下可以得到 `ages[x] / 2 + 7 < ages[y] <= ages[x]` 这个区间内是可以发送请求的，

所以我们主要对每个位置，维护这个区间就可以了，这里可以采用双指针的做法

````c++
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        const int len = ages.size();
        sort(ages.begin(), ages.end());

        // [left, right] 维护一个合法的区间
        int left = 0, right = 0;
        int res = 0;
        for (int i = 0; i < len; ++i) {
            if (ages[i] < 15) {
                continue;
            }

            // 左指针右移
            while (2 * ages[left] <= ages[i] + 14) {
                ++left;
            }
            // 右指针右移
            while (right + 1 < len && ages[right + 1] <= ages[i]) {
                ++right;
            }
            res += right - left;
        }
        return res;
    }

 private:
    bool Check(int x, int y) {
        return y <= x / 2 + 7
            || y > x
            || y > 100 && x < 100;
    }
};
````
