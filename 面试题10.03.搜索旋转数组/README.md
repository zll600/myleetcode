# [面试题 10.03. 搜索旋转数组](https://leetcode-cn.com/problems/search-rotate-array-lcci/)

## 题目

搜索旋转数组。给定一个排序后的数组，包含n个整数，但这个数组已被旋转过很多次了，次数不详。请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。若有多个相同元素，返回索引值最小的一个。

示例1:

 输入: arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 5
 输出: 8（元素5在该数组中的索引）
示例2:

 输入：arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 11
 输出：-1 （没有找到）
提示:

arr 长度范围在[1, 1000000]之间

## 解题思路

这道题目可以同 第33、81、153、154四道题联系起来一起看，都是可以用 ”二分搜索“来解决。

## 代码

``````c++
class Solution {
public:
    int search(vector<int>& arr, int target) {
        int lo = 0;
        int hi = arr.size() - 1;

        while (lo <= hi) {  // 因为答案不一定在数组中，所以采用等号，不符合直接返回 -1
            if (arr[lo] == target) {    // 如果当前搜索区间的第一个元素就是，直接俄返回
                return lo;      // 如果没有这步会超时
            }
            
            int mid = lo + (hi - lo) / 2;

            if (arr[mid] == target) {   // 要找到第一个等于的，所有向左缩
                hi = mid;
            } else if (arr[mid] > arr[lo]) {    // 在数值较大的一边找
                if (arr[lo] <= target && target < arr[mid]) {
                    hi = mid -1;
                } else {
                    lo = mid + 1;
                }
            } else if (arr[mid] < arr[hi]) {    // 在数值较小的一边找
                if (arr[mid] < target && target <= arr[hi]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            } else {
                if (arr[mid] == arr[lo]) {  // 处理与边界值相同，但不是答案的情况，
                    ++lo;                   // 要进行跳过处理，否则会出现死循环
                }
                if (arr[mid] == arr[hi]) {
                    --hi;
                }
            }
        }

        return -1;
    }
};
``````

