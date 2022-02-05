# [478. Generate Random Point in a Circle](https://leetcode.com/problems/generate-random-point-in-a-circle/)

## 题目

Given the radius and the position of the center of a circle, implement the function `randPoint` which generates a uniform random point inside the circle.

Implement the `Solution` class:

- `Solution(double radius, double x_center, double y_center)` initializes the object with the radius of the circle `radius` and the position of the center `(x_center, y_center)`.
- `randPoint()` returns a random point inside the circle. A point on the circumference of the circle is considered to be in the circle. The answer is returned as an array `[x, y]`.

 

**Example 1:**

```
Input
["Solution", "randPoint", "randPoint", "randPoint"]
[[1.0, 0.0, 0.0], [], [], []]
Output
[null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]

Explanation
Solution solution = new Solution(1.0, 0.0, 0.0);
solution.randPoint(); // return [-0.02493, -0.38077]
solution.randPoint(); // return [0.82314, 0.38945]
solution.randPoint(); // return [0.36572, 0.17248]
```

 

**Constraints:**

- `0 < radius <= 108`
- `-107 <= x_center, y_center <= 107`
- At most `3 * 104` calls will be made to `randPoint`.

## 题目大意

给定一个圆的圆心和半径，实现 `randPoint` 函数在这个圆范围内产生一个随机数，

实现 `Solution` 类：

- `Solution(double radius, double x_center, double y_center)` 用半径 `radius` 和 圆心 `(x_center, y_center)` 初始化对象
- `randPoint()` 返回圆中的一个随机点，圆上的点被认为在圆中，按照 `[x, y]` 的形式返回答案

## 解题思路

这道题目的核心思路是先利用 `(0, 0)` 为圆心，找出符合条件的坐标，然后在加上 圆心坐标作为偏移，

这道题目也可以参考 [这篇题解](https://leetcode-cn.com/problems/generate-random-point-in-a-circle/solution/c-tui-dao-gai-lu-fen-bu-by-vclip-wp0z/)

### Solution 1:

这种解法从测试用例来看的话，精度上是有问题的，但是目前没有找到原因，下面给出了 go 的版本，是可以通过的，

````c++
class Solution {
public:
    Solution(double radius, double x_center, double y_center) 
        : radius_(radius),
        x_center_(x_center),
        y_center_(y_center) {
    }
    
    vector<double> randPoint() {
        uniform_real_distribution<double> rand(0, 1.0000000);
        double nx = 0.0, ny = 0.0;
        double dx = 0.0, dy = 0.0;
        while (dx * dx + dy * dy > radius_ * radius_) {
            nx = 2.0 * rand(engine_) - 1.0;
            ny = 2.0 * rand(engine_) - 1.0;
            dx = radius_ * nx;
            dy = radius_ * ny;
        }
        return {x_center_ + dx, y_center_ + dy};
    }
    
 private:
    int radius_;
    int x_center_;
    int y_center_;
    default_random_engine engine_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */
````

### Solution 2:

[这种解法](https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0478.Generate-Random-Point-in-a-Circle/)，是可以通过的，

````go
type Solution struct {
	r float64
	x float64
	y float64
}

func Constructor(radius float64, x_center float64, y_center float64) Solution {
	rand.Seed(time.Now().UnixNano())
	return Solution{radius, x_center, y_center}
}

func (this *Solution) RandPoint() []float64 {
	/*
	   a := angle()
	   r := this.r * math.Sqrt(rand.Float64())
	   x := r * math.Cos(a) + this.x
	   y := r * math.Sin(a) + this.y
	   return []float64{x, y}*/
	for {
		rx := 2*rand.Float64() - 1.0
		ry := 2*rand.Float64() - 1.0
		x := this.r * rx
		y := this.r * ry
		if x*x+y*y <= this.r*this.r {
			return []float64{x + this.x, y + this.y}
		}
	}
}

func angle() float64 {
	return rand.Float64() * 2 * math.Pi
}

/**
 * Your Solution object will be instantiated and called as such:
 * obj := Constructor(radius, x_center, y_center);
 * param_1 := obj.RandPoint();
 */
````
