/**
 * Problem: Codeforces 1336A - Linova and Kingdom
 * Contest: Codeforces Round 635 (Div. 1) — Problem A (also Div. 2 Problem C / 1337C)
 * Rating: 1600
 * URL: https://codeforces.com/contest/1336/problem/A
 * 
 * Algorithm / Approach:
 * - Root the tree at capital city 1 with 1-indexed depth (`depth[1] = 1`).
 * - Use an iterative DFS to record traversal order, parents, and depths without stack overflow risk.
 * - Traverse nodes in reverse DFS order to compute each subtree size `sz[u]` (including `u` itself).
 * - Greedy Observation:
 *   - Suppose we convert city `u` from a tourism city to an industrial city (assuming its descendants
 *     are already industrial and its ancestors are tourism cities):
 *     - City `u` gains `depth[u] - 1` happiness (number of tourism ancestors to root 1).
 *     - Each of its `sz[u] - 1` descendants loses 1 happiness because `u` is no longer a tourism city.
 *     - Net contribution of selecting `u`: `(depth[u] - 1) - (sz[u] - 1) = depth[u] - sz[u]`.
 *   - Since `depth[child] > depth[parent]` and `sz[child] < sz[parent]`, every child strictly has a
 *     higher score than its parent, so sorting scores descending guarantees descendants are always
 *     selected before their ancestors.
 * - Sum the top `k` largest scores to obtain the maximum total happiness.
 * 
 * Time Complexity: O(N log N) due to sorting scores (iterative DFS and subtree sizes take O(N)).
 * Space Complexity: O(N) for adjacency list, parent, depth, subtree size, order, and scores arrays.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false); // Faster input/output
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;               // n = cities, k = industrial cities

    vector<vector<int>> adj(n + 1); // Adjacency list of the tree

    // Build the undirected tree
    for (int i = 0; i < n - 1; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);     // Connect v to u
        adj[v].push_back(u);     // Connect u to v
    }

    vector<int> parent(n + 1, 0); // Stores parent of each node
    vector<int> depth(n + 1, 0);  // Stores depth of each node
    vector<int> sz(n + 1, 1);     // Initially every subtree has its own node

    vector<int> order;            // Stores DFS traversal order
    order.reserve(n);

    // Iterative DFS starting from root 1
    stack<int> st;
    st.push(1);

    depth[1] = 1;                 // Root depth is 1

    while (!st.empty()) {

        int u = st.top();
        st.pop();

        order.push_back(u);       // Record current node

        for (int v : adj[u]) {

            if (v == parent[u])   // Avoid travelling back to parent
                continue;

            parent[v] = u;        // Store parent of child
            depth[v] = depth[u] + 1; // Calculate child depth

            st.push(v);           // Explore child later
        }
    }

    // Calculate subtree sizes in reverse DFS order
    for (int i = n - 1; i > 0; i--) {

        int u = order[i];

        sz[parent[u]] += sz[u];   // Add child's subtree to parent's subtree
    }

    vector<int> scores;
    scores.reserve(n);

    // Calculate greedy score for every city
    for (int u = 1; u <= n; u++) {

        int score = depth[u] - sz[u];

        scores.push_back(score);
    }

    // Sort scores from largest to smallest
    sort(scores.rbegin(), scores.rend());

    long long ans = 0;

    // Select exactly k cities with the highest scores
    for (int i = 0; i < k; i++) {

        ans += scores[i];         // Add selected city's contribution
    }

    cout << ans << '\n';          // Print maximum happiness

    return 0;
}
