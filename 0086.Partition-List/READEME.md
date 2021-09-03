# [86. Partition List](https://leetcode.com/problems/partition-list/)

## 题目

Given the `head` of a linked list and a value `x`, partition it such that all nodes **less than** `x` come before nodes **greater than or equal** to `x`.

You should **preserve** the original relative order of the nodes in each of the two partitions.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/04/partition.jpg)

```
Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
```

**Example 2:**

```
Input: head = [2,1], x = 2
Output: [1,2]
```

 

**Constraints:**

- The number of nodes in the list is in the range `[0, 200]`.
- `-100 <= Node.val <= 100`
- `-200 <= x <= 200`

## 题目大意

给定一个链表和一个值，调整链表是所有小于 x 的节点都出现在 大于等于 x 的前面，你必须在两部分中保留原来的顺序，

## 解题思路

* 可以建立两个链表，一个存储比 x 小的节点，一个存储 大于等于 x 的节点，最终将大于等于的节点，置于小于的节点之后，注意将最后一个节点的next 置空。
* 

## 代码

````
````



