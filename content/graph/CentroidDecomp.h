/**
 * Author: BForBruteForce
 * Description: Centroid decomposition. Make arrays global if too slow.
 * Time: O(n log n)
 * Status: Tested on CSES
 */
struct Centroid {
    void build(const vector<vi>& A) {
        adj = A;
        dfs_sub(0, 0);
    }
    void dfs_sub(int v, int p) {
        sub[v] = 1;
        for (auto u: adj[v]) {
            if (!vis[u] && u != p) {
                dfs_sub(u, v);
                sub[v] += sub[u];
            }
        }
    }
    int find_centroid(int v, int p, int s) {
        for (auto u: adj[v]) {
            if (!vis[u] && u != p && sub[u] > s / 2) {
                return find_centroid(u, v, s);
            }
        }
        return v;
    }
    int n;
    vector<int> sub;
    vector<vector<int>> adj;
    vector<bool> vis;
    Centroid(int _n): n(_n) {
        sub.resize(n);
        adj.resize(n);
    }
    // Declare required members
    void process (int c) {
        // Process component with centroid c
        // Remember to not visit vis[u] = 1
    };
    void decomp(int v, int p) {
        dfs_sub(v, -1);
        int c = find_centroid(v, -1, sub[v]);
        vis[c] = 1;
        process(c);
        for (auto u: adj[c]) {
            if (!vis[u]) {
                decomp(u, c);
            }
        }
    }
};