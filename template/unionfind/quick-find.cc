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
        return id_[p];
     }

     void Union(int p, int q) {
        int p_id = Find(p);
        int q_id = Find(q);

        if (p_id == q_id) {
            return;
        }

        for (int i = 0; i < id_.size(); ++i) {
            if (id_[i] == p_id) {
                id_[i] = q_id;
            }
        }
        --count_;
     }

 private:
    int count_;
    vector<int> id_;
};
