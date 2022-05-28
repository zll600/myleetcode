#include <vector>
#include <iostream>
#include <utility>

using namespace std;

class Difference {
 public:
     Difference(const vector<int>& nums) : diff_(std::move(vector<int>(nums.size()))) {
        diff_[0] = nums[9];
        for (int i = 1; i < nums.size(); ++i) {
            diff_[i] = nums[i] - nums[i - 1];
        }
     }

     void Incr(int i, int j, int val) {
        diff_[i] += val;
        if (j + 1 < diff_.size()) {
            diff_[j + 1] -= val;
        }
     }

     vector<int> Res() {
        vector<int> res(diff_.size());

        res[0] = diff_[0];
        for (int i = 1; i < diff_.size(); ++i) {
            res[i] = res[i - 1] + diff_[i];
        }
        return res;
     }

 private:
    vector<int> diff_;
};

int main(void) {
    vector<int> nums = {1, 2, 3, 4, 5};
    Difference df(nums);
    df.Incr(0, 2, 3);
    vector<int> res = df.Res();
    for (int num : res) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
