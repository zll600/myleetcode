# [1773. Count Items Matching a Rule](https://leetcode-cn.com/problems/count-items-matching-a-rule/)

## 题目

You are given an array `items`, where each `items[i] = [typei, colori, namei]` describes the type, color, and name of the `ith` item. You are also given a rule represented by two strings, `ruleKey` and `ruleValue`.

The `ith` item is said to match the rule if **one** of the following is true:

- `ruleKey == "type"` and `ruleValue == typei`.
- `ruleKey == "color"` and `ruleValue == colori`.
- `ruleKey == "name"` and `ruleValue == namei`.

Return *the number of items that match the given rule*.

 

**Example 1:**

```
Input: items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]], ruleKey = "color", ruleValue = "silver"
Output: 1
Explanation: There is only one item matching the given rule, which is ["computer","silver","lenovo"].
```

**Example 2:**

```
Input: items = [["phone","blue","pixel"],["computer","silver","phone"],["phone","gold","iphone"]], ruleKey = "type", ruleValue = "phone"
Output: 2
Explanation: There are only two items matching the given rule, which are ["phone","blue","pixel"] and ["phone","gold","iphone"]. Note that the item ["computer","silver","phone"] does not match.
```

 

**Constraints:**

- `1 <= items.length <= 104`
- `1 <= typei.length, colori.length, namei.length, ruleValue.length <= 10`
- `ruleKey` is equal to either `"type"`, `"color"`, or `"name"`.
- All strings consist only of lowercase letters.

## 题目大意

给定一个数组 items，数组中的每一项 items[i] = [typei, colori, namei] 描述了类型、颜色、名称，给定两个字符串表示 ruleKey 和 ruleValue

第i 个item 如果满足下列条件之一，就认为是正确的

- `ruleKey == "type"` and `ruleValue == typei`.
- `ruleKey == "color"` and `ruleValue == colori`.
- `ruleKey == "name"` and `ruleValue == namei`.

返回满足给定条件的项目的数量

## 解题思路

这道题目比较简单

### Solution 1:

思路见代码，不难

`````c++
class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        // 首先根据ruleyKey 确定位置
        int pos = 0;
        if (ruleKey == "color") {
            pos = 1;
        } else if (ruleKey == "name") {
            pos = 2;
        }
        
        // 一次遍历进行统计
        int ans = 0;
        for (const auto item : items) {
            if (item[pos] == ruleValue) {
                ++ans;
            }
        }
        
        return ans;
    }
};
`````

