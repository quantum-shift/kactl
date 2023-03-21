/**
 * Author: BForBruteForce
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: General lazy segment tree
 * Time: O(\log N).
 * Usage: SegTree st(n, init); or SegTree st(n);
 * Status: Tested on few problems
 */

struct SegTree {
#define DEF(x, lx, rx) \
        int mid = (lx + rx) >> 1; \
        int a = (x << 1) | 1, b = a + 1;
    struct node {
        ll val = 0, lazy = 0;
        void apply (int lx, int rx, ll x) {
            // val += x;
            // lazy += x;
        }
    };
    node unite(const node &a, const node &b) const {
        node res;
        // res.val = max(a.val, b.val);
		return res;
    }
    inline void pull(int x, int a, int b) { st[x] = unite(st[a], st[b]); }
    inline void push(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        DEF(x, lx, rx);
        if (st[x].lazy) {
            st[a].apply(lx, mid, st[x].lazy);
            st[b].apply(mid, rx, st[x].lazy);
            st[x].lazy = 0;
        }
    }
    vector<node> st;
    int n;
    const node query_id;

    template<class M = ll>
    SegTree (int _n, const vector<M>& A = {}) {
        n = 1;
        while (n < _n) n <<= 1;
        st.resize(n << 1);
        if (!A.empty()) build(A, 0, 0, n);
    }
    template<class M = ll>
    void build(const vector<M>& A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) st[x].apply(lx, rx, A[lx]);
            return;
        }
        DEF(x, lx, rx);
        build(A, a, lx, mid); build(A, b, mid, rx);
        pull(x, a, b);
    }
    node query(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return query_id;
        if (lx >= l && rx <= r) return st[x];
        DEF(x, lx, rx);
        push(x, lx, rx);
        return unite(query(l, r, a, lx, mid), query(l, r, b, mid, rx));
    }
    node query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
    template<class... M>
    void modify(int l, int r, int x, int lx, int rx, const M &... v) {
        if (l >= rx || r <= lx) return;
        if (lx >= l && rx <= r) {
            st[x].apply(lx, rx, v...);
            return;
        }
        DEF(x, lx, rx);
        push(x, lx, rx);
        modify(l, r, a, lx, mid, v...);
        modify(l, r, b, mid, rx, v...);
        pull(x, a, b);
    }
    template<class... M>
    void modify(int l, int r, const M &... v) {
        modify(l, r, 0, 0, n, v...);
    }
    bool f(const node& x, ll v){
        return x.val >= v;
    }
    template<class... M>
    int find_first(int l, int r, int x, int lx, int rx, const M &... v) {
        if (l >= rx || r <= lx) return -1;
        if (lx >= l && rx <= r) {
            if (!f(st[x], v...)) return -1;
            if (rx - lx == 1) return lx;
        }
        DEF(x, lx, rx);
        push(x, lx, rx);
        int q = find_first(l, r, a, lx, mid, v...);
        if (q == -1) return find_first(l, r, b, mid, rx, v...);
        else return q;
    }
    template<class... M>
    int find_first(int l, int r, const M &... v) { return find_first(l, r, 0, 0, n, v...); }
    template<class... M>
    int find_last(int l, int r, int x, int lx, int rx, const M &... v) {
        if (l >= rx || r <= lx) return -1;
        if (lx >= l && rx <= r) {
            if (!f(st[x], v...)) return -1;
            if (rx - lx == 1) return lx;
        }
        DEF(x, lx, rx);
        push(x, lx, rx);
        int q = find_last(l, r, b, mid, rx, v...);
        if (q == -1) return find_last(l, r, a, lx, mid, v...);
        else return q;
    }
    template<class... M>
    int find_last(int l, int r, const M &... v) { return find_last(l, r, 0, 0, n, v...); }
};