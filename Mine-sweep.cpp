#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <ctime>
using namespace std;
const int N = 110;

int mp[N][N];
int randmark[N][N];
char showus[N][N];
int vis[N][N];
int dir[8][2]={{-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}}, res;

struct node {
	int x, y;
};

inline void bfs(int X, int Y) {
	queue<node> q;
	node t;
	t.x = X, t.y = Y;
	q.push(t);
	vis[X][Y] = 1;
	while (!q.empty()) {
		++res;
		t = q.front();
		q.pop();
		showus[t.x][t.y] = mp[t.x][t.y] + '0';
		for (int i = 0; i < 8; ++i) {
			int nx = t.x + dir[i][0];
			int ny = t.y + dir[i][1];
			if (0 <= nx && nx < 10 && 0 <= ny && ny < 10) {
				if (!vis[nx][ny] && mp[nx][ny] == 0) {
					t.x = nx, t.y = ny;
					vis[nx][ny] = 1;
					showus[nx][ny] = mp[nx][ny] + '0';
					q.push(t);
				}
				if (!vis[nx][ny] && mp[nx][ny] > 0 && mp[t.x][t.y] == 0) {
					t.x = nx, t.y = ny;
					vis[nx][ny] = 1;
					showus[nx][ny] = mp[nx][ny] + '0';
					q.push(t);
				}
			}
		}
	}
}

int main() {
	memset(mp, 0, sizeof mp);
	memset(randmark, 0, sizeof randmark);
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			showus[i][j] = '*';
		}
	}
	srand(unsigned(time(NULL)));
	int sum = 0;
	while (1) {
		if (sum == 10) break;
		int x = rand()%10;
		int y = rand()%10;
		if (randmark[x][y] != 1) {
			randmark[x][y] = 1;
			sum++;
		}
	}
	res = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (randmark[i][j]) mp[i][j] = -1;
		}
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (mp[i][j] != -1) {
				for (int k = 0; k < 8; ++k) {
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if (0 <= x && x < 10 && 0 <= y && y < 10 && mp[x][y] == -1) {
						mp[i][j]++;
					}
				}
			}
		}
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << showus[i][j] << " ";
		}
		cout << endl;
	}
	cout << "请输入要翻开的位置的坐标: " << endl;
	int x, y;
	while (1) {
		if (res == 90) cout << "恭喜您胜利啦， 排雷成功! " << endl;
		cin >> x >> y;
		if (mp[x][y] == -1) {
			cout << "您中雷啦！ " << endl;
			break;
		} else if (!vis[x][y] && mp[x][y] > 0) {
			res++;
			vis[x][y] = 1;
			showus[x][y] = mp[x][y] + '0';
			system("cls");
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					cout << showus[i][j] << " ";
				}
				cout << endl;
			}
			cout << "请输入要翻开的位置的坐标 : " << endl;
		}
		else if (!vis[x][y] && mp[x][y] == 0) {
			bfs(x, y);
			system("cls");
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					cout << showus[i][j] << " ";
				}
				cout << endl;
			}
			cout << "请输入要翻开的位置的坐标 : " << endl;
		}
	}
	return 0;
}