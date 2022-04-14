# [838. Push Dominoes](https://leetcode.com/problems/push-dominoes/)

## 题目

There are `n` dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the  left or to the right.

After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the  right push their adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.

For the purposes of this question, we will consider that a falling  domino expends no additional force to a falling or already fallen  domino.

You are given a string `dominoes` representing the initial state where:

- `dominoes[i] = 'L'`, if the `ith` domino has been pushed to the left,
- `dominoes[i] = 'R'`, if the `ith` domino has been pushed to the right, and
- `dominoes[i] = '.'`, if the `ith` domino has not been pushed.

Return *a string representing the final state*.

 

**Example 1:**

```
Input: dominoes = "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.
```

**Example 2:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/05/18/domino.png)

```
Input: dominoes = ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."
```

 

**Constraints:**

- `n == dominoes.length`
- `1 <= n <= 105`
- `dominoes[i]` is either `'L'`, `'R'`, or `'.'`.

## 题目大意

`n` 张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。在开始时，同时把一些多米诺骨牌向左或向右推。

每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。

如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡， 该骨牌仍然保持不变。

就这个问题而言，我们会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。

给你一个字符串 `dominoes` 表示这一行多米诺骨牌的初始状态，其中：

- `dominoes[i] = 'L'`，表示第 `i` 张多米诺骨牌被推向左侧，
- `dominoes[i] = 'R'`，表示第 `i` 张多米诺骨牌被推向右侧，
- `dominoes[i] = '.'`，表示没有推动第 `i` 张多米诺骨牌。

返回表示最终状态的字符串

## 解题思路



### Solution 1:

这种解法在边界的处理上有些困难，不是那么好理解

````c++
class Solution {
public:
    string pushDominoes(string dominoes) {
        const int len = dominoes.size();

        // 滑动窗口
        int left = 0;
        while (left < len) {
            int right = left + 1;
            // [left, right) 是一个区间
            while (right < len - 1 && dominoes[right] == '.') {
                ++right;
            }
            Process(dominoes, left, right + 1);
            left = right;
        }

        return dominoes;
    }

 private:
    void Process(string& dominoes, int first, int last) {
        --last;
        // cout << "first: " << first << " - " << dominoes[first] << " --- "
            // << "last: " << last << " - " << dominoes[last] << endl;
        switch(dominoes[first]) {
            // 如果起点是 '.'，那么只有右边有向左倒的
            case '.':
                if (dominoes[last] == 'L') {
                    while (first < last) {
                        dominoes[first] = 'L';

                        ++first;
                    }
                }
                break;
            // 如果起点是 'L'，那么只有左边是向左倒的
            case 'L':
                if (dominoes[last] == 'L') {
                    while (first < last) {
                        dominoes[first] = 'L';
                        ++first;
                    }
                }
                break;
            case 'R':
                // 如果起点是 'R'，
                if (dominoes[last] == '.' || dominoes[last] == 'R') {
                    while (first <= last) {
                        dominoes[first] = 'R';
                        ++first;
                    }
                } else {
                    while (first < last) {
                        dominoes[first] = 'R';
                        ++first;
                        dominoes[last] = 'L';
                        --last;
                    }
                }
                break;
        }
    }
};
````
