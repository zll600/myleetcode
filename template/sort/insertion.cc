#include <vector>
#include <iostream>

using namespace std;

void InsertationSort(vector<int>& nums) {
    const int len = nums.size();
    for (int i = 1; i < len; ++i) {
        int tmp = nums[i];
        int j = i;
        while (j > 0 && nums[j - 1] > tmp) {
            nums[j] = nums[j - 1];
            --j;
        }
        nums[j] = tmp;
    }
}

int main(void) {
    vector<int> nums = {2, 4, 3, 5, 1, 8, 7, 9, 0};
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    InsertationSort(nums);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}

