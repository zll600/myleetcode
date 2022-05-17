# [1353. Maximum Number of Events That Can Be Attended](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/)

## 题目

You are given an array of `events` where `events[i] = [startDayi, endDayi]`. Every event `i` starts at `startDayi` and ends at `endDayi`.

You can attend an event `i` at any day `d` where `startTimei <= d <= endTimei`. You can only attend one event at any time `d`.

Return *the maximum number of events you can attend*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/02/05/e1.png)

```
Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.
```

**Example 2:**

```
Input: events= [[1,2],[2,3],[3,4],[1,2]]
Output: 4
```

 

**Constraints:**

- `1 <= events.length <= 105`
- `events[i].length == 2`
- `1 <= startDayi <= endDayi <= 105`

## 题目大意

给你一个数组 `events`，其中 `events[i] = [startDayi, endDayi]` ，表示会议 `i` 开始于 `startDayi` ，结束于 `endDayi` 

你可以在满足 `startDayi <= d <= endDayi` 中的任意一天 `d` 参加会议 `i` 

注意，一天只能参加一个会议。请你返回你可以参加的 最大 会议数目。

## 解题思路

这道题目还是比较容易想到使用贪心的，

先排序，按照 startDay 进行排序，startDay 一样的按照 endDay 进行排序

但是这里还会出现问题，比如这组用例 `[[1,4],[4,4],[2,2],[3,4],[1,1]]`，这种情况会出现遗漏，解决方法即使判断相邻的两个，将 endDay 较晚的放在后面，有限 endDay 较早

### Solution 1:

这种解法可以参考 [这种解法](https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/solution/sao-miao-suan-fa-tan-xin-by-lucifer1004/)

可以这样想，对于每一个时间点，开始时间在此时，或者在此之前，结束时间在此时或者在此之后的会议都是可以参见的，所以对于开始时间相同的会议，优先选择结束时间较早的回忆参加

这种解法使用一个小根堆，来存储开始时间相同的会议，在每次判断是否哟能参加的会议时，必须先排除已经结束的会议，

为了能快速获得开始时间相同的会议，这里对输入数组做了预处理，

````c++
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        vector<vector<int>> meets(kMAX);
        // 将每个回忆做标号然后放入数组中
        for (int i = 0; i < events.size(); ++i) {
            meets[events[i][0]].emplace_back(i);
        }

        // 构建一个小根堆
        priority_queue<int, vector<int>, greater<int>> pq;
        int attend = 0;
        for (int i = 1; i < kMAX; i++) {
            // 将起始时间
            for (int id : meets[i]) {
                pq.push(events[id][1]);
            }

            // 弹出已经结束的会议
            while (!pq.empty() && pq.top() < i) {
                pq.pop();
            }

            // 如果未空，表示今天可以参加一场会议
            if (!pq.empty()) {
                pq.pop();
                ++attend;
            }
        }
        return attend;
    }

 private:
    const int kMAX = 100001;
};
````
