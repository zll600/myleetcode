# [690. Employee Importance](https://leetcode.com/problems/employee-importance/)

## 题目

You have a  data structure of employee information, including the employee's unique  ID, importance value, and direct subordinates' IDs.

You are given an array of employees `employees` where:

- `employees[i].id` is the ID of the `ith` employee.
- `employees[i].importance` is the importance value of the `ith` employee.
- `employees[i].subordinates` is a list of the IDs of the direct subordinates of the `ith` employee.

Given an integer `id` that represents an employee's ID, return *the **total** importance value of this employee and all their direct and indirect subordinates*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/31/emp1-tree.jpg)

```
Input: employees = [[1,5,[2,3]],[2,3,[]],[3,3,[]]], id = 1
Output: 11
Explanation: Employee 1 has an importance value of 5 and has two direct subordinates: employee 2 and employee 3.
They both have an importance value of 3.
Thus, the total importance value of employee 1 is 5 + 3 + 3 = 11.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/31/emp2-tree.jpg)

```
Input: employees = [[1,2,[5]],[5,-3,[]]], id = 5
Output: -3
Explanation: Employee 5 has an importance value of -3 and has no direct subordinates.
Thus, the total importance value of employee 5 is -3.
```

 

**Constraints:**

- `1 <= employees.length <= 2000`
- `1 <= employees[i].id <= 2000`
- All `employees[i].id` are **unique**.
- `-100 <= employees[i].importance <= 100`
- One employee has at most one direct leader and may have several subordinates.
- The IDs in `employees[i].subordinates` are valid IDs.

## 题目大意

给定一个保存员工信息的数据结构 `employees`，它包含了员工 唯一的 `id ，importance 和 subordinates` 的 id 。

给定一个 `employee` 的数组，其中:

- `employees[i].id` 是第 `i` 个员工的 ID
- `employees[i].importance` 是第 i 个员工的 importance value
- `employees[i].subordinates` 是第 i 个员工的所有直接下属的 `id`,

给定一个 `id` 表示一个员工的 ID，返回这个员工和他所有直接和间接下属的 importance value

## 解题思路

这道题目可以抽象为 树的遍历问题，因此可以这里可以考虑使用 DFS 和 BFS 来解决

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0690.Employee-Importance/)

````c++
/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        // 这里做一个记录，方便后面查找
        // id -> Employee*
        unordered_map<int, Employee*> records;
        for (Employee* employee : employees) {
            records[employee->id] = employee;
        }
        
        // BFS
        queue<int> ids;
        ids.push(id);
        
        // 保存最终的结果
        int res = 0;
        while (!ids.empty()) {
            Employee *employee = records[ids.front()];
            ids.pop();
            
            res += employee->importance;
            
            // 遍历所有的下属的id
            for (int subordinate_id : employee->subordinates) {
                ids.push(subordinate_id);
            }
        }
        
        return res;
    }
};
````
