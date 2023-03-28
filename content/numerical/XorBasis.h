/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Description: Add binary vectors to basis, find kth smallest or
 * largest in basis.
 * Time: O(\log(N)) per query
 * Status: Amazing
 */

struct XorBasis {
    const int D = 30;
    int s = 0;
    vector<ll> b;
    XorBasis() {
        b.resize(D);
    }
    void add(ll m) {
        for (int i = D - 1; i >= 0; --i) {
            if (m & (1LL << i)) {
                if (!b[i]) {
                    b[i] = m, ++s;
                    return;
                } else {
                    m ^= b[i];
                }
            }
        }
    }
    ll kth_small(ll k) {
        assert(k <= (1LL << s));
        ll m = 0;
        ll t = 1LL << s;
        for (int i = D - 1; i >= 0; --i) {
            if (b[i]) {
                ll l = t / 2;
                if (l < k && (m >> i & 1) == 0) m ^= b[i];
                else if (l >= k && (m >> i & 1)) m ^= b[i];
                if (l < k) k -= l;
                t /= 2;
            }
        }
        return m;
    }
    ll kth_large(ll k) {
        assert(k <= (1LL << s));
        return kth_small((1LL << s) - k + 1);
    }
};