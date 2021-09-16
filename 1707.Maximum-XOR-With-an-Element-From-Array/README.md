# [1707. Maximum XOR With an Element From Array](https://leetcode.com/problems/maximum-xor-with-an-element-from-array/)

## 题目

You are given an array `nums` consisting of non-negative integers. You are also given a `queries` array, where `queries[i] = [xi, mi]`.

The answer to the `ith` query is the maximum bitwise `XOR` value of `xi` and any element of `nums` that does not exceed `mi`. In other words, the answer is `max(nums[j] XOR xi)` for all `j` such that `nums[j] <= mi`. If all elements in `nums` are larger than `mi`, then the answer is `-1`.

Return *an integer array* `answer` *where* `answer.length == queries.length` *and* `answer[i]` *is the answer to the* `ith` *query.*

 

**Example 1:**

```
Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
Output: [3,3,7]
Explanation:
1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
2) 1 XOR 2 = 3.
3) 5 XOR 2 = 7.
```

**Example 2:**

```
Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
Output: [15,-1,5]
```

 

**Constraints:**

- `1 <= nums.length, queries.length <= 105`
- `queries[i].length == 2`
- `0 <= nums[j], xi, mi <= 109`

## 题目大意

给定一个由非负数组成的数组，同时也给定一个查询数组 queries, queries[i] = [xi, mi]，第 i 个查询的答案是 xi 和数组中任意一个小于mi 的元素的异或结果，换句话说，答案就是 max(nums[j] XOR xi) 对于所有的 j 均满足 nums[j] <= mi，如果 nums 中的所有元素都比 mi 大，答案就是 -1，

然会一个数组来表示查询的结果，

## 解题思路

* 这里补充两个概念：离线和在线查询：https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array/solution/c-chi-xian-he-zai-xian-by-qiank-5y3f/
* 离线查询：
  * 先将nums 数组由小到大进行排序，然后将 queries 数组按照第二个元素的大小进行排序，不过排序之前需要保存好原本的下标的映射关系，
  * 这道题目我们可以在遍历 queries 数组时构建字典树，这样可以保证**已经建立好的 Tries 中没有大于当前queries 中mi 的值，**
* 在线查询：
  * 给每个节点设置一个标志，用来表示该路径上的最小值，如果这最小值已经不满足条件，代表这条分支是不能走的，应该跳过，走下一条
* 这道题可以参考第 421 题，只不过，这道题有了更多的限制条件

## 代码

`````c++
/*离线查询，对两个数组都需要进行排序操作
class Trie {
 public:
    Trie() : root_(new TrieNode()) {
    }
    
    void Insert(int num) {
        TrieNode *node = root_;
        ++node->path_;
        for (int i = 31; i >= 0; --i) {
            int val = (num >> i) & 1;
            if (node->dict_[val] == nullptr) {
                node->dict_[val] = new TrieNode();
            }
            node = node->dict_[val];
            ++node->path_;
        }
        ++node->end_;
    }
    
    int GetMaxXOR(int num) {
        TrieNode *node = this->root_;
        int ans = 0;
        for (int i = 31; i >= 0; --i) { // 这里的步骤同第 421 题，
            int val = (num >> i) & 1;
            if (node->dict_[1 - val] != nullptr) {
                ans |= 1 << i;
                val = 1 -val;
            } 
            node = node->dict_[val];
        }
        return ans;
    }

 private:
    struct TrieNode {
        int path_;
        int end_;
        vector<TrieNode*> dict_;
        
        TrieNode()
            : path_(0),
            end_(0) {
            dict_.resize(2);
            for (auto it : dict_) {
                it = nullptr;
            }
        }
        ~TrieNode() {
            for (auto it : dict_) {
                if (it != nullptr) {
                    delete it;
                    it = nullptr;
                }
            }
        }
    };
    
    TrieNode *root_;
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end()); // nums 数组按照从小到大进行排序
        for (int i = 0; i < queries.size(); ++i) {  // 排序之前需要保存queries 和原来下标之间的映射关系
            queries[i].push_back(i);
        }
        // queries 按照limit 的限制从小到大进行排序
        sort(queries.begin(), queries.end(), [](const auto& query1, const auto& query2) {
            return query1[1] < query2[1];
        });
        
        Trie trie;
        int idx = 0;
        int n = nums.size();
        vector<int> ans(queries.size());
        for (auto& q : queries) {
            int x = q[0];
            int limit = q[1];
            int qid = q[2];
            
            while (idx < n && nums[idx] <= limit) { // 这里我们只插入小于 limit 的nums中的元素，这样题目就变成了第 421 题，揭发完全一样
                trie.Insert(nums[idx++]);
            }
            
            if (idx == 0) {
                ans[qid] = -1;
            } else {
                ans[qid] = trie.GetMaxXOR(x);
            }
        }
        return ans;
    }
};*/

// 在线查询，超时
class Tries {
 public:
    Tries() : root_(new TrieNode()) {}
    
    void Insert(int num) {
        TrieNode *node = root_;
        node->smallest_ = min(node->smallest_, num);
        
        for (int i = 30 - 1; i >= 0; --i) {
            int val = (num >> i) & 1;
            if (node->dict_[val] == nullptr) {
                node->dict_[val] = new TrieNode();
            }
            node = node->dict_[val];
            ++node->path_;
            node->smallest_ = min(node->smallest_, num);
        }
        ++node->end_;
    }
    
    int GetMaxXOR(int num, int limit) {
        TrieNode *node = this->root_;
        if (node->smallest_ > limit) {
            return -1;
        }
        
        int res = 0;
        for (int i = 30 - 1; i >= 0; --i) { // 这里的步骤同第 421 题，
            int val = (num >> i) & 1;
            if (node->dict_[1 - val] != nullptr && node->dict_[1 -val]->smallest_ <= limit) {
                res |= 1 << i;
                val = 1 -val;
            }
            node = node->dict_[val];
        }
        return res;
    }

 private:
    struct TrieNode {
        int path_;
        int end_;
        int smallest_;  // 这里新增加一个标志，如果这个标志都大于 limit，那么显然此路不同，只能走其他路，
        vector<TrieNode*> dict_;
        
        TrieNode()
            : path_(0),
            end_(0),
            smallest_(INT_MAX) {
            dict_.resize(2);
            for (auto& it : dict_) {
                it = nullptr;
            }
        }
        ~TrieNode() {
            for (auto& it : dict_) {
                if (it != nullptr) {
                    delete it;
                }
                it = nullptr;
            }
        }
    };
    
    TrieNode *root_;
};

class Solution {
 public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Tries trie;
        for (int num : nums) {
            trie.Insert(num);
        }
        
        vector<int> res;
        for (auto& it : queries) {
            int num = it[0];
            int limit = it[1];
            res.push_back(trie.GetMaxXOR(num, limit));
        }
        return res;
    }
};
`````

