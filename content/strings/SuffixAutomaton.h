/**
 * Author: BForBruteForce
 * Description: Node corresponds to a suffix
 * Number of nodes is number of equivalence endpos-class
 * link corresponds to longest suffix smaller than itself
 * Time: $O(n \log k)$ to build
 * Status: Tested on some problems
 */

struct suffix_automaton {
    struct state {
        int len = 0, link = -1;
        // len=Lengthes of largest strings in states
        map<char, int> to;
        ll cnt1 = 0, cnt2 = 0;
    } st[260000];
    int last = 0, sz = 1;
    void add_letter(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].to.count(c)) {
            st[p].to[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].to[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].to = st[q].to;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].to[c] == q) {
                    st[p].to[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    void build(string &s) { // add '#' before build
        for (int i = 0; i < s.size(); i++)
            add_letter(s[i]);
        used.assign(sz, 0);
        dfs(0);
    }
    vector<int> used;
    void dfs(int x) {
        used[x] = 1;
        for (auto it : st[x].to) {
            if (!used[it.ss])
                dfs(it.ss);
            if (it.ff == '#')
                st[x].cnt1++;
            else
                st[x].cnt1 += st[it.ss].cnt1;
            st[x].cnt2 += st[it.ss].cnt2;
        }
        st[x].cnt2 += st[x].cnt1;
    }
    void order(ll cur, ll k, string &ans, int x) {
        if (cur >= k)
            return;
        for (auto it = st[x].to.begin(); it != st[x].to.end(); it++) {
            if (cur + st[it->ss].cnt2 >= k) {
                cur += st[it->ss].cnt1;
                ans += it->ff;
                order(cur, k, ans, it->ss);
                return;
            } else
                cur += st[it->ss].cnt2;
        }
        ans = "No such line.";
    }
    string order(ll k) {
        string ret;
        order(0, k, ret, 0);
        return ret;
    }
}