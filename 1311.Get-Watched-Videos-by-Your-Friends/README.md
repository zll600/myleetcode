#### [1311. Get Watched Videos by Your Friends](https://leetcode.cn/problems/get-watched-videos-by-your-friends/)

There are `n` people, each person has a unique *id* between `0` and `n-1`. Given the arrays `watchedVideos` and `friends`, where `watchedVideos[i]` and `friends[i]` contain the list of watched videos and the list of friends respectively for the person with `id = i`.

Level **1** of videos are all watched videos by your friends, level **2** of videos are all watched videos by the friends of your friends and so on. In general, the level `k` of videos are all watched videos by people with the shortest path **exactly** equal to `k` with you. Given your `id` and the `level` of videos, return the list of videos ordered by their frequencies  (increasing). For videos with the same frequency order them  alphabetically from least to greatest. 

 

**Example 1:**

**![img](https://assets.leetcode.com/uploads/2020/01/02/leetcode_friends_1.png)**

```
Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"] 
Explanation: 
You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
Person with id = 1 -> watchedVideos = ["C"] 
Person with id = 2 -> watchedVideos = ["B","C"] 
The frequencies of watchedVideos by your friends are: 
B -> 1 
C -> 2
```

**Example 2:**

**![img](https://assets.leetcode.com/uploads/2020/01/02/leetcode_friends_2.png)**

```
Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation: 
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
```

 

**Constraints:**

- `n == watchedVideos.length == friends.length`
- `2 <= n <= 100`
- `1 <= watchedVideos[i].length <= 100`
- `1 <= watchedVideos[i][j].length <= 8`
- `0 <= friends[i].length < n`
- `0 <= friends[i][j] < n`
- `0 <= id < n`
- `1 <= level < n`
- if `friends[i]` contains `j`, then `friends[j]` contains `i`

## 题目大意

有 `n` 个人，每个人都有一个  `0` 到 `n-1` 的唯一 id 

给你数组 `watchedVideos`  和 `friends` ，其中 `watchedVideos[i]`  和 `friends[i]` 分别表示 `id = i` 的人观看过的视频列表和他的好友列表。

`Level 1` 的视频包含所有你好友观看过的视频，`level 2` 的视频包含所有你好友的好友观看过的视频，以此类推。一般的，`Level 为 k` 的视频包含所有从你出发，最短距离为 k 的好友观看过的视频。

给定你的 `id`  和一个 `level` 值，请你找出所有指定 `level` 的视频，并将它们按观看频率升序返回。如果有频率相同的视频，请将它们按字母顺序从小到大排列。

### 解题思路



### Solution 1: BFS

这里还是可以比较直接的看出来应该使用 BFS 来做的

题目不难，就是简单的 BFS，细心一点就好了

````c++
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        const int len = friends.size();
        queue<int> que;
        vector<int> visited(len, 0);
        
        que.push(id);
        visited[id] = 1;
        while (level > 0) {
            const int list_len = que.size();
            
            for (int i = 0; i < list_len; ++i) {
                int cur = que.front();
                que.pop();

                for (int user : friends[cur]) {
                    if (visited[user]) {
                        continue;
                    }
                    que.push(user);
                    visited[user] = 1;
                }
            }
            
            --level;
        }

        map<string, int> buckets;
        int max_cnt = 0;
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            
            for (const auto& video : watchedVideos[cur]) {
                ++buckets[video];
                max_cnt = max(max_cnt, buckets[video]);
            }
        }
        vector<pair<string, int>> tmp;
        for (const auto& [video, freq] : buckets) {
            tmp.emplace_back(video, freq);
        }
        sort (tmp.begin(), tmp.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs.second == rhs.second) {
                return lhs.first < rhs.first;
            }
            return lhs.second < rhs.second;
        });
        
        vector<string> ans;
        for (const auto& [video, freq] : tmp) {
            ans.push_back(video);
        }
        
        return ans;
    }
};
````

