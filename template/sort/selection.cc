#include <vector>
#include <iostream>

using namespace std;

void Selection(vector<int>& nums) {
    const int len = nums.size();
    for (int i = 0; i < len - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < len; ++j) {
            if (nums[min_idx] > nums[j]) {
                min_idx = j;
            }
        }
        swap(nums[i], nums[min_idx]);
    }
}

int main(void) {
    vector<int> nums = {2, 4, 3, 5, 1, 8, 7, 9, 0};
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    Selection(nums);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
