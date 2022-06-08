# [954. Array of Doubled Pairs](https://leetcode.cn/problems/array-of-doubled-pairs/)

## 题目

Given an integer array of even length `arr`, return `true` *if it is possible to reorder* `arr` *such that* `arr[2 * i + 1] = 2 * arr[2 * i]` *for every* `0 <= i < len(arr) / 2`*, or* `false` *otherwise*.

 

**Example 1:**

```
Input: arr = [3,1,3,6]
Output: false
```

**Example 2:**

```
Input: arr = [2,1,2,6]
Output: false
```

**Example 3:**

```
Input: arr = [4,-2,2,-4]
Output: true
Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
```

 

**Constraints:**

- `2 <= arr.length <= 3 * 104`
- `arr.length` is even.
- `-105 <= arr[i] <= 105`

## 题目大意

给定一个长度为偶数的整数数组 `arr`，只有对 `arr` 进行重组后可以满足 “对于每个 `0 <= i < len(arr) / 2`，都有 `arr[2 * i + 1] = 2 * arr[2 * i]`” 时，返回 true；否则，返回 false

## 解题思路

这里的解法还是比较好像的，记录下每个数的频数，分正数、0 和 负数，负数转化为正数

## Solution 1:

````c++
class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        map<int, int> positives;
        map<int, int> negatives;
        int zeros = 0;
        for (int num : arr) {
            if (num > 0) {
                ++positives[num];
            } else if (num < 0) {
                ++negatives[abs(num)];
            } else {
                ++zeros;
            }
        }

        if (zeros % 2 != 0) {
            return false;
        }


        Process(positives);
        Process(negatives);

        return positives.empty() && negatives.empty();
    }

 private:
    void Process(map<int, int>& freq) {
        while (!freq.empty()) {
            bool flag = false;
            auto smaller = freq.begin();
            // cout << smaller->first << ": " << smaller->second << " --- ";
            auto larger = freq.find(2 * smaller->first);
            if (larger != freq.end()) {
                // cout << larger->first << ": " << larger->second << endl;
                flag = true;
                --smaller->second;
                if (smaller->second == 0) {
                    freq.erase(smaller);
                }
                --larger->second;
                if (larger->second == 0) {
                    freq.erase(larger);
                }
            }

            if (!flag) {
                break;
            }
        }
    }
};
````

