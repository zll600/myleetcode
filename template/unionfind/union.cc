#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : count_(n) {
        for (int i = 0; i < n; i++) {
            parent_.push_back(i);
            rank_.push_back(0);
        }
    }

    // 路径压缩， 遍历过程中的所有父节点直接指向根节点，
    // 减少后续查找次数
    int Find(int x) {
        if (parent_[x] != x) {
            parent_[x] = Find(parent_[x]);
        }
        return parent_[x];
    }

    // 合并两个节点
    // 如果处于同一个并查集， 不需要合并
    // 如果不处于同一个并查集，判断两个rootx和rooty谁的秩大
    void Union(int x, int y) {
        int rx = Find(x);
        int ry = Find(y);
        if (rx != ry) {
            if (rank_[rx] < rank_[ry]) {
                swap(rx, ry);
            }
            parent_[ry] = rx;
            count_--;
            if (rank_[rx] == rank_[ry]) {
                rank_[rx] += 1;
            }
        }
    }
 
 private:
    // 用于记录该节点的父节点，所有父节点相同的节点位于同一连通图
    vector<int> parent_; 
    // 节点的秩，主要记录该节点目前位于的树的深度，从子节点出发
    // 主要用于优化，在合并两个父节点时，通过rank_的大小判断谁父谁子
    vector<int> rank_;
    // 用于记录并查集的数量,某些情况下该成员非必要
    int count_;

};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        UnionFind uf(n);
        for (const auto& e : pairs) {
            uf.Union(e[0], e[1]);
        }

        unordered_map<int, vector<int> > um;
        for (int i = 0; i < n; i++) {
            um[uf.Find(i)].push_back(s[i]);
        }

        for (auto& [x, vec] : um) {
            sort(vec.begin(), vec.end(), greater<int>());
        }
        for (int i = 0; i < s.length(); i++) {
            int x = uf.Find(i);
            s[i] = um[x].back();
            um[x].pop_back();
        }
        return s;
    }
};

int main(void) {
    string str = "bacd";
    vector<vector<int>> pairs = { {0,3}, {1,2} };
    Solution obj;

    cout << obj.smallestStringWithSwaps(str, pairs) << endl;

    return 0;
}
