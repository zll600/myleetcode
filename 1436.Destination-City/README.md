# [1436. Destination City](https://leetcode.com/problems/destination-city/)

You are given the array `paths`, where `paths[i] = [cityAi, cityBi]` means there exists a direct path going from `cityAi` to `cityBi`. *Return the destination city, that is, the city without any path outgoing to another city.*

It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.

 

**Example 1:**

```
Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
Output: "Sao Paulo" 
Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".
```

**Example 2:**

```
Input: paths = [["B","C"],["D","B"],["C","A"]]
Output: "A"
Explanation: All possible trips are: 
"D" -> "B" -> "C" -> "A". 
"B" -> "C" -> "A". 
"C" -> "A". 
"A". 
Clearly the destination city is "A".
```

**Example 3:**

```
Input: paths = [["A","Z"]]
Output: "Z"
```

 

**Constraints:**

- `1 <= paths.length <= 100`
- `paths[i].length == 2`
- `1 <= cityAi.length, cityBi.length <= 10`
- `cityAi != cityBi`
- All strings consist of lowercase and uppercase English letters and the space character.

## 题目大意

给定一个数组 paths，其中`paths[i] = [cityAi, cityBi]` 表示存在一条直接的路径从 cityAi 到 cityBi，返回不通往任何城市的终点城市

题目保证存在一条不存在环的路线，因此只会有一个目的地

## 解体思路

找出只出现在 目的地，而没有出现在出发地的城市

### 解法1

这里的思路可以参见代码，并不是很难

`````c++
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> dsts;
        // 将所有的出发地加入道 set 中
        for (const vector<string>& path : paths) {
            dsts.insert(path[0]);
        }
        
        // 如果出现在 目的地 却没有出现在 出发地的就是最终的目的地
        for (const vector<string>& path : paths) {
            if (dsts.find(path[1]) == dsts.end()) {
                return path[1];
            }
        }
        
        return "";
    }
};
`````

