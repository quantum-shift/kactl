/**
 * Author: BForBruteForce
 * Description: Find 2 disjoint paths with minimum total sum in directed graph
 * Time: O((E + V)\log V)
 * Status: Tested
 */
#pragma once

template<class T = ll>
struct E {
    int u, v;
    T wt;
    E(int _u = -1, int _v = -1, T _wt = 0)
    : u(_u), v(_v), wt(_wt) {}
    int oth(int a) {
        assert(a == u || a == v);
        return u ^ v ^ a;
    }
    bool operator<(const E& o) const {
        return wt < o.wt;
    }
};

template<class T>
pair<vector<T>, vector<int>> dijkstra_tree(int n, const vector<vector<int>>& adj, 
    const vector<E<T>>& edges, int s, int t) {
    priority_queue<pair<T, int>> q;
    vector<bool> v(n);
    vector<T> d(n, numeric_limits<T>::max());
    q.push({0, s}); d[s] = 0;
    vector<int> p(n, -1);
    while(!q.empty()){
        auto [_, a] = q.top();
        q.pop();
        if(v[a]) continue;
        v[a] = 1;
        for(auto id : adj[a]){
            auto &e = edges[id];
            if(d[e.v] > d[a] + e.wt){
                d[e.v] = d[a] + e.wt;
                q.push({-d[e.v], e.v});
                p[e.v] = id;
            }
        }
    }
    vector<int> eIdx;
    while(t != s){
        eIdx.push_back(p[t]);
        t = edges[p[t]].u;
        assert(eIdx.size() <= n);
    }
    return {d, eIdx};
}

template<class T>
T suurballes_algorithm(int n, vector<vector<int>>& adj, 
    vector<E<T>>& e, int s, int t) {
    // Nodes have to be zero indexed
    assert(adj.size() == n);
    auto [d, te] = dijkstra_tree(n, adj, e, s, t);
    sort(all(te));
    auto se = e;
    T ans = 0;
    for (int i = 0; i < e.size(); ++i) {
        e[i].wt -= d[e[i].v] - d[e[i].u];
        if (binary_search(all(te), i)) {
            adj[e[i].u].erase(find(all(adj[e[i].u]), i));
            adj[e[i].v].push_back(i);
            swap(e[i].u, e[i].v);
        }
    }
    auto [_, nte] = dijkstra_tree(n, adj, e, s, t);
    sort(all(nte));
    for (auto u: nte) {
        if (!binary_search(all(te), u)) {
            ans += se[u].wt;
        }
    }
    for (auto u: te) {
        if (!binary_search(all(nte), u)) {
            ans += se[u].wt;
        }
    }
    return ans;
}