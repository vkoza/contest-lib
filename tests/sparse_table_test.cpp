// https://judge.yosupo.jp/submission/115619

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T, class F = function<T(T&, T&)>>
struct SparseTable {
	int n = 0;
	vector<vector<T>> data;
	F func;
	SparseTable(const vector<T>& v, F f) : n((int) v.size()), func(f) {
		int k = 32 - __builtin_clz(n);
		data.resize(k);
		data[0] = v;
		for (int i = 1; i < k; i++) {
			data[i].resize(n - (1 << i) + 1);
			for (int j = 0; j + (1 << i) <= n; j++) {
				data[i][j] = func(data[i-1][j], data[i-1][j + (1 << (i-1))]);
			}
		}
	}
	T query(int l, int r) {
		int lg = 32 - __builtin_clz(r - l + 1) - 1;
		return func(data[lg][l], data[lg][r - (1 << lg) + 1]);
	}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int n, q; cin >> n >> q;
	vector<int> a(n); 
	for (int i = 0; i < n; i++) cin >> a[i];
	auto get_min = [](int i, int j) { return min(i, j); };
	SparseTable<int> rmin(a, get_min);
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r;
		cout << rmin.query(l, r-1) << "\n";
	}
	return 0;
}
