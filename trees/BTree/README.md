# B Tree

## Introduction
B-tree is a height-balanced multiway search tree.

B-trees, or some variant of B-trees, are the standard file organization for applications requiring insertion, deletion, and key range searches in disks. They are used to implement most modern file systems. B-trees address effectively all of the major problems encountered when implementing disk-based search trees:

- A high branching factor and guaranteed height balance keep the tree flat, meaning very few disk blocks are accessed during a search.

- Search and update operations only affect the specific blocks on the direct path from the root to the target leaf, drastically reducing disk I/O.

- Related records with similar keys are grouped onto the same disk block. Once a node is found, a large collection of close keys is immediately accessible, making range queries highly efficient.

- Nodes are guaranteed to be full to a certain minimum percentage, maximizing space utilization and reducing necessary disk fetches.

- Because nodes can hold many keys and accommodate empty space, structural restructuring (insertions/deletions) is rarely triggered.

Reading data from a disk happens in chunks called **pages** or **blocks** (usually 4KB to 8KB). Fetching a block from a disk is an expensive operation in terms of time, so we usually want to minimize our block reads $\Rightarrow$ B-tree helps us do this.

Normally, the size of a node in the B-tree is chosen to fill a disk block. A B-tree node implementation typically allows 100 or more children. Thus, a B-tree node is equivalent to a disk block, and a “pointer” value stored in the tree is not an address in RAM like in other trees but is actually the number of the block containing the child node (**offset**). In a typical application, the B-tree’s access to the disk file will be managed using a buffer pool and a block-replacement scheme such as LRU.

## Definition
For an integer $m \ge 3$, a B-tree of order $m$ is a multway searcg tree with the following properties, assuming it is not empty:
- The root is either a leaf or has at least $2$ children.
- Each internal nodes, except the root, has between $\lceil m/2 \rceil - 1$ and $m-1$ keys $\Rightarrow$ between $\lceil m/2 \rceil$ and $m$ children.
- All leaves are at the same level, so the tree is always **height-balanced**.

The B-tree is a generalization of the 2-3 tree. Put another way, a 2-3 tree is a B-tree of order three. 

Example of B-tree of order $4$.
<img src='/trees/BTree/images/b-treeExample.png' alt='Example of B-Tree of order 4'>

## Properties

### Height

> [!IMPORTANT]
> Let $h$ be the height of a B-tree of order $m$ with $k$ keys, then: 
> $$h = \Theta(\log k)$$

**Proof**:

1. Proving $h = O(\log k)$

The root must have $2$ children and $1$ key.

Each internal node have at least $d=\lceil m/2 \rceil $ children $\Rightarrow d-1$ keys.

Therefore, the number of nodes at level $i$ is $2\cdot d^{i-1}$.

We have the total number of keys:

```math
\begin{align*}
k &\ge 1+ \sum_{i=1}^{h}(2\cdot d^{i-1})\cdot(d-1) \\
k & \ge 1+ 2 \cdot (d-1)\sum_{i=1}^{h}d^{i-1} \\
k &\ge 1 + 2 \cdot (d-1) \cdot \dfrac{d^{h}-1}{d-1} \\
k &\ge 2 \cdot d^{h}-1 \\
\Rightarrow h &\le \log_d \left(\dfrac{k+1}{2}\right) \\
h &\le \log_{\lceil m/2 \rceil} \left(\dfrac{k+1}{2}\right) = O(\log k)\\
\end{align*}
```

2. Proving $h = \Omega(\log k)$

The upper bound of $k$ will be the densest tree where every node has $m-1$ keys and $m$ children.

Thus, the number of nodes at level $i$ is $m^i$.

The total number of keys is:

```math
\begin{align*}
k &\le \sum_{i=0}^{h}m^{i}\cdot(m-1) \\
k & \le \dfrac{m^{h+1}-1}{m-1} \cdot (m-1) \\
k & \le m^{h+1}-1\\
\Rightarrow h &\ge \log_m (k+1) -1 = \Omega(\log k)
\end{align*}
```

Therefore, we have proven $h = \Theta(k)$.



## Operations

### Search
Search in B-tree is similar to multiway tree:
1. Perform a binary search on the records in the current node. If a record with the search key is found, then return that record. If the current node is a leaf node and the key is not found, then report an unsuccessful search.
2. Otherwise, follow the proper branch and repeat the process.

### Tree restructuring

We need to deal with 2 kinds of B-tree violation:
- Overfull Node: A node has $m + 1$ children ($m$ keys).
- Underfull Node: A node has $\lceil m/2\rceil − 1 $ children $( \lceil m/2\rceil − 2$ keys $)$.

#### Rotation


In a B-tree, key rotation is a restructuring operation used when a node is either overfull or underfull, provided an **adjacent sibling has available key space**. This is considered the best-case scenario for restructuring because it is not computationally intensive.   

Overfull nodes:
- Right Rotation: Used when a node ($n_1$) is overfull and its right sibling ($n_2$) has key space.
    - The largest key in $n_1$ is promoted to the parent, replacing the next largest key.
    - The displaced key from the parent is demoted into the sibling $n_2$ (at the start of its keys).
    - The largest child of $n_1$ is moved to become the smallest child of $n_2$.

- Left rotation is the symmetric to right rotation.

<img src='/trees/BTree/images/rotate.png' alt='Example of Right Rotation when there is a overfull node'>

Underfull nodes:
- Right Rotation: Used when a node ($n_1$) is underfull and its left sibling ($n_2$) has excess keys (more than the minimum required).
    - The next smallest key in the parent (which separates $n_2$ and $n_1$) is demoted into $n_1$ (at the start of its keys).
    - The largest key in $n_2$ is promoted to the parent, replacing the demoted key.
    - The largest child of $n_2$ is moved to become the smallest child of $n_1$.
- Left rotation is the symmetric to right rotation.

#### Splitting

Used when a node temporarily contains too many children and keys ($m+1$ children and $m$ keys) due to an insertion.

Splitting Process:
- The **median** (or **lower median**) key of the overfull node is promoted to the parent node. This key is inserted into the parent at the location corresponding to the branch that led to the overfull node $\Rightarrow$ eliminate the branch and split the overfull node in half.
- The remaining keys and children of the overfull node are divided into two new nodes.
- These two new nodes are connected to the parent via two new branches that straddle the newly promoted median key.
- Because the parent gains a key and a child, it may become overfull itself, requiring the splitting process to potentially propagate one level up the tree.

This is an example of splitting in a B-tree of order $m=7$.

<img src='/trees/BTree/images/split.png' alt='Example of splitting for m = 7'>

**Ensuring validity**:
If the number of keys $m$ is odd:
- Take the median key and promote it to the parent, inserting it where the node’s parent branch extended. This leaves an even $m − 1$ keys with $(m −1)/2$ smaller and $(m − 1)/2$ larger.
- Take the $(m − 1)/2$ keys which are smaller than this median as well as the $(m − 1)/2 + 1 = (m + 1)/2$ leftmost children and create a new node. The same goes for larger keys and rightmost children.

To ensure this works we have to make sure that each of the new nodes is valid, meaning each has between $\lceil m/2 \rceil$ and $m$ children. In other words we claim that:

$$\lceil m/2 \rceil \le (m+1)/2 \le m$$

This can be easily proved correct.

If the number of keys $m$ is even:
- Take the lower median key and promote it to the parent, inserting it where the node’s parent branch extended. This leaves $(m − 2)/2$ smaller and $m/2$ larger keys.
- Take the $(m − 2)/2$ keys which are smaller than this median as well as the $(m − 2)/2+1 = m/2$ leftmost children and create a new node.
- Take the $m/2$ keys which are larger than this median as well as the $m/2+1 = (m+2)/2$ rightmost children and create a new node.

We can also prove that:

- For new left node:

$$\lceil m/2 \rceil \le m/2 \le m$$

- For new right node:

$$\lceil m/2 \rceil \le (m+2)/2 \le m$$

> [!IMPORTANT]
> **Time complexity:** $O(m)$ for copying and shifting array of size $m$.

#### Merging

Used when an underfull node occurs-having $\lceil m/2 \rceil−1$ children and $\lceil m/2 \rceil−2$ keys, and its adjacent siblings lack the extra keys or children required for a rotation (meaning they have exactly $\lceil m/2 \rceil$ children).   

**The Merge Operation:**

- The underfull node is merged with one of its siblings.   

- The parent loses the child branch that separated the two siblings, meaning it must also lose the key that was associated with that branch.   

- This separated key from the parent is demoted and inserted into the newly merged node, positioned between the keys from the two original nodes.   

- Because the parent node loses a key and a child during this process, it may become underfull itself, potentially requiring the merge operation to propagate one level higher in the tree. 

This is an example of merging in a B-tree of order $m=7$.

<img src='/trees/BTree/images/merge.png' alt='Example of merging for m = 7'>

**Validity:**
Our underfull node has $\lceil m/2 \rceil−1$ children and $\lceil m/2 \rceil−2$ keys and the sibling we chose has $\lceil m/2 \rceil$ children and $\lceil m/2 \rceil−1$ keys.

When we merge them there are $2\lceil m/2 \rceil−1$ children and $2\lceil m/2 \rceil−3$ keys. This is enough children but not enough keys. We address this by demote one key from the parent node.

Similarly to splitting, we can also prove that:
$$\lceil m/2 \rceil \le 2\lceil m/2 \rceil−1 \le m$$

> [!IMPORTANT]
> **Time complexity:** $O(m)$ for copying and shifting array of size $m$.

### Insertion

At this point insertion is easy. We find the correct leaf node and insert it and then we rotate and/or split up the tree until the restructuring is finished. Note that it’s possible that no restructuring is required at all.

Take this tree as an example.

<img src='/trees/BTree/images/insert1.png' alt='Insertion 1'>

We insert $24$.

<img src='/trees/BTree/images/insert2.png' alt='Insertion 2'>

Neither adjacent sibling has space for a rotation so instead we split the overfull node in the middle, at the $22$ and promote that middle $22$. Unfortunately, due to the promotion of the $22$ the parent node is now overfull:

<img src='/trees/BTree/images/insert3.png' alt='Insertion 3'>

Luckly the parent has a sibling to the right which can accept a key, so we rotate it over:

<img src='/trees/BTree/images/insert4.png' alt='Insertion 4'>

Now we are done.

> [!IMPORTANT]
> **Time complexity:** 
> - Searching: $O(h \log_2m)$ like in multiway tree, but $h$ is balanced thus $O(\log_mk \cdot \log_2m) = O(\log_2k)$
> - Restructuring: 
>   - Best case: The target leaf node has empty key space so the key is written instantly or we only need one rotation. Total restructuring time is $O(1)$.
>   - Worst case: Cascading splitting and merging. This may happen when every node from the leaf up to its ancestor is completely full or at minimum capacity. Thus restructuring takes $O(m \cdot \log_mk)$.
>   - Average case / Amortized complexity: The average time spent  restructuring per insertion or deletion is actually constant, $O(1)$ because the continuous restructuring is so rare. Thus, amortized complexity is $O(\log_mk)$.
> Therefore, on average, time complexity for insertion is $O(\log k)$

### Deletion

If the target key is not in a leaf then we find a replacement key (the inorder predecessor or successor). This replacement key will necessarily be in a leaf so effectively we are deleting a key from a leaf.

If the leaf is not underfull we are done, otherwise we rotate and/or merge up the tree until the restructuring is finished.

Take this tree as an example:

<img src='/trees/BTree/images/delete1.png' alt='Deletion 1'>

We delete $66$. This results in an underfull node.

<img src='/trees/BTree/images/delete2.png' alt='Deletion 2'>

Neither adjacent sibling can offer a key via rotation so the only choice is to merge with a sibling. Let’s merge with the left sibling, which means that the sandwiched key $54$ in the parent is pulled down:

<img src='/trees/BTree/images/delete3.png' alt='Deletion 3'>

Luckily the parent could give up a key with no issue and we are done.

> [!IMPORTANT]
> **Time complexity:** $O(\log k)$
> The analysis is basically the same as insertion.

## B+ Tree: 

### Introduction

B+ tree is a variation on B tree that:
- Internal nodes do not store values (the actual data) but rather just the keys. (In B trees, we store key-value pairs in internal nodes aside from the child pointers)
- All the key-value pairs are stored in the leaf nodes.
- Each leaf node has a pointer which points to the leaf node to the right.

Essentially the keys in the internal node are guideposts to the leaf nodes and the leaf nodes contain the key-value pairs which really constitute the data.

<img src='/trees/BTree/images/b+tree.png' alt='B+ Tree Example'>

- Since the values (data) are saved only in the leaves this saves space in internal nodes.
- All queries (looking for keys with associated values) will reliably travel to
the bottom of the tree, providing consistent, $O(\log k)$ performance.
- Range queries are especially nice. For example in the above tree if we’re
looking for all keys (with values) in the range $[30, 88]$ we simply find the
$30$ and then follow the leaf nodes across.

<img src='/trees/BTree/images/rangeQueries.png' alt='B+ Tree Example'>

### Operations
Insertion and deletion in B+ Tree are somewhat the same as in B Tree but with more restrictions and updates thus more complicated.

In this part, we will just go over the algorithm.

#### Insertion
When inserting a new key-value pair, we always navigate down to the appropriate leaf node first.
- **Case 1:** The leaf node has space: Simply insert the key and data into the leaf node in sorted order.The tree height is unchanged.
- **Case 2:** If the leaf node is full ($M-1$ keys for an order-$M$ tree), it must be split.
    - Create a new leaf node. Keep the first $\lceil M/2 \rceil$ elements in the original leaf, and move the remaining elements to the new leaf.
    - Take the smallest key of the right (new) leaf and **copy** it up into the parent node to act as a router.
    - Update the leaf-level pointers so the original leaf points to the new leaf.
- **Case 3:** If copying a key up causes the parent internal node to overflow:
    - Split the keys evenly between the old and new internal nodes.
    - Unlike the leaf split, the middle key is pushed up (**removed from the node entirely**) into its parent.
    - If the root splits, a new root is created, and the tree grows in height by $1$.

#### Deletion

Deletion always begins at the leaf node. Because keys in internal nodes only exist to direct traffic, deleting a key from a leaf doesn't always mean you have to immediately remove it from the internal routing nodes—as long as the search path remains valid.

- **Case 1**: The leaf remains half hull: Delete the key-value pair from the leaf. If the deleted key was the minimum value of that leaf, update the corresponding routing key in the parent internal node with the new minimum.
- **Case 2**: If deleting the key causes the leaf to be underfull, look at its immediate left and right siblings. If a sibling has extra keys, do a rotation to borrow a key, and then adjust the parent node's routing key to accurately reflect the new boundary between the two leaves.
- **Case 3**: If no adjacent sibling has extra keys to spare, the underfull node must merge with a sibling.
    - Combine the keys of the underfull leaf and its sibling into a single node. Update the leaf linked list pointers.
    - Because two nodes became one, the parent node loses a child pointer. Remove the routing key that separated them from the parent node.
    - If removing that key from the parent causes the parent to underflow, repeat the rotate/merge process for the internal nodes. If the root loses its last routing key, the merged child becomes the new root, and the tree height shrinks by $1$.




















