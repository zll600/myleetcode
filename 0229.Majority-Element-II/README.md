# [229. Majority Element II](https://leetcode.com/problems/majority-element-ii/)

## 题目

Given an integer array of size `n`, find all elements that appear more than `⌊ n/3 ⌋` times.

 

**Example 1:**

```
Input: nums = [3,2,3]
Output: [3]
```

**Example 2:**

```
Input: nums = [1]
Output: [1]
```

**Example 3:**

```
Input: nums = [1,2]
Output: [1,2]
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `-109 <= nums[i] <= 109`

 

**Follow up:** Could you solve the problem in linear time and in `O(1)` space?

## 题目大意

给定一个整数表示数组的大小，找到所有出现次数大于 n / 3（这里采用向下取整）次的数

进阶要求：使用 O(1) 的空间来解决问题

## 解题思路

这道题可以类比第 169 题来做，这道题比那道更难

### 解法1

这里使用的方法是用一个 map 来做缓存，

`````c++
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;  // 统计每种元素出现的次数
        for (int num : nums) {
            freq[num]++;
        }
        
        vector<int> res;
        int size = nums.size();
        for (const auto& item : freq) {
            if (item.second > size / 3) {  // 找出符合条件的元素
                res.push_back(item.first);
            }
        }
        
        return res;
    }
};
`````

### 解法2

先排序，然后统计连续字符的个数，符合条件的加入到结果集中，

`````c++
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 排序
        int i = 0;
        int j = 0;
        
        vector<int> res;
        int size = nums.size();
        while (i < size) {
            // 循环不变量 [i, j) 这里
            while (j < size && nums[i] == nums[j]) {  // 统计同一个元素出现的次数
                j++;
            }
            if (j - i > size / 3) {  // 满足条件
                res.push_back(nums[i]);
            }
            i = j;
        }
        
        return res;
    }
};
`````

### 解法3（摩尔计数）

关于这道题的摩尔计数，我觉得这篇题解讲的很好：https://leetcode-cn.com/problems/majority-element-ii/solution/liang-fu-dong-hua-yan-shi-mo-er-tou-piao-fa-zui-zh/

我觉得该算法的核心在于，如果相等就增加候选人的票数，如果不相等，就抵消，如果最终候选人的票数大于 0，则其有可能满足条件，需要继续进行一次验证，如果等于0，则肯定不能满足条件

````c++
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        // 初始化候选人，这里因为选出的元素出现的次数应该大于size / 3
        // 所以至多只能选出两个
        int candidate1 = nums[0];
        int cnt1 = 0;
        int candidate2 =nums[0];
        int cnt2 = 0;
        
        // 配队阶段
        for (int num : nums) {
            if (candidate1 == num) {
                cnt1++;
            } else if (candidate2 == num) {
                cnt2++;
            } else if (cnt1 <= 0) {
                candidate1 = num;
                cnt1 = 1;
            } else if (cnt2 <= 0) {
                candidate2 = num;
                cnt2 = 1;
            } else {
                cnt1--;
                cnt2--;
            }
        }
        // 重新计数
        cnt1 = 0;
        cnt2 = 0;
        for (int num : nums) {
            if (candidate1 == num) {
                cnt1++;
            } else if (candidate2 == num) {
                cnt2++;
            }
        }
        
        vector<int> res;
        if (cnt1 > nums.size() / 3) {
            res.push_back(candidate1);
        }
        if (cnt2 > nums.size() / 3) {
            res.push_back(candidate2);
        }
        
        return res;
    }
};
````

