# Graph
## Concept of a Graph
### Directed and Undirected Graphs 
**A directed graph** (or digraph) $G = (V, E)$ is defined by:  
- **Vertex Set** ($V$): A non-empty set of points or nodes.  
- **Edge Set** ($E$): A set of directed links. Each edge $e \in E$ is associated with an ordered pair of vertices $(v_i, v_j)$, where $v_i$ is the initial vertex and $v_j$ is the terminal vertex.  
- **Order**: The total number of vertices ($|V|$). 
- **Size**: The total number of edges ($|E|$). 

**Undirected Graph**: The pairs of vertices $\{v_i, v_j\}$ linked by an edge are unordered. There are no arrows; travel can go both ways.  
- **Underlying Undirected Graph**: The undirected graph formed by stripping away all the directional arrows from a directed graph.  
- **Mixed Graph**: A graph containing both directed and undirected edges. 

Vertices and edges can be assigned labels, colors, or weights to model real-world data.  
- **Loop Edge**: An edge whose initial vertex is the exact same as its terminal vertex.  
- **Multiple/Parallel Edges**: Two or more distinct edges that share the exact same initial and terminal vertices.  
 
### Adjacency and Incidence Relations
- **Vertex-to-Vertex Adjacency**: Two vertices are adjacent if they are connected by an edge.  
- **Edge-to-Edge Adjacency**: Two edges are adjacent if they share a common vertex.  
- **Incidence**: If an edge $e$ connects $(v_i, v_j)$, the vertices $v_i$ and $v_j$ are incident with edge $e$, and the edge $e$ is incident with those vertices.  

### Advanced Vertex Sets
- **Independent Vertex Set / Stable Set**: A subset of vertices $V' \subset V$ where no two vertices are adjacent to each other.  
- **Independent Edge Set / Matching Set**: A subset of edges $E' \subset E$ where no two edges share a common vertex.  
- **Clique**: A subset of vertices $V' \subset V$ where every pair of vertices is mutually adjacent (they form a complete network within the graph).  
## Concept of Vertex Degree
### Defining Degrees
- **Undirected Degree** ($deg(v)$ or $d(v)$): The total number of edges incident to vertex $v$. 
Crucial Rule: A loop edge counts as 2 toward the degree of its vertex.  
- **Maximum Degree** ($\Delta(G)$): The highest degree value among all vertices in graph $G$.  
- **Minimum Degree** ($\delta(G)$): The lowest degree value among all vertices in graph $G$.  
- **In-Degree** ($d^-(v)$): The number of edges pointing into vertex $v$.  
- **Out-Degree** ($d^+(v)$): The number of edges pointing out of vertex $v$.  
### Special Vertex/Edge Types
- **Isolated Vertex**: A vertex with a degree of $0$ ($deg(v) = 0$).  
- **Pendant Vertex / Leaf**: A vertex with a degree of 1 ($deg(v) = 1$).  
- **Pendant Edge**: An edge connected to a pendant vertex.  
### Core Degree Theorems
> [!IMPORTANT]
> **Theorem 2.1: The Handshaking Lemma**
> 
> In any graph $G = (V, E)$, the sum of the degrees of all vertices is exactly twice the number of edges:
>  $$\sum_{v \in V} d(v) = 2|E|$$

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> 
> Consider any single, arbitrary edge $e \in E$.
> 
> - If $e$ is a standard edge connecting two distinct vertices $u$ and $v$ (i.e., $e = \{u, v\}$), it has exactly 2 distinct endpoints. Thus, it contributes exactly $2$ to the total count of incidence pairs.
> - If $e$ is a loop edge connecting a vertex $v$ to itself (i.e., $e = \{v, v\}$), it connects to only one vertex, but it meets that vertex at both of its ends. By standard definition, a loop edge contributes exactly $2$ to the degree of that vertex.
> 
> Since every single edge $e \in E$ contributes exactly $2$ endpoints to the graph, the total number of endpoints across the entire edge set is:
> 
> $$\text{Total Endpoints} = 2 \times |E|$$ $\blacksquare$
> 
> </details>
  
> [!IMPORTANT]
> **Corollary 2.1**: 
>
> The number of vertices with an odd degree in any graph must always be an even number.  

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> 
> $$\sum_{v \in V} \text{deg}(v) = 2|E|$$
> $$\sum_{v \in V_{\text{even}}} \text{deg}(v) + \sum_{v \in V_{\text{odd}}} \text{deg}(v) = 2|E|$$
> $$\text{Even} + \sum_{v \in V_{\text{odd}}} \text{deg}(v) = \text{Even}$$
> $$\sum_{v \in V_{\text{odd}}} \text{deg}(v) = \text{Even}$$
> Because our total sum is guaranteed to be even, the number of terms inside that sum—which is the number of vertices with an odd degree ($|V_{\text{odd}}|$)—must be an even number. $\blacksquare$
> </details>

> [!IMPORTANT]
> **Theorem 2.2 (Digraph Handshaking):** 
>
> In a directed graph, the sum of all in-degrees equals the sum of all out-degrees, which equals the total edge size:
> $$\sum_{v \in V} d^+(v) = \sum_{v \in V} d^-(v) = |E|$$

> [!IMPORTANT]
> **Theorem 2.3:** 
>
> In any **simple graph** with $n \ge 2$ vertices, there always exist at least two vertices with the exact same degree. 

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> 
> Let $G$ be a simple graph with $n$ vertices ($n \ge 2$). The theoretically possible degree for any vertex is an integer from the set $\{0, 1, 2, \dots, n-1\}$.  
> 
> However, a simple graph cannot simultaneously contain a vertex of degree $0$ (completely isolated) and a vertex of degree $n-1$ (connected to everyone else).  
> 
> Thus, the actual degrees can only come from one of two restricted sets:
> - Set 1 (No vertex has degree $n-1$): $\{0, 1, 2, \dots, n-2\}$
> - Set 2 (No vertex has degree $0$): $\{1, 2, 3, \dots, n-1\}$
> 
> In either case, there are exactly $n-1$ available degree values (pigeonholes) to distribute among $n$ vertices (pigeons).
> 
> By the Pigeonhole Principle, when assigning $n$ vertices to $n-1$ degree values, at least two vertices must be assigned the exact same degree value. $\blacksquare$
> </details>

### Graphical Sequences
A sequence of non-negative integers $\{d_1, d_2, \dots, d_n\}$ is graphical if there exists a real **simple graph** whose vertex degrees match those numbers.  

> [!IMPORTANT]
> **Erdős–Gallai Theorem:** 
>
> A non-increasing sequence of positive integers $\{d_1, \dots, d_n\}$ is graphical if and only if their sum is even, and for every $k$ from $1$ to $n$:
> $$\sum_{i=1}^{k} d_i \le k(k - 1) + \sum_{j=k+1}^{n} \min(k, d_j)$$

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> 
> Let $G = (V, E)$ be a simple graph with $n$ vertices whose degrees are sorted such that $d_1 \ge d_2 \ge \dots \ge d_n$. Fix an integer $k \in \{1, 2, \dots, n\}$. Partition the vertex set into $V_1 = \{v_1, \dots, v_k\}$ and $V_2 = \{v_{k+1}, \dots, v_n\}$.
> 
> Consider the sum of degrees of vertices in $V_1$. By definition, this sum counts the total number of incidences with vertices in $V_1$:
> 
> $$\sum_{i=1}^{k} d_i = 2|E(V_1)| + |E(V_1, V_2)|$$
> 
> where $E(V_1)$ is the set of edges with both endpoints in $V_1$, and $E(V_1, V_2)$ is the set of cut-edges with one endpoint in $V_1$ and the other in $V_2$.
> 
> We bound these two constituent terms individually:
> - Internal Edges ($V_1$): Since $G$ is a simple graph, the maximum number of edges within a clique of size $k$ is $\binom{k}{2}$. Thus:
> 
> $$2|E(V_1)| \le 2 \binom{k}{2} = k(k-1)$$
> 
> - Cross-Boundary Edges ($V_1 \times V_2$): For any fixed vertex $v_j \in V_2$, its maximum number of neighbors in $V_1$ is bounded by $|V_1| = k$ since $G$ is simple. Simultaneously, its total degree bounding its total neighbors in the entire graph is $d_j$. Thus, $v_j$ can share at most $\min(k, d_j)$ edges with $V_1$. Summing over all vertices in $V_2$:
> 
> $$|E(V_1, V_2)| \le \sum_{j=k+1}^{n} \min(k, d_j)$$
> 
> Combining these structural upper bounds yields:
> 
> $$\sum_{i=1}^{k} d_i \le k(k-1) + \sum_{j=k+1}^{n} \min(k, d_j)$$
> </details>

## Types of Graphs
### Simple Graph
A simple graph is represented as an ordered pair $G = (V, E)$, where:  
- $V$ is a non-empty set of vertices.  
- $E$ is a set of edges, where each edge $e \in E$ is an unordered pair $\{u, v\}$ of distinct vertices from $V$ ($u \neq v$).
$\Rightarrow$ unweighted, undirected, no loops, no parallel edges.
### Null Graph
Contains vertices but has zero edges ($E = \emptyset$) _(some books might define this as having no vertices and no edges)_.
<img src='/graph/images/null.png' width=300>

### Regular Graph
Every vertex has the exact same degree $k$ (called a $k$-regular graph). It contains $\frac{n \times k}{2}$ edges.  
<img src='/graph/images/regular.png' width=600>

### Complete Graph 
A Complete Graph ($K_n$) is a simple graph where an edge exists between every single pair of vertices. It has exactly $\frac{n(n-1)}{2}$ edges.  

This is a complete graph of $5$ vertices $K_5$.
<img src='/graph/images/complete.png' width=400>

### Bipartite Graph 
The vertex set $V$ can be partitioned into two sets ($V, U$) such that edges only connect vertices between $V$ and $U$, never within the same set.  
<img src='/graph/images/bipartite.png' width=300>

#### Properties
1. An undirected graph is bipartite if and only if it does **not contain an odd cycle**.
2. A graph is bipartite if and only if it is **2-colorable**, (i.e. its chromatic number is less than or equal to 2).
3. ${\displaystyle \sum _{v\in V}\deg v=\sum _{u\in U}\deg u=|E|\,.}$

#### Testing bipartiteness
To test whether a graph is bipartite, we leverage the fundamental property: a graph is bipartite if and only if it can be colored using exactly 2 colors (with no two adjacent vertices sharing a color), which is mathematically equivalent to saying it contains no odd cycles.

We can use either DFS or BFS.

**Core Idea:** 
As we traverse the graph, assign every vertex a status label or "color" (e.g., 1 or -1). When we are at a vertex colored 1, we force all of its unvisited neighbors to be colored -1. 

If we ever discover a neighbor that has already been visited and it shares the same color as the current vertex, we have discovered an odd cycle, meaning the graph is not bipartite.

```cpp
IS_BIPARTITE_BFS(G)
    create color array/map
    for each vertex v in V
        color[v] = 0  // 0 means uncolored/unvisited

    create a queue Q

    for each vertex v in V
        if color[v] == 0
            color[v] = 1  // Start component with color 1
            Q.push(v)

            while Q is not empty
                cur = Q.front
                Q.pop

                for neighbor in G[cur]
                    if color[neighbor] == 0
                        // Alternatingly assign the opposite color
                        color[neighbor] = -color[cur] 
                        Q.push(neighbor)
                    else if color[neighbor] == color[cur]
                        return false      
    return true
```

```cpp
IS_BIPARTITE_DFS(G)
    create color array/map
    for each vertex v in V
        color[v] = 0  // 0 means uncolored/unvisited

    for each vertex v in V
        if DFS_VISIT(G, v, 1, color) == false
            return false

    return true

DFS_VISIT(G, cur, c, color)
    color[cur] = c

    for neighbor in G[cur]
        if color[neighbor] == 0
            if DFS(G, neighbor, -c, color) == false
                return false
        else if color[neighbor] == c
            return false
    return true
```
> [!NOTE]
> [C++ Code](/graph/bipartite.cpp)

### Complete Bipartite Graph 
Complete Bipartite Graph $K_{m,n}$ is a bipartite graph  where every single vertex in $V_1$ ($|V_1|=m$) connects to every single vertex in $V_2$ ($|V_2|=n$). It contains $m \times n$ edges.  
<img src='/graph/images/completeBipartite.png' width=400>

### Cycle Graph
A Cycle Graph ($C_n$) is a simple graph with $n$ vertices connected in a closed structural ring. 

The number of vertices in $C_n$ equals the number of edges, and every vertex has degree 2.

A cycle graph is:
- 2-edge colorable, if and only if it has an even number of vertices
2-regular
- 2-vertex colorable, if and only if it has an even number of vertices. More generally, a graph is bipartite if and only if it has no odd cycles.
- Connected
<img src='/graph/images/cycle.png' width=200>

### Star Graph
Star Graph ($S_k$) is a graph with $k+1$ vertices where one central vertex has a degree of $k$ and the remaining $k$ outer vertices have a degree of 1.  

Is a complete bipartite graph $K_{1,k}$.

<img src='/graph/images/star.png' width=300>

### Wheel Graph 
Wheel Graph $W_{n+1}$ (or $W_n$ in some books) is created by taking a cycle graph $C_n$ and adding a single central "hub" vertex that connects to every vertex along the cycle.  

<img src='/graph/images/wheel.png' width=400>

- For odd values of $n$, $W_n$ is a perfect graph with chromatic number $3$.
- For even $n$, $W_n$ has chromatic number $4$, and (when $n \ge 6$) is not perfect.

### n-Cube / Hypercube Graph 
n-Cube / Hypercube Graph ($Q_n$) has $2^n$ vertices, each represented by an $n$-bit binary string. 

Two nodes are adjacent if their binary strings differ by exactly 1 bit. 

It has a total of $n \times 2^{n-1}$ edges.  

<img src='/graph/images/hypercube.png' width=300>

- Is a $n$-regular graph.
- Is bipartite (can be divided into one set of binary strings with an even number of $1$s and one set of binary strings with an odd number of $1$s.)

<img src='/graph/images/hyperBipartite.png' width=400>


## Graph Operations & Products
### Basic Graph Operations
- **Add Vertex** $v$: $V = V + \{v\}$.  
- **Delete Vertex** $v$: Remove $v$ from $V$, then automatically erase all edges connected to it ($E = E - \{\text{incident edges}\}$).  
- **Add Edge** $e=(x,y)$: $E = E + \{e\}$ (and add vertices $x,y$ to $V$ if they don't exist yet).  
- **Delete Edge** $e$: $E = E - \{e\}$ (vertices remain untouched).  
- **Union** ($G_1 \cup G_2$): Combines vertices and edges: $(V_1 \cup V_2, E_1 \cup E_2)$.  
- **Intersection** ($G_1 \cap G_2$): Keeps only overlapping vertices and edges: $(V_1 \cap V_2, E_1 \cap E_2)$. 
 
### Cartesian Product
Cartesian Product ($G \times G'$) creates a complex structural grid out of two simpler graphs.  
- **Vertex Set**: The cross product $V \times V'$.  
- **Adjacency Rule**: Two coordinate nodes $(u, u')$ and $(v, v')$ are adjacent if and only if:  $u = v$ and $u'$ is adjacent to $v'$ in $G'$, OR  $u' = v'$ and $u$ is adjacent to $v$ in $G$ _( **identical in one coordinate and adjacent in the other** )_.

<img src='/graph/images/product.png' width=500>

## Structural Relationships & Isomorphism
- **Subgraph**: A graph $G_1=(V_1, E_1)$ is said to be a subgraph of a graph $G_1=(V_1, E_1)$ if $V1 \subseteq V2$ and $E1 \subseteq E2$.
_Note that since a subgraph is itself a graph, the endpoints of any edge in a subgraph must also be in the subgraph._

- **Spanning Subgraph**: A subgraph that must keep all vertices from the original graph, but retains only a subset of the edges. This is highly important for algorithms like Minimum Spanning Trees ($V' = V$).  
<img src='/graph/images/spanningSubgraph.png' width=500>
- **Induced Subgraph**:  a subset of a graph’s vertices, along with all the edges from the original graph that connect those vertices.
<img src='/graph/images/inducedSub.png' width=500>
- **Complement Graph** ($\overline{G}$): A graph containing the exact same vertex set ($V' = V$), but its edge set contains only the lines that are missing from the original graph. Combining a simple graph and its complement yields a Complete Graph: $G \cup \overline{G} = K_n$.  
<img src='/graph/images/complement.png' width=500>
- **Self-Complementary Graph**: A special graph that is structurally identical (isomorphic) to its own complement ($G \cong \overline{G}$).
<img src='/graph/images/self-complementary.png' width=200>
### Isomorphism
Two graphs $G$ and $G'$ are isomorphic ($G \cong G'$) if they are structurally identical, even if they are drawn completely differently on paper. 

Formally, if $G_1(V_1, E_1)$ and $G_2(V_2, E_2)$ are two graphs, then we say that $G_1$ is isomorphic to $G_2$ iff there exists a bijection $f: V_1 \to V_2$ such that for every pair of vertices $(u, v) \in V_1$:

$$\{u, v\} \in E_1 \iff \{f(u), f(v)\} \in E_2$$

The function $f$ is called an isomorphism between $G_1$ and $G_2$.

In other words, two graphs are isomorphic if they are the same up to a relabeling of their vertices.

Isomorphism preserves the connection properties of a graph, abstracting out what the vertices are called, what they are made out of, or where they appear in a drawing of the graph.

<img src='/graph/images/isomorphism.png' width=400>


To quickly prove two graphs are not isomorphic, check if they fail any of these conditions:
1. They must have an equal number of vertices ($|V_1| = |V_2|$).
2. They must have an equal number of edges ($|E_1| = |E_2|$).
3. Their sorted vertex degree sequences must be completely identical.

## Graph Representations

<img src='/graph/images/represent.png' width=700>

### Adjancency Matrix

An $n \times n$ square matrix $A = (a_{ij})$ where $n = |V|$.  
- $a_{ij} = 1$ if there is an edge pointing from vertex $i$ to vertex $j$.  
- $a_{ij} = 0$ if there is no edge.  

**Space Complexity**: $O(V^2)$.

**Key Property:** The adjacency matrix of an undirected graph is always perfectly symmetrical along its main diagonal ($a_{ij} = a_{ji}$). For multigraphs, $a_{ij}$ stores the integer count of parallel edges. For weighted graph, $a_{ij}$ stores the weight of the edge and we replace $0$ with a sensible value (like `NIL`, $0$, or $\infty$, depending on the application).



**Of bipartite graph**
The adjacency matrix $A$ of a bipartite graph whose two parts have $r$ and $s$ vertices can be written in the form
$$A = \begin{pmatrix} 
\mathbf{0}_{r \times r} & B_{r \times s} \\ 
B^T_{s \times r} & \mathbf{0}_{s \times s} 
\end{pmatrix}$$
- $\mathbf{0}_{r \times r}$ and $\mathbf{0}_{s \times s}$: zero matrices, represent the complete absence of edges within $V_1$ and within $V_2$.
- $B_{r \times s}$ (biadjacency matrix): represents the edges going from vertices in $V_1$ to vertices in $V_2$. If vertex $i \in V_1$ is connected to vertex $j \in V_2$, then $B[i][j] = 1$.

> [!IMPORTANT]
> **Theorem 5.1:** 
>
> Two graphs are isomorphic if and only if we can convert one adjacency matrix into the other using a permutation matrix $P$:
>
> $$P \cdot A_1 \cdot P^T = A_2 $$
>
> (A permutation matrix contains exactly one '1' in each row and column, effectively swapping rows and columns to re-index the nodes).  

<img src='/graph/images/permutation.png' width=700>

> [!NOTE]
> If we have already know the isomorphism $f$ of the two graphs, then we can come up with the permutation matrix $P$:
> $$f(i) = j \iff P_{ji} = 1$$

### Incidence Matrix
In undiretec graph, an incidence matrix is a $n \times m$ matrix $A = (a_{ij})$ where rows represent vertices ($n = |V|$) and columns represent individual edges ($m = |E|$).  
- $a_{ij} = 1$ if vertex $i$ is directly connected to edge $j$.  
- $a_{ij} = 0$ if they do not touch.

**Space Complexity**: $O(V\cdot E)$.

<img src='/graph/images/incidence.png' width=500>

In directed graph, we use $1$ or $-1$ depending on whether the edge goes in or out of the vertex.

### Adjacency List
An array of lists. Each index $v$ in the array stores a dynamic collection containing all the neighbor vertices that $v$ connects to directly.

**Space Complexity**: $O(V + E)$.

<img src='/graph/images/list.png' width=500>

### Tradeoffs
Graph Density ($D$), which tracks the ratio of actual edges to the maximum possible edges:

$$D = \frac{2|E|}{|V|(|V|-1)}$$

- Sparse Graph: Graphs where $|E|$ is significantly smaller than $|V|^2$ (low density). Choose Adjacency Lists here. It saves massive amounts of memory by only storing connections that actually exist.  
- Dense Graph: Graphs where $|E|$ approaches $|V|^2$ (high density). Choose Adjacency Matrices here. Matrix overhead drops, and checking if two nodes are connected becomes a fast $O(1)$ lookup operation. 

## Graph Traversal Algorithms
### Depth-First Search (DFS)
Use a **Stack**
- Start at any chosen vertex and mark it as visited.
- Move to an adjacent neighbor that has not been visited yet.
- Repeat this process recursively: keep moving forward along a single path, marking each new node as visited, until we hit a "dead end" (a node with no unvisited neighbors).
- Backtrack along our current path to the most recent node that still has unvisited neighbors, and immediately dive down that new branch.
- Finish when we have backtracked all the way to the starting node and it has no unvisited neighbors left.

```
DFS(G)
    create a visited array (all false)

    // Loop through all vertices to handle disconnected graphs
    for each vertex u in G.V
        if visited[u] == false
            DFS_VISIT(G, u, visited)
```
```
DFS_VISIT(G, u, visited)
    visited[u] = true        // Mark the current node as visited
    PRE_VISIT_ACTION(u)      // Optional: process node before exploring neighbors

    // Explore all adjacent neighbors
    for each v in G.Adj[u]
        if visited[v] == false
            DFS_VISIT(G, v, visited)
            
    POST_VISIT_ACTION(u)     // Optional: process node after backtracking
```

### Breadth-First Search (BFS)
Use a **Queue (FIFO)**
- Start at a chosen node, mark it as visited, and place it inside a tracking queue.
- Remove the node at the front of the queue to explore it.
- Examine all of its immediate neighbors. For every neighbor that hasn't been visited yet, mark it as visited and add it to the back of the queue.
- Repeat this process: keep pulling the next node from the front of the queue, checking its unvisited neighbors, and adding them to the back.
- Finish when the queue becomes completely empty, meaning all reachable nodes have been processed. 

**Single Source**
```
BFS(start, G)
    create a queue Q
    create a visited array/set (initially all false)
    
    // Initialize the start node
    Q.push(start)
    visited[start] = true
    
    while Q is not empty
        u = Q.pop()
        PROCESS(u)       // Process the node when it is removed from the queue
        
        for each neighbor v in G[u]
            if not visited[v]
                visited[v] = true
                Q.push(v)
```

**Full Traversal (If G is not connected)**
```
BFS_Full_Traversal(G)                 
    create a visited array (all false)
    create a queue Q

    for each vertex u in V             
        if not visited[u]
            Q.push(u)
            visited[u] = true
            
            while Q is not empty
                curr = Q.pop()
                PROCESS(curr)
                
                for each neighbor v in G[curr]
                    if not visited[v]
                        visited[v] = true
                        Q.push(v)
```

### Computational Complexity Comparison
The data structure we choose dictates our runtime execution performance:  
- Adjacency List: The algorithm inspects every node and loops through every edge exactly once, achieving linear time: $O(V + E)$.  
- Adjacency Matrix: Even if a vertex has zero connections, the algorithm is forced to look across an entire matrix row of size $V$, resulting in a quadratic cost: $O(V^2)$.

Both DFS and BFS use additional $O(V)$ space.

### Problems
1. [Number of Province](/graph/noProvince.cpp)
2. [Connected Components](/graph/connectedCompo.cpp)
3. [Number of islands](/graph/noIsland.cpp)
4. [Surrounded Regions](/graph/surroundedRegion.cpp)
5. [Distance of nearest cell having one](/graph/nearestOne.cpp)
6. [Word Ladder 1](/graph/wordLadder.cpp)
7. [Word Ladder 2](/graph/wordLadder2.cpp)
8. [Bipartite Graph](/graph/bipartite.cpp)
9. [Cycle Detection in Undirected Graph](/graph/cycleUndirected.cpp)
10. [Cycle Detection in Directed Graph](/graph/cycleDirected.cpp)

## Walks, Paths, Cycles, and Circuits

| Type Term | Structural Traversal Constraints | Direction |
| --- | --- | --- |
| Walk |  Alternating sequence of vertices and edges where each consecutive pair of vertices is connected by an edge. Freedom to repeat both. | No (Undirected) |
| Simple Walk | A walk where no edges are repeated. |  No (Undirected) |
| Path | A walk where no vertices are repeated. | No (Undirected)|
| Cycle | A closed walk where initial vertex = terminal vertex. |  No (Undirected) |
| Directed Path |  Sequence of vertices and edges that must strictly follow arrows. | Yes (Directed) |
| Circuit | A closed directed path where initial vertex = terminal vertex. | Yes (Directed) |

> [!IMPORTANT]
> **Lemma**: If there is a walk from a vertex $u$ to a vertex $v$ in a graph, then there is a path from $u$ to $v$.

> [!IMPORTANT]
> **Corollary**: For any walk of length $k$ in a graph, there is a path of length at most $k$ with the same endpoints. Moreover, the shortest walk between a pair of vertices is, in fact, a path.

> [!IMPORTANT]
> Let $G(V,E)$ be an $n$-node graph with $V= \{v_1, v2,..., v_n\}$
and let $A_G=\{a_{ij}\}$ denote the adjacency matrix for $G$. Let $a_{ij}^{(k)}$ denote the $(i,j)$-entry of the $k$th power of $A_G$. Then the number of walks of length $k$ between $v_i$ and $v_j$ is $a_{ij}^{(k)}$

### Cycle Detection

#### Cycle Detection in Undirected Graph

**Idea**: A cycle exists if we encounter a vertex that has already been **visited**, and that vertex is **not the immediate parent** of the current vertex.

This idea can be implemented using both DFS and BFS.

> [!NOTE]
> [C++ Solution](/graph/cycleUndirected.cpp)

#### Cycle Detection in Directed Graph

In a directed graph, simply hitting a visited node does not mean there is a cycle. It could just be a "cross edge" (two parallel paths meeting at a common destination, like a diamond shape).

**Idea**: A cycle only exists if we hit a node that is currently **active in our ongoing path**.

Therefore, we use DFS and maintain a `recStack` (recursion stack) array to track the active path. We turn it to true when diving down a path, and backtrack it to false when retreating.

> [!NOTE]
> [C++ Solution](/graph/cycleDirected.cpp)

The BFS approach is using Kahn's algorithm, which will be talked about in more detail in a later part [Kahn's algorithm](#kahns-algorithm).

## Connectivity & Graph Components
### Undirected Connectivity
**Connected Graph**:

A graph where a **path** exists between every single pair of vertices.  

**Connected Component**: 

A maximal isolated island of fully connected subgraphs within a larger disconnected network.  
<img src='/graph/images/component.png' width=400>

> [!IMPORTANT]
> **Theorem**: Every graph with $v$ vertices and $e$ edges has at least $v-e$ connected components.

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> We use induction on the number of edges, $e$. Let $P(e)$ be the proposition that for every $v$, every graph with $v$ vertices and $e$ edges has at least $v-e$ connected components.
> 
> **Base case**: ($e = 0$). In a graph with $0$ edges and $v$ vertices, each vertex is itself a connected component, and so there are exactly $v-0=v$ connected components. So $P(e)$ holds.
> 
> **Inductive step**: Now we assume that the induction hypothesis holds for every $e$ edge graph in order to prove that it holds for every $e+1$-edge graph, where $e\ge0$.
> 
> Consider a graph, $G$, with $e+1$ edges and $v$ vertices. we want to prove that $G$ has at least $v-(e+1)$ connected components. To do this, remove an arbitrary edge $\{a, b\}$ and call the resulting graph $G'$. By the induction assumption, $G'$ has at least $v-e$ connected components. Now add back the edge $\{a, b\}$ to obtain the original graph $G$. 
> - If $a$ and $b$ were in the same connected component of $G'$, then $G$ has the same connected components as $G'$, so $G$ has at least $v-e > v-(e+1)$ components.
> - If $a$ and $b$ were in different connected components of $G'$, then these two components are merged into one component in $G$, but all other components remain unchanged, reducing the number of components by $1$. Therefore, $G$ has at least $v-e-1 = v-(e+1)$ connected components. 
> 
> So in either case, $P(e+1)$ holds.
> 
> This completes the Inductive step. The theorem now follows by induction. $\blacksquare$
> </details>

> [!IMPORTANT]
> **Corollary**: Every connected graph with $v$ vertices has at least $v-1$ edges.

**Cut Vertex / Articulation Point**: 

A single critical node whose removal breaks an otherwise stable graph into disconnected components.  

**Bridge**: 

A critical link edge whose erasure tears the graph into disconnected components.  

#### Problems
[**Number of Provinces (Disconnected Components)**](/graph/noProvince.cpp)
- Problem: we are given an adjacency matrix representing a network of cities. A "province" is a group of directly or indirectly connected cities. Return the total number of provinces.
- Core Approach: Initialize a counter. Iterate through all nodes; whenever we find an unvisited node, trigger a BFS/DFS to mark all reachable nodes as visited, and increment your counter. Alternatively, use a Disjoint Set Union (DSU) data structure.

[**Number of Islands (Grid Graphs)**](/graph/noIsland.cpp)
- Problem: Given an $m \times n$ 2D binary grid grid representing a map of '1's (land) and '0's (water), return the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. (basically the same as the previous problem, only the graph is given as a grid).
- Core Approach: Traverse the grid. When we hit a '1', increment your island count and run a "flood fill" (DFS/BFS) to flip all connected '1's to '0's so they aren't recounted.

[**Connected Components in an Undirected Graph**](/graph/connectedComp.cpp)

[**Rotten Oranges**](https://leetcode.com/problems/rotting-oranges/solutions/3166554/c-bfs-easiest-beginner-friendly-sol-on2-54gzi/)

### Vertex and Edge Connectivity Coefficients
- **Vertex Connectivity** ($\kappa(G)$): The minimum number of vertices that must be deleted to completely destroy graph connectivity.  
- **Edge Connectivity** ($\lambda(G)$): The minimum number of edges that must be cut to disconnect the graph.  
- **Biconnected Graph**: A graph containing zero cut vertices.

> [!IMPORTANT]
> - The Whitney inequalities gives a relation between the edge connectivity  $\lambda$ , the vertex connectivity  $\kappa$ , and the minimum degree of any vertex in the graph $\delta$:
> $$\kappa \le \lambda \le \delta$$ 
> - The edge-connectivity for a graph with at least 2 vertices is less than or equal to the minimum degree of the graph because removing all the edges that are incident to a vertex of minimum degree will disconnect that vertex from the rest of the graph.

> [!NOTE]
> $\lambda$ and $\kappa$ can be found algorithmically using **Max-Flow Min-Cut Theorem**.

### Directed Connectivity Structures
Directed arrows change routing mechanics completely, splitting connectivity profiles into two classes:  
- **Weakly Connected**: A digraph is weakly connected if it forms a connected layout only after we completely strip away the arrows to analyze its underlying undirected shape.  
- **Strongly Connected**: A directed graph where every pair of vertices is mutually reachable.

<img src='/graph/images/connect.png' width=500>

- **A Strongly Connected Component (SCC)**: 
    - Every vertex is reachable from every other vertex within that subgraph.
    - **Maximal**: no vertex can be added without violating the above condition.

<img src='/graph/images/scc.png' width=500>

- **Quasi-strongly connected**: A directed graph (digraph) is quasi-strongly connected if, for every pair of vertices, there exists at least one node that can reach both of them. This structural property ensures the network has a directed spanning tree, allowing information or influence to flow to all other nodes.

#### Tarjan's strongly connected components algorithm

Tarjan's algorithm works by tracking two crucial pieces of metadata for every vertex as it walks through the graph using DFS:
- Discovery Time (`disc`): A unique, incrementing counter that records exactly when a node was first visited during the DFS.
- Low-Link Value (`low`): The lowest discovery time reachable from that node, including itself, its descendants, and at most one back-edge up to an active ancestor.

As the DFS drives deeper into the graph, it pushes every visited node onto a working Stack. This stack keeps track of all nodes currently under evaluation that could potentially form an SCC together.

How the Algorithm Executes

The magic happens when the recursive DFS function finishes evaluating all neighbors of a node and begins to backtrack.

During the backtracking step, a node updates its low value by checking the low values of its neighbors. If a neighbor can reach a higher up, older ancestor, the current node inherits that reachability.

An SCC Root is discovered the exact moment the DFS backtracks to a node where its discovery time matches its low-link value:

$$\text{disc}[u] == \text{low}[u]$$

When this condition is met, it means node $u$ is the deepest "entry point" to a completed strongly connected component. The algorithm then pops nodes off the stack one by one until it pops $u$ itself. All of those popped nodes are grouped together to form one complete SCC.

```
TARJAN_SCC(Graph)
    Initialize 'disc' array of size V filled with -1  // Discovery times
    Initialize 'low' array of size V filled with -1   // Smallest reachable discovery time
    Initialize 'inStack' array of size V filled with false
    Initialize an empty Stack 'st'
    Initialize 'time' = 0
    Initialize 'sccs' as an empty list of components

    for i from 0 to V - 1
        if disc[i] == -1
            TARJAN_DFS(i, Graph, disc, low, inStack, st, time, sccs)

    return sccs


TARJAN_DFS(u, Graph, disc, low, inStack, st, time, sccs)
    time = time + 1
    disc[u] = time
    low[u] = time
    PUSH(st, u)
    inStack[u] = true

    for each neighbor v of u
        // Case 1: Neighbor is unvisited -> Recurse
        if disc[v] == -1
            TARJAN_DFS(v, Graph, disc, low, inStack, st, time, sccs)
            low[u] = MIN(low[u], low[v])
            
        // Case 2: Neighbor is in the stack -> Back-edge found
        else if inStack[v] == true
            low[u] = MIN(low[u], disc[v])

    // If u is a root node of an SCC, pop the stack
    if disc[u] == low[u]
        Initialize 'current_scc' as an empty list
        
        while true
            v = POP(st)
            inStack[v] = false
            add v to 'current_scc'
            if u == v
                break
                
        add 'current_scc' to 'sccs'
```

#### Problems
**Critical Connections in a Network (Bridges / Tarjan's)**
- Problem: An apex network contains server connections. A "critical connection" (bridge) is an edge whose deletion disconnects the graph. Find all critical connections.
- Core Approach: A brute force approach of removing each edge and running DFS takes $O(E \cdot (V + E))$, which is too slow. Instead, use Tarjan's Algorithm or Fleury's/Kosaraju's structural variations using Discovery Time and Low Values in a single DFS pass to find bridges in $O(V + E)$.



## Weighted Graphs & Applied Contexts
### Weighted Networks
Graphs can assign real-number coefficients to model scalar physical constraints:  
- Vertex Weights ($K: V \rightarrow \mathbb{R}$): Modeling costs at locations (e.g., handling delays at a shipping terminal).  
- Edge Weights ($L: E \rightarrow \mathbb{R}$): Distance, financial costs, or transit delays along pathways.  
- Total Graph Weight ($L(G)$): Summation of all edge properties across the structure.  
### Matrix Representation of Weights
Instead of storing simple 1s and 0s, a Weighted Matrix updates its values to match structural paths:  
- $a_{ij} = 0$ along the main diagonal where $i = j$.  
- $a_{ij} = \text{weight of edge } (i, j)$ if a line exists.  
- $a_{ij} = \infty$ if there is no line connecting the nodes.  
## Concrete Computer Science Frameworks 
Graphs drive major modern application models:  
- Entity-Relationship (ER) Schemas: Databases use nodes for system entities and edges to chart dependencies across keys.  
- Flowcharts & Compilers: Directed Acyclic Graphs (DAGs) map instruction execution paths within programming code modules.  
- Finite State Machines (FSM): Vertices symbolize operating states, while directed edges act as conditions trigger phase shifts.  
- Routing Maps: Powering global positioning systems like Google Maps using Dijkstra and shortest-path variants over weighted coordinates.

## Tree Graph Theory
- Tree: an undirected graph in which every pair of distinct vertices is connected by exactly one path, or equivalently, a connected acyclic undirected graph.
- Forest: Every connected component of a forest is a tree.

### Theorems on Tree Structures
> [!IMPORTANT]
> **Theorem 2.1:** Existence of Pendant Vertices (Leaves)
>
> Every tree with $n \ge 2$ vertices contains at least two pendant vertices (vertices with a degree of 1, also known as leaves).

**Proof Intuition:** If we find the absolute longest simple path $P = u \dots v$ in a finite tree, the two end-nodes $u$ and $v$ cannot connect back to any internal nodes (which would create an illegal cycle) nor can they extend further, forcing them to have a degree of 1.  

> [!IMPORTANT]
> **Theorem 2.2:** Six Equivalent Statements for Trees
>
> For any graph $G$ with $n$ vertices, the following statements are completely equivalent:
> 1. $G$ is a tree.
> 2. There exists exactly one unique simple path connecting any two vertices.
> 3. $G$ is minimally connected (removing any single edge instantly disconnects the graph).
> 4. Adding a new edge between any two non-adjacent vertices creates exactly one unique cycle.
> 5. $G$ is connected and has exactly $n - 1$ edges.
> 6. $G$ has no cycles and has exactly $n - 1$ edges.

### Spanning Trees
A Spanning Tree $T = (V, F)$ of a connected graph $G = (V, E)$ is a subgraph that contains all vertices of $G$ but retains only a minimal subset of edges $F \subseteq E$ such that $T$ forms a valid tree.  
> [!IMPORTANT]
> **Theorem 2.3:**
> 
> A graph is connected if and only if it possesses a spanning tree.  

> [!NOTE]
> <details>
> <summary><b>Proof</b></summary>
> 
> Assume there exists a connected graph $G = (V, E)$ that does not contain a spanning tree.
> 
> If $G$ is acyclic, then by definition it is a tree, which means it serves as its own spanning tree—a contradiction. Therefore, $G$ must contain a cycle.
> 
> Let $e$ be an edge in that cycle. Remove $e$ to form a new subgraph $G'$. Because $e$ was part of a cycle, its endpoints remain connected via the alternative path around the cycle, meaning $G'$ is still connected and spans $V$.
> 
> If we repeat this process of removing cycle edges, we eventually obtain a subgraph $T$ that contains no more cycles. Since edge removal never breaks connectivity, $T$ remains connected and spans $V$. By definition, $T$ is a spanning tree of $G$.
> 
> This directly contradicts our initial assumption that $G$ has no spanning tree. Thus, the assumption must be false, and every connected graph contains a spanning tree. $\blacksquare$
> 
> </details>

**Constructions**: To manually build a spanning tree from a connected cyclic graph, find any cycle, delete one edge from it, and repeat this process until no cycles remain.

### Minimum Spanning Tree (MST) Algorithms

When edges have real-number weights, the Spanning Tree with the absolute lowest combined total edge weight is the Minimum Spanning Tree. 

We need a MST because it solves a fundamental real-world problem: **_How do we connect a set of points together using the minimum possible total distance, cost, or resource allocation?_**

<img src='/graph/images/mst.png' width=500>

To find a MST in a connected, weighted graph, two **greedy** algorithms dominate: Kruskal’s Algorithm and Prim’s Algorithm.

#### Prim’s Algorithm (Vertex-Centric): 

##### Description

The minimum spanning tree is built gradually by adding edges one at a time. At first the spanning tree consists only of a single vertex (chosen arbitrarily). Then the minimum weight edge outgoing from this vertex is selected and added to the spanning tree. After that the spanning tree already consists of two vertices. Now select and add the edge with the minimum weight that has one end in an already selected vertex (i.e. a vertex that is already part of the spanning tree), and the other end in an unselected vertex. And so on, i.e. every time we select and add the edge with minimal weight that connects one selected vertex with one unselected vertex. The process is repeated until the spanning tree contains all vertices (or equivalently until we have  
$n - 1$  edges).

##### Proof

We define two concepts:
- A Cut: A partition of the vertices of a graph into two disjoint sets, $S$ and $V \setminus S$.
- A Crossing Edge: An edge that has one endpoint in set $S$ and the other endpoint in set $V \setminus S$.

To prove why Prim’s Algorithm is guaranteed to find a Minimum Spanning Tree (MST), we rely on a fundamental property in graph theory known as the Cut Property.

> [!IMPORTANT]
> If $G = (V, E)$ is a connected graph with weighted edges, and $S$ is a subset of $V$, then the minimum-weight crossing edge $e$ across the cut $(S, V \setminus S)$ must belong to a minimum spanning tree of $G$.

We can prove Prim's algorithm works by using mathematical induction on the number of vertices added to the growing tree structure.

Let $T_k$ be the tree constructed by Prim's algorithm after $k$ steps. we assume by induction that $T_k$ is a subgraph of some Minimum Spanning Tree $M$.

**Base Case** ($k = 1$)

Prim's algorithm starts by picking an arbitrary vertex $v$ and setting $T_1 = \{v\}$. Since a single vertex has no edges, it contains no cycles and its total weight is zero. Any valid MST must include this vertex $v$. Therefore, $T_1$ is trivially a subgraph of an MST. The base case holds.

**The Inductive Step**
In the next step, Prim's defines a cut separating the visited vertices ($S$) from the unvisited vertices ($V \setminus S$). It greedily chooses the absolute minimum-weight crossing edge $e = (u, v)$ to add to the tree.

If $e \in M$, the induction holds. If $e \notin M$:
- Adding $e$ to the MST $M$ creates a unique cycle $C$.This cycle must cross back over the cut using a different edge, $e'$.
- Remove $e'$ to break the cycle, creating a new spanning tree:
$$M' = M \cup \{e\} \setminus \{e'\}$$

Because Prim's explicitly selected $e$ as the minimum-weight edge crossing this cut, we know $w(e) \le w(e')$.

$$\text{weight}(M') = \text{weight}(M) + w(e) - w(e')$$

- If $w(e) < w(e')$, then $\text{weight}(M') < \text{weight}(M)$, contradicting that $M$ is a minimum spanning tree.
- Therefore, $w(e) = w(e')$, making $M'$ an equally valid MST.

Since $M'$ contains $T_k$ and our new edge $e$, the growth remains optimal. By induction, Prim's algorithm is guaranteed to produce an MST. $\blacksquare$

##### Implementation

Given the graph is represented as adjacency list. There are usually 2 versions of Prim implementation: Lazy Prim and Eager Prim. Here, I show eager Prim as it is usually for efficient.

**Eager**
```
PRIM_MST(G, start_vertex)
    // Step 1: Initialization
    for each vertex u in G.V
        key[u] = infinity       // Stores the minimum weight edge to connect u to the MST
        parent[u] = null        // Stores the parent of u in the MST
        in_mst[u] = false       // Tracks if u is already absorbed into the MST

    key[start_vertex] = 0
    create an empty Min-Priority Queue PQ
    
    // Push all vertices into the priority queue ordered by their key value
    for each vertex u in G.V
        PQ.insert(u, key[u])

    // Step 2: Main Loop
    while PQ is not empty
        u = PQ.extract_min()    // Pick the vertex closest to the growing tree
        in_mst[u] = true        // Add it permanently to the MST

        // Explore all neighbors of the absorbed vertex
        for each neighbor v in G.Adj[u]
            weight_uv = G.weight(u, v)

            // If neighbor is not in MST 
            // and we found a cheaper connecting edge to the growing tree (not necessarily to u)
            if in_mst[v] == false and weight_uv < key[v]
                parent[v] = u
                key[v] = weight_uv
                PQ.decrease_key(v, key[v]) // Update its priority in the queue
```

> [!NOTE]
> For this pseudocode, we meet an obstable that C++’s standard `std::priority_queue` does not support a `decrease_key` operation. To get around this while keeping the queue size strictly capped at $V$ elements (e.g., no duplicates), we can use a `std::set`, which inherently supports element modification by combining a `.erase()` and an `.insert()`.

> [!IMPORTANT]
> - Time Complexity: $O(E \log V)$
>   - Removing the minimum element (extract_min) happens $V$ times. Each removal takes $O(\log V)$ to rebalance the set. Total: $O(V \log V)$.
>   - The inner loop evaluates edges $O(E)$ times. When a cheaper path is found, it updates the set via find(), erase(), and insert(). Since the set size is capped at $V$, this takes $O(\log V)$ per update. Total: $O(E \log V)$.
> 
> $$\text{Total Time} = O(V \log V + E \log V) = O(E \log V)$$
> - Space Complexity: $O(V + E)$
> Required to hold the graph structures along with the tracking tracking metrics (`key`, `parent`, `in_mst`) and the priority queue/set elements of size $V$.

> [!NOTE]
> When a dense graph is given as an Adjacency Matrix, we do not need a priority queue or `std::set` at all.
> 
> Instead, a simple linear scan (an array) becomes both faster and more space-efficient. we scan when picking the smallest connecting edge (replace `PQ.extract_min()`) and when inspecting adjacent nodes. 
>
> The time complexity becomes $O(V^2)$, which is mathematically optimal for dense graphs because just reading the matrix input takes $O(V^2)$ time anyway.

#### Kruskal’s Algorithm (Edge-Centric): 

##### Description

- Sort all edges in the graph in ascending order of their weights (cheapest to most expensive).
- Create a forest where each vertex is initialized as its own separate, independent tree.
- Iterate through the sorted edges one by one. For each edge connecting vertex $A$ to vertex $B$:
- Check if $A$ and $B$ are already in the same tree.
    - If they are in different trees: Add the edge to your MST and merge (union) the two trees into one.
    - If they are already in the same tree: Discard the edge. (Adding it would create an illegal loop/cycle).  
- Stop once we have added exactly $V - 1$ edges (where $V$ is the total number of vertices). 

##### Proof

To prove the correctness of Kruskal’s Algorithm, we must prove that the tree $T$ it produces is both a Spanning Tree and Minimum in total weight.

**Spanning Tree Property (No Cycles)**
Kruskal’s only accepts an edge $(u, v)$ if `FIND(u)` != `FIND(v)`. This explicitly means $u$ and $v$ belong to separate, disconnected components. Adding an edge between two disjoint trees cannot form a cycle. Since it connects components until only one remains, it produces a valid spanning tree.

**Minimality Property**
Let $T$ be the tree produced by Kruskal's, and let $e = (u, v)$ be the first edge in $T$ that is missing from an optimal tree $T_{opt}$.
- Define the Cut: Just before Kruskal's picked $e$, vertex $u$ belonged to an isolated component $S$. Let the rest of the graph be $V - S$.
- The Cycle: If we add $e$ to $T_{opt}$, it creates a cycle. This cycle must cross our cut via some alternative edge $e'$.
- The Weight Comparison: Because Kruskal's scans edges globally in strictly sorted order, and it hadn't picked an edge to connect component $S$ to the rest of the graph yet, $e$ is guaranteed to be the cheapest available edge crossing this cut. Therefore:

$$w(e) \le w(e')$$

Just like in Prim's proof, if $w(e) < w(e')$, then swapping $e'$ for $e$ in $T_{opt}$ creates a cheaper tree, contradicting its optimality. Thus, $w(e) = w(e')$. We can substitute $e$ into $T_{opt}$ without changing its total weight, proving Kruskal's greedy choice is optimal.

##### Simplest implementation

Information regarding the subtree to which a vertex belongs is maintained with the help of an array `tree_id[]` - for each vertex `v`, `tree_id[v]` stores the number of the tree , to which `v` belongs.

```
 KRUSKAL_FLAT_ARRAY(G)
    // Step 1: Initialize structures
    Initialize an empty list called 'result' to store the MST edges
    total_cost = 0

    // Create an array where each vertex starts as its own component ID
    Initialize an array 'tree_id' of size V
    for i from 0 to V - 1
        tree_id[i] = i

    // Step 2: Sort the edge pool by weight ascending
    sort the edges of G.E in non-decreasing order by weight

    // Step 3: Process the sorted edges
    for each edge e connecting (u, v) with weight in the sorted list
        
        // If u and v have different IDs, they belong to different components
        if tree_id[u] != tree_id[v]
            total_cost = total_cost + e.weight
            add e to 'result'

            // Record the old and new IDs to prepare for the merge
            old_id = tree_id[u]
            new_id = tree_id[v]

            // Merge step: Scan and rewrite all vertices using the old ID
            for i from 0 to V - 1
                if tree_id[i] == old_id
                    tree_id[i] = new_id

    return total_cost, result
```
> [!IMPORTANT]
>  - Sorting edges requires $O(E \log E)$. 
> - For each edge, whether it belongs to the ends of different trees, can be determined in $O(1)$ . 
> - The union of the two trees is carried out in $O(V)$  by a simple pass through `tree_id[]` array. 
> 
> The total number of merge operations is $V-1$ 
> 
> $\Rightarrow O(E \log E + V^2)$ .

##### Disjoint Set Implemetation
To make it lightning-fast, Kruskal’s relies on a data structure called Disjoint Set Union (DSU) or Union-Find.
- `find(u)`: Determines which specific tree/component vertex $u$ belongs to.
- `union(u, v)`: Merges the tree containing $u$ with the tree containing $v$.

By using optimization techniques like path compression and union by rank, the DSU can determine if two points belong to the same tree in near-constant time—almost $O(1)$.

```
INITIALIZE_DSU(V)
    Initialize array 'parent' of size V
    Initialize array 'rank' of size V
    for i from 0 to V - 1
        parent[i] = i    // Every element is initially its own parent (root)
        rank[i] = 0      // Height of each individual tree is initially 0

FIND(i, parent)
    // Path Compression Optimization
    if parent[i] == i
        return i
    // Recursively find the root and make it the direct parent of i
    parent[i] = FIND(parent[i], parent) 
    return parent[i]

UNION(i, j, parent, rank)
    root_i = FIND(i, parent)
    root_j = FIND(j, parent)

    if root_i != root_j
        // Union by Rank Optimization (Attach smaller tree under taller tree)
        if rank[root_i] < rank[root_j]
            parent[root_i] = root_j
        else if rank[root_i] > rank[root_j]
            parent[root_j] = root_i
        else
            parent[root_j] = root_i
            rank[root_i] = rank[root_i] + 1
```

```
KRUSKAL_WITH_DSU(G)
    Initialize an empty list called 'result' to store the MST edges
    total_cost = 0
    edges_count = 0

    // Step 1: Initialize the DSU structures
    INITIALIZE_DSU(G.V)

    // Step 2: Sort all edges by weight ascending
    sort the edges of G.E in non-decreasing order by weight

    // Step 3: Iterate through sorted edges
    for each edge e connecting (u, v) with weight w in the sorted list
        // Stop early if we have already built a valid spanning tree
        if edges_count == G.V - 1
            break

        // Find the root leaders of the components containing u and v
        root_u = FIND(u, parent)
        root_v = FIND(v, parent)

        // If roots are different, u and v belong to separate components
        if root_u != root_v
            total_cost = total_cost + w
            add e to 'result'
            edges_count = edges_count + 1
            
            // Merge the two components in near-constant time
            UNION(root_u, root_v, parent, rank)

    return total_cost, result
```

> [!IMPORTANT]
> - Sorting all $E$ edges by weight takes $ O(E \log E)$.
> - For each edge, we call `FIND` twice and `UNION` once. Thanks to Path Compression and Union by Rank, each of these operations runs in near-constant time, mathematically bounded by $ O(\alpha(V))$ (the Inverse Ackermann function, which is practically $\le 4$ for all realistic inputs).
> 
> $$\text{Total Time} =  O(E \log E + E \cdot \alpha(V)) = \mathbf{ O(E \log E)}$$
>
> Because the maximum number of edges in a simple graph is $V^2$, we can state that $\log E \le \log(V^2) = 2 \log V$. Dropping the constant factor, the runtime is equivalent to $ O(E \log V)$.

### Fundamental Cycle Basis 
If we have a spanning tree $T$ of a graph $G$, any edge $e$ that belongs to the graph but was excluded from the tree ($e \in E - F$) is called a non-tree edge.  
- Adding this single edge $e$ back into the tree creates a unique single cycle, known as a Fundamental Cycle ($C_e$).  
- The collection of all such unique cycles formed by adding non-tree edges is called the Fundamental Cycle Basis ($\Omega$).  
- If a graph has $n$ vertices and $m$ edges, its fundamental cycle set will contain exactly $m - n + 1$ distinct cycles. Any other cycle in the graph can be written as a combination (XOR sum) of these fundamental cycles.

<img src='/graph/images/fundcycle.png' width=600>

### Directed Trees

A directed graph $G = (V, E)$ is a directed tree if it satisfies two conditions:
- No cycles.
- Has a Root ($r$): There is a specific starting vertex $r$ such that a directed path exists from $r$ to every other vertex in the graph.

A directed tree is a directed acyclic graph (DAG) whose underlying undirected graph is a tree (the reverse is not correct).

> [!IMPORTANT]
> **Equivalent Statements**
> 
> If a directed graph satisfies any one of these, it automatically satisfies all the others and is a directed tree:
> 1. $G$ is a directed tree.
> 2. There is a UNIQUE path from root $r$ to every vertex. If there were two different ways to reach a node, it wouldn't be a tree anymore—it would form a diamond/loop shape.
> 3. Minimal quasi-strongly connected: delete even one edge, and the graph breaks into disconnected pieces.
> 4. $G$ is connected, and there exists a root $r$ such that $d^-(r) = 0$ and $d^-(v) = 1$ for all $v \neq r$.
> 5. $G$ is acyclic, and there exists a root $r$ such that $d^-(r) = 0$ and $d^-(v) = 1$ for all $v \neq r$.

> [!IMPORTANT]
> **Theorem**
> 
> Given a large directed graph $G$, the theorem states a two-way (if-and-only-if) relationship: 
> $G$ contains a subgraph (spanning subgraph) $T$ that is a directed tree $\iff$ $G$ is quasi-strongly connected.

### Applications of Trees

Real-life tree applications: Family Tree, File System Organization, Biology Tree, Expression Evaluation,...

When applied to computer science, trees are treated as rooted, directed structures where parent-child hierarchies outline clear paths of data dependencies.
- Binary Search Tree
- Huffman Trees
- DFS Trees
- Game Trees

## DAG
A DAG (Directed Acyclic Graph) is a directed graph that contains no cycles. It is the ideal structure for modeling scheduling systems, task prerequisites, compile dependencies, and data pipeline execution paths.

<img src='/graph/images/dag.png' width=300>

### Topological Sort
A Topological Sort is a linear ordering of the vertices in a digraph such that for every directed edge $(u, v)$ pointing from node $u$ to node $v$, vertex $u$ must appear before vertex $v$ in the sequence. 

Topological order may not be unique.

<img src='/graph/images/topo.png' width=500>

> [!IMPORTANT]
> **Theorem 2.9:** Definitive Constraint
>
> A directed graph can be topologically sorted if and only if it is a valid DAG. If a graph contains even a single cycle, a topological sort is impossible.

There are two approaches to perform topological sort: DFS and BFS (Kahn's algorithm). Usually, we can do cycle detection in the meantime.

#### Topological Sorting Using DFS
**Idea**: 

Perform a DFS traversal starting from every unvisited vertex (from $0$ to $n − 1$). For each DFS call, we first explore all unvisited neighbors of the current node. Once the recursive calls for all its neighbors are complete, we start pushing these nodes into a stack while backtracking. 

After all vertices are processed, we pop elements from the stack one by one into a list — this gives a valid topological ordering, as each node is placed before all nodes it points to.

Cycle Detection: Keep a list of where we've been globally (`visited`), and a list of the path we are currently walking down (`recStack`). If we run into the current path, we are walking in a circle.

```
DFS_TOPOLOGICAL_SORT(Graph)
    Initialize 'visited' array of size V filled with false
    Initialize 'recStack' array of size V filled with false
    Initialize an empty Stack 'S'

    // Run DFS starting from every unvisited vertex
    for i from 0 to V - 1
        if visited[i] == false
            // We initiate the tracking sequence here. If the recursive 
            // chain hits a node already in 'recStack', it bubbles 'true' back up.
            if DFS_VISIT(i, Graph, visited, recStack, S) == true
                return "Error: Graph contains a cycle, Topological Sort impossible!"

    // Pop everything from stack to get the correct topological order
    Initialize 'result' as an empty list
    while S is not empty
        add POP(S) to 'result'

    return result


DFS_VISIT(u, Graph, visited, recStack, S)
    visited[u] = true
    recStack[u] = true // Push the current node onto the active recursion path

    // Recur for all vertices adjacent to this vertex
    for each neighbor v of u
        // If a neighbor is already active in the current path stack, it's a cycle!
        if recStack[v] == true
            return true 
            
        if visited[v] == false
            if DFS_VISIT(v, Graph, visited, recStack, S) == true
                return true

    recStack[u] = false // Backtrack: remove the node from the active path stack
    PUSH(S, u)
    return false
```

#### Kahn’s Algorithm
**Idea**: Repeatedly finding vertices that have zero dependencies (in-degree $= 0$), peeling them out of the graph, and updating the rest of the network.

- Initialization: Calculate the in-degree of every vertex. Find all vertices with an in-degree of $0$ and push them into a set/queue $S$. Initialize an empty output list $L$.  
- The Processing Loop: While $S$ is not empty:  
    - Pop a vertex $v$ from $S$ and append it to your output list $L$.  
    - For every neighbor vertex $u$ that $v$ points to, conceptually delete the edge $(v, u)$ from the graph. This decrements $u$'s in-degree by $-1$.  
    - If this cause $u$'s in-degree to drop to 0, immediately push $u$ into the set $S$.  
- Cycle Detection Check: If the algorithm finishes and there are still edges left in the graph, it means the graph contains a cycle and cannot be sorted. Otherwise, return $L$ as the valid topological order.

```
KAHN_TOPOLOGICAL_SORT(Graph)
    Initialize 'result' as an empty list
    Initialize 'in_degree' array of size V filled with 0
    Initialize a Queue 'Q'

    // Step 1: Calculate in-degree for every vertex
    for each vertex u in Graph
        for each neighbor v of u
            in_degree[v] = in_degree[v] + 1

    // Step 2: Push all vertices with 0 in-degree into the queue
    for i from 0 to V - 1
        if in_degree[i] == 0
            ENQUEUE(Q, i)

    // Step 3: Process vertices
    while Q is not empty
        u = DEQUEUE(Q)
        add u to 'result'

        // Reduce in-degree for all outgoing neighbors
        for each neighbor v of u
            in_degree[v] = in_degree[v] - 1
            
            // If in-degree becomes 0, it has no more prerequisites
            if in_degree[v] == 0
                ENQUEUE(Q, v)

    // Step 4: Check for cycles
    if length of 'result' != V
        return "Error: Graph contains a cycle, Topological Sort impossible!"
    else
        return result
```

#### Analysis

> [!IMPORTANT]
> Both Kahn's algorithm and the DFS approach are highly efficient and scale linearly:
> - Time Complexity: $ O(V + E)$ Look at every vertex exactly once when processing it, and iterate through every edge exactly once when updating neighbors or traversing.
> - Space Complexity: $ O(V)$ Need extra memory proportional to the number of vertices to store the tracking metrics (the `in_degree` array and a queue for Kahn's, or the `visited` array and a stack for DFS).
