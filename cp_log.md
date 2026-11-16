# 🏆 Competitive Programming Log

## 📊 Ratings Dashboard

* **Codeforces Rating:** —
* **CodeChef Rating:** —
* **AtCoder Rating:** —

---

## 📉 Weakness Analysis

Identify whether weaknesses in contests are due to:
* **Algorithm Knowledge:** (e.g., didn't know Segment Tree, FFT)
* **Problem-solving:** (e.g., couldn't find the constructive logic/pattern)
* **Speed:** (e.g., solved A and B but ran out of time for C)
* **Mathematics:** (e.g., number theory, combinatorics, probability)
* **Implementation:** (e.g., coding took too long, bugs in implementation)
* **Debugging:** (e.g., spent 45 minutes finding a small bug)
* **Contest Strategy:** (e.g., spent too much time on a hard problem instead of scanning others)
* **Understanding the problem:** (e.g., misread the statement and solved a different problem)

| Weakness Category | Frequency / Notes |
| :--- | :--- |
| Algorithm Knowledge | 1x (1328E: Naive parent climbing gave TLE on deep trees; resolved using Euler tour tin/tout O(1) ancestor check) |
| Problem-solving | |
| Speed | |
| Mathematics | |
| Implementation | |
| Debugging | |
| Contest Strategy | |
| Understanding Problem | |

---

## 📅 Contest Log

| Date | Platform | Contest Name | Rank | Rating (Before ➡️ After) | Attempted | Solved (During/After) | Wrong Subs | Topics | Primary Weakness / Failure Reason |
| :---: | :---: | :--- | :---: | :---: | :---: | :---: | :---: | :--- | :--- |
| 2026-11-14 | Codeforces | Codeforces Round 1134 (Div. 4) | — | — | 1 | 1 (H) | 0 | Trees, Binary Search, Tree Diameter | None (Clean solve / Upsolve) |
| 2026-11-14 | Codeforces | Codeforces Round 321 (Div. 2) | — | — | 1 | 1 (C) | 0 | Trees, DFS, Graphs | None (Clean solve / Upsolve) |
| 2026-11-16 | Codeforces | Codeforces Round 629 (Div. 3) | — | — | 1 | 1 (E) | 1 (TLE) | Trees, DFS, Euler Tour, Ancestors | TLE on Test 80: Replaced O(K*H) parent climbing with O(1) tin/tout check |

*Platforms: Codeforces / CodeChef / AtCoder*

---

## 📝 Detailed Contest Reviews

*(Use this section to review each contest in detail, analyzing specific problems, wrong submissions, and key takeaways.)*

### Codeforces Round 1134 (Div. 4) (Date: 2026-11-14)
* **Contest URL:** [Codeforces Contest 2290](https://codeforces.com/contest/2290)
* **Solved During/After:** H (2290H - Extra Road)
* **Wrong Submissions:** 0
* **Topics Involved:** Binary Search, Trees, Tree Diameter, Subtree Size
* **Key Problem Review - 2290H (Extra Road):**
  * **Solution File:** [`codeforces/2290H_extra_road.cpp`](file:///d:/leetcode/codeforces/2290H_extra_road.cpp)
  * **Approach:** Binary search on the answer $x$ (the minimum number of unreachable cities after adding at most one shortcut edge). For a candidate $x$, mark all edges whose subtree size exceeds $x$. Any single added shortcut edge can connect the ends of at most one path; hence, all critical edges exceeding $x$ must lie along a single simple path in the tree. We verify this by computing the diameter endpoints among marked nodes using double DFS/BFS and checking if all marked edges are covered by this diameter path.
  * **Complexity:** Time $O(N \log N)$, Space $O(N)$.

### Codeforces Round 321 (Div. 2) (Date: 2026-11-14)
* **Contest URL:** [Codeforces Contest 580](https://codeforces.com/contest/580)
* **Solved During/After:** C (580C - Kefa and Park)
* **Wrong Submissions:** 0
* **Topics Involved:** Trees, Depth-First Search (DFS), Graphs
* **Key Problem Review - 580C (Kefa and Park):**
  * **Solution File:** [`codeforces/580C_kefa_and_park.cpp`](file:///d:/leetcode/codeforces/580C_kefa_and_park.cpp)
  * **Approach:** Perform DFS from the root (vertex 1) down to the leaves, keeping track of the running consecutive count of vertices with cats along the current root-to-node path. If the current vertex has a cat, increment the consecutive count; otherwise, reset it to 0. If `consecutive > m`, prune that subtree immediately. If a leaf vertex is reached without exceeding $m$ consecutive cats, increment the valid restaurant count.
  * **Complexity:** Time $O(N)$, Space $O(N)$.

### Codeforces Round 629 (Div. 3) (Date: 2026-11-16)
* **Contest URL:** [Codeforces Contest 1328](https://codeforces.com/contest/1328)
* **Solved During/After:** E (1328E - Tree Queries)
* **Wrong Submissions:** 1 (TLE on Test 80)
* **Main Reason for Failure / Refactoring:** Initial solution climbed parent pointers step-by-step (`while (depth[v] > depth[p]) v = parent[v]`), which degraded to $O(K \cdot H)$ per query ($O(K \cdot N)$ on degenerate chain trees) causing TLE on test 80. Refactored to precompute Euler tour entry/exit timestamps (`tin`, `tout`) via iterative DFS, enabling $O(1)$ ancestor verification (`tin[u] <= tin[v] && tout[v] <= tout[u]`).
* **Topics Involved:** Trees, Depth-First Search (DFS), Euler Tour Timestamps (`tin`/`tout`), Ancestor Checking
* **Key Problem Review - 1328E (Tree Queries):**
  * **Solution File:** [`codeforces/1328E_tree_queries.cpp`](file:///d:/leetcode/codeforces/1328E_tree_queries.cpp)
  * **Approach:** A query vertex $u$ is within distance 1 of a root-to-$v$ path if and only if $u$ or $parent[u]$ lies on the path. Since the path begins at the root, every node on it is an ancestor of the path endpoint. Therefore, replacing each $u$ (except 1) with $parent[u]$ reduces the problem to checking if all adjusted vertices lie on a single ancestor chain. We pick the deepest vertex among the query set as the target endpoint, and verify that the parent of every other query vertex is an ancestor of this deepest vertex using $O(1)$ Euler tour entry/exit timestamp intervals.
  * **Complexity:** Time $O(N + \sum K)$, Space $O(N).
