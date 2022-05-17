#include <vector>

using namespace std;

class UF {
 public:
     UF(int n) : count_(n), id_(std::move(vector<int>(n))) {}

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
        int p_root = Find(p);
        int q_root = Find(q);
        if (p_root == q_root) {
            return;
        }

        id_[p_root] = q_root;
        count_--;
     }

 private:
    int count_;
    vector<int> id_;
};
