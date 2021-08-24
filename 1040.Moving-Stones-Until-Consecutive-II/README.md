# [1040. Moving Stones Until Consecutive II](https://leetcode.com/problems/moving-stones-until-consecutive-ii/)

## 题目

There are some stones in different positions on the X-axis. You are given an integer array `stones`, the positions of the stones.

Call a stone an **endpoint stone** if it has the smallest or largest position. In one move, you pick up an **endpoint stone** and move it to an unoccupied position so that it is no longer an **endpoint stone**.

- In particular, if the stones are at say, `stones = [1,2,5]`, you cannot move the endpoint stone at position `5`, since moving it to any position (such as `0`, or `3`) will still keep that stone as an endpoint stone.

The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).

Return *an integer array* `answer` *of length* `2` *where*:

- `answer[0]` *is the minimum number of moves you can play, and*
- `answer[1]` *is the maximum number of moves you can play*.

 

**Example 1:**

```
Input: stones = [7,4,9]
Output: [1,2]
Explanation: We can move 4 -> 8 for one move to finish the game.
Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
```

**Example 2:**

```
Input: stones = [6,5,4,3,10]
Output: [2,3]
Explanation: We can move 3 -> 8 then 10 -> 7 to finish the game.
Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
```

 

**Constraints:**

- `3 <= stones.length <= 104`
- `1 <= stones[i] <= 109`
- All the values of `stones` are **unique**.

## 题目大意

给定一个关于石头位置的数组，如果一块石头处于最小或者最大位置，则称这个石头为端点石头，每一次移动，你可以选择一个端点石头，将其移动到一个未占用的位置，使其不再是一个端点石头，当你无法移动任何石头时，游戏结束，即所有石头处于连续的位置,

* 特别的，如果一个数组如：[1,2,5]，你不能移动位置5上的石头，因为无论你将它移动到任何地方（如：0或者3），它依旧是一个端点石头，

返回一个整数数组:answer = [min_movements, max_movements].

## 解题思路

* 给定一个数组，数组中存储的是石头的坐标，要求移动石头，最终使这些石头的坐标是一个连续的自然数序列，但是当一个石头是端点石头的时候是不能移动的
* 这道题的关键是如何**保证端点石头不能再次移动到端点**的限制。例如：[5,6,8,20]，20是端点，但是 20 就可以移动到 7 的位置，最终形成 [5,6,7,8,9]的连续序列。但是 [5,6,7,8,20]，这种情况 20 就不能移动到 9 了，只能让 8 移动到 9， 20 再移动到 8 的位置，最终还是形成 [5,6,7,8,9]，但是步数需要 2 步，可以总结为：端点石头只能往中间空档的位置移动，如果中间没有空档，那么需要借助一个石头先制造一个空档，然后将端点石头再插入到中间，所以端点石头插入最少需要 2 步。
* 再来考虑极值的情况。先看最大步数，最大步数往往需要慢慢移动，每次移动一格，并且移动的格数最多。这里有两个极端情况，把数组里面的数，全部移动到最左端点，把数组里面的数全部移动到最右端点，每次只移动一格。例如，全部都移到最右端点：

````
	[3,4,5,6,10] // 初始状态，连续的情况
	[4,5,6,7,10] // 第一步，把 3 移到右边第一个可以插入的位置，即 7
	[5,6,7,8,10] // 第二部，把 4 移到右边第一个可以插入的位置，即 8
	[6,7,8,9,10] // 第三步，把 5 移到右边第一个可以插入的位置，即 9
	
	
	[1,3,5,7,10] // 初始状态，不连续的状态
	[3,4,5,7,10] // 第一步，把 1 移到右边第一个可以插入的位置，即 4
	[4,5,6,7,10] // 第二部，把 3 移到右边第一个可以插入的位置，即 6
	[5,6,7,8,10] // 第三步，把 4 移到右边第一个可以插入的位置，即 8
	[6,7,8,9,10] // 第四步，把 5 移到右边第一个可以插入的位置，即 9
````

​	移动的过程类似于翻滚，最左边的石头移动到右边第一个可以放下的地方。然后不断的往右翻滚。把数组中的数，全部都移动到最左边也同理。找出二者的最大	值，就是移动的最大步数 。

* 再看最小步数，这里就要利用“滑动窗口”。由于最终最终要形成连续的自然数列，所以滑动窗口的大小就为固定的 size ，从数组的 0 下标可以往右滑动滑动窗口，这个窗口能包含的数字越多，代表窗口外的数字越少，那么把这些数字放进窗口内的步数也最小。于是可以求得最小步数。这里有一个需要**注意**的地方，就是题目中的`端点不能移动之后还是端点`的限制。针对这种情况，需要附加额外的判断：如果当前窗口中已经有 size - 1 个元素了，即只有一个端点再窗外，并且窗口右边界减去左边界的值也等于 size - 1， 代表这个窗口已经都是连续数字了。这种情况，想移动端点石头，至少需要两步
* 注意一些边界情况。如果窗口从左往右滑动，窗口右边界滑到最右边了，但是窗口右边界的数字减去左边界的数字还是小于窗口大小 n，代表已经滑到头了，可以直接 break 出去。为什么滑到头了呢？由于数组经过从小到大排序以后，数字越往右边越大，当前数字是小值，已经满足了 `stones[right]-stones[left] < n`，左边界继续往右移动只会使得 `stones[left]` 更大，就更加小于 n 了。而我们需要寻找的是 `stones[right]-stones[left] >= n` 的边界点，肯定再也找不到了。
* 注意一些边界情况。如果窗口从左向右滑动，窗口右边界滑到最右边了，但是窗口右边界的数字减去左边界的数字还是小于窗口大小 size，代表已经滑到头了。可以直接 break 出去。为什么滑到头了呢？由于数组经过排序后，数字越往右，越大，当前数字是小值，已经满足了 stone[right] - stone[left] < n，左边界继续往右移动只会使得 stones[left] 更大，就更加小于  size 了，而我们需要寻找的是 stones[right] - stones[left] >= n 的边界点，肯定找不到了

## 代码

````c++
class Solution {
public:    
    vector<int> numMovesStonesII(vector<int>& stones) {
        int size = stones.size();
        sort(stones.begin(), stones.end());
        
        int left = 0;
        int right = 0;
        int res = 0;
        int max_steps = max(stones[size - 1] - stones[1] - size + 2,
                            stones[size - 2] - stones[0] - size + 2);
        int min_steps = size + 1;
        
        while (left < size) {
            if (right < size - 1 && stones[right] - stones[left] < size) {
                ++right;
            } else {
                if (stones[right] - stones[left] >= size) {
                    --right;
                }
                
                if (right - left + 1 == size - 1
                    && stones[right] - stones[left] + 1 == size - 1) {
                    min_steps = min(min_steps, 2);
                } else {
                    min_steps = min(min_steps, size - (right - left + 1));
                }
                
                if (right == size - 1 && stones[right] - stones[left] < size) {
                    break;
                }
                ++left;
            }
        }
        
        return vector<int>{min_steps, max_steps};
    }
};
````

