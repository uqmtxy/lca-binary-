#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <set>
#include <queue>
#include <ctime>
#include <random>
#include <numeric>

using namespace std;

int n, l = 0, tme = 0;
//Время входа и выхода
vector <int> t_in, t_out;
vector < vector <int> > g, up;

void dfs (int v, int p) {

	up[v][0] = p;
	t_in[v] = ++tme;
	// Считаем массив подъема для текущей вершины
	for (int i = 1; i <= l; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	// Переходим к потомкам
	for (int to : g[v]) {
		if (to != p) {
			dfs(to, v);
		}
	}
	t_out[v] = ++tme;
}

// Является ли вершина а предком вершины b
bool upper (int a, int b) {
	return ((t_in[a] <= t_in[b]) && (t_out[a] >= t_out[b]));
}

int lca (int a, int b) {
	if (upper(a, b)) return a;
	if (upper(b, a)) return b;
	for (int i = l; i >= 0; i--) {
		if (!upper(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

int main() {

	cin >> n;
	g.resize(n);
//	d.resize(n);
	up.resize(n);
	t_in.resize(n);
	t_out.resize(n);
	// l - максимальная степень двойки, которая меньше n
	while ((1 << l) <= n) l++;
	for (int i = 0; i < n; i++) {
		up[i].resize(l);
	}
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		g[a-1].push_back(b-1);
		g[b-1].push_back(a-1);
	}
	dfs(0, 0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		cout << lca(a-1, b-1) + 1 << "\n";
	}
//	fdskfsdkfs
}