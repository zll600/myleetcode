# [957. Prison Cells After N Days](https://leetcode.cn/problems/prison-cells-after-n-days/)

## 题目

There are `8` prison cells in a row and each cell is either occupied or vacant.

Each day, whether the cell is occupied or vacant changes according to the following rules:

- If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
- Otherwise, it becomes vacant.

**Note** that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.

You are given an integer array `cells` where `cells[i] == 1` if the `ith` cell is occupied and `cells[i] == 0` if the `ith` cell is vacant, and you are given an integer `n`.

Return the state of the prison after `n` days (i.e., `n` such changes described above).

 

**Example 1:**

```
Input: cells = [0,1,0,1,1,0,0,1], n = 7
Output: [0,0,1,1,0,0,0,0]
Explanation: The following table summarizes the state of the prison on each day:
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
```

**Example 2:**

```
Input: cells = [1,0,0,1,0,0,1,0], n = 1000000000
Output: [0,0,1,1,1,1,1,0]
```

 

**Constraints:**

- `cells.length == 8`
- `cells[i]` is either `0` or `1`.
- `1 <= n <= 109`

## 题目大意

`8` 间牢房排成一排，每间牢房不是有人住就是空着

每天，无论牢房是被占用或空置，都会根据以下规则进行更改：

-   如果一间牢房的两个相邻的房间都被占用或都是空的，那么该牢房就会被占用
-   否则，它就会被空置

（请注意，由于监狱中的牢房排成一行，所以行中的第一个和最后一个房间无法有两个相邻的房间。）

我们用以下方式描述监狱的当前状态：如果第 i 间牢房被占用，则 cell[i]==1，否则 cell[i]==0

根据监狱的初始状态，在 N 天后返回监狱的状况（和上述 N 种变化）

## 解题思路


### Solution 1: TLE

暴力解法，超时了

````c++
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<int> other_cells(8, 0);
        
        while (n > 0) {
            cout << other_cells[0] << " -- ";
            for (int i = 1; i < 7; ++i) {
                if ((cells[i - 1] == 1 && cells[i + 1] == 1)
                || (cells[i - 1] == 0 && cells[i + 1] == 0)) {
                    other_cells[i] = 1;
                } else {
                    other_cells[i] = 0;
                }
                cout << other_cells[i] << " -- ";
            }
            cout << other_cells[7] << endl;
            cells.swap(other_cells);
            other_cells[0] = 0;
            other_cells[7] = 0;
            --n;
        }
        return cells;
    }
};
````

### Solution 2:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/prison-cells-after-n-days/solution/mo-ni-ji-suan-zhou-qi-ha-xi-biao-xiang-x-th6w/)

这种解法利用记忆化查找周期

````c++
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        // 第几天 --> cells
        unordered_map<int, vector<int>> records;
        // 加入第 0 天
        records.emplace(0, cells);

        // 开始遍历
        for (int i = 1; i <= n; ++i) {
            // 第一天需要将首尾置 0
            if (i == 1) {
                cells[0] = 0;
                cells[7] = 0;
            }

            // 改变状态
            for (int j = 1; j < 7; ++j) {
                if (records[i - 1][j - 1] == 0 && records[i - 1][j + 1] == 0) {
                    cells[j] = 1;
                } else if (records[i - 1][j - 1] == 1 && records[i - 1][j + 1] == 1) {
                    cells[j] = 1;
                } else {
                    cells[j] = 0;
                }
            }
            records.emplace(i, cells);

            // 和 第一天相比 是否出现周期
            bool flag = true;
            for (int j = 0; j < 8; ++j) {
                if (cells[j] != records[1][j]) {
                    flag = false;
                    break;
                }
            }

            // 如果出现周期
            if (i > 1 && flag) {
                if (n % (i - 1) == 0) {
                    // 可以整数，返回上一种状态
                    return records[i - 1];
                } else {
                    return records[n % (i - 1)];
                }
            }
        }
        return cells;
    }
};
````
