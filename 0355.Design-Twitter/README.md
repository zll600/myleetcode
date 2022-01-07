# [355. Design Twitter](https://leetcode-cn.com/problems/design-twitter/)

## 题目

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the `10` most recent tweets in the user's news feed.

Implement the `Twitter` class:

- `Twitter()` Initializes your twitter object.
- `void postTweet(int userId, int tweetId)` Composes a new tweet with ID `tweetId` by the user `userId`. Each call to this function will be made with a unique `tweetId`.
- `List<Integer> getNewsFeed(int userId)` Retrieves the `10` most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be **ordered from most recent to least recent**.
- `void follow(int followerId, int followeeId)` The user with ID `followerId` started following the user with ID `followeeId`.
- `void unfollow(int followerId, int followeeId)` The user with ID `followerId` started unfollowing the user with ID `followeeId`.

 

**Example 1:**

```
Input
["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
[[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
Output
[null, null, [5], null, null, [6, 5], null, [5]]

Explanation
Twitter twitter = new Twitter();
twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
twitter.follow(1, 2);    // User 1 follows user 2.
twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.unfollow(1, 2);  // User 1 unfollows user 2.
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.
```

 

**Constraints:**

- `1 <= userId, followerId, followeeId <= 500`
- `0 <= tweetId <= 104`
- All the tweets have **unique** IDs.
- At most `3 * 104` calls will be made to `postTweet`, `getNewsFeed`, `follow`, and `unfollow`.

## 题目大意

设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见最近 `10` 条推文

实现 `Twitter` 类：

* `Twitter()` 初始化`twitter`对象
* `void postTweet(int userId, int tweetId)` 根据给定的 `tweetId` 和 `userId` 创建一条新推文。每次调用此函数都会使用一个不同的 `tweetId` 
* `List<Integer> getNewsFeed(int userId)` 检索当前用户新闻推送中最近  10 条推文的 ID 。新闻推送中的每一项都必须是由用户关注的人或者是用户自己发布的推文。推文必须 按照时间顺序由最近到最远排序 
* `void follow(int followerId, int followeeId)` ID 为 `followerId` 的用户 follow ID 为 `followeeId` 的用户
* `void unfollow(int followerId, int followeeId)` ID 为 `followerId` 的用户不再关注 ID 为 `followeeId` 的用户

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/design-twitter/solution/ha-xi-biao-lian-biao-you-xian-dui-lie-java-by-liwe/

这里只维护每个人关注了谁，用一个 map，键是用户 id，值是用户的关注集合

另外对每个用户维护一个消息列表，这里使用的链表，采用头插法，最新的消息，在最前面，

### Solution1:

````c++
class Twitter {
public:
    Twitter() : timestamp_(0) {
    }
    
    void postTweet(int user_id, int tweet_id) {
        // 每一篇推文都是 <tweet_id, timestamp_>
        feeds_[user_id].emplace_front(tweet_id, timestamp_);
        ++timestamp_;
    }
    
    vector<int> getNewsFeed(int user_id) {
        // 构建一个大顶堆，按照时间的升序排序
        auto cmp = [](const list<pair<int, int>>& a,
                      const list<pair<int, int>>& b) {
            // 按照链表首篇推文的 时间戳来排序
            return a.front().second < b.front().second;
        };
        priority_queue<list<pair<int, int>>,
                        vector<list<pair<int, int>>>,
                        decltype(cmp)> heap(cmp);
        
        if (feeds_.find(user_id) != feeds_.end()) {
            // 将当前用户的推文列表加入
            if (!feeds_[user_id].empty()) {
                // 只有非空才加入
                heap.push(feeds_[user_id]);
            }
        }
        
        const unordered_set<int>& users = followings_[user_id];
        for (int user : users) {
            // 将关注的用户的推文列表加入
            if (!feeds_[user].empty()) {
                heap.push(feeds_[user]);
            }
        }
        
        vector<int> res; // 结果
        // 这里只需要前 10 条
        while (!heap.empty() && res.size() < 10) {
            // 拿出堆顶
            auto feed = heap.top();
            heap.pop();
            
            res.push_back(feed.front().first); // 加入结果集中
            feed.pop_front(); // 删掉首元素
            
            if (!feed.empty()) {
                // 如果不为空，加入堆中
                heap.push(feed);
            }
        }
        
        return res;
    }
    
    void follow(int follower_id, int followee_id) {
        if (follower_id == followee_id) {
            // 不能自己关注自己
            return;
        }
        
        // 这个检查也可以不做
        if (followings_[follower_id].find(followee_id) != followings_[follower_id].end()) {
            // 如果已经添加过了，就不用再添加了
            return;
        }
        followings_[follower_id].insert(followee_id);
    }
    
    void unfollow(int follower_id, int followee_id) {
        if (follower_id == followee_id) {
            return;
        }
        
        // 这个检查也可以省略
        if (followings_[follower_id].find(followee_id) == followings_[follower_id].end()) {
            // 如果没有关注，就无法取消
            return;
        }
        
        followings_[follower_id].erase(followee_id);
    }
    
 private:
    int timestamp_; // 时间戳，递增
    // priority_queue<int> heap_; // 大顶堆，用于合并
    unordered_map<int, unordered_set<int>> followings_; // key: 用户，value: 关注者的集合
    unordered_map<int, list<pair<int, int>>> feeds_; // key: 用户，value: 推文的链表
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
````





