struct Node {
	int val; 
	Node(int val_ = 0) : val(val_) {};
	friend ostream& operator << (std::ostream& o, const Node& p) { return o << p.val; }
};

Node prod(Node& x, Node& y) {
	return Node(x.val + y.val);
}

template <typename T, typename F>
struct SegmentTree {
	int n, size, log;
	vector<T> t;
	F op; T e;
	SegmentTree(int n_, F op_, T e_) : SegmentTree(vector<T>(n_, e_), op_, e_) {}
	SegmentTree(vector<T>& t_, F op_, T e_) : n((int) t_.size()), op(op_), e(e_) {
		log = __lg(max(n-1, 1)) + 1, size = 1 << log;
		t = vector<T>(size << 1, e);
		for (int i = 0; i < n; i++) t[i+size] = t_[i];
		for (int i = size-1; i >= 1; i--) update(i);
	}
	void set(int p, T x) {
		t[p += size] = x;
		for (int i = 1; i <= log; i++) update(p >> i);
	}
	void modify(int p, T x) {
		p += size;
		t[p] = op(t[p], x);
		for (int i = 1; i <= log; i++) update(p >> i);
	}
	T query(int p) { return t[p + size]; }
	T query(int l, int r) {
		T left = e; T right = e;
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) left = op(left, t[l++]);
                        if (r & 1) right = op(right, t[--r]);
                }
		return op(left, right);
	}
	inline void update(int i) { t[i] = op(t[i << 1], t[i << 1 | 1]); }
};

using SegTree = SegmentTree<Node, function<Node(Node&, Node&)>>;
