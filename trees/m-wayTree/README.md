# m-Way Tree

## Definition

M-Way Tree allows each node to have multiple elements.

A node on an M-way search tree with $M−1$ distinct and ordered keys: $K_1 < K_2 < K_3 < . . . < k_{M−1}$, has $M$ children $\{T_0, T_1, T_2, . . . , T_{M−1}\}$

Every element in child $T_i$ has a value larger than $K_i$ and smaller than $K_{i+1}$

Number of valid keys doesn’t have to be the same for every node on the tree

<img src='/trees/m-wayTree/images/example.png' alt='Example of M-Way Tree'>

A node in an M-Way Tree can be represented as:
```cpp
struct Node {
    int in_use; // How many of the m keys this node are in use
    Key keys[m-1];
    Node* children[m];
};
```
<img src='/trees/m-wayTree/images/node.png' alt='Node in M-Way Tree'>

## Property
> [!IMPORTANT]
> Let $T$ be an $m$-way tree with height $h$, $n$ entries and $n_E$ external nodes. Then the following inequalities hold:
> 1. $h \le n \le m^h-1$
> 2. $\log_m(n+1) \le h \le n$
> 3. $n_e = n + 1$

**Proof:**
1. $h \le n \le m^h-1$
- Lower bound: We consider m-way tree with one internal node and one entry for each level $0,1,.., h-1$, and level $h$ contains only external nodes.
$\Rightarrow n \ge h$.

<img src='/trees/m-wayTree/images/lowerbound.png' alt='Node in M-Way Tree' width=200>

- Upper bound: 
We consider an m-way tree with height $h$ where each internal nodes on levels $0..h-1$ have exactly $m$ children (external nodes are at level $h$).
Then the number of internal nodes is: $\sum_{i=0}^{h-1}m^i = \dfrac{m^h-1}{m-1}$.
Each internal node has $m-1$ entries, thus total number of entries is $n = m^h-1$.

2. $\log_m(n+1) \le h \le n$
- Upper bound: This is the same as in $1$.
- Lower bound: According to $1$, $m^h-1 \ge n \Rightarrow h \ge log_m(n+1)$.

3. $n_e = n + 1$
We will prove this using induction on number of internal nodes $I$ of an m-way tree.
- Base case: Let $I=1$, the tree contains only one root node with $n$ entries and $n_E = n+1$ external nodes. Thus, the proposition holds.
- Inductive step: 

Assume the proposition holds for an m-way tree with $I$ internal nodes. That is, the tree has $n$ entries and $I$ internal nodes, then:

$$n_E = n+1$$

We add one more node with $k$ entries to replace a previous external node (empty node). 

Then, the number of entries is $n' = n+k$.

The new node with $k$ entries replaces one old external nodes and introduces $k+1$ new external nodes. Therefore, the number of external nodes is $n_E'= n_E-1+k$.
We have
```math
\begin{align} n_E' &= n_E-1+k+1 \\ 
&= (n+1)-1+k+1 \\
&= n+k+1 \\
&= n'+1
\end{align}
```

## Searching

Let $T$ be a m-way tree and a key $k$. The algorithm for searching $k$ is simple.
- We trace a path in $T$ starting from the root. 
- When we are at a $d$-node $v$ during the search, we compare $k$ with the keys $K_1, K_2,..,K_{d-1}$ stored at $v$. 
    - If $k=K_i$ for some $i$, we have found $k$.
    - Otherwise, we go to a child node $v_i$ of $v$ such that $K_i<k<K_{i+1}$

- If we reach an external node, the key $k$ isn't in the tree.

## Insertion

To insert a new key $K$ into an $m$-way tree:
- Search: Start at the root and traverse down the tree to find the appropriate leaf node where $K$ belongs, following the standard multi-way search properties.
- Check for Duplicates: If $K$ is already present in the tree, the insertion is typically aborted (or handled based on duplicate rules).
- Insert or Create:
    - Case 1 (Node has space): If the target leaf node has fewer than $m-1$ keys, insert $K$ into this node in sorted order.
    - Case 2 (Node is full): If the target leaf node already has $m-1$ keys, you cannot add it there. Instead, create a new child node, place $K$ into it, and link this new node to the correct child pointer of the full leaf node.

<img src='/trees/m-wayTree/images/insertion.png' alt='Node in M-Way Tree'>

## Deletion

When deleting a key $K$, we first search the tree to locate the node containing it. Once found, the deletion falls into one of two major categories:
- Case 1: The key is in a Leaf Node
    - If the leaf node contains other keys, simply remove $K$ and shift the remaining keys in the node leftward to close the gap.
    - If $K$ was the only key in that leaf node, delete the key and remove the now-empty node pointer from its parent.
- Case 2: The key is in an Internal Node (Non-Leaf)
    - Find either the in-order predecessor or successor (both will always reside in a leaf node).
    - Copy that substitute key over the key $K$ we want to delete.
    - Recursively delete the substitute key from its original leaf node (which reduces to Case 1).

## Complexity of Operations

### Node processing
We look at what happens inside a single node during any operation. When evaluating a node, we must find the correct interval among its keys to choose the next child pointer.

The time spent at a node depends on the implementation of the node. If we use a sorted array then, using binary search, we can search a node in $𝑂(\lg m)$ time.

### Search Complexity
To find a key, we traverse from the root down to a leaf node, performing a binary search at every level of the tree.
- Average/Balanced Case: $O(h \cdot \lg m)$ We visit $h$ nodes from root to leaf. At each node, we spend $O(\lg m)$ time finding the correct branch. If the tree is perfectly balanced, the height $h \approx \log_m n$, which simplifies the total time to:
$$\text{Time} = O\left(\log_m n \cdot \lg m\right) = O\left(\frac{\lg n}{\lg m} \cdot \lg m\right) = O(\lg n)$$
- Worst Case (Skewed Tree): $O(n)$ If keys are inserted in strictly sorted order, the tree degenerates into a linear chain where each node contains only a single key ($h \approx n$). The multi-way advantage disappears, and it degrades to a linear search through $n$ levels.

### Insertion Complexity
- Search: Takes $O(h \cdot \lg m)$ to find the target leaf.
- Insertion:  
    - If the node has space, inserting the key in sorted order and shifting elements takes $O(m)$ in the worst case for array manipulation.
    - If the node is full, creating a new child pointer takes $O(1)$ (fixed-size) or $O(m)$ (dynamic) depending on how child pointer arrays are allocated.

Total Complexity: Dominated by the tree traversal on average, yielding $O(h \cdot \lg m)$. In a badly skewed tree, this degrades to $O(n)$.

### Deletion Complexity

Deletion is structurally similar to insertion but requires an extra traversal step if the target key resides in an internal node.
- Search: Finding the element to delete takes $O(h \cdot \lg m)$.
- Leaf Node Deletion: Shifting elements within the node array takes $O(m)$.
- Internal Node Deletion: Finding the in-order predecessor or successor requires traveling down to a leaf node, which takes at most $O(h \cdot \lg m)$ additional steps. Once swapped, deleting the leaf element requires shifting elements within that leaf node ($O(m)$).

Total Complexity: On average, the operation is bound by the height of the tree, giving $O(h \cdot \lg m)$. In the absolute worst case (a completely skewed tree where elements must be shifted continuously), it becomes $O(n)$.

**Summary Table**
| Operation | Best Case| Average Case| Worst Case (Skewed Tree) | 
| --- | --- | --- | --- |  
| Search | $O(\lg m)$ | $O(h \cdot \lg m)$ | $O(n)$ | 
| Insertion | $O(\lg m)$ | $O(h \cdot \lg m)$ | $O(n)$ | 
| Deletion | $O(\lg m)$ | $O(h \cdot \lg m)$ | $O(n)$ |
