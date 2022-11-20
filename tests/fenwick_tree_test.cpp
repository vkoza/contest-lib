#include <bits/stdc++.h>
using namespace std;

typedef int64_t int64;

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

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int N, Q; cin >> N >> Q;
	FenwickTree<int64> fenwick(N);
	for (int i = 0; i < N; i++) {
		int64 x; cin >> x;
		fenwick.add(i, x);
	}
	for (int i = 0; i < Q; i++) {
		int t; cin >> t;
		if (t == 0) {
			int p; int64 x;
			cin >> p >> x;	
			fenwick.add(p, x);
		} else {
			int l, r;
			cin >> l >> r;
			cout << fenwick.sum(l, r) << "\n";
		}
	}
	return 0;
}
