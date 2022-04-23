#include <vector>
#include <iostream>

using namespace std;

void SiftDown(vector<int>& nums, int cur, int high) {
    while (2 * cur + 1 <= high) {
        int j = 2 * cur + 1;
        
        if (j + 1 <= high && nums[j + 1] > nums[j]) {
            ++j;
        }

        if (nums[cur] < nums[j]) {
            swap(nums[cur], nums[j]);
        } else {
            break;
        }

        cur = j;
    }
}

void Heapify(vector<int>& nums) {
    const int len = nums.size();

    for (int i = (len - 1) / 2; i >= 0; --i) {
        SiftDown(nums, i, len - 1);
    }
}


void HeapSort(vector<int>& nums) {
    Heapify(nums);

    const int len = nums.size();
    for (int i = len - 1; i >= 0;) {
        swap(nums[i], nums[0]);
        --i;
        SiftDown(nums, 0, i);
    }
}

int main(void) {
    vector<int> nums = {2, 4, 3, 5, 1, 6, 8, 7, 9, 0};
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    HeapSort(nums);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
