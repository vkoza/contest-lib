template <typename T>
struct FenwickTree {
	int n; 
	vector<T> t;
	FenwickTree(int n_) : n(n_), t(n_+1, 0) {}
	void add(int p, T x) {
		for (p += 1; p <= n; p += (p & -p)) t[p] += x;
	}
	T sum(int p) {
		T s = 0;
		for (; p != 0; p &= p - 1) s += t[p];
		return s;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l);
	}
};
