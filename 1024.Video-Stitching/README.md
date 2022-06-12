# [1024. Video Stitching](https://leetcode.cn/problems/video-stitching/)

## 题目

You are given a series of video clips from a sporting event that lasted `time` seconds. These video clips can be overlapping with each other and have varying lengths.

Each video clip is described by an array `clips` where `clips[i] = [starti, endi]` indicates that the ith clip started at `starti` and ended at `endi`.

We can cut these clips into segments freely.

- For example, a clip `[0, 7]` can be cut into segments `[0, 1] + [1, 3] + [3, 7]`.

Return *the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event* `[0, time]`. If the task is impossible, return `-1`.

 

**Example 1:**

```
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
Output: 3
Explanation: We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
```

**Example 2:**

```
Input: clips = [[0,1],[1,2]], time = 5
Output: -1
Explanation: We cannot cover [0,5] with only [0,1] and [1,2].
```

**Example 3:**

```
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
Output: 3
Explanation: We can take clips [0,4], [4,7], and [6,9].
```

 

**Constraints:**

- `1 <= clips.length <= 100`
- `0 <= starti <= endi <= 100`
- `1 <= time <= 100`

## 题目大意

你将会获得一系列视频片段，这些片段来自于一项持续时长为 `time` 秒的体育赛事。这些片段可能有所重叠，也可能长度不一

使用数组 `clips` 描述所有的视频片段，其中 `clips[i] = [starti, endi]` 表示：某个视频片段开始于 `starti` 并于 `endi` 结束

甚至可以对这些片段自由地再剪辑：

-   例如，片段 `[0, 7]` 可以剪切成 `[0, 1] + [1, 3] + [3, 7]` 三部分

我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段 `（[0, time]）` 。返回所需片段的最小数目，如果无法完成该任务，则返回 `-1`

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/video-stitching/solution/shou-hua-tu-jie-dong-tai-gui-hua-si-lu-pou-xi-xian/)

这里 `dp[j]` 表示拼接 `[0, j]` 所需片段的最小数目，这里需要做的就是遍历每一个片段，更新 dp[j]，dp[j] 必须是从前向后更新，所以这里也需要将数组按照 start 时间进行排序

下面思考一下状态转移：

对于每一个片段 [start, end]

- 如果 start 不可达，那么就设置一个不可达标志，这里使用的是 101
- 如果 start 可达，
    - 如果 j 是第一次到达，那么 dp[j] = dp[start] + 1
    - 如果 j 不是第一次到达，那么 dp[j] = min(dp[j], dp[start] + 1)

如果将dp 数组初始化为 101, 那么就可以得到 dp[j] = min(dp[j], dp[start] + 1)

````javascript

/**
 * @param {number[][]} clips
 * @param {number} time
 * @return {number}
 */
var videoStitching = function(clips, T) {
    clips.sort((a, b) => a[0] - b[0]); // 按开始时间从小到大排序
  // dp[j]：涵盖[0:j]需要的clip的最少个数，目标是求dp[T]，初始值为101，大于所有可能值
  const dp = new Array(T + 1).fill(101);
  dp[0] = 0; // 涵盖[0:0]不需要clip，所以为0

  for (let i = 0; i < clips.length; i++) { // 遍历每个片段
    const [start, end] = clips[i];         // 获取当前片段的开始和结束时间
    if (dp[start] == 101) { // 该片段上都覆盖不了，直接退出循环，保持为101
      break;
    }
    for (let j = start + 1; j <= end; j++) { // 计算当前片段上每个点的dp[j]
      dp[j] = Math.min(dp[j], dp[start] + 1);
    }
  }

  if (dp[T] == 101) {
    return -1;
  }
  return dp[T];
};
`````

