#include <vector>
#include <queue>

using namespace std;

int SPFA(int s) {
	std::queue<int> q;
	bool inq[maxn] = {false};
	for(int i = 1; i <= N; i++) dis[i] = 2147483647;
	dis[s] = 0;
	q.push(s); inq[s] = true;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		inq[x] = false;
		for(int i = front[x]; i !=0 ; i = e[i].next) {
			int k = e[i].v;
			if(dis[k] > dis[x] + e[i].w) {
				dis[k] = dis[x] + e[i].w;
				if(!inq[k]) {
					inq[k] = true;
					q.push(k);
				}
			}
		}
	}
	for(int i =  1; i <= N; i++) std::cout << dis[i] << ' ';
	std::cout << std::endl;
	return 0;
}

