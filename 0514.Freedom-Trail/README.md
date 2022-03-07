# [514. Freedom Trail](https://leetcode-cn.com/problems/freedom-trail/)



In the video game Fallout 4, the quest **"Road to Freedom"** requires players to reach a metal dial called the **"Freedom Trail Ring"** and use the dial to spell a specific keyword to open the door.

Given a string `ring` that represents the code engraved on the outer ring and another string `key` that represents the keyword that needs to be spelled, return *the minimum number of steps to spell all the characters in the keyword*.

Initially, the first character of the ring is aligned at the `"12:00"` direction. You should spell all the characters in `key` one by one by rotating `ring` clockwise or anticlockwise to make each character of the string key aligned at the `"12:00"` direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character `key[i]`:

1. You can rotate the ring clockwise or anticlockwise by one place, which counts as **one step**. The final purpose of the rotation is to align one of `ring`'s characters at the `"12:00"` direction, where this character must equal `key[i]`.
2. If the character `key[i]` has been aligned at the `"12:00"` direction, press the center button to spell, which also counts as **one step**. After the pressing, you could begin to spell the next character in the key (next stage). Otherwise, you have finished all the spelling.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/22/ring.jpg)

```
Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
Also, we need 1 more step for spelling.
So the final output is 4.
```

**Example 2:**

```
Input: ring = "godding", key = "godding"
Output: 13
```

 

**Constraints:**

- `1 <= ring.length, key.length <= 100`
- `ring` and `key` consist of only lower case English letters.
- It is guaranteed that `key` could always be spelled by rotating `ring`.

## 题目大意

电子游戏“辐射4”中，任务 “通向自由” 要求玩家到达名为 “Freedom Trail Ring” 的金属表盘，并使用表盘拼写特定关键词才能开门。

给定一个字符串 `ring` ，表示刻在外环上的编码；给定另一个字符串 `key` ，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。

最初，`ring` 的第一个字符与 `12:00` 方向对齐。您需要顺时针或逆时针旋转 `ring` 以使 `key` 的一个字符在 `12:00` 方向对齐，然后按下中心按钮，以此逐个拼写完 `key` 中的所有字符。

旋转 `ring` 拼出 `key` 字符 `key[i]` 的阶段中：

您可以将 `ring` 顺时针或逆时针旋转 一个位置 ，计为1步。旋转的最终目的是将字符串 `ring` 的一个字符与 `12:00` 方向对齐，并且这个字符必须等于字符 `key[i]` 。
如果字符 `key[i]` 已经对齐到 `12:00` 方向，您需要按下中心按钮进行拼写，这也将算作 `1` 步。按完之后，您可以开始拼写 `key` 的下一个字符（下一阶段）, 直至完成所有拼写。

## 解题思路

这里我们解决的问题有

1. 每个key 中的字符都需要一步
2. 每次将匹配的字符旋转到 12点的位置，都有两种方法，我们选择较小的一种，

### Solution 1: DFS

这种解法可以参考i [这篇题解](https://leetcode-cn.com/problems/freedom-trail/solution/shou-hua-tu-jie-di-gui-ji-yi-hua-di-gui-514-zi-you/)

这里的话 c++ 有些问题，会有些差异，这里直接用了题解的 go 答案，后面二刷会进行修正

````go
func findRotateSteps(ring string, key string) int {
	indexMap := make([][]int, 26) // ring中的字符在ring中的索引集合
	for i, c := range ring { // 遍历ring
		cInt := c - 'a'      // 用一个int数代表当前字符
		indexMap[cInt] = append(indexMap[cInt], i) // 索引i加入对应的索引集合
	}

	memo := make([][]int, len(ring)) // memo二维数组，长度为ring的长度
	for i, _ := range memo {
		memo[i] = make([]int, len(key)) // 子数组是数组，长度为key长度
		for j, _ := range memo[i] {
			memo[i][j] = -1	// 初始填充-1，区别于距离（非负）
		}
	}
	var dfs func(ringI, keyI int) int
	// 当前12点对齐了ringI，对齐key[keyI]到key末尾字符，所需的最少步数
	dfs = func(ringI, keyI int) int {
		if keyI == len(key) { // 扫描key字符串的指针越界，返回步数0
			return 0
		}
		if memo[ringI][keyI] != -1 { // memo中有直接用memo的
			return memo[ringI][keyI]
		}
		cur := key[keyI]    // 当前想对齐的key字符
		curInt := cur - 'a' // 对应的int数
		res := math.MaxInt32 // 当前子问题的解
		// 遍历key[keyI]在ring中的索引数组，targetI是当前要对齐的目标索引
		for _, targetI := range indexMap[curInt] {
			d1 := abs(ringI - targetI)  // 从对齐ringI到对齐targetI的距离1
			d2 := len(ring) - d1   // 从对齐ringI到对齐targetI的距离2
			curMin := min(d1, d2)  // 取二者中的较小值
			res = min(res, curMin + dfs(targetI, keyI+1))// 当前targetI的解，试图刷新res
		}
		memo[ringI][keyI] = res  // 算出一个子问题的解，存入memo
		return res
	}

	return len(key) + dfs(0, 0) // 递归的入口
}

func abs(a int) int {
	if a < 0 {return -a}
	return a
}
func min(a, b int) int {
	if a > b {return b}
	return a
}

````
