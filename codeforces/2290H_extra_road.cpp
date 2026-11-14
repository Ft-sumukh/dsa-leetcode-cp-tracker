/**
 * Problem: Codeforces 2290H - Extra Road
 * Contest: Codeforces Round 1134 (Div. 4)
 * URL: https://codeforces.com/contest/2290/problem/H
 * 
 * Algorithm / Approach:
 * - Root the tree at vertex 1 and calculate subtree sizes for all nodes using BFS order.
 * - Binary search the minimum number of unreachable cities x in [0, n - 1].
 * - For a fixed threshold x, identify all "important" edges whose subtree size exceeds x.
 * - If no subtree size exceeds x, threshold x is trivially feasible.
 * - Otherwise, find the tree diameter among all marked endpoints of the important edges
 *   using double BFS/DFS (find farthest marked vertex `a` from an arbitrary marked vertex,
 *   then find farthest marked vertex `b` from `a`).
 * - Mark all vertices along the tree path between `a` and `b`.
 * - Feasibility condition: An extra road can cover all cuts > x if and only if every 
 *   important edge lies entirely on this simple path between `a` and `b`.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    // Build the tree
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Root the tree at vertex 1
    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    vector<int> order;

    order.push_back(1);

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];

        for (int v : adj[u]) {
            if (v == parent[u]) continue;

            parent[v] = u;
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }

    // Calculate subtree sizes
    vector<int> sz(n + 1, 1);

    for (int i = n - 1; i > 0; i--) {
        int u = order[i];
        sz[parent[u]] += sz[u];
    }

    // Binary search feasibility check
    auto check = [&](int x) -> bool {

        vector<char> marked(n + 1, false);
        vector<int> important;

        // Mark endpoints of edges with subtree size > x
        for (int v = 2; v <= n; v++) {
            if (sz[v] > x) {
                marked[v] = true;
                marked[parent[v]] = true;
                important.push_back(v);
            }
        }

        if (important.empty()) {
            return true;
        }

        // Find farthest marked vertex
        auto farthest = [&](int start) {
            int best = start;
            int bestDist = -1;

            vector<tuple<int, int, int>> st;
            st.push_back({start, 0, 0});

            while (!st.empty()) {
                auto [u, p, d] = st.back();
                st.pop_back();

                if (marked[u] && d > bestDist) {
                    bestDist = d;
                    best = u;
                }

                for (int v : adj[u]) {
                    if (v != p) {
                        st.push_back({v, u, d + 1});
                    }
                }
            }

            return best;
        };

        // Find diameter endpoints among marked vertices
        int a = farthest(important[0]);
        int b = farthest(a);

        // Mark the path between a and b
        vector<char> onPath(n + 1, false);

        int u = a;
        int v = b;

        while (depth[u] > depth[v]) {
            onPath[u] = true;
            u = parent[u];
        }

        while (depth[v] > depth[u]) {
            onPath[v] = true;
            v = parent[v];
        }

        while (u != v) {
            onPath[u] = true;
            onPath[v] = true;

            u = parent[u];
            v = parent[v];
        }

        onPath[u] = true;

        // Every important edge must belong to this path
        for (int node : important) {
            if (!onPath[node] || !onPath[parent[node]]) {
                return false;
            }
        }

        return true;
    };

    // Binary search minimum number of unreachable cities
    int low = 0;
    int high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (check(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << n - low << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
