# AA Tree

## Definition and Properties:

A Red-Black Tree's implementation and number of rotations is complex. Therefore, we are introduced a variation of Red-Black Tree, which is **AA Tree**.

It has the same 5 properties as RBT, but with one additional property: **Left children are RED.**

<img src="/trees/AATree/images/aatree_example.png" alt="AA Tree Example">

AA Tree has fewer rotations so easier to code, especially in deletion.

AA-trees still have $O(\lg n)$ searches in the worst case, although they are slightly less efficient empirically.

### Redefinition of Leaf:

A leaf in an AA tree is a node with no black internal node as children.

<img src="/trees/AATree/images/leaf.png" alt="Leaf nodes in AA Tree">

### Redefinition of Levels:
The **level** of a node, instead of color, is used as balancing information. Red nodes are simply nodes that are on the same level as their parents.

The level of a node is defined as follow:
The level of a node is defined as follows:
- The lowest black nodes (leaves) have level 1.
- Red nodes are at the same level as their parents.
- Black nodes are at one level less then their parents.

<img src="/trees/AATree/images/level.png" alt="Level in AA Tree">

### Implications of Ordering Properties:
1. Horizontal links are right links (because only right children are red).
2. There are no double horizontal links.
3. Nodes at level 2 or higher must have two children.
4. If a node does not have horizontal link, its children are at the same level.
5. Any simple path from a black node to a leaf contains one black node on each level.

## Operations

New node attributes:
- `data`
- `level`
- `left`
- `right`
(`parent` is ommitted)

### Balancing Operations
#### Split
<img src="/trees/AATree/images/split.png" alt="Split in AA Tree">

We use `split` when there are two adjacent red nodes, a.k.a two right horizontal links.

It is basically a left rotation + updating level.

```cpp
SPLIT(x)
    if x == nil
        return nil
    if root->right != nil 
    and root->right->right != nil 
    and root->right->level == root->right->right->level
        // Rotate Left
        set y = x->right
        x->right = y->left
        y->left = x

        y->level = y->level + 1
        return y
    return x
```

#### Skew
<img src="/trees/AATree/images/skew.png" alt="Skew in AA Tree">

We use `skew` when there is a red left node, a.k.a left horizontal link.

`Skew` is basically right rotation. P level is the same as X after the rotation.

```cpp
SKEW(x)
    if x == nil
        return nil
    if root->left != nil 
    and root->left->level == root->level
        // Rotate Right
        set y = x->left
        x->left = y->right
        y->right = x

        return y
    return x
```

### Insertion

The `INSERT` function recursively finds the correct leaf position, creates a new node at level 1, and then applies `skew` followed by `split` as the recursion unwinds.

```cpp
INSERT(node, value):
    // Base case - standard BST insertion at a leaf
    if node == nil:
        // Create a new leaf node at level 1
        new_node = create_new_node(value)
        new_node->level = 1
        new_node->left = nil
        new_node->right = nil
        return new_node
        
    // Recurse down the tree
    if value < node->data:
        node->left = INSERT(node->left, value)
    else if value > node->data:
        node->right = INSERT(node->right, value)
    else:
        // Duplicate value: Handle according to implementation rules 
        // (e.g., do nothing or update value)
        return node

    // Bottom-up rebalancing
    // First, eliminate any left horizontal links
    node = skew(node)
    
    // Second, eliminate consecutive right horizontal links
    node = split(node)
    
    return node
```

<img src="/trees/AATree/images/insert.png" alt="Skew in AA Tree">

> [!IMPORTANT]
> Each of the skew and split operations is $O(1)$ and we may need $O(\lg n)$ of them, yielding a time complexity of $O(\lg n)$.

### Deletion

Deletion in an AA tree follows the standard Binary Search Tree deletion strategy: find the node, replace it with its internal successor (or predecessor) if it has two children, remove the leaf, and then rebalance the tree on the way back up.

However, because deletion can decrease the level of a subtree, the rebalancing phase requires a few more checks than insertion to ensure the level invariants are maintained.

- Search and Replace: Traverse down the tree to find the node to delete. If the node has two internal children, find its in-order successor (the smallest node in its right subtree), copy the successor's value to this node, and recursively delete the successor instead.

- Decrease Level: When a node is physically removed, the height of that branch drops. We must check if the current node's level is now more than 1 level higher than either of its children. If it is, we must lower the level of the current node (and its right child, if it was a horizontal link).

- Rebalance (Skew and Split): Lowering a level can cause a cascade of invariant violations. We fix these by calling skew and split on the current node, its right child, and its right-grandchild.

```cpp
UPDATE_LEVEL(node)
    // Calculate what the correct level should be based on children
    ideal_level = min(node->left->level, node->right->level)

    // If the node's current level is too high, pull it down
    if (node->level > ideal_level)
        node->level = ideal_level
        // If the right child was a horizontal link, its level 
        // cannot be greater than the parent's new level
        node->right->level = ideal_level
    return node
```
```cpp
DELETE(node, value)
    if node == nil
        return nil
    
    if value < node->data
        node->left = DELETE(node->left)
    else if value > node->data
        node->right = DELETE(node->right)
    else
        // Case 1: Node is a leaf or has only one horizontal right child
        if node->left == nil
            return node->right
        else if node->right == nil
            return node->left
        
        // Case 2: Node has two internal children
        else
            // Find the in-order successor (leftmost node in right subtree)
            successor = successor(node)
            node->data = successor->data
            // Delete the successor
            node->right = DELETE(node->right, successor->data)

        // Fix levels if a child's level dropped
        node = UPDATE_LEVEL(node)

        // Rebalance the structural cascade
        // Check and fix the current node
        node = SKEW(node)
        node->right = SKEW(node->right)
        if node->right != nil:
            node->right->right = SKEW(node->right->right)

        // Split to fix any double-horizontal links created by the skews
        node = SPLIT(node)
        node->right = SPLIT(node->right)

        return node
```

<img src="/trees/AATree/images/delete.png" alt="Deletion in AA Tree Example">

