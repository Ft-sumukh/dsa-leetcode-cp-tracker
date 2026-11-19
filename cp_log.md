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
| 2026-11-17 | Codeforces | Codeforces Round 498 (Div. 3) | — | — | 1 | 1 (E) | 0 | Trees, DFS, Preorder, Euler Tour | None (Clean solve / Upsolve) |
| 2026-11-18 | Codeforces | Codeforces Round 635 (Div. 1) | — | — | 1 | 1 (A) | 0 | Trees, DFS, Greedy, Subtree Size, Sorting | None (Clean solve / Upsolve) |
| 2026-11-19 | Codeforces | Codeforces Round 722 (Div. 1) | — | — | 1 | 1 (A) | 0 | Trees, DP on Trees, Greedy, DFS | None (Clean solve / Upsolve) |

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
  * **Complexity:** Time $O(N + \sum K)$, Space $O(N)$.

### Codeforces Round 498 (Div. 3) (Date: 2026-11-17)
* **Contest URL:** [Codeforces Contest 1006](https://codeforces.com/contest/1006)
* **Solved During/After:** E (1006E - Military Problem)
* **Wrong Submissions:** 0
* **Topics Involved:** Trees, Depth-First Search (DFS), Preorder Traversal, Subtree Range
* **Key Problem Review - 1006E (Military Problem):**
  * **Solution File:** [`codeforces/1006E_military_problem.cpp`](file:///d:/leetcode/codeforces/1006E_military_problem.cpp)
  * **Approach:** Subordinates are visited in increasing order of IDs, exactly matching a DFS preorder traversal where child adjacency lists are sorted. Using an iterative DFS, record preorder sequence `order` and subtree bounds `tin[u]` and `tout[u]`. The entire subtree of `u` occupies contiguous positions `order[tin[u] ... tout[u]]`. For each query `(u, k)`, the $k$-th visited subordinate is located at index `pos = tin[u] + k - 1`. If `pos <= tout[u]`, answer is `order[pos]`; otherwise `-1`.
  * **Complexity:** Time $O(N + Q)$ ($O(N)$ DFS preprocessing, $O(1)$ per query), Space $O(N)$.

### Codeforces Round 635 (Div. 1) (Date: 2026-11-18)
* **Contest URL:** [Codeforces Contest 1336](https://codeforces.com/contest/1336) *(also Div. 2 Problem C / 1337C)*
* **Solved During/After:** A (1336A - Linova and Kingdom)
* **Wrong Submissions:** 0
* **Topics Involved:** Trees, Depth-First Search (DFS), Greedy, Subtree Sizes, Sorting
* **Key Problem Review - 1336A (Linova and Kingdom):**
  * **Solution File:** [`codeforces/1336A_linova_and_kingdom.cpp`](file:///d:/leetcode/codeforces/1336A_linova_and_kingdom.cpp)
  * **Approach:** Root the tree at capital city 1 with 1-indexed depth (`depth[1] = 1`). Run an iterative DFS to record traversal order, parents, and depths, then accumulate subtree sizes `sz[u]` bottom-up in reverse DFS order. Making node `u` an industrial city contributes `(depth[u] - 1)` happiness from its ancestors minus `(sz[u] - 1)` lost by its descendants, giving a net greedy score of `depth[u] - sz[u]`. Because every child strictly scores higher than its parent, sorting scores descending and summing the top `k` automatically selects valid subtrees first and yields the maximum happiness.
  * **Complexity:** Time $O(N \log N)$ (sorting scores; DFS and subtree calculation are $O(N)$), Space $O(N)$.

### Codeforces Round 722 (Div. 1) (Date: 2026-11-19)
* **Contest URL:** [Codeforces Contest 1528](https://codeforces.com/contest/1528) *(also Div. 2 Problem C / 1529C)*
* **Solved During/After:** A (1528A - Parsa's Humongous Tree)
* **Wrong Submissions:** 0
* **Topics Involved:** Trees, Dynamic Programming (Tree DP), Greedy, DFS
* **Key Problem Review - 1528A (Parsa's Humongous Tree):**
  * **Solution File:** [`codeforces/1528A_parsas_humongous_tree.cpp`](file:///d:/leetcode/codeforces/1528A_parsas_humongous_tree.cpp)
  * **Approach:** Because the objective is a sum of convex functions $|a_u - a_v|$, the optimal value for each vertex $u$ is guaranteed to lie at an extreme boundary: either $a_u = l_u$ or $a_u = r_u$. We run an iterative DFS to build parent pointers and topological order, then compute a 2-state Tree DP bottom-up in reverse DFS order: $dp[u][0]$ (if choosing $l_u$) and $dp[u][1]$ (if choosing $r_u$). For each child $v$, transition greedily by taking the maximum between $v$ picking $l_v$ and $r_v$. Total answer is $\max(dp[1][0], dp[1][1])$.
  * **Complexity:** Time $O(N)$ per testcase ($O(\sum N)$ overall), Space $O(N)$.

