# [777. Swap Adjacent in LR String](https://leetcode.cn/problems/swap-adjacent-in-lr-string/)

## 题目

In a string composed of `'L'`, `'R'`, and `'X'` characters, like `"RXXLRXRXL"`, a move consists of either replacing one occurrence of `"XL"` with `"LX"`, or replacing one occurrence of `"RX"` with `"XR"`. Given the starting string `start` and the ending string `end`, return `True` if and only if there exists a sequence of moves to transform one string to the other.

 

**Example 1:**

```
Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: true
Explanation: We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
```

**Example 2:**

```
Input: start = "X", end = "L"
Output: false
```

 

**Constraints:**

- `1 <= start.length <= 104`
- `start.length == end.length`
- Both `start` and `end` will only consist of characters in `'L'`, `'R'`, and `'X'`.

## 题目大意

在一个由 `'L'` , `'R'` 和 `'X'` 三个字符组成的字符串（例如 `"RXXLRXRXL"` ）中进行移动操作

一次移动操作指用一个`"LX"` 替换一个 `"XL"`，或者用一个`"XR"` 替换一个 `"RX"` 。现给定起始字符串 `start` 和结束字符串 `end`，请编写代码，当且仅当存在一系列移动操作使得 `start` 可以转换成 `end` 时， 返回 `True`

## 解题思路

这种脑筋急转弯的题目还是挺难的

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/swap-adjacent-in-lr-string/solution/zhong-gui-zhong-ju-777-zai-lrzi-fu-chuan-jiyn/)

````c++
class Solution {
public:
    bool canTransform(string start, string end) {
        int n = start.size();
        int i = 0, j = 0;
        while (i < n && j < n) {
            // 跳过多余的 'X'
            while (i < n && start[i] == 'X') {
                ++i;
                continue;
            }
            while (j < n && end[j] == 'X') {
                ++j;
                continue;
            }

            // 防止越界
            if (i == n && j == n) {
                return true;
            } else if (i == n || j == n) {
                return false;
            }

            // 如果不一样，那么最终一定无法转换
            if (start[i] != end[j]) {
                return false;
            }

            // ‘L’只能向前变换，所以如果 i 已经小于 j 了，那么一定无法转换
            if (i < n && start[i] == 'L' && i < j) {
                cout << "L" << endl;
                return false;
            }
            // 'R' 只能向后转换，所以如果 i 已经大于 j 了，那么一定无法转换
            if (i < n && start[i] == 'R' && i > j) {
                return false;
            }

            ++i;
            ++j;
        }

        // 将整个 start 遍历完
        while (i < n) {
            if (start[i] != 'X') {
                return false;
            }
            ++i;
        }
        // 将 end 遍历完
        while (j < n) {
            if (end[j] != 'X') {
                return false;
            }
            ++j;
        }

        return true;
    }
};
````

