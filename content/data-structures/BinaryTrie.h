/**
 * Author: BForBruteForce
 * License: CC0
 * Description: Add strings, find maximum xor, kth maximum xor and
 * number of xors less than k. Can create 2 log n new nodes per operation.
 * Time: All operations are $O(\log N)$.
 * Status: Tested on some problems
 */
struct tn {
    int c[2];
    int sub = 0;
};
struct BinaryTrie {
    const int D = 30;
    vector<tn> np;
    int counter = 1;
    BinaryTrie(int sz = 0) {
        np.resize(sz + 1);
    }
    void init_node(int v) {
        if (np[v].c[0]) return;
        if (counter >= np.size()) np.emplace_back(), np.emplace_back();
        np[v].c[0] = counter++;
        np[v].c[1] = counter++;
    }
    void add(ll v, int x) {
        int r = 0;
        for (int i = D - 1; i >= 0; --i) {
            int l = (v >> i) & 1;
            init_node(r);
            np[r].sub += x;
            r = np[r].c[l];
        }
        np[r].sub += x;
    }
    void add(ll v) { // Optional
        add(v, 1);
    }
    void del(ll v) { // Optional
        add(v, -1);
    }
    ll max_xor(ll v) { // Optional
        int r = 0;
        ll ans = 0;
        for (int i = D - 1; i >= 0; --i) {
            int l = (v >> i) & 1 ^ 1;
            init_node(r);
            int a = np[r].c[l], b = np[r].c[l ^ 1];
            if (np[a].sub > 0) {
                r = a;
                ans += (1 << i);
            } else r = b;
        }
        return ans;
    }
    int cnt_ltk(ll v, ll k){ // Optional
        // Count number of x ^ v < k
        int r = 0, ans = 0;
        for(int i = D - 1; i >= 0; i--){
            init_node(r);
            int l = (v >> i) & 1;
            int a = np[r].c[l], b = np[r].c[l ^ 1];
            if(k & (1LL << i)){
                ans += np[a].sub;
                r = b;
            }
            else{
                r = a;
            }
        }
        return ans;
    }
    ll get_kth_xor(ll v, int k){ // Optional
        // k is one-indexed (minimum A[i] ^ v is given by k = 1)
        int r = 0;
        ll ans = 0;
        assert(np[r].sub >= k);
        for(int i = D - 1; i >= 0; i--){
            init_node(r);
            int l = (v >> i) & 1;
            int a = np[r].c[l], b = np[r].c[l ^ 1];
            if(np[a].sub < k){
                k -= np[a].sub;
                ans ^= 1LL << i;
                r = b;
            }
            else{
                r = a;
            }
        }
        return ans;
    }
};