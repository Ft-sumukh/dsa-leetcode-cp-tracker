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
 * 
 * Optimization Note (Fix for TLE on Test 80):
 * - The naive approach climbed parent pointers step-by-step from `deepest` to `depth[p]` in O(K * H)
 *   time per query, which exceeded the time limit (TLE on test 80) for degenerate/deep trees.
 * - In this optimal version, we preprocess entry and exit timestamps (`tin` and `tout`) during an
 *   iterative DFS (avoiding call stack overflow on deep trees).
 * - An ancestor check `isAncestor(u, v)` is evaluated in O(1):
 *     isAncestor(u, v) = (tin[u] <= tin[v] && tout[v] <= tout[u])
 * - This drops query time to O(K) and overall time to O(N + sum(K)).
 * 
 * Time Complexity:
 * - Preprocessing: O(N) via iterative DFS to record tin, tout, parent, and depth.
 * - Per Query: O(K) using O(1) ancestor checks with tin/tout timestamps.
 * - Total Time: O(N + sum(K)) <= 2e5 operations.
 * Space Complexity: O(N) for adjacency list, parent, depth, tin, and tout arrays.
 */

#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<vector<int>> adj;
vector<int> parent, depth;
vector<int> tin, tout;

int timer = 0;

// Iterative DFS to calculate parent, depth, entry and exit times
void dfs(int root) {

    // {current node, parent node, state}
    // state 0 = entering node
    // state 1 = exiting node
    stack<tuple<int, int, int>> st;

    st.push({root, root, 0});

    while (!st.empty()) {

        auto [u, p, state] = st.top();
        st.pop();

        if (state == 0) {

            parent[u] = p;       // Store parent of current node
            tin[u] = timer++;    // Record entry time

            st.push({u, p, 1});  // Schedule exit after children

            // Visit children in reverse adjacency order
            for (int i = (int)adj[u].size() - 1; i >= 0; i--) {

                int v = adj[u][i];

                if (v == p) continue;

                depth[v] = depth[u] + 1; // Calculate child depth

                st.push({v, u, 0});      // Schedule child traversal
            }
        }
        else {

            tout[u] = timer++;   // Record exit time
        }
    }
}

// Check whether u is an ancestor of v
bool isAncestor(int u, int v) {

    return tin[u] <= tin[v] &&
           tout[v] <= tout[u];
}

// Process one query
void solve() {

    int k;
    cin >> k;

    vector<int> nodes(k);

    int deepest = 1;

    // Read query nodes and find the deepest node
    for (int i = 0; i < k; i++) {

        cin >> nodes[i];

        if (depth[nodes[i]] > depth[deepest]) {
            deepest = nodes[i];
        }
    }

    // Check whether all adjusted nodes are ancestors of deepest
    for (int u : nodes) {

        if (u == deepest) continue;

        // Move the node up by one edge
        if (u != 1) {
            u = parent[u];
        }

        // The adjusted node must be an ancestor of deepest
        if (!isAncestor(u, deepest)) {

            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    adj.resize(n + 1);
    parent.resize(n + 1);
    depth.resize(n + 1, 0);
    tin.resize(n + 1);
    tout.resize(n + 1);

    // Build the adjacency list
    for (int i = 0; i < n - 1; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Preprocess the tree
    dfs(1);

    // Answer all queries
    while (m--) {
        solve();
    }

    return 0;
}
