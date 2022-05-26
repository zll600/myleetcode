# [1705. Maximum Number of Eaten Apples](https://leetcode.com/problems/maximum-number-of-eaten-apples/)

## 题目

There is a special kind of apple tree that grows apples every day for `n` days. On the `ith` day, the tree grows `apples[i]` apples that will rot after `days[i]` days, that is on day `i + days[i]` the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by `apples[i] == 0` and `days[i] == 0`.

You decided to eat **at most** one apple a day (to keep the doctors away). Note that you can keep eating after the first `n` days.

Given two integer arrays `days` and `apples` of length `n`, return *the maximum number of apples you can eat.*

 

**Example 1:**

```
Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7
Explanation: You can eat 7 apples:
- On the first day, you eat an apple that grew on the first day.
- On the second day, you eat an apple that grew on the second day.
- On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
- On the fourth to the seventh days, you eat apples that grew on the fourth day.
```

**Example 2:**

```
Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
Output: 5
Explanation: You can eat 5 apples:
- On the first to the third day you eat apples that grew on the first day.
- Do nothing on the fouth and fifth days.
- On the sixth and seventh days you eat apples that grew on the sixth day.
```

 

**Constraints:**

- `n == apples.length == days.length`
- `1 <= n <= 2 * 104`
- `0 <= apples[i], days[i] <= 2 * 104`
- `days[i] = 0` if and only if `apples[i] = 0`.

## 题目大意

有一棵特殊的苹果树，一连 `n` 天，每天都可以长出若干个苹果。在第 `i` 天，树上会长出 `apples[i]` 个苹果

这些苹果将会在  `days[i]` 天后（也就是说，第 `i + days[i]` 天时）腐烂，变得无法食用

也可能有那么几天，树上不会长出新的苹果，此时用  apples[i] == 0 且 days[i] == 0 表示

你打算每天 最多 吃一个苹果来保证营养均衡。注意，你可以在这 n 天之后继续吃苹果

给你两个长度为 n 的整数数组 days 和 apples ，返回你可以吃掉的苹果的最大数目

## 解题思路

这道题目和之前做过的一道，可以参加的最大会议数思路很想，

这里我们贪心的选择 最快腐烂的 苹果，既可以迟到最多的苹果

具体的做法就是维护一个小顶堆，每天选择最快过期的苹果消耗，就可以迟到最多的苹果

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1700~1799/1705.Maximum-Number-of-Eaten-Apples/)

具体的证明可以参考 [这篇题解](https://leetcode.cn/problems/maximum-number-of-eaten-apples/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-hfdy0/)

`````c++
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        // 这里使用一个小顶堆
        auto cmp = [](const auto& lhs, const auto& rhs) {
            return lhs.first > rhs.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        int ans = 0;
        int i = 0;
        for (; i < apples.size(); ++i) {
            // 先排除过期的苹果
            while (!pq.empty() && pq.top().first <= i) {
                pq.pop();
            }

            // 有产出才加入到结果集中
            if (apples[i] > 0) {
                pq.push({days[i] + i, apples[i]});
            }
            // 吃苹果
            if (!pq.empty()) {
                auto [expire, cnt] = pq.top();
                pq.pop();

                ++ans;
                if (cnt > 1) {
                    pq.push({expire, cnt - 1});
                }
            }
        }

        // 这里计算只消耗不产生苹果，可以吃到的最多
        while (!pq.empty()) {
            while (!pq.empty() && pq.top().first <= i) {
                pq.pop();
            }

            if (pq.empty()) {
                break;
            }

            auto [expire, cnt] = pq.top();
            pq.pop();
            int num = min(expire - i, cnt);
            ans += num;
            i += num;
        }
        return ans;
    }
};
````
