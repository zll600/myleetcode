# [638. Shopping Offers](https://leetcode.com/problems/shopping-offers/)

## 题目

In LeetCode Store, there are `n` items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.

You are given an integer array `price` where `price[i]` is the price of the `ith` item, and an integer array `needs` where `needs[i]` is the number of pieces of the `ith` item you want to buy.

You are also given an array `special` where `special[i]` is of size `n + 1` where `special[i][j]` is the number of pieces of the `jth` item in the `ith` offer and `special[i][n]` (i.e., the last integer in the array) is the price of the `ith` offer.

Return *the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers*. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.

 

**Example 1:**

```
Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
Output: 14
Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B. 
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
```

**Example 2:**

```
Input: price = [2,3,4], special = [[1,1,0,4],[2,2,1,9]], needs = [1,2,1]
Output: 11
Explanation: The price of A is $2, and $3 for B, $4 for C. 
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C. 
You cannot add more items, though only $9 for 2A ,2B and 1C.
```

 

**Constraints:**

- `n == price.length`
- `n == needs.length`
- `1 <= n <= 6`
- `0 <= price[i] <= 10`
- `0 <= needs[i] <= 10`
- `1 <= special.length <= 100`
- `special[i].length == n + 1`
- `0 <= special[i][j] <= 50`

## 题目大意

在 `LeetCode` 商店中， 有 `n` 件在售的物品。每件物品都有对应的价格。然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。

给你一个整数数组 `price` 表示物品价格，其中 `price[i]` 是第 `i` 件物品的价格。另有一个整数数组 `needs` 表示购物清单，其中 `needs[i]` 是需要购买第 `i` 件物品的数量。

还有一个数组 `special` 表示大礼包，`special[i]` 的长度为 `n + 1` ，其中 `special[i][j]` 表示第 `i` 个大礼包中内含第 `j` 件物品的数量，且 `special[i][n]` （也就是数组中的最后一个整数）为第 `i` 个大礼包的价格

返回 **确切** 满足购物清单所需花费的最低价格，你可以充分利用大礼包的优惠活动。你不能购买超出购物清单指定数量的物品，即使那样会降低整体价格。任意大礼包可无限次购买

## 解题思路

这道题目中我们要找的状态就是 `needs`，整个 DFS 的过程中，我们需要根据是否选择礼包来更新 `needs`，的状态，然后给出结果，

这里的优化点在于 DFS ，通常很容易加上 记忆化 来加速递归

### Solution 1: DFS + map

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/shopping-offers/solution/wei-rao-li-lun-kan-qi-lai-xiang-bei-bao-l4trt/)

````c++
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return DFS(price, special, needs);
    }
    
 private:
    map<vector<int>, int> cache_; // 缓存
    
    int DFS(const vector<int>& price, const vector<vector<int>>& special, vector<int>& needs) {
        // 先查缓存
        if (cache_.find(needs) != cache_.end()) {
            return cache_[needs];
        }
        
        int ans = 0;
        const int len = needs.size();
        
        // 想尝试不购买大礼包
        for (int i = 0; i < len; ++i) {
            ans += needs[i] * price[i];
        }
        
        // 尝试购买大礼包
        const int special_len = special.size();
        for (int i = 0; i < special_len; ++i) {
            vector<int> next = needs; // 先保留 needs 数组
            bool is_valid = true; // 这次能否购买礼包
            
            for (int j = 0; j < len; ++j) {
                if (special[i][j] > needs[j]) {
                    // 如果礼包中含有的数目已经超过所需的，就说明不能购买礼包
                    is_valid = false;
                    break;
                }
            }
            if (!is_valid) {
                continue;
            }
            
            // 如果可以购买大礼包，就缩小剩余的需求
            for (int j = 0; j < len; ++j) {
                next[j] -= special[i][j];
            }
            
            // 我们始终求最小的
            ans = min(ans, DFS(price, special, next) + special[i].back());
        }
        cache_[needs] = ans;
        return ans;
    }
};
````

### Solution 2: DFS + unordered_map



````c++
struct HashFunc_t {
	size_t operator() (const vector<int>& key) const {
		std::hash<int> hasher;
		size_t seed = 0;
		for (int i : key) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return DFS(price, special, needs);
    }
    
 private:
    unordered_map<vector<int>, int, HashFunc_t> cache_; // 缓存
    
    int DFS(const vector<int>& price, const vector<vector<int>>& special, vector<int>& needs) {
        // 先查缓存
        if (cache_.find(needs) != cache_.end()) {
            return cache_[needs];
        }
        
        int ans = 0;
        const int len = needs.size();
        
        // 想尝试不购买大礼包
        for (int i = 0; i < len; ++i) {
            ans += needs[i] * price[i];
        }
        
        // 尝试购买大礼包
        const int special_len = special.size();
        for (int i = 0; i < special_len; ++i) {
            vector<int> next = needs; // 先保留 needs 数组
            bool is_valid = true; // 这次能否购买礼包
            
            for (int j = 0; j < len; ++j) {
                if (special[i][j] > needs[j]) {
                    // 如果礼包中含有的数目已经超过所需的，就说明不能购买礼包
                    is_valid = false;
                    break;
                }
            }
            if (!is_valid) {
                continue;
            }
            
            // 如果可以购买大礼包，就缩小剩余的需求
            for (int j = 0; j < len; ++j) {
                next[j] -= special[i][j];
            }
            
            // 我们始终求最小的
            ans = min(ans, DFS(price, special, next) + special[i].back());
        }
        cache_[needs] = ans;
        return ans;
    }
};
````
