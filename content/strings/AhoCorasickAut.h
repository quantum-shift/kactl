/**
 * Author: BForBruteForce
 * Date: 2015-02-18
 * License: CC0
 * Description: Simpler AhoCorasick automaton implementation.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * Status: Tested on some problems
 */
#pragma once

struct Aho {
    enum {alp = 26, first = 'a'}; // change this!
    vi sl, de, ol;
    int sz = 0;
    vector<vi> aut;
    Aho(int n): sl(n), de(n), ol(n), aut(n, vi(alp)) {
    }
    void add(string& s){
        int u = 0;
        for(char c: s){
            if(!aut[u][c - first]){
                aut[u][c - first] = ++sz;
            }
            u = aut[u][c - first];
        }
        ol[u] = u;
    }
    void aho_corasick(){
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int v = q.front(); q.pop();
            int u = sl[v];
            rep(i, 0, alp) {
                if(aut[v][i]){
                    int x = aut[v][i];
                    de[x] = de[v] + 1;
                    sl[x] = v ? aut[sl[v]][i] : 0;
                    if(!ol[x]){
                        ol[x] = ol[sl[x]];
                    }
                    q.push(x);
                }
                else{
                    aut[v][i] = aut[u][i];
                }
            }
        }
    }
};
