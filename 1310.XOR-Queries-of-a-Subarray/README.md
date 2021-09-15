# [1310. XOR Queries of a Subarray](https://leetcode.com/problems/xor-queries-of-a-subarray/)

## 题目

Given the array `arr` of positive integers and the array `queries` where `queries[i] = [Li, Ri]`, for each query `i` compute the **XOR** of elements from `Li` to `Ri` (that is, `arr[Li] **xor** arr[Li+1] **xor** ... **xor** arr[Ri]` ). Return an array containing the result for the given `queries`.

 

**Example 1:**

```
Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8] 
Explanation: 
The binary representation of the elements in the array are:
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
The XOR values for queries are:
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8
```

**Example 2:**

```
Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
Output: [8,0,4,4]
```

 

**Constraints:**

- `1 <= arr.length <= 3 * 10^4`
- `1 <= arr[i] <= 10^9`
- `1 <= queries.length <= 3 * 10^4`
- `queries[i].length == 2`
- `0 <= queries[i][0] <= queries[i][1] < arr.length`

## 题目大意

给定一个正整数数组 arr 和一个查询数组 query，其中query[i] = [Li, Ri]，对于每个查询 i，请你计算从 Li 到 Ri 的 XOR 值（即 arr[Li] xor arr[Li+1] xor … xor arr[Ri]）作为本次查询的结果。并返回一个包含给定查询 queries 所有结果的数组。

## 解题思路

* 这道题求区间的时求区间异或，与区间求和的思路相同，所以可以用前缀和的思路分析，这里利用了两个特点：相同数值进行异或结果为0，
* 这道题目建议还是参考一下这篇题解：https://leetcode-cn.com/problems/xor-queries-of-a-subarray/solution/gong-shui-san-xie-yi-ti-shuang-jie-shu-z-rcgu/

## 代码

`````c++
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int size = arr.size();
        vector<int> xors(size + 1, 0);
        for (int i = 1; i <= size; ++i) {
            xors[i] = xors[i - 1] ^ arr[i - 1];
        }
        
        int len = queries.size();
        vector<int> res(len, 0);
        for (int i = 0; i < len; ++i) {
            int left = queries[i][0] + 1;
            int right = queries[i][1] + 1;
            
            res[i] = xors[right] ^ xors[left - 1];
        }
        return res;
    }
};
`````

