# [1603. Design Parking System](https://leetcode.com/problems/design-parking-system/)

## 题目

Design a  parking system for a parking lot. The parking lot has three kinds of  parking spaces: big, medium, and small, with a fixed number of slots for each size.

Implement the `ParkingSystem` class:

- `ParkingSystem(int big, int medium, int small)` Initializes object of the `ParkingSystem` class. The number of slots for each parking space are given as part of the constructor.
- `bool addCar(int carType)` Checks whether there is a parking space of `carType` for the car that wants to get into the parking lot. `carType` can be of three kinds: big, medium, or small, which are represented by `1`, `2`, and `3` respectively. **A car can only park in a parking space of its** `carType`. If there is no space available, return `false`, else park the car in that size space and return `true`.

 

**Example 1:**

```
Input
["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
[[1, 1, 0], [1], [2], [3], [1]]
Output
[null, true, true, false, false]

Explanation
ParkingSystem parkingSystem = new ParkingSystem(1, 1, 0);
parkingSystem.addCar(1); // return true because there is 1 available slot for a big car
parkingSystem.addCar(2); // return true because there is 1 available slot for a medium car
parkingSystem.addCar(3); // return false because there is no available slot for a small car
parkingSystem.addCar(1); // return false because there is no available slot for a big car. It is already occupied.
```

 

**Constraints:**

- `0 <= big, medium, small <= 1000`
- `carType` is `1`, `2`, or `3`
- At most `1000` calls will be made to `addCar`

## 题目大意

请你给一个停车场设计一个停车系统。停车场总共有三种不同大小的车位：`大`，`中`和`小`，每种尺寸分别有固定数目的车位。

请你实现 `ParkingSystem` 类：

- `ParkingSystem(int big, int medium, int small)` 初始化 `ParkingSystem` 类，三个参数分别对应每种停车位的数目。
- `bool addCar(int  carType)` 检查是否有 `carType` 对应的停车位。 `carType` 有三种类型：大，中，小，分别用数字 1， 2 和 3 表示。一辆车只能停在 carType 对应尺寸的停车位中。如果没有空车位，请返回 false ，否则将该车停入车位并返回 true 

## 解题思路

这道题目比较简单，直接求解就可以了

### Solution 1:

````c++
class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small)
        : big_(big),
        medium_(medium),
        small_(small) {
    }

    bool addCar(int car_type) {
        if (car_type == 1) {
            if (big_ > 0) {
                --big_;
                return true;
            }
        } else if (car_type == 2) {
            if (medium_ > 0) {
                --medium_;
                return true;
            }
        } else {
            if (small_ > 0) {
                --small_;
                return true;
            }
        }
        return false;
    }

 private:
    int big_;
    int medium_;
    int small_;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
````
