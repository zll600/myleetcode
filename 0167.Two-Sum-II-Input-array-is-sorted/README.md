#  [167. Two Sum II - Input array is sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

## 题目

Given an array of integers `numbers` that is already ***sorted in non-decreasing order\***, find two numbers such that they add up to a specific `target` number.

Return *the indices of the two numbers (**1-indexed**) as an integer array* `answer` *of size* `2`*, where* `1 <= answer[0] < answer[1] <= numbers.length`.

The tests are generated such that there is **exactly one solution**. You **may not** use the same element twice.

 

**Example 1:**

```
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
```

**Example 2:**

```
Input: numbers = [2,3,4], target = 6
Output: [1,3]
```

**Example 3:**

```
Input: numbers = [-1,0], target = -1
Output: [1,2]
```

 

**Constraints:**

- `2 <= numbers.length <= 3 * 104`
- `-1000 <= numbers[i] <= 1000`
- `numbers` is sorted in **non-decreasing order**.
- `-1000 <= target <= 1000`
- The tests are generated such that there is **exactly one solution**.

## 题目大意

给定一个已排序的数组，数组中的元素按照哦啊非降序排列，找出恋歌数，他们相加的值为 target，返回结果的对应的下标（下表从 1 开始，），不能使用同一个元素两次。

## 解题思路

* 类比 0001 题，这道题目的输入是排好序的，因此可以直接用“双指针”，

## 代码

````
// 解法一：Two pointers 时间复杂度 O(logn)
/*
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int size = numbers.size();
        
        int left = 0;
        int right = size - 1;
        while (left < right) {
            long sum = 1L * numbers[left] + numbers[right];
            
            if (sum < target) {
                ++left;
            } else if (sum > target) {
                --right;
            } else {
                return vector<int>{left + 1, right + 1};
            }
        }
        
        return vector<int>();
    }
};
*/

//解法二：利用 map 作缓存，空间复杂度比上一种要高许多O(n),时间复杂度 O(n)
class Solution {
 public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> dict;
        
        for (int i = 0; i < nums.size(); ++i) {
            if (dict.count(target - nums[i])) {
                return vector<int>{dict[target - nums[i]] + 1, i + 1};
            }
            dict[nums[i]] = i;
        }
        
        return vector<int>();
    }
};
````

