/**
 * Problem: Codeforces 1006E - Military Problem
 * Contest: Codeforces Round 498 (Div. 3)
 * URL: https://codeforces.com/contest/1006/problem/E
 * 
 * Algorithm / Approach:
 * - The army hierarchy is represented as a rooted tree at vertex 1.
 * - Officers give commands to their subordinates in increasing order of IDs, exactly matching
 *   a depth-first search (DFS) preorder traversal where children are visited in increasing ID order.
 * - Since each node `i` (from 2 to n) is pushed to `adj[p]` in increasing order of `i`, the children
 *   lists are naturally sorted in ascending order.
 * - Perform an iterative DFS to record:
 *   - `order[t]`: The vertex visited at preorder timestamp `t`.
 *   - `tin[u]`: Preorder start index for vertex `u`.
 *   - `tout[u]`: Preorder end index for vertex `u`'s subtree.
 * - The entire subtree of `u` occupies a contiguous segment in `order` from `tin[u]` to `tout[u]`.
 * - For each query `(u, k)`:
 *   - The k-th visited officer in `u`'s subtree corresponds to index `pos = tin[u] + k - 1`.
 *   - If `pos <= tout[u]`, output `order[pos]`.
 *   - Otherwise, the subtree has fewer than `k` vertices, so output `-1`.
 * 
 * Time Complexity:
 * - Preprocessing: O(N) via iterative DFS preorder traversal.
 * - Per Query: O(1) direct array indexing.
 * - Total Time: O(N + Q).
 * Space Complexity: O(N) for tree adjacency, preorder order array, tin, tout, and recursion/stack.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false); // Faster input/output
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;               // Read number of nodes and queries

    vector<vector<int>> adj(n + 1); // Stores children of every node

    // Read the parent of each node
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;

        adj[p].push_back(i);     // Add node i as a child of p
    }

    vector<int> tin(n + 1);      // Starting DFS index of each subtree
    vector<int> tout(n + 1);     // Ending DFS index of each subtree
    vector<int> order(n);        // Stores the DFS preorder traversal

    vector<int> nextChild(n + 1, 0); // Tracks the next child to visit

    int timer = 0;               // Current DFS preorder index

    stack<int> st;
    st.push(1);                  // Start DFS from root node 1

    // Iterative DFS traversal
    while (!st.empty()) {

        int u = st.top();        // Get current node

        // First time visiting this node
        if (nextChild[u] == 0 && tin[u] == 0) {

            tin[u] = timer;      // Record starting index
            order[timer] = u;    // Store node in DFS order
            timer++;             // Move to next index
        }

        // If unvisited children remain
        if (nextChild[u] < (int)adj[u].size()) {

            int v = adj[u][nextChild[u]]; // Get next child
            nextChild[u]++;               // Move to next child index

            st.push(v);                   // Explore child first
        }
        else {

            // All children have been processed
            tout[u] = timer - 1;           // Record ending index

            st.pop();                      // Finish current node
        }
    }

    // Process queries
    while (q--) {

        int u, k;
        cin >> u >> k;

        // Calculate the required position in DFS order
        int pos = tin[u] + k - 1;

        // Check whether the position belongs to u's subtree
        if (pos <= tout[u]) {
            cout << order[pos] << '\n';    // Print required node
        }
        else {
            cout << -1 << '\n';            // Not enough subtree nodes
        }
    }

    return 0;
}
