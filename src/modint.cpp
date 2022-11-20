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

template <int _MOD>
struct ModularInt {
        static constexpr int MOD = MOD_;
        int v;
        ModularInt(int64_t _v = 0) : v(normalize(_v)) {};
        explicit operator int() const { return v; }

        friend ostream& operator << (ostream& out, const ModularInt& z) { return out << int(z); }
	friend istream& operator >> (istream& in, ModularInt& z) { int _v; in >> _v; z = ModularInt(_v); return in; }

        friend bool operator == (const ModularInt& lhs, const ModularInt& rhs) { return lhs.v == rhs.v; };
        friend bool operator != (const ModularInt& lhs, const ModularInt& rhs) { return lhs.v != rhs.v; };

        ModularInt inv() const {
                ModularInt res;
                res.v = inverse(v, MOD);
                return res;
        }
        friend ModularInt inv(const ModularInt& z) { return z.inv(); }
        ModularInt& operator += (const ModularInt& rhs) { 
                v += rhs.v;
                if (v >= MOD) v -= MOD;
                return *this;
        }
        ModularInt& operator -= (const ModularInt& rhs) {
                v -= rhs.v;
                if (v < 0) v += MOD;
                return *this;
        }
        ModularInt& operator *= (const ModularInt& rhs) {
                int64_t x = (int64_t) v * (int64_t) rhs.v;
                v = normalize(x);
                return *this;
        }
        ModularInt& operator /= (const ModularInt& rhs) {
                ModularInt res = rhs.inv();
                return (*this) *= res;
        };
        ModularInt& operator++() {
                v++;
                if (v == MOD) v = 0;
                return v;
        }
        ModularInt& operator--() {
                v--;
                if (v == -1) v = MOD - 1;
                return v;
        }
        friend ModularInt operator + (const ModularInt& lhs, const ModularInt& rhs) { return ModularInt(lhs.v) += rhs; }
        friend ModularInt operator - (const ModularInt& lhs, const ModularInt& rhs) { return ModularInt(lhs.v) -= rhs; }
        friend ModularInt operator * (const ModularInt& lhs, const ModularInt& rhs) { return ModularInt(lhs.v) *= rhs; }
        friend ModularInt operator / (const ModularInt& lhs, const ModularInt& rhs) { return ModularInt(lhs.v) /= rhs; }

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

// const int md = 998244353;
// const int md = (int) 1e9 + 7;
using mint = ModularInt<md>;
