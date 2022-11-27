template <typename T> 
T inverse(T a, T m) {
        T x = a, y = m;
        T vx = 1, vy = 0;
        while (x) {
                T k = y / x;
                y %= x;
                vy -= k * vx;
                swap(x, y);
                swap(vx, vy);
        }
        assert(y == 1);
        return vy < 0 ? m + vy : vy;
}
 
template<typename id>
struct DynamicModularInt {
	inline static int MOD_ = 0;
	inline static uint64_t BARRETT_M = 0;
	static constexpr int const& MOD = MOD_;
	
	int v; 
	
	static void set_mod(int mod) {
		assert(mod > 0);
		MOD_ = mod;
		BARRETT_M = (uint64_t(-1) / MOD);
	}
	static uint32_t barrett_reduce_partial(uint64_t a) {
		return uint32_t(a - uint64_t((__uint128_t(BARRETT_M) * a) >> 64) * MOD);
	}
	static int barrett_reduce(uint64_t a) {
		int32_t res = int32_t(barrett_reduce_partial(a) - MOD);
		return (res < 0) ? res + MOD : res;
	}
 
	DynamicModularInt(int64_t v_ = 0) : v(normalize(v_)) {};
	explicit operator int() const { return v; }
 
	friend std::ostream& operator << (std::ostream& out, const DynamicModularInt& z) { return out << int(z); }
	friend std::istream& operator >> (std::istream& in, const DynamicModularInt& z) { int64_t v_; in >> v_; z = DynamicModularInt(v_); return in; }
 
	friend bool operator == (const DynamicModularInt& a, const DynamicModularInt& b) { return a.v == b.v; }
	friend bool operator != (const DynamicModularInt& a, const DynamicModularInt& b) { return a.v != b.v; }
 
	DynamicModularInt inv() const {
		DynamicModularInt res;
		res.v = inverse(v, MOD);
		return res;
	}
	friend DynamicModularInt inv(const DynamicModularInt& z) { return z.inv(); }
 
	DynamicModularInt& operator += (const DynamicModularInt& o) {
		v -= MOD-o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	DynamicModularInt& operator -= (const DynamicModularInt& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	DynamicModularInt& operator *= (const DynamicModularInt& o) {
		v = barrett_reduce(int64_t(v) * int64_t(o.v));
		return *this;
	}
	DynamicModularInt& operator /= (const DynamicModularInt& o) {
		return *this *= o.inv();
	}
 
	friend DynamicModularInt operator + (const DynamicModularInt& a, const DynamicModularInt& b) { return DynamicModularInt(a) += b; }
	friend DynamicModularInt operator - (const DynamicModularInt& a, const DynamicModularInt& b) { return DynamicModularInt(a) -= b; }
	friend DynamicModularInt operator * (const DynamicModularInt& a, const DynamicModularInt& b) { return DynamicModularInt(a) *= b; }
	friend DynamicModularInt operator / (const DynamicModularInt& a, const DynamicModularInt& b) { return DynamicModularInt(a) /= b; }
 
 
	static int normalize(int64_t x) {
                x %= MOD;
                if (x < 0) x += MOD;
                return x;
        }
};
 
template <typename T>
T power(T a, long long n) {
        T r = 1;
        while (n) { if (n & 1) r *= a; a *= a; n >>= 1; }
        return r;
}
 
struct mod_base{};
using mint = DynamicModularInt<mod_base>;
