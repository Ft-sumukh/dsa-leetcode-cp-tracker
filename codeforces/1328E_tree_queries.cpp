/**
 * Problem: Codeforces 1328E - Tree Queries
 * Contest: Codeforces Round 629 (Div. 3)
 * URL: https://codeforces.com/contest/1328/problem/E
 * 
 * Algorithm / Approach:
 * - A vertex `u` is at distance at most 1 from a simple path from the root (node 1) to some node `v`
 *   if and only if either `u` itself or `parent[u]` lies on that path.
 * - Since the path starts at the root, every node on the path is an ancestor of the path's endpoint.
 * - Thus, replace every selected query vertex `u` (except root 1) with `parent[u]`. The condition
 *   holds if and only if all these adjusted vertices lie on a single chain from the root.
 * - To verify this, select the deepest query vertex (`deepest`). If a valid chain exists, it must
 *   lead down to `deepest`.
 * - For every query node `u`, check whether `parent[u]` is an ancestor of `deepest` by walking up
 *   parent pointers from `deepest` to the depth of `parent[u]`.
 * 
 * Time Complexity:
 * - Preprocessing: O(N) via DFS to compute depths and parents.
 * - Per Query: O(K * H) where H <= N is the tree height; sum of K <= 2e5.
 * Space Complexity: O(N) for tree adjacency, parent, and depth arrays.
 */

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> parent, depth;

// DFS to calculate parent and depth of every node
void dfs(int u, int p) {
    parent[u] = p;                  // Store the parent of current node

    for (int v : adj[u]) {          // Visit every neighbour
        if (v == p) continue;       // Do not travel back to parent

        depth[v] = depth[u] + 1;    // Calculate depth of child
        dfs(v, u);                  // Recursively visit child
    }
}

void solve() {
    int k;
    cin >> k;                       // Number of selected vertices

    vector<int> nodes(k);

    for (int i = 0; i < k; i++)
        cin >> nodes[i];            // Read selected vertices

    int deepest = nodes[0];         // Assume first node is deepest

    // Find the deepest selected vertex
    for (int u : nodes) {
        if (depth[u] > depth[deepest])
            deepest = u;
    }

    // Check whether every selected vertex can reach
    // the path to deepest by moving up at most one edge
    for (int u : nodes) {

        if (u == 1) continue;       // Root has no parent

        int p = parent[u];          // Move selected node to its parent

        // The adjusted node must be an ancestor of deepest
        // (or be deepest itself)
        int v = deepest;

        while (depth[v] > depth[p])
            v = parent[v];

        if (v != p) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";                // All selected nodes satisfy the condition
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;                  // Read number of nodes and queries

    adj.resize(n + 1);
    parent.resize(n + 1);
    depth.resize(n + 1, 0);

    // Build the tree
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);                      // Root the tree at node 1

    while (m--)
        solve();                    // Process each query

    return 0;
}
