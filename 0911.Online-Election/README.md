# [911. Online Election](https://leetcode.com/problems/online-election/)

## 题目

You are given two integer arrays `persons` and `times`. In an election, the `ith` vote was cast for `persons[i]` at time `times[i]`.

For each query at a time `t`, find the person that was leading the election at time `t`. Votes cast at time `t` will count towards our query. In the case of a tie, the most recent vote (among tied candidates) wins.

Implement the `TopVotedCandidate` class:

- `TopVotedCandidate(int[] persons, int[] times)` Initializes the object with the `persons` and `times` arrays.
- `int q(int t)` Returns the number of the person that was leading the election at time `t` according to the mentioned rules.

 

**Example 1:**

```
Input
["TopVotedCandidate", "q", "q", "q", "q", "q", "q"]
[[[0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]], [3], [12], [25], [15], [24], [8]]
Output
[null, 0, 1, 1, 0, 0, 1]

Explanation
TopVotedCandidate topVotedCandidate = new TopVotedCandidate([0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]);
topVotedCandidate.q(3); // return 0, At time 3, the votes are [0], and 0 is leading.
topVotedCandidate.q(12); // return 1, At time 12, the votes are [0,1,1], and 1 is leading.
topVotedCandidate.q(25); // return 1, At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
topVotedCandidate.q(15); // return 0
topVotedCandidate.q(24); // return 0
topVotedCandidate.q(8); // return 1
```

 

**Constraints:**

- `1 <= persons.length <= 5000`
- `times.length == persons.length`
- `0 <= persons[i] < persons.length`
- `0 <= times[i] <= 109`
- `times` is sorted in a strictly increasing order.
- `times[0] <= t <= 109`
- At most `104` calls will be made to `q`.

## 题目大意

在选举中，第 i 张票是在时间为 times[i] 时投给 persons[i] 的。

现在，我们想要实现下面的查询函数： TopVotedCandidate.q(int t) 将返回在 t 时刻主导选举的候选人的编号。

在 t 时刻投出的选票也将被计入我们的查询之中。在平局的情况下，最近获得投票的候选人将会获胜。

## 解题思路

这道题们我们要做的就是快读找到每次投票时间点为止的leader ，存放在数组 leaders 中，然后根据给定的时间，查找时间数组，然后再查找 leaders 数组

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0911.Online-Election/)

````c++
class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) : times_(times) {
        int leader = persons[0]; 
        const int len = persons.size();
        
        vector<int> votes(len, 0);
        for (int i = 0; i < len; ++i) {
            int cur = persons[i];
            votes[cur]++;
            if (votes[cur] >= votes[leader]) {
                leader = cur;
            }
            leaders_.push_back(leader);
        }
        
    }
    
    int q(int t) {
        auto pos = std::lower_bound(times_.begin(), times_.end(), t);
        // 大于最大的时间
        if (pos == times_.end()) {
            return leaders_.back();
        }
        
        int idx = pos - times_.begin();
        // 等于
        if (*pos == t) {
            return leaders_[idx]; 
        }
        
        // 小于
        return leaders_[idx - 1];
    }
    
 private:
    vector<int> leaders_;
    vector<int> times_;
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
````
