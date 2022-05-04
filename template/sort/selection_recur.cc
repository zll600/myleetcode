#include <vector>
#include <iostream>

using namespace std;

int PrefixMax(vector<int>& nums, int idx) {
    if (idx > 0) {
        int j = PrefixMax(nums, idx - 1);
        if (nums[idx] < nums[j]) {
            return j;
        }
    }
    return idx;
}

void Selection(vector<int>& nums, int idx) {
    if (nums.empty()) {
        idx = nums.size() - 1;
    }

    if (idx > 0) {
        int j = PrefixMax(nums, idx);
        swap(nums[idx], nums[j]);
        Selection(nums, idx - 1);;
    }
}

int main(void) {
    vector<int> nums{ 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    
    cout << "Before sort: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    Selection(nums, nums.size() - 1);
    
    cout << "After sort: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
