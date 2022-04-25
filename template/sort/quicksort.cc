#include <vector>
#include <iostream>

using namespace std;

int Partition(vector<int>& nums, int low, int high) {
    int rand_idx = rand() % (high - low + 1) + low;
    swap(nums[low], nums[rand_idx]);

    int pivot = nums[low];
    int lt = low;
    for (int i = low + 1; i <= high; ++i) {
        if (nums[i] < pivot) {
            ++lt;
            swap(nums[i], nums[lt]);
        }
    }
    swap(nums[lt], nums[low]);

    return lt;
}

int Partition2(vector<int>& nums, int low, int high) {
    int rand_idx = rand() % (high - low + 1) + low;
    swap(nums[low], nums[rand_idx]);

    int pivot = nums[low];
    int lt = low + 1;
    int gt = high;

    while (true) {
        while (lt <= high && nums[lt] < pivot) {
            ++lt;
        }
        while (gt > low && nums[gt] > pivot) {
            --gt;
        }

        if (lt >= gt) {
            break;
        }

        swap(nums[lt], nums[gt]);
        ++lt;
        --gt;
    }

    swap(nums[gt], nums[low]);

    return gt;
}

void QuickSort(vector<int>& nums, int low, int high) {
    if (low >= high) {
        return;
    }

    int idx = Partition(nums, low, high);
    QuickSort(nums, low, idx - 1);
    QuickSort(nums, idx + 1, high);
}

void QuickSort2(vector<int>& nums, int low, int high) {
    if (low >= high) {
        return;
    }

    int rand_idx = low + rand() % (high - low + 1);
    swap(nums[rand_idx], nums[low]);

    int pivot = nums[low];
    int lt = low;
    int gt = high + 1;
    
    int i = low + 1;
    while (i < gt) {
        if (nums[i] < pivot) {
            ++lt;
            swap(nums[i], nums[lt]);
            ++i;
        } else if (nums[i] > pivot) {
            --gt;
            swap(nums[i], nums[gt]);
        } else {
            ++i;
        }
    }
    swap(nums[low], nums[lt]);

    QuickSort2(nums, low, lt - 1);
    QuickSort2(nums, gt, high);
}

int main(void) {
    vector<int> nums = {2, 4, 3, 5, 1, 6, 8, 7, 9, 0};
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    QuickSort2(nums, 0, nums.size() - 1);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
