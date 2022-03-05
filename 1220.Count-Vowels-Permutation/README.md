# [1220. Count Vowels Permutation](https://leetcode-cn.com/problems/count-vowels-permutation/)

## 题目

Given an integer `n`, your task is to count how many strings of length `n` can be formed under the following rules:

- Each character is a lower case vowel (`'a'`, `'e'`, `'i'`, `'o'`, `'u'`)
- Each vowel `'a'` may only be followed by an `'e'`.
- Each vowel `'e'` may only be followed by an `'a'` or an `'i'`.
- Each vowel `'i'` **may not** be followed by another `'i'`.
- Each vowel `'o'` may only be followed by an `'i'` or a `'u'`.
- Each vowel `'u'` may only be followed by an `'a'.`

Since the answer may be too large, return it modulo `10^9 + 7.`

 

**Example 1:**

```
Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
```

**Example 2:**

```
Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
```

**Example 3:** 

```
Input: n = 5
Output: 68
```

 

**Constraints:**

- `1 <= n <= 2 * 10^4`

## 题目大意

计算有多少个长度为 `n` 的字符串符合下列条件：

- 每个字符都是一个小写的元音字符(`'a'`, `'e'`, `'i'`, `'o'`, `'u'`),
- `'a'` 的后面只能加 `'e'`,
- `'e'` 后面只能加 `'a'` 或者 `'i'`
- `'i'` 后面不能加 `'i'`,
- `'o'` 后面只能加 `'i'` 或者 `'u'`
- `'u'` 后面只能加 `'a'`

结果可能很大，对 `10^9 + 7` 取模

## 解题思路

这道题目可以联系第 1641 题、不过这道题目的状态转移方程更难写

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/count-vowels-permutation/solution/wei-rao-li-lun-zi-dong-ji-zhuang-tai-ji-9vf5d/)

这里面提到的 **有限状态机** 概念是很值得学习的

````c++
class Solution {
public:
    int countVowelPermutation(int n) {
        // 初始化以每个字符结尾的字符串最短为 1
        state_ = vector<int>(5, 1);
        tmp_ = vector<int>(5, 1);

        // 这里就是递推的过程
        for (int i = 2; i <= n; ++i) {
            Solve();
        }

        int sum = 0;
        // for (int i = 0; i < 5; ++i) {
        //     sum += state_[i];
        //     sum %= mod_;
        // }

        for_each(state_.begin(), state_.end(), [&](int num) {
            sum += num;
            sum %= mod_;
        });

        return sum;
    }

 private:
    vector<int> state_; // 状态数组
    vector<int> tmp_; // 为了避免频繁创建数组，不过这里数组的长度并不大，所以应该不太会影响性能

    const int mod_ = 1000000007;

    // 状态转移，当前字符可以由哪些字符转移而来
    void Solve() {
        tmp_[0] = (1LL * state_[1] + state_[2] + state_[4]) % mod_;
        tmp_[1] = (state_[0] + state_[2]) % mod_;
        tmp_[2] = (state_[1] + state_[3]) % mod_;
        tmp_[3] = state_[2] % mod_;
        tmp_[4] = (state_[2] + state_[3]) % mod_;

        swap(tmp_, state_);
    }
};
````
