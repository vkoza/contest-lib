struct UnionFind {
	int n;
	vector<int> p;
	UnionFind(int n_) : n(n_), p(n, -1) {};
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	int find(int x) {
		if (p[x] < 0) return x;
		return p[x] = find(p[x]);
	}
	int size(int x) {
		return -p[find(x)];
	}
	int merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return x;
		if (p[x] > p[y]) swap(x, y);
		p[x] += p[y];
		p[y] = x;
		return x;
	}
};
