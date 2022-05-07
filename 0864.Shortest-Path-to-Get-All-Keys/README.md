# [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/)

## 题目

You are given an `m x n` grid `grid` where:

- `'.'` is an empty cell.
- `'#'` is a wall.
- `'@'` is the starting point.
- Lowercase letters represent keys.
- Uppercase letters represent locks.

You start at the starting point and one move consists of walking one  space in one of the four cardinal directions. You cannot walk outside  the grid, or walk into a wall.

If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.

For some `1 <= k <= 6`, there is exactly one lowercase and one uppercase letter of the first `k` letters of the English alphabet in the grid. This means that there is  exactly one key for each lock, and one lock for each key; and also that  the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

Return *the lowest number of moves to acquire all keys*. If it is impossible, return `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-keys2.jpg)

```
Input: grid = ["@.a.#","###.#","b.A.B"]
Output: 8
Explanation: Note that the goal is to obtain all the keys not to open all the locks.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-key2.jpg)

```
Input: grid = ["@..aA","..B#.","....b"]
Output: 6
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-keys3.jpg)

```
Input: grid = ["@Aa"]
Output: -1
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 30`
- `grid[i][j]` is either an English letter, `'.'`, `'#'`, or `'@'`.
- The number of keys in the grid is in the range `[1, 6]`.
- Each key in the grid is **unique**.
- Each key in the grid has a matching lock.

## 题目大意

给定一个 `m x n` 网格 `grid`

- “.” 代表一个空房间
- “#” 代表一堵墙 
- “@” 是起点
- 小写字母代表钥匙
- 大写字母代表锁

你从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。我们不能在网格外面行走，也无法穿过一堵墙

如果途经一个钥匙，我们就把它捡起来。除非我们手里有对应的钥匙，否则无法通过锁

假设 `k` 为钥匙/锁的个数，且满足 `1 <= K <= 6`，字母表中的前 `k` 个字母在网格中都有自己对应的一个小写和一个大写字母。换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。另外，代表钥匙和锁的字母互为大小写并按字母顺序排列

返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 

## 解题思路

这道题目的状态就是 坐标+钥匙，在整个 bfs 的过程中需要维护这个变量

### Solution 1: BFS

这里同样需要设置 访问标记数组，防止发生循环访问

在绕过墙之后，利用当前状态判断，如果当前位置是锁，能否解开

这种解法的难点在在于这里使用了位运算的技巧，将状态进行了压缩，使得不那么好理解

````Go
func shortestPathAllKeys(grid []string) int {
    if len(grid) == 0 {
        return 0
    }
    m, n := len(grid), len(grid[0])
    
    matrix := make([][]byte, m)
    for i := 0; i < m; i++ {
        matrix[i] = make([]byte, n)
    }
    
    // fullKeys 用来保持状态
    startX, startY, fullKeys := 0, 0, 0
    for i, str := range grid {
        matrix[i] = []byte(str)
        
        for _, c := range str {
            if c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' {
                fullKeys |= (1 << uint(c - 'a'))
            }
        }
        if strings.Contains(str, "@") {
            startX, startY = i, strings.Index(str, "@")
        }
    }
    
    visited := make([][][]bool, m)
    for i := 0; i < m; i++ {
        visited[i] = make([][]bool, n)
    }
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            visited[i][j] = make([]bool, 64)
        }
    }
    
    // BFS
    // 队列中存储的是 坐标 + 状态之后的压缩值
    que := []int{}
    que = append(que, (startY << 16 | startX << 8))
    visited[startX][startY][0] = true
    
    // 方向数组
    dirs := []int{0, 1, 0, -1, 0}
    res := 0
    for len(que) > 0 {
        qLen := len(que)
        for i := 0; i < qLen; i++ {
            state := que[0]
            que = que[1:]
            startY, startX = state >> 16, (state >> 8) & 0xff
            keys := state & 0xff
            
            if keys == fullKeys {
                return res
            }
            
            for i := 0; i < 4; i++ {
                newState := keys
                nx := startX + dirs[i]
                ny := startY + dirs[i + 1]
                
                if !isInMatrix(matrix, nx, ny) || matrix[nx][ny] == '#' {
                    continue
                }
                
                flag, canThrougLock := keys & (1 << (matrix[nx][ny] - 'A')), false
                // 如果可以解锁的话
                if flag != 0 {
                    canThrougLock = true
                }
                
                // 如果是锁且无法没有对应钥匙的话
                if isLock(matrix, nx, ny) && !canThrougLock {
                    continue
                }
                // 如果是钥匙，更新状态
                if isKey(matrix, nx, ny) {
                    newState |= (1 << (matrix[nx][ny] - 'a'))
                }
                if visited[nx][ny][newState] {
                    continue
                }
                
                que = append(que, (ny << 16) | (nx << 8) | newState)
                visited[nx][ny][newState] = true
            }
        }
        res++
    }
    return -1
}

func isInMatrix(matrix [][]byte, x, y int) bool {
    m, n := len(matrix), len(matrix[0])
    
    return x >= 0 && x < m && y >= 0 && y < n
}


func isLock(matrix [][]byte, x, y int) bool {
    if matrix[x][y] == 'A' || matrix[x][y] == 'B' ||
    matrix[x][y] == 'C' || matrix[x][y] == 'D' ||
    matrix[x][y] == 'E' || matrix[x][y] == 'F' {
        return true;
    }
    return false
}

func isKey(matrix [][]byte, x, y int) bool {
    if matrix[x][y] == 'a' || matrix[x][y] == 'b' ||
    matrix[x][y] == 'c' || matrix[x][y] == 'd' ||
    matrix[x][y] == 'e' || matrix[x][y] == 'f' {
        return true;
    }
    return false
}
````
