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


### Solution 1: Bruce Force(TLE)


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
