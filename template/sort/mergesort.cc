#include <vector>
#include <iostream>

using namespace std;

void MergeTwoSortedArr(vector<int>& nums, int low, int mid, int high, vector<int>& lux) {
    copy(nums.begin() + low, nums.begin() + high + 1, lux.begin() + low);

    int i = low;
    int j = mid + 1;

    for (int k = low; k <= high; ++k) {
        if (i == mid + 1) {
            nums[k] = lux[j];
            ++j;
        } else if (j == high + 1) {
            nums[k] = lux[i];
            ++i;
        } else if (lux[i] <= lux[j]) {
            nums[k] = lux[i];
            ++i;
        } else {
            nums[k] = lux[j];
            ++j;
        }
    }
}

void MergeSort(vector<int>& nums, int low, int high, vector<int>& lux) {
    if (low >= high) {
        return;
    }

    const int mid = low + (high - low) / 2;
    MergeSort(nums, low, mid, lux);
    MergeSort(nums, mid + 1, high, lux);

    if (nums[mid] <= nums[mid + 1]) {
        return;
    }

    MergeTwoSortedArr(nums, low, mid, high, lux);
}

int main(void) {
    vector<int> nums = {2, 4, 3, 5, 1, 6, 8, 7, 9, 0};
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    vector<int> lux(nums.size());
    MergeSort(nums, 0, nums.size() - 1, lux);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
