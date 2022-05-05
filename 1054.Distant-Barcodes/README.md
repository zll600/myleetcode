# [1054. Distant Barcodes](https://leetcode.com/problems/distant-barcodes/)

## 题目

In a warehouse, there is a row of barcodes, where the `ith` barcode is `barcodes[i]`.

Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.

 

**Example 1:**

```
Input: barcodes = [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
```

**Example 2:**

```
Input: barcodes = [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,1,2,1,2]
```

 

**Constraints:**

- `1 <= barcodes.length <= 10000`
- `1 <= barcodes[i] <= 10000`

## 题目大意

在一个仓库里，有一排条形码，其中第 i 个条形码为 barcodes[i]。请你重新排列这些条形码，使其中两个相邻的条形码 不能 相等。 你可以返回任何满足该要求的答案，此题保证存在答案。


### Solution 1: Hash + Sort

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/distant-barcodes/solution/1054-ju-chi-xiang-deng-de-tiao-xing-ma-z-qy0w/)

1. 先统计每种数值的频数，用无序 map
2. 按照频数排序，使用有序 map
3. 将有序 map 展开到一个数组中
4. 间隔放入结果数组中

````c++

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        const int codes_len = barcodes.size();
        // 统计频数
        unordered_map<int, int> freq;
        for (int barcode : barcodes) {
            ++freq[barcode];
        }
        
        // 利用 map 的有序特性
        map<int, vector<int>> vals;
        for (const auto& item : freq) {
            vals[item.second].push_back(item.first);
        }
        
        // 将所有的元素经过频数排序后平铺
        vector<int> tmp(codes_len);
        auto tmp_it = tmp.begin();
        for (auto it = vals.rbegin(); it != vals.rend(); ++it) {
            for (int val : it->second) {
                // cout << val << endl;
                fill(tmp_it, tmp_it + it->first, val);
                tmp_it += it->first;
            }
        }
        
        // 间隔分布即可
        int j = 0;
        vector<int> res(codes_len);
        for (int i = 0; i < codes_len; i += 2, ++j) {
            res[i] = tmp[j];
        }
        
        for (int i = 1; i < codes_len; i += 2, ++j) {
            res[i] = tmp[j];
        }
        
        return res;
    }
};
````
