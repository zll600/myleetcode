# [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/)

## 题目

You are given an array of integers `nums` represents the numbers written on a chalkboard.

Alice and Bob take turns erasing exactly one number from the  chalkboard, with Alice starting first. If erasing a number causes the  bitwise XOR of all the elements of the chalkboard to become `0`, then that player loses. The bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is `0`.

Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to `0`, then that player wins.

Return `true` *if and only if Alice wins the game, assuming both players play optimally*.

 

**Example 1:**

```
Input: nums = [1,1,2]
Output: false
Explanation: 
Alice has two choices: erase 1 or erase 2. 
If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
If Alice erases 2 first, now nums become [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.
```

**Example 2:**

```
Input: nums = [0,1]
Output: true
```

**Example 3:**

```
Input: nums = [1,2,3]
Output: true
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] < 216`

## 题目

黑板上写着一个非负整数数组 `nums[i]` 。`Alice` 和 `Bob` 轮流从黑板上擦掉一个数字，`Alice` 先手。

如果擦除一个数字后，剩余的所有数字 *按位异或* 运算得出的结果等于 `0` 的话，当前玩家游戏失败。 (另外，如果只剩一个数字，按位异或运算得到它本身；如果无数字剩余，按位异或运算结果为 0。）

并且，轮到某个玩家时，如果当前黑板上所有数字按位异或运算结果等于 `0`，这个玩家获胜。

假设两个玩家每步都使用最优解，当且仅当 Alice 获胜时返回 true

## 解题思路

Alice 能赢需要满足下列条件之一：

- 在自己的回合中擦除一个数后，剩下的所有数字异或值不为 0
- 如果自己的回合时，黑板上的数字异或为 0，那么其获胜



### Solution 1:


````c++
class Solution {
public:
    bool xorGame(vector<int>& nums) {
        // 如果数组的长度是偶数，那么一定就可以获胜，
        if (nums.size() % 2 == 0) {
            return true;
        }
        
        // 或者当前的数组异或值已经是 0 了，那么可以获胜
        int res = 0;
        for (int num : nums) {
            res ^= num;
        }
        return res == 0;
    }
};
````
