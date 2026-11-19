/**
 * Problem: Codeforces 1528A - Parsa's Humongous Tree
 * Contest: Codeforces Round 722 (Div. 1) — Problem A (also Div. 2 Problem C / 1529C)
 * Rating: 1600
 * URL: https://codeforces.com/contest/1528/problem/A
 * 
 * Algorithm / Approach:
 * - We are given a tree where each node u must pick a value a[u] in [l[u], r[u]] to maximize
 *   the sum of absolute differences |a[u] - a[v]| across all edges (u, v).
 * - Key Mathematical Property (Convexity / Extremal Principle):
 *   Since the objective function is a sum of convex functions |a[u] - a[v]|, the maximum must
 *   occur at one of the endpoints of the allowed interval for each vertex. That is, for every
 *   node u, either a[u] = l[u] or a[u] = r[u] in an optimal assignment.
 * - Tree Dynamic Programming:
 *   - dp[u][0]: Maximum beauty of u's subtree if u chooses l[u].
 *   - dp[u][1]: Maximum beauty of u's subtree if u chooses r[u].
 *   - For each child v of u:
 *     - dp[u][0] += max(dp[v][0] + |l[u] - l[v]|, dp[v][1] + |l[u] - r[v]|)
 *     - dp[u][1] += max(dp[v][0] + |r[u] - l[v]|, dp[v][1] + |r[u] - r[v]|)
 * - Traversal:
 *   - An iterative DFS roots the tree at node 1 and establishes parent pointers and topological
 *     order, avoiding call stack overflow on deep/skewed trees.
 *   - DP is computed bottom-up in reverse DFS order.
 * 
 * Time Complexity: O(N) per testcase, O(sum N) overall <= 2e5 operations.
 * Space Complexity: O(N) for tree adjacency, parent, order, and DP arrays.
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {

    int n;
    cin >> n;

    vector<ll> l(n + 1), r(n + 1);

    // Read the two possible values for every node
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }

    vector<vector<int>> adj(n + 1);

    // Build the undirected tree
    for (int i = 0; i < n - 1; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order;

    order.reserve(n);

    // Iterative DFS to establish parent-child relationships
    stack<int> st;
    st.push(1);

    parent[1] = -1;

    while (!st.empty()) {

        int u = st.top();
        st.pop();

        order.push_back(u);

        for (int v : adj[u]) {

            if (v == parent[u])
                continue;

            parent[v] = u;
            st.push(v);
        }
    }

    // dp[u][0] = Best answer if node u chooses l[u]
    // dp[u][1] = Best answer if node u chooses r[u]

    vector<array<ll, 2>> dp(n + 1, {0, 0});

    // Process nodes in reverse DFS order (children before parents)
    for (int i = n - 1; i >= 0; i--) {

        int u = order[i];

        // Process every child of current node
        for (int v : adj[u]) {

            if (v == parent[u])
                continue;

            // Contribution if u chooses l[u]
            ll chooseL = max(
                dp[v][0] + abs(l[u] - l[v]),
                dp[v][1] + abs(l[u] - r[v])
            );

            // Contribution if u chooses r[u]
            ll chooseR = max(
                dp[v][0] + abs(r[u] - l[v]),
                dp[v][1] + abs(r[u] - r[v])
            );

            // Add child's best contribution to current node
            dp[u][0] += chooseL;
            dp[u][1] += chooseR;
        }
    }

    // Root can choose either l[1] or r[1]
    cout << max(dp[1][0], dp[1][1]) << '\n';
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;                   // Number of test cases

    while (t--) {
        solve();
    }

    return 0;
}
