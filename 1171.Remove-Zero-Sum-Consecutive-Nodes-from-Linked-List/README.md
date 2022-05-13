# [1171. Remove Zero Sum Consecutive Nodes from Linked List](https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/)

## 题目

Given the `head` of a linked list, we repeatedly delete consecutive sequences of nodes that sum to `0` until there are no such sequences.

After doing so, return the head of the final linked list. You may return any such answer.

 

(Note that in the examples below, all sequences are serializations of `ListNode` objects.)

**Example 1:**

```
Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
```

**Example 2:**

```
Input: head = [1,2,3,-3,4]
Output: [1,2,4]
```

**Example 3:**

```
Input: head = [1,2,3,-3,-2]
Output: [1]
```

 

**Constraints:**

- The given linked list will contain between `1` and `1000` nodes.
- Each node in the linked list has `-1000 <= node.val <= 1000`.

## 题目

给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。删除完毕后，请你返回最终结果链表的头节点。你可以返回任何满足题目要求的答案。

（注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）

## 解题思路

看到累加和为 0，就可以想到可能会使用前缀和来计算，降低时间复杂度

### Solution 1: PrefixSum

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1171.Remove-Zero-Sum-Consecutive-Nodes-from-Linked-List/)

如果出现连续的节点累加和为 0，那么前缀和数组中就会出现同样的值两次，因为每次前缀和中出现相同的值，就会进行删除操作，所以这里每次都是重新计算前缀和

这里通过一个 map 来存储 前缀和 和 参与的节点数，

删除的时候，从头节点开始遍历，遍历到要删除节点的前驱节点

这是上面的这些不能处理整个链表的累加和为 0 的情况，所以这种情况需要做特殊处理，

````Go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func removeZeroSumSublists(head *ListNode) *ListNode {
    // 如果为空直接返回
    if head == nil {
        return nil
    }

    // h 逐个遍历每个节点
    // prefixSumMap  key 是前缀和 val 是组成这样的前缀和 使用了几个节点
    h, prefixSumMap, sum, counter, lastNode := head, map[int]int{}, 0, 0, &ListNode{Val: 1010}
    // 循环遍历
    for h != nil {
        // 每次选择一个新的起点开始遍历
        for h != nil {
            // 累加和
            sum += h.Val
            // 计数
            counter++

            // 如果这个累加和之前出现过
            if val, ok := prefixSumMap[sum]; ok {
                lastNode, counter = h, val
                break
            }
            // 如果累加和为0，说明当前的整个链表累加和为 0
            if sum == 0 {
                head = h.Next
                break
            }
            prefixSumMap[sum] = counter
            h = h.Next
        }

        // 删除
        if lastNode.Val != 1010 {
            h = head
            for counter > 1 {
                counter--
                h = h.Next
            }
            h.Next = lastNode.Next
        }
        // 如果整个链表为空
        if h != nil {
            h, prefixSumMap, sum, counter, lastNode = head, map[int]int{}, 0, 0, &ListNode{Val: 1010}
        }
    }
    return head
}
````
