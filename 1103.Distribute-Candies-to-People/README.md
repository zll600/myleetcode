# [1103. Distribute Candies to People](https://leetcode-cn.com/problems/distribute-candies-to-people/)

## 题目

We distribute some number of `candies`, to a row of **`n = num_people`** people in the following way:

We then give 1 candy to the first person, 2 candies to the second person, and so on until we give `n` candies to the last person.

Then, we go back to the start of the row, giving `n + 1` candies to the first person, `n + 2` candies to the second person, and so on until we give `2 * n` candies to the last person.

This process repeats (with us giving one more candy each time, and  moving to the start of the row after we reach the end) until we run out  of candies. The last person will receive all of our remaining candies  (not necessarily one more than the previous gift).

Return an array (of length `num_people` and sum `candies`) that represents the final distribution of candies.

 

**Example 1:**

```
Input: candies = 7, num_people = 4
Output: [1,2,3,1]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0,0].
On the third turn, ans[2] += 3, and the array is [1,2,3,0].
On the fourth turn, ans[3] += 1 (because there is only one candy left), and the final array is [1,2,3,1].
```

**Example 2:**

```
Input: candies = 10, num_people = 3
Output: [5,2,3]
Explanation: 
On the first turn, ans[0] += 1, and the array is [1,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0].
On the third turn, ans[2] += 3, and the array is [1,2,3].
On the fourth turn, ans[0] += 4, and the final array is [5,2,3].
```

 

**Constraints:**

- 1 <= candies <= 10^9
- 1 <= num_people <= 1000

## 题目大意

我们买了一些糖果 `candies`，打算把它们分给排好队的 `n = num_people` 个小朋友

给第一个小朋友 `1` 颗糖果，第二个小朋友 `2` 颗，依此类推，直到给最后一个小朋友 `n` 颗糖果

然后，我们再回到队伍的起点，给第一个小朋友 `n + 1` 颗糖果，第二个小朋友 `n + 2` 颗，依此类推，直到给最后一个小朋友 `2 * n` 颗糖果。

重复上述过程（每次都比上一次多给出一颗糖果，当到达队伍终点后再次从队伍起点开始），直到我们分完所有的糖果

注意，就算我们手中的剩下糖果数不够（不比前一次发出的糖果多），这些糖果也会全部发给当前的小朋友

返回一个长度为 `num_people`、元素之和为 `candies` 的数组，以表示糖果的最终分发情况（即 `ans[i]` 表示第 `i` 个小朋友分到的糖果数）。

## 解题思路

### Solution 1:

这道题目比较简单，根据题意来做就可以了

这里需要注意的就是每个位置分配 糖果的时候，需要注意理论上需要分配的数目和剩余的糖果数目取较小值

````python3
class Solution:
    def distributeCandies(self, candies: int, num_people: int) -> List[int]:
        # create a list with size of num_people
        kids = [0] * num_people
        i = 0
        
        while candies > 0:
            # distribute candies to each position
            # choose min count
            kids[i % num_people] += min(i + 1, candies)
            
            candies -= i + 1
            i += 1
        
        return kids
````
