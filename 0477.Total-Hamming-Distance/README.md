# [477. Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/)

The [Hamming distance](https://en.wikipedia.org/wiki/Hamming_distance) between two integers is the number of positions at which the corresponding bits are different.

Given an integer array `nums`, return *the sum of **Hamming distances** between all the pairs of the integers in* `nums`.

 

**Example 1:**

```
Input: nums = [4,14,2]
Output: 6
Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case).
The answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
```

**Example 2:**

```
Input: nums = [4,14,4]
Output: 4
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 109`
- The answer for the given input will fit in a **32-bit** integer.

## 题目大意

汉明距离是指两个数的对应的二进制位不同的位置的数目，给定一个数组，返回任意两个数之间汉明距离的总和

## 解题思路

* 这道题目如果用暴力方法，先任取两个数，然后计算其 汉明距离，结果会超时
* 另一个方法是，分别结算n 个数的每一位上有多少个 0 和多少个 1，然后 32 位进行组合
* 因为32 位 中 0 的数目加上 1 的数目就是 n，所以可以优化空间，详情参考代码，这里给出一个题解：https://leetcode-cn.com/problems/total-hamming-distance/solution/c-an-wei-qiu-he-zhu-bu-you-hua-by-answer-5arq/

## 代码

`````c++
class Solution {
public:
    // 解法一：暴力解法（TLE） 
    int totalHammingDistance1(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                res += HammingDistance(nums[i], nums[j]);
            }
        }

        return res;
    }

    // 解法二：使用数组进行记录
    int totalHammingDistance2(vector<int>& nums) {
        vector<int> ones(32, 0);
        // vector<int> zeros(32, 0);

        int len = nums.size();
        for (int num : nums) {
            for (int i = 31; i >= 0; --i) {
                if (num & (1 << i)) {
                    ++ones[i];
                }
                // else {
                //     ++zeros[i];
                // }
            }
        }

        int res = 0;
        for (int i = 31; i >= 0; --i) {
            // res += onse[i] * zeros[i];
            res += ones[i] * (len - ones[i]);
        }

        return res;
    }

    int totalHammingDistance(vector<int>& nums) {
        int res = 0;
        int len = nums.size();

        for (int i = 31; i >= 0; --i) {
            int count = 0;
            for (auto& num : nums) {
                if (num & (1 << i)) {
                    ++count;
                }
            }
            res += count * (len - count);
        }
        return res;
    }

 private:
    int HammingDistance(int a, int b) {
        int res = 0;
        for (int i = 0;  i < 32; ++i) {
            int c = (a >> i) & 1;
            int d =  (b >> i) & 1;
            
            res += c ^ d;
        }

        return res;
    }
};
`````

