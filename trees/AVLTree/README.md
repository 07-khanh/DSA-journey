# AVL Tree

## Properties:
- Self balancing BST.
- Maintaing extra information called **balanced factor** whose value is $\in \\{-1;0;1\\}$.
- **Balanced Factor**: $$BF(N) = \text{Height}(\text{Left Subtree}) - \text{Height}(\text{Right Subtree})$$.
  - By keeping balance factor of each node $\in \\{-1;0;1\\}$ after operations, AVL tree is balanced.
  
<img src="/trees/AVLTree/images/image.png" width=50%></a>

>[!NOTE] 
> **Minimum number of nodes in AVL Tree**
>
> Denote $N(h)$ to be minimum # nodes in AVL Tree of height $h$.
>
> We will prove that:
>
>$$N(h) = F_{h+3}-1$$
>
> where $F_{i}$ is the $i$-th Fibonacci number (starting from $F_0$).
> 
> **Observation**: Worst case of AVL Tree is when every node's subtrees' heights differ by $1$.
>
> Then, assume, without loss of generality, that left subtree is bigger than right subtree.
>
> We have a recurrence relation:
>
> $$N(h) = 1 + N(h - 1) + N(h - 2)$$
>
> where $N(h - 1)$ is # nodes in left subtree,  $N(h - 2)$ is # nodes in right subtree.
>
>**Base Cases**: (0-indexed)
> $h = 0$: A single root node.
>
> $$N(0) = 1$$
>
>$h = 1$: A root with one child (height $0$).
>
> $$N(1) = N(0) + N(-1) + 1 = 1 + 0 + 1 = 2$$
>
> (Note: $N(-1)$ represents an empty tree, which has $0$ nodes).
>
> Calculating the first few cases gives us a sequence remsembling the **Fibonacci Sequence** ($F_0=0, F_1=1, F_2=1, F_3=2, F_4=3, F_5=5, F_6=8, F_7=13...$).
> The exact relationship is:
>
>$$N(h) = F_{h+3} - 1$$
>
> <img src="/trees/AVLTree/images/image-1.png  width=50%"></a>
>
>_(Even though # nodes does not follow Fibonacci sequence exactly, # leaves do)._
>
> Verification for $h=2$:
>
> $N(2) = F_{2+3} - 1 = F_5 - 1 = 5 - 1 = 4$. (Matches).

> [!NOTE]
> **Height of AVL Tree**
> 
> We will prove that the height of AVL Tree is $O(\log n)$.
> 
> We have the Bitnet formula:
>
> $$F_k = \dfrac{\phi^k - \psi^k}{\sqrt{5}}$$
> 
> with $\phi=\dfrac{1+\sqrt{5}}{2},\ \psi=\dfrac{1-\sqrt{5}}{2}$.
>
> Since $\dfrac{|\psi^k|}{\sqrt{5}} < 1/2 \Rightarrow F_k = \left \lfloor \dfrac{\phi^k}{\sqrt{5}}\right \rceil$.
>
> OR $\dfrac{\phi^k}{\sqrt{5}} - 1/2 \le F_k \le \dfrac{\phi^k}{\sqrt{5}} + 1/2$.
> 
> We apply this to AVL Tree:
>
> ```math
> \begin{align*} N(h) &= F_{h+3}-1 \\
> &\ge \dfrac{\phi^{h+3}}{\sqrt{5}} - \dfrac{1}{2} - 1 \\
> & \ge \dfrac{\phi^{h+3}}{\sqrt{5}} - \dfrac{3}{2} 
> \end{align*}
> ```
> 
> Let $n$ be # nodes in AVL Tree, then
> 
> $$n \ge N(h) \ge \dfrac{\phi^{h+3}}{\sqrt{5}} - \dfrac{3}{2} $$
> 
> $$n \ge \dfrac{\phi^{h+3}}{\sqrt{5}} - \dfrac{3}{2}$$
> 
> $$\sqrt{5}\left(n + \dfrac{3}{2}\right)  \ge \phi^{h+3}$$
> Take $\log_\phi$:
> 
> ```math
> \begin{align*}h &\le \log_{\phi}\left[\sqrt{5}\left(n + \dfrac{3}{2}\right)\right]-3 \\
> & \le 1,44 \log_2\left(n+\dfrac{3}{2}\right) - 0,328 \\
> &= O(\log n)
> \end{align*}
> ```
>

## Basic Operations

### Node structure
A node now stores $4$ information: 
- Associated data, 
- Pointer to Left Subtree,
- Pointer to Right Subtree,
- Node's height.

### Rotation
There will be $4$ cases needed rebalancing using rotations: **Left Left (L-L), Right Right (R-R), Left Right (L-R), Right Left (R-L)**.

<img src="/trees/AVLTree/images/image-4.png"  width=50%></a>

**SINGLE ROTATIONS**

<img src="/trees/AVLTree/images/image-3.png"  width=50%></a>

```cpp
ROTATE_RIGHT(root)
    Set newNode = root->left
    root->left = newRoot->right
    newRoot->right = root

    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right))
    root->height = 1 + max(height(root->left), height(root->right))

    return newRoot
```

```cpp
ROTATE_LEFT(root)
    Set newRoot = root->right
    root->right = newRoot->left
    newRoot->left = root

    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right))
    root->height = 1 + max(height(root->left), height(root->right))

    return newRoot
```
**DOUBLE ROTATIONS**

<img src="/trees/AVLTree/images/image-2.png"  width=50%></a>

```cpp
LEFT_RIGHT(root)
    root->left = LEFT_ROTATE(root->left)
    return RIGHT_ROTATE(root)
```

```cpp
RIGHT_LEFT(root)
    root->right = RIGHT_ROTATE(root->right)
    return LEFT_ROTATE(root)
```

### Insertion
Do normal BST Insertion, then rebalance using rotations ($4$ cases).

<img src="/trees/AVLTree/images/image-5.png"  width=50%></a>
<img src="/trees/AVLTree/images/image-6.png"  width=50%></a>
```cpp
GET_BALANCE(root)
    if root is NULL return 0 
    return root->left->height - root->right->height
```

```cpp
INSERT(node, key)
    if node is NULL
        create and return new Node(key)

    if node->data > key
        node->left = INSERT(node->left, key)
    else if node->data <> key
        node->right = INSERT(node->right, key)
    else 
        return node

    // Update the ancestors' height
    node->height = 1 + max(node->left->height, node->right->height)

    set balance = GET_BALANCE(node)

    if balance > 1
        // L-L
        if key <= node->left->data
            return LEFT_ROTATION(node)
        // L-R
        else 
            return LEFT_RIGHT(node)
    else if balance < -1
        // R-R
        if key >= node->right->data
            return RIGHT_ROTATION(node)
        // R-L
        else
            return RIGHT_LEFT(node)

    return node
```

> [!NOTE]
After Insertion, if rebalancing is needed, the height of the modified subtree is still the same as it was before the insertion.
> 
This implies that no further rotations are required.

### Deletion
Do normal BST Deletion, then rebalance using rotations ($4$ cases).

<img src="/trees/AVLTree/images/image-7.png"  width=50%></a>
<img src="/trees/AVLTree/images/image-8.png"  width=50%></a>

```cpp
DELETE(node, key)
    if node is NULL 
        return node

    if key < node->data 
        node->left = DELETE(node->left, key)
    else if key > node->data 
        node->right = DELETE(node->right, key)
    else
        if node->right is NULL
            create Node pointer temp = node->left
            delete node
            return temp
        else if node->left is NULL
            create Node pointer temp = node->right
            delete node
            return temp
        else
            create Node pointer suc = node->right
            while suc->left
                suc = suc->left
            node->data = suc->data
            node->right = DELETE(node->right, suc->data)

    if node is NULL
        return node

    node->height = 1 + max(node->left->height, node->right->height)

    set balance = GET_BALANCE(node)

    if balance > 1
        // L-L
        if GET_BALANCE(node->left) >= 0
            return LEFT_ROTATION(node)
        // L-R
        else 
            return LEFT_RIGHT(node)
    else if balance < -1
        // R-R
        if GET_BALANCE(node->right) <= 0
            return RIGHT_ROTATION(node)
        // R-L
        else
            return RIGHT_LEFT(node)

    return node
```

## Notes
- AVL Tree has height $h = O(\log n)$. Therefore, all BST operations can have time complexity from $O(h) \Rightarrow O(\log n)$ if we use AVL Tree implementation.
