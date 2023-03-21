/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

struct BinaryLifting {
    vector<vi> tbl;
    vi depth;
    BinaryLifting (vi& P, vi& _depth): depth(_depth){
        int on = 1, d = 1;
        while(on < sz(P)) on *= 2, d++;
        tbl.assign(d, P);
        rep(i,1,d) rep(j,0,sz(P))
            tbl[i][j] = tbl[i-1][tbl[i-1][j]];
    }
    BinaryLifting(vector<vi>& adj, int r) {
        // Graph must be zero indexed
        int n = adj.size();
        vi P(n,-1), q;
        depth.resize(n);
        q.reserve(n);
        q.push_back(r);
        P[r] = r;
        rep(i,0,sz(q)) {
            for (auto u:adj[q[i]]) {
                if (P[u] == -1) {
                    P[u] = q[i];
                    depth[u] = depth[q[i]] + 1;
                    q.push_back(u);
                }
            }
        }
        int on = 1, d = 1;
        while(on < sz(P)) on *= 2, d++;
        tbl.assign(d, P);
        rep(i,1,d) rep(j,0,sz(P))
            tbl[i][j] = tbl[i-1][tbl[i-1][j]];
    }
    int jmp(int nod, int steps){
        rep(i,0,sz(tbl))
            if(steps&(1<<i)) nod = tbl[i][nod];
        return nod;
    }
    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = jmp(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int i = sz(tbl); i--;) {
            int c = tbl[i][a], d = tbl[i][b];
            if (c != d) a = c, b = d;
        }
        return tbl[0][a];
    }
    int distBetween(int a,int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
    int good(int a, int b) {
        return depth[b] < depth[a] ? false : jmp(b, depth[b] - depth[a]) == a;
    }
};
