# [888. Fair Candy Swap](https://leetcode.com/problems/fair-candy-swap/)

## 题目

Alice and Bob have a different total number of candies. You are given two integer arrays `aliceSizes` and `bobSizes` where `aliceSizes[i]` is the number of candies of the `ith` box of candy that Alice has and `bobSizes[j]` is the number of candies of the `jth` box of candy that Bob has.

Since they are friends, they would like to exchange one candy box each so that after the exchange, they both have the same total amount of candy. The total amount of candy a person has is the sum of the number of candies in each box they have.

Return a*n integer array* `answer` *where* `answer[0]` *is the number of candies in the box that Alice must exchange, and* `answer[1]` *is the number of candies in the box that Bob must exchange*. If there are multiple answers, you may **return any** one of them. It is guaranteed that at least one answer exists.

 

**Example 1:**

```
Input: aliceSizes = [1,1], bobSizes = [2,2]
Output: [1,2]
```

**Example 2:**

```
Input: aliceSizes = [1,2], bobSizes = [2,3]
Output: [1,2]
```

**Example 3:**

```
Input: aliceSizes = [2], bobSizes = [1,3]
Output: [2,3]
```

 

**Constraints:**

- `1 <= aliceSizes.length, bobSizes.length <= 104`
- `1 <= aliceSizes[i], bobSizes[j] <= 105`
- Alice and Bob have a different total number of candies.
- There will be at least one valid answer for the given input.

## 题目大意

爱丽丝和鲍勃有总数不同的糖果: `aliceSizes[i]` 是爱丽丝拥有的第 `i` 盒糖果的数数目，`bobSizes[j]` 是鲍勃拥有的第 `j` 盒糖果的数目。

因为他们是朋友，所以他们想交换一盒糖果，这样交换后，他们都有相同的糖果总量。（一个人拥有的糖果总量是他们拥有的每一盒糖果数量的总和。）

返回一个整数数组 ans，其中 `ans[0]` 是爱丽丝必须交换的那盒糖果的数目，`ans[1]` 是 Bob 必须交换的那盒糖果的大小。如果有多个答案，你可以返回其中任何一个。保证答案存在。



## 解题思路



### Solution 1: 

暴力解法，最终超时，不过这里还是尝试一下

````c++
class Solution {
public:
    vector<int> fairCandySwap(vector<int>& alice_sizes, vector<int>& bob_sizes) {
        const int alice_len = alice_sizes.size();
        int alice_sum = accumulate(alice_sizes.begin(), alice_sizes.end(), 0);
        const int bob_len = bob_sizes.size();
        int bob_sum = accumulate(bob_sizes.begin(), bob_sizes.end(), 0);
        
        // 暴力求解
        for (int i = 0; i < alice_len; ++i) {
            int alice = alice_sizes[i];
            alice_sum -= alice;
            for (int j = 0; j < bob_len; ++j) {
                int bob = bob_sizes[j];
                bob_sum -= bob;
                if (alice_sum + bob == bob_sum + alice) {
                    return vector<int>({alice, bob});
                }
                bob_sum += bob; // 恢复
            }
            alice_sum += alice; // 恢复
        }
        return vector<int>();
    }
};
````



### Solution 2: 使用缓存

这种解法来自霜神：https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0888.Fair-Candy-Swap/

但这里我用了 set 来查询，而没有使用map，这种解法就是典型的空间换时间

````c++
class Solution {
public:
    vector<int> fairCandySwap(vector<int>& alice_sizes, vector<int>& bob_sizes) {
        const int alice_len = alice_sizes.size();
        int alice_sum = accumulate(alice_sizes.begin(), alice_sizes.end(), 0);
        const int bob_len = bob_sizes.size();
        int bob_sum = accumulate(bob_sizes.begin(), bob_sizes.end(), 0);
        int diff = (alice_sum - bob_sum) / 2; // 总和的 diff
        
        unordered_set<int> query; // 为了后面的查询方便，这里使用集合
        for (int num : alice_sizes) {
            query.insert(num);
        }
        
        for (int num : bob_sizes) {
            if (query.find(num + diff) != query.end()) {
                // 如果 num + diff 在缓存中
                return vector<int>({num + diff, num});
            }
        }
        
        return vector<int>();
    }
};
````





