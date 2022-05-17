#include <vector>

using namespace std;

class UF {
 public:
     UF(int n)
         : count_(n),
         id_(std::move(vector<int>(n))),
        sz_(std::move(vector<int>(n, 1))) {
     }

     int GetCnt() const { return count_; }

     bool IsConnected(int p, int q) {
        return Find(p) == Find(q);
     }

     int Find(int p) {
        while (p != id_[p]) {
            p = id_[p];
        }
        return p;
     }

     void Union(int p, int q) {
        int i = Find(p);
        int j = Find(q);
        if (i == j) {
            return;
        }

        if (sz_[i] < sz_[j]) {
            id_[i] = j;
            sz_[j] += sz_[i];
        } else {
            id_[j] = i;
            sz_[i] += sz_[j];
        }
        count_--;
     }


 private:
    int count_;
    vector<int> id_;
    vector<int> sz_;
};
