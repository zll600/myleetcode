# [374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)

## 题目

We are playing the Guess Game. The game is as follows:

I pick a number from `1` to `n`. You have to guess which number I picked.

Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.

You call a pre-defined API `int guess(int num)`, which returns 3 possible results:

- `-1`: The number I picked is lower than your guess (i.e. `pick < num`).
- `1`: The number I picked is higher than your guess (i.e. `pick > num`).
- `0`: The number I picked is equal to your guess (i.e. `pick == num`).

Return *the number that I picked*.

 

**Example 1:**

```
Input: n = 10, pick = 6
Output: 6
```

**Example 2:**

```
Input: n = 1, pick = 1
Output: 1
```

**Example 3:**

```
Input: n = 2, pick = 1
Output: 1
```

**Example 4:**

```
Input: n = 2, pick = 2
Output: 2
```

 

**Constraints:**

- `1 <= n <= 231 - 1`
- `1 <= pick <= n`

## 题目大意

玩一个游戏，游戏规则如下：

* 每轮游戏，我都会从 1 到 n，选取一个数，你必须猜我取得的数
* 每次你猜错了，我都会告诉你，你猜大了还是猜小了

这里有一个预先定义的接口 int guess(int num)，返回 3 中可能的结果

* -1，我选取的数小于你猜的（pick < num）
* 1，我选取的数大于你猜的（pick > num）
* 0，我选取的数等你你猜的（pick < num）

## 解题思路

* 这道题目可以采用二分搜索来解决，并不是很难。

## 代码

````c++
/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int lo = 1;
        int hi = n;
        
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (guess(mid) == 0) {
                return mid;
            } else if (guess(mid) > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        return -1;
    }
};
````

