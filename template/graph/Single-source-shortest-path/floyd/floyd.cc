#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    int floyd(int n, vector<vector<int>>& edges) {
        // 定义邻接矩阵D，并初始化各个城市间距离为INT_MAX（无穷）
        vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
        // 根据edges[][]初始化D[][]
        for (auto &edge : edges) {
            // 无向图两个城市间的两个方向距离相同
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
        // Floyd算法
        for (int k = 0; k < n; k++) {
            // n个顶点依次作为插入点
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j || graph[i][k] == INT_MAX || graph[k][j] == INT_MAX) {
                        // 这些情况都不符合下一行的if条件，
                        // 单独拿出来只是为了防止两个INT_MAX相加导致溢出
                        continue;
                    }
                    graph[i][j] = min(graph[i][k] + graph[k][j], graph[i][j]);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << i << "-> " << j << ": " << graph[i][j] << endl;
            }
        }

        return 0;
    }
};

int main(void) {
    vector<vector<int>> edges = {{0,1,3}, {1,2,1}, {1,3,4},{2,3,1}};

    Solution obj;
    obj.floyd(4, edges);

    return 0;
}
