# [18. 4Sum](https://leetcode.com/problems/4sum/)

## 题目

Given an array `nums` of `n` integers, return *an array of all the **unique** quadruplets* `[nums[a], nums[b], nums[c], nums[d]]` such that:

- `0 <= a, b, c, d < n`
- `a`, `b`, `c`, and `d` are **distinct**.
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

You may return the answer in **any order**.

 

**Example 1:**

```
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**Example 2:**

```
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
```

 

**Constraints:**

- `1 <= nums.length <= 200`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`

## 题目大意

给定一个整数数组，返回所有唯一的四元组，其和等于给定值

## 解题思路

* 这道题同样可以应用三数和的思路，用双指针，可以减少一层循环，

````c++
// 解法一：Two pointers
/* 
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {  
        int size = nums.size();
        if (size < 4) {
            return vector<vector<int>>();
        }
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        
        for (int a = 0; a < size - 3; ++a) {
            // 可以设置更多的优化条件
            if ((a > 0 && nums[a] == nums[a - 1])
               || nums[a] + nums[size - 3] + nums[size - 2] + nums[size - 1] < target) {
                continue;
            }
            for (int b = a + 1; b < size - 2; ++b) {
                // 同上进行优化
                if ((b > a + 1 && nums[b] == nums[b - 1])
                   || nums[a] + nums[b] + nums[size - 1] + nums[size - 2] < target) {
                    continue;
                }
                
                int c = b + 1;
                int d = size - 1;
                
                while (c < d) {
                    // 这里防止溢出，必须将右侧任意一个数提升为 long 类型
                    long sum = 1L * nums[a] + nums[b] + nums[c] + nums[d];
                    
                    if (sum == target) {
                        res.emplace_back(vector<int>{nums[a], nums[b], nums[c], nums[d]});
                        while (c < d && nums[d] == nums[--d]);
                        while (c < d && nums[c] == nums[++c]);
                    } else if (sum > target) {
                        while (c < d && nums[d] == nums[--d]);
                    } else {
                        while (c < d && nums[c] == nums[++c]);
                    }
                }
            }
        }
        return res;
    }
};
*/
````

## 泛化之后的求k数之和

```go
// 解法二 kSum
func fourSum1(nums []int, target int) [][]int {
	res, cur := make([][]int, 0), make([]int, 0)
	sort.Ints(nums)
	kSum(nums, 0, len(nums)-1, target, 4, cur, &res)
	return res
}

func kSum(nums []int, left, right int, target int, k int, cur []int, res *[][]int) {
	if right-left+1 < k || k < 2 || target < nums[left]*k || target > nums[right]*k {
		return
	}
	if k == 2 {
		// 2 sum
		twoSum(nums, left, right, target, cur, res)
	} else {
		for i := left; i < len(nums); i++ {
			if i == left || (i > left && nums[i-1] != nums[i]) {
				next := make([]int, len(cur))
				copy(next, cur)
				next = append(next, nums[i])
				kSum(nums, i+1, len(nums)-1, target-nums[i], k-1, next, res)
			}
		}
	}

}

func twoSum(nums []int, left, right int, target int, cur []int, res *[][]int) {
	for left < right {
		sum := nums[left] + nums[right]	// 这里可能溢出
		if sum == target {
			cur = append(cur, nums[left], nums[right])
			temp := make([]int, len(cur))
			copy(temp, cur)
			*res = append(*res, temp)
			// reset cur to previous state
			cur = cur[:len(cur)-2]
			left++
			right--
			for left < right && nums[left] == nums[left-1] {
				left++
			}
			for left < right && nums[right] == nums[right+1] {
				right--
			}
		} else if sum < target {
			left++
		} else {
			right--
		}
	}
}

// 解法三
// map 记录每个数字出现的次数，然后对 map 的 key 数组进行排序，最后在这个排序以后的数组里面扫，找到另外 3 个数字能和自己组成 0 的组合
func fourSum2(nums []int, target int) [][]int {
	res := [][]int{}
	counter := map[int]int{}
	for _, value := range nums {
		counter[value]++
	}

	uniqNums := []int{}
	for key := range counter {
		uniqNums = append(uniqNums, key)
	}
	sort.Ints(uniqNums)

	for i := 0; i < len(uniqNums); i++ {
		if (uniqNums[i]*4 == target) && counter[uniqNums[i]] >= 4 {
			res = append(res, []int{uniqNums[i], uniqNums[i], uniqNums[i], uniqNums[i]})
		}
		for j := i + 1; j < len(uniqNums); j++ {
			if (uniqNums[i]*3+uniqNums[j] == target) && counter[uniqNums[i]] > 2 {
				res = append(res, []int{uniqNums[i], uniqNums[i], uniqNums[i], uniqNums[j]})
			}
			if (uniqNums[j]*3+uniqNums[i] == target) && counter[uniqNums[j]] > 2 {
				res = append(res, []int{uniqNums[i], uniqNums[j], uniqNums[j], uniqNums[j]})
			}
			if (uniqNums[j]*2+uniqNums[i]*2 == target) && counter[uniqNums[j]] > 1 && counter[uniqNums[i]] > 1 {
				res = append(res, []int{uniqNums[i], uniqNums[i], uniqNums[j], uniqNums[j]})
			}
			for k := j + 1; k < len(uniqNums); k++ {
				if (uniqNums[i]*2+uniqNums[j]+uniqNums[k] == target) && counter[uniqNums[i]] > 1 {
					res = append(res, []int{uniqNums[i], uniqNums[i], uniqNums[j], uniqNums[k]})
				}
				if (uniqNums[j]*2+uniqNums[i]+uniqNums[k] == target) && counter[uniqNums[j]] > 1 {
					res = append(res, []int{uniqNums[i], uniqNums[j], uniqNums[j], uniqNums[k]})
				}
				if (uniqNums[k]*2+uniqNums[i]+uniqNums[j] == target) && counter[uniqNums[k]] > 1 {
					res = append(res, []int{uniqNums[i], uniqNums[j], uniqNums[k], uniqNums[k]})
				}
				c := target - uniqNums[i] - uniqNums[j] - uniqNums[k]
				if c > uniqNums[k] && counter[c] > 0 {
					res = append(res, []int{uniqNums[i], uniqNums[j], uniqNums[k], c})
				}
			}
		}
	}
	return res
}