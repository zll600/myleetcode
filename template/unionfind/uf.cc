#include <vector>

using namespace std;

class UF {
 public:
    UF(int len) : data_(len), cnt_(len) {
        for (int i = 0; i < len; ++i) {
            data_[i] = i;
        }
    }

    int Find(int x) {
        while (x != data_[x]) {
            data_[x] = data_[data_[x]];
            x = data_[x];
        }

        return x;
    }

    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);

        if (root_x == root_y) {
            return;
        }
        
        data_[root_x] = data_[root_y];
        --cnt_;
    }

    int TotalCount() const {
        return cnt_;
    }

 private:
    vector<int> data_;
    int cnt_;
};
