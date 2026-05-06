<center>
    <h1>BINARY SEARCH TREES</h1>
</center>

## Properties:
> [!NOTE] Binary Search Tree (BST) Property:
> Let $x$ be a node in a binary search tree. 
> - If $y$ is a node in the left subtree of $x$ , then $y.key \le x.key$.  
> - If $y$ is a node in the right subtree of $x$ , then $y.key \ge x.key$.

- **Inorder Traversal** of a BST gives sorted order of elements.
- Average height: $O(\log n)$.
- Worst case height: $O(n)$ (skewed Tree)

## Basic Operations:
### Tree Walk
```cpp
INORDER-TREE-WALK(x)
  if x != NIL
    INORDER-TREE-WALK(left[x])
    print key[x]
    INORDER-TREE-WALK(right[x])
```

- Time complexity: $\Theta (n)$.

> [!NOTE] Proof (Optional):
> - Let $T(n)$ be the time complexity for a tree walk on a tree with $n$ nodes.   
> - Since a tree walk must visit every one of the $n$ nodes at least once, we have $T(n) = \Omega(n)$.  
> - It remains to show that $T(n)= O(n)$.  
> - Since `INORDER-TREE-WALK` takes a small, constant amount of time on an empty subtree (for the test $x = NIL$), we have $T(0) = c$ for some constant $c>0$.
> - For $n > 0$, suppose that `INORDER-TREE-WALK` is called on a node $x$ whose left subtree has $k$ nodes and whose right subtree has $n -k - 1$ nodes. The time to perform `INORDER-TREE-WALK(x)` is bounded by $T(n) \le T(k) + T(n-k-1)+ d$ for some constant $d > 0$ that reflects an upper bound on the time to execute the body of `INORDER-TREE-WALK(x)`, exclusive of the time spent in recursive calls.  
> - We use the substitution method to show that $T(n) = O(n)$ by proving that $T(n) \le (c + d)n + c$. 
> For $n = 0$, we have $T(0) = c$, which satisfies $(c+d)(0) + c = c$. 
> For $n > 0$ we have: 
> $T(n) \le T(k) + T(n-k-1)+ d$
> $ \ \ \ \ \ \ \ \ \ \ \le ((c+d)k + c) + ((c+d)(n-k-1) + c) + d$
> $ \ \ \ \ \ \ \ \ \ \ = (c+d)n + c - (c +d) + c + d$
> $  \ \ \ \ \ \ \ \ \ \ = (c+d)n + c$.
> which completes the proof.

### Other Operations:
<a href="/trees/binarySearchTree/main.cpp">Search, Insertion, Deletion, Max/Min, Ceil/ Floor, Successor/Predecessor</a>.
- Time complexity: $O(h)$.

## Problems:
1. <a href="/trees/binarySearchTree/kthSmallest.cpp">Kth Smallest Element in BST</a>.
2. <a href="trees/binarySearchTree/isBST.cpp">Validate BST</a>.
3. <a href="/trees/binarySearchTree/lca.cpp">LCA in BST</a>.
4. <a href="trees/binarySearchTree/twoSum.cpp">Two Sum In BST | Check if there exists a pair with Sum K</a>.
5. <a href="/trees/binarySearchTree/bstFromPreorder.cpp">Construct BST from a preoder traversal</a>.
6. <a href="trees/binarySearchTree/recoverBST.cpp">Recover Binary Search Tree</a>

## AVL Tree:



