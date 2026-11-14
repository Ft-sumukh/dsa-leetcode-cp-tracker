/**
 * Problem: Codeforces 580C - Kefa and Park
 * Contest: Codeforces Round 321 (Div. 2)
 * URL: https://codeforces.com/contest/580/problem/C
 * 
 * Algorithm / Approach:
 * - The problem asks for the number of leaves reachable from root vertex 1 such that 
 *   no path from the root to the leaf contains more than m consecutive vertices with cats.
 * - Perform Depth-First Search (DFS) starting at vertex 1:
 *   - Track the current consecutive count of cats along the path. If the current vertex
 *     has a cat (cats[u] == 1), increment `consecutive`; otherwise reset `consecutive = 0`.
 *   - If `consecutive > m`, prune this branch immediately.
 *   - Continue DFS to all children (v != parent).
 *   - If a vertex has no unvisited children (and u != 1), it is a leaf. If reached without 
 *     violating the condition, increment the answer.
 * 
 * Time Complexity: O(N) where N is the number of vertices.
 * Space Complexity: O(N) for recursion stack and tree representation.
 */

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> cats;
vector<vector<int>> adj;
int ans = 0;

void dfs(int u, int parent, int consecutive) {

    // Update consecutive cat count
    if (cats[u] == 1) {
        consecutive++;
    } else {
        consecutive = 0;
    }

    // Stop if too many consecutive cats
    if (consecutive > m) {
        return;
    }

    // Check whether current vertex is a leaf
    bool isLeaf = true;

    for (int v : adj[u]) {
        if (v != parent) {
            isLeaf = false;
            dfs(v, u, consecutive);
        }
    }

    // Count valid leaf vertices
    if (isLeaf) {
        ans++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    cats.resize(n + 1);
    adj.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> cats[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 0);

    cout << ans << '\n';

    return 0;
}
