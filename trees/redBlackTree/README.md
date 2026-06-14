# Red Black Tree

## Properties

Red Black Tree (RBT) is a self-balancing BST, with each node containing one extra bit denoting its **color**, either **RED** or **BLACK**.

A RBL satisfies the following properties:
1. Every node is either **red** or **black**.
2. The **root** is **black**.
3. Every leaf (**NIL**) is black.
4. If a node is **red**, then both its **children** are **black**.
5. For each node, all simple paths from that node to the descendant leaves contain the **same number of black nodes (black height)**.

Then, every node now has the following attributes:
- `parent`
- `left`
- `right`
- `data`
- `color`

<img src='/trees/redBlackTree/images/image.png' alt='example of RBT'>

### Sentinel
As a matter of convenience in dealing with boundary conditions, we use a sentinel (dummy node) to presensent NIL (leaves and root's parent)

=> Save space and enable simpler code.

<img src='/trees/redBlackTree/images/image-1.png' alt='example of RBT using sentinel'>

In RBT, we only concern ourselves with internal nodes (nodes with data).Therefore, we can omit NIL when drawing RBT.

<img src='/trees/redBlackTree/images/image-2.png' alt='example of RBT omitting NIL'>

### Height properties
#### Black-height

Black-height of a node $x$, denoted by $bh(x)$ is the number of black nodes on any simple paths from, but not including, node $x$ down to a leaf. 

The black-height of a RBT is the black-height of its root.

<img src='/trees/redBlackTree/images/image.png' alt='example of RBT'>

#### Claims

> [!IMPORTANT]
> Any node with height $h$ has black-height $\ge h/2$.
>
> **Proof:**
>
> By property 4, there are $\le h/2$ red nodes on a path from a node to a leaf. Hence $\ge h/2$ are black.

> [!IMPORTANT]
> The subtree rooted at any node $x$ contains $\ge 2^{\text{bh}(x)}-1$ internal nodes.
>
> **Proof**: Prove by induction on height of $x=h(x)$.
>
> **Base case**: 
>
> $h(x)=0 \Rightarrow x$ is a leaf $\Rightarrow \text{bh}(x)=0$.
>
> The subtree rooted at $x$ has $0$ internal nodes, and $2^0-1=0$.
>
> **Inductive step:**
>
> Consider node $x$ which is an internal node. Let height of $x$ be $h$ and $\text{bh}(x)=b$. Any child of $x$ has height $< h$ and black-height either $b-1$ (if the child is black) or $b$ (if the child is red). 
>
> By the inductive hypothesis, each child has $\ge 2^{b-1}-1$ internal nodes. Thus the subtree rooted at $x$ contains $\ge 2\cdot (2^{b-1}-1) + 1 = 2^{b}-1$ internal nodes, which proves the claim.

> [!IMPORTANT]
> **Lemma:** A RBT with $n$ internal nodes has height at most $2\lg(n+1)$.
> 
> **Proof:** Let $h$ and $b$ be the height and black-height of the root, respectively. By the above two claims:
>
> $$n \ge 2^b-1 \ge 2^{h/2}-1$$
> $$\Rightarrow h \le 2\lg(n+1)$$
>
> which proves the lemma.

As a consequence of this lemma, all basic operations on RBT will take $O(\lg n)$ time.

## Basic operations
### Rotations

<img src='/trees/redBlackTree/images/image-3.png' alt='left, right rotations'>

```cpp
LEFT_ROTATE(T, x)
    // Set new root as y
    set Node pointer y = x->right   

    // Fix link between y's left subtree and x
    x->right = y->left              
    if y->left is not T.NIL
        y->left->parent = x

    // Fix link between y and x's parent 
    y->parent = x->parent           // Link x's parent to y.
    if x->parent == T.NIL           // If x's parent is root
        T.root = y
    else if x == x->parent->left    // If x is left child
        x->parent->left = y
    else                            // If x is right child
        x->parent->right = y
    
    // Fix link between x and y (x is y's left child)
    y->left = x
    x->parent = y
```

_Pseudocode for `RIGHT_ROTATE` is symmetric to `LEFT_ROTATE`, just exchange `left` and `right` everywhere_.

### Insertion

First, start with regular BST node insertion. The new node `z` is colored **red**. Then, call another `INSERT_FIXUP` function to fix possible violated red-black properties.

```cpp
INSERT(T, val)
    set new Node pointer z  // Create new node z
    z->data = val

    set x = T.root          // node being compared with z
    set y = T.NIL           // y will be parent of z

    while (x != T.NIL)      // descend until reaching the sentinel
        y = x   
        if val < x->data
            x = x->left
        else 
            x = x->right
    
    z->parent = y           // found the location-insert z with parent y
    if y == T.NIL           // tree T is empty
        T.root = z
    else if val < y->data
        y->left = z
    else
        y->right = z

    z->left = T.NIL         // both of z's children are sentinels
    z->right = T.NIL
    z->color = RED          // the new node starts out red

    INSERT_FIXUP(T, z)      // correct violations of red-black properties
```

```cpp
INSERT_FIXUP(T, z)
    while z->parent->color == RED                   // only fix if z's parent's color is red
        if z->parent == z->parent->parent->left     // if z' parent is a left child
            set y = z->parent->parent->right        // y is z's uncle

            // CASE 1: both parent and uncle are red
            if y->color == RED                      // if z's uncle and parent are red
                z->parent->color = BLACK            // change color of z's parent to black
                y->color = BLACK                    // change color of z's uncle to black
                z->parent->parent->color = RED      // change color of z's grandparent to red
                z = z->parent->parent               // z's grandparent becomes new z (possibly violates red-black properies)
            
            // CASE 2, 3: parent is red and uncle is black
            else
                // CASE 2: z is right child of left child (LR)
                if z == z->parent->right
                    z = z->parent                   // change to case 3
                    LEFT_ROTATE(T, z)
                // CASE 3:
                z->parent->color = BLACK            // change color of z's parent to black
                z->parent->parent->color = RED      // change color of z's grandparent to red
                RIGHT_ROTATE(T, z->parent->parent)  // rotate to fix black height
        
        else  // if z' parent is a right child (same as the first case, with 'left' and 'right' exchanged)
            set y = z->parent->parent->left
            if y->color == RED        
                z->parent->color = BLACK
                y->color = BLACK
                z->parent->parent->color = RED
                z = z->parent->parent
            else
                if z == z->parent->left
                    z = z->parent
                    RIGHT_ROTATE(T, z)
                z->parent->color = BLACK
                z->parent->parent->color = RED
                LEFT_ROTATE(T, z->parent->parent)

    T.root->color = BLACK
```

**Loop invariant:**

At the start of each iteration of the **while** loop:
- `z` is red
- There is at most one red-black violation
    - Property 2: `z` is a red root
    - Property 4: `z` and `z`'s parent are red

**1. Initilization:** obviously seen

**2. Termination:** The loop terminates when `z`'s parent is black. Thus, property 4 is OK. Only property 2 might be violated and the last line fixes that.

**3. Maintenance:** We drop out when `z` is the root because then its parent is `T.NIL` which is black. When we start the loop body, the only violation is property 4.

There are 6 cases, 3 of which are symmetric to the other 3. We here consider the cases when `z` is a left child.

Let `y` be `z`'s uncle.

**3.1 Case 1:** `y` is red.
- `z`'s grandparent is black as both `z`'s parent and uncle are red and there is no violation of property 4 before.
- Make `z`' parent and `y` black $\Rightarrow$ fix property 2, but property 5 (equal black heights) might be violated.
- Make `z`'s grandparent red $\Rightarrow$ restore property 5.
- The next iteration has `z`'s grandparent as new `z`. (Move up 2 levels).

<img src='/trees/redBlackTree/images/case1.png' alt='Case 1 of insertion'>

**3.2 Case 2:** `y` is black and `z` is a right child (LR).
- Left rotate around `z`'s parent. Now `z` is a left child, both `z` and `z`'s parent are red.
- This takes us to case 3.

**3.3 Case 3:** `y` is black and `z` is a left child (LL).
- Make `z`'s parent black and `z`'s grandparent red.
- Right rotate on `z`'s grandparent $\Rightarrow$ preserve propery 5
- No longer have 2 reds in a row.
- `z`'s parent is now black $\Rightarrow$ no more iterations.

<img src='/trees/redBlackTree/images/case2_3.png' alt='Case 2 and 3 of insertion'>

> [!IMPORTANT]
> **Analysis:**
>
> It takes $O(h) = O(\lg n)$ time to do initial BST insertion.
>
> Within `INSERTION_FIXUP`:
> - Each iterations takes $O(1)$ time.
> - Only repeats if case 1 occurs, and `z` moves up 2 levels. There are $O(\lg n)$ levels so this takes at most $O(\lg n)$ time.
> - There are **at most 2 rotations** since the while loop terminates after case 2 or 3 is executed.
>
> Thus insertion into a RBT takes $O(\lg n)$ time.

### Deletion:
Start by doing regular BST deletion (Suppose the node is guarenteed to be in the tree).
```cpp
REMOVE(T, val)
    set Node pointer z = T.root
    while (z != T.NIL)
        if (val < z->data)
            z = z->left
        else if (val > z->data)
            z = z->right
        else
            DELETE(T, z)
```

This is the main deletion function. It accepts a value, find it in the tree and then call `DELETE` do actually delete the node.

```cpp
TRANSPLANT(T, u, v)     // u's parent becomes v's parent
    if u->parent == T.NIL            
        T.root = v
    else if u == u->parent->left    
        u->parent->left = v
    else
        u->parent->right = v
    v->parent = u->parent
```

This helper function `TRANSPLANT` takes a subtree rooted at node `u` and replaces it entirely with a subtree rooted at node `v`. It disconnects `u` from its parent and wires `v` into that exact parent pointer. Crucially, `TRANSPLANT` only handles the top-level parent connection; it does not touch or update any left or right child pointers.

```cpp
DELETE(T, z)
    set y = z
    y_original_color = y->color

    // if z has at most one child
    if z->left == T.NIL
        x = z->right
        TRANSPLANT(T, z, z->right)      // replace z by its right child
    else if z->right = T.NIL
        x = z->left
        TRANSPLANT(T, z, z->left)       // replace z by its left child
    // if z has two children
    else                                
        y = SUCCESSOR(z)                // y is z's successor
        y_original_color = y->color     
        x = y->right                    // x is y's right child (only child)
        if y != z->right                // if y is farther down the tree
            TRANSPLANT(T, y, y->right)  // replace y by its right child
            y->right = z->right         // z's right child becomes 
            y->right->parent = y        //      y's right child
        else
            x->parent = y               // in case x is T.NIL
        TRANSPLANT(T, z, y)             // replace z by its successor y
        y->left = z->left               // give z's left child to y, 
        y->left->parent = y             //      which has no left child
        y->color = z->color             // y takes z's color
    if y_original_color == BLACK        // if any red-black violations occurred
        DELETE_FIXUP(T, x)              // correct them
```
The basic layout of `TREE-DELETE` is preserved, but with a strict focus on tracking two key nodes:
- Node `y`: Represents the node that is either completely removed from the tree or moved within it.
    - If the target node `z` has at most one child, `y` is `z` itself.
    - If `z` has two children, `y` is `z`’s successor (which is guaranteed to have no left child) and will physically move into `z`'s position.
- Node `x`: Represents `y`’s only child (or the sentinel `T.NIL` if `y` has no children). `x` is the node that shifts upward to fill the gap left behind by `y`.

`y_original_color` will be the original color that is lost after deletion (`z`'s color in the first case and successor `y` color in the second case).

Now we go to the algorithm.

**Case 1: z has at most one child (`y` = `z`)**
If `z` lacks a left child, its right child `x` takes its place. If `z` lacks a right child, its left child `x` takes its place.

`TRANSPLANT` unlinks `z` entirely, hooks `z`’s original parent directly to `x`, and automatically configures `x.p` correctly.

**Case 2: `z` has two children (`y` = successor)**
When `z` has two children, the algorithm cannot simply tear it out without creating a massive hole. Instead, it finds `z`’s successor `y` deep in the right subtree. Because `y` is the minimum node of that subtree, it is guaranteed to have no left child, meaning its right child is our node `x`.

The algorithm then executes a two-step physical relocation:

- Extracting `y` from below: If `y` is deep in the tree (not the direct right child of `z`), the algorithm runs `TRANSPLANT(T, y, x)` to slide `x` up into `y`’s old slot. `y` is now completely detached, so the algorithm manually forces `y` to adopt `z`’s right subtree:

(if `y` is already `z`’s direct right child, this extraction step is skipped, and the code manually patches `x.p = y` instead).

- Now that `y` has cleanly extracted its own roots, it replaces `z` at the top of the subtree.

Once the physical pointer updates are finished, the algorithm masks the structural change at the top of the subtree by forcing `y` to inherit `z`’s original color.

Because `y` now perfectly mimics `z`'s color, the top half of the tree experiences zero disruption. However, because node `y` was physically removed or shifted out of its original home downstairs, the algorithm looks back at the variable `y_original_color` to determine if the tree's balance was compromised:

- If `y_original_color` was RED: The deletion process terminates immediately. Removing a red node changes nothing—it does not alter the black height of any path, it cannot create adjacent red nodes (since a red node's parent and children are guaranteed to be black), and it cannot affect the root.

- If `y_original_color` was BLACK: A structural deficit has been created. The branch where `y` used to live is now short exactly one black node. We then call `DELETE_FIXUP` to fix this.


```cpp
DELETE_FIXUP(T, x)
    while x != T.root and x->color != BLACK
        if x == x->parent->left         // if x is a left child
            w = x->parent->right        // w is x's sibling
            // CASE 1
            if w->color == RED          
                w->color = BLACK
                x->parent->color = RED
                LEFT_ROTATE(T, x->parent)
                w = x->parent->right
            // CASE 2
            if w->left->color == BLACK and w->right->color == BLACK
                w->color = RED
                x = x->parent
            else 
                // CASE 3
                if w->right->color == BLACK
                    w->left->color = BLACK
                    w->color = RED
                    RIGHT_ROTATE(T, w)
                    w = x->parent->right
                // CASE 4
                w->color = x->parent->color
                x->parent->color = BLACK
                w->right->color = BLACK
                LEFT_ROTATE(T, x->parent)
                x = T.root
        else    // same as before with 'left' 'right' exchanged
            w = x->parent->left
            if w->color == RED
                w->color = BLACK
                x->parent->color = RED
                RIGHT_ROTATE(T, x->parent)
                w = x->parent->left
            if w->right->color == BLACK and w->left->color == BLACK
                w->color = RED
                x = x->parent
            else 
                if w->left->color == BLACK
                    w->right->color = BLACK
                    w->color = RED
                    LEFT_ROTATE(T, w)
                    w = x->parent->left
                w->color = x->parent->color
                x->parent->color = BLACK
                w->left->color = BLACK
                RIGHT_ROTATE(T, x->parent)
                x = T.root
    x->color = BLACK
```

If `y` was black, there problems will arise, which needs `DELETE_FIXUP`:
- `y` is the root, and `y`'s child that takes `y`'s place is red. Then, the root is red **(Property 2)**.
- `x` and `x`'s new parent are red **(Property 4)**.
- Moving `y` within the tree causes any simple path that previously contained `y` to have one less black node. Thus, any ancestor of `y` in the tree violates **Property 5**.

For the last case, we can fix violation of property 5 by saying that when `y` is moved or removed, its blackness is transfered to `x` that moves into `y`'s original position, giving `x` an "extra" black. This means we add 1 to the black count of any path containing `x`. 
- if `x`'s color is black, then now it is **doubly black**.
- if `x`'s color is red, then now it is **red-black**.

However, now `x` is neither red nor black, thus violates property 1.
> [!NOTE]
> `x` is now not a fixed node but a pointer that points to the node with "extra black". That means the paths with `x` are deficit of one black unit.
>
> In other words, the color attribute of all the nodes is still normal, only the node pointed by `x` will implicitly have "extra black".

<img src='/trees/redBlackTree/images/deletion.png' alt='Four cases of deletion'>

The procedure `DELETE-FIXUP`restores properties 1, 2, and 4. The goal of the `while` loop is to move the extra black up the tree until
1. `x` points to a red-and-black node, in which case the last line colors `x` (singly) black to absorb the extra black (compensate for one missing black node);
2. `x` points to the root, in which case the extra black simply vanishes; or
3. having performed suitable rotations and recolorings, the loop exits.

The transformation in each case preserves property 5 as in each case, the transformation applied preserves the number of black nodes (including `x`’s extra black) from (and including) the root of the
subtree shown to the roots of each of the subtrees $\alpha, \beta, \zeta$.

In this analysis, we focus on the case when `x` is a left child. The other case will be symmetric to this.

**Case 1: `x` sibling's `w` is red**

Because `w` is black, its children are red. Therfore, we switch colors of `w` and `x`'s parent, then do a `LEFT_ROTATE` on `x`'s parent without violating property 5. The new sibling of `x`, which is one of `w`'s children prior to the rotation, is now black, and thus convert case 1 to case 2, 3, or 4.

Case 2, 3, 4 occur when `w` is black, and are distinguished by `w`'s children's colors.

**Case 2: `w` is black and both of `w`'s children are black**

We remove one black unit from both `x` and `w`, leaving `x` with one black and leaving `w` red. To compensate for `x` and `w` losing one black, `x`'s parent can take that extra black. We do this by moving `x` up one level, thus `x`'s parent becomes new `x`. If the new `x` is red-and-black, the loop exits and we turn `x` (singly) black.

**Case 3: `w` is black, `w`’s left child is red, and `w`’s right child is black**

We switch colors of `w` and `w` left child, then do a `RIGHT_ROTATE` on `w` without violating red-black properties. The new sibling `w` of `x` is now a black node with a red right child, and thus case 3 falls through into case 4.

**Case 4: `w` is black, and `w`'s right child is red**

This case will really absorb the extra black. First, the paths containing `x` is deficit of one black unit. Therefore we might want to do a `LEFT_ROTATE` to have one more black. 
If so: 
- The Parent (`x`'s parent) must become black: Since the parent was dragged down directly above `x`, making it black injects the missing black node directly into `x`'s path. `x` can now drop its "double-black" status and become a normal, singly-black node. The deficit on the left is fixed.
- The sibling (`w`) inherits the parent's color: Because `w` replaces the parent at the top of this subtree, giving it the parent's original color ensures that the rest of the tree higher up sees absolutely zero changes in black height or coloring.
- `w`'s right child must become black: When `w` rotated up, its right branch moved up with it. To compensate for `w` changing colors and to keep the right branch balanced, we dye `w`'s right black.

Finally, we set `x` to be the root so that the loop terminates in the next iteration.

> [!IMPORTANT]
> **Time analysis:**
>
> - Searching takes $O(h) = O(\lg n)$.
> - `DELETE` without doing `DELETE_FIXUP` takes $O(h) = O(\lg n)$ (mostly just for finding successor, the other processes take $O(1)$ time).
> - `DELETE_FIXUP`: Case 1, 3, 4 each takes $O(1)$ time. Only in case 2 is the while loop repeated, and then the pointer `x` moves up the tree at most $O(\lg n)$ times, performing no rotations.
> 
> Overall, deletion takes $O(\lg n)$ time.
