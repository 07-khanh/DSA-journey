# Heap

## Heap Data Structure:
- Heap DS is a nearly complete **binary tree**.
- A heap can be stored in an array (complete BT property):
    - Root of tree: $a[0]$.
    - Left child of $a[i]$: $a[2i+1]$.
    - Right child of $a[i]$: $a[2i+2]$.
    - Parent of $a[i]$: $a[\ \lfloor (i-1)/2 \rfloor\ ]$.

## Heap Property:
- **Max-heaps**: for all nodes $i$ except for the root:
$$a[\ \text{Parent}[i]\ ] \ge a[i]$$
- **Min-heaps**: for all nodes $i$ except for the root:
$$a[\ \text{Parent}[i]\ ] \le a[i]$$

Thus, the maximum element in a max-heap is at the root. Similar argument for min-heaps.

**Max-heap operations**: _(the same can be infered for min-heaps)_.

```cpp
PARENT(i)
    return floor( (i-1)/2 )
```
```cpp
LEFT(i)
    return 2 * i + 1
```
```cpp
RIGHT(i)
    return 2 * i + 2
```

## Heap Operations:

### Max-Heapify:
Used to mainain heap property.
- Before `MAX_HEAPIFY`, `a[i]` may be smaller than its children.
    Assume left and right subtree are max-heaps.
- After `MAX_HEAPIFY`, the subtree rooted at `i` is a max-heap.
  
```cpp
MAX_HEAPIFY(a, i, n)
    l = LEFT(i)
    r = RIGHT(i)

    set i as largest

    // Find the largest in a[i], l , and r.
    if l < n and a[l] > a[largest]
        largest = l
    if r < n and a[r] > a[largest]
        largest = r

    if i != largest 
        swap a[i] and a[largest]
        MAX_HEAPIFY(a, largest, n) // Call MAX_HEAPIFY on subtree rooted at 'largest' with swapped value.
```

> [!IMPORTANT]
> Time complexity: $O(\log n)$.
> - Intuition:
>   
> The algorithm does constant work per node $\Rightarrow \Theta(1)$.
> 
> In the worst case, this is carried out for all $O(\log n)$ levels in the heap, leading to running time of $O(\log n)$.
> - More rigorous proof:
> Worst case happens when the last level of complete BT is half full. Then, the # nodes in left subtree is $O(2n/3)$.
> 
> We have the recurrence
>
> $$T(n) \le T(2n/3) + \Theta(1)$$
> 
> Using master theorem, $T(n)=O(\log n)$.

### Build a heap:

```cpp
BUILD_MAX_HEAP(a, n)
    for i = (floor(n/2) - 1) downto 0
        MAX_HEAPIFY(a, i, n)
```

> [!IMPORTANT]
> In a heap of $n$ elements, the number of nodes at height $h$ is at most:
>
> $$\left\lceil \frac{n}{2^{h+1}} \right\rceil$$
> 
> The time required by `MAX-HEAPIFY` when called on a node of height $h$ is $O(h)$.
> The total time $T(n)$ is the sum of (nodes at height $h$) $\times$ (work at height $h$) for all possible heights from $0$ to $\lfloor \lg n \rfloor$:
>
> $$T(n) = \sum_{h=0}^{\lfloor \lg n \rfloor} \left\lceil \frac{n}{2^{h+1}} \right\rceil O(h) = O\left(n \sum_{h=0}^{\lfloor \lg n \rfloor} \frac{h}{2^h}\right) \text{}$$
> 
> To evaluate the summation $\sum_{h=0}^{\infty} \frac{h}{2^h}$, we use the general geometric series formula:
>
> $$\sum_{k=0}^{\infty} kx^k = \frac{x}{(1-x)^2}$$
>
> By substituting $x = 1/2$, the sum becomes:
>
> $$\frac{1/2}{(1-1/2)^2} = \frac{1/2}{1/4} = 2 \text{}$$
>
> Since the summation part is just a constant (2), the entire expression simplifies to:
>
> $$T(n) = O(n \cdot 2) = O(n)$$
> 
> Thus, `BUILD_MAX_HEAP` takes **linear time**.

> [!NOTE]
> **Correctness of `BUILD_MAX_HEAP`**
> 
> **Loop invariant**: At the start of each iteration of the `for` loop, every node `i+1`, `i+2`..., `n` is the root of a valid max-heap.
> - **Initialization**: Before the first iteration, `i=floor(n/2) - 1`. The node indexed from `floor(n/2)` till `n-1` are leaves of the tree. Since leaves have no children, they are roots of valid max-heap.
> - **Maintenance**: Suppose the invariant holds for `i`. All children of `i` are indexed higher than `i`, so by the invariant, they are roots of max-heap. Calling `MAX_HEAPIFY` on `i` will also make `i` root of a max-heap. Decrementing `i` reestablishes the loop invariant at each iteration.
> - **Termination**: When `i = -1`, the loop ends. By the invariant, all nodes, notably node `0` are max-heap roots. Therefore, the entire array satisfies max-heap property.

## Heapsort Algorithm:
```cpp
HEAPSORT(a, n)
1.    BUILD_MAX_HEAP(a, n)
2.    for i = n-1 downto 1
3.        swap(a[i], a[0])
4.        MAX_HEAPIFY(a, 0, i)
```

> [!IMPORTANT]
> Line 1: `BUILD_MAX_HEAP` $\Rightarrow O(n)$.
> 
> Line 2-4: `for` loop runs $n-1$ times.
> 
> Line 3: swap $\Rightarrow O(1)$.
> 
> Line 4: `MAX_HEAPIFY` $\Rightarrow O(\log n)$.
>
> 
> Therefore, running time of Heapsort is $O(n\log n)$

> [!IMPORTANT]
> Space complexity: $O(n)$ due to call stack.

> [!NOTE]
> Heapsort is **unstable**.

## Other problems

Usually, we can use heap in problems where in each step (iteration) in its solution, we only care about the largest/ smallest element.

1. We can keep $k$**-th largest / smallest** elements in an array using heap of size $k$ without sorting the whole array.

2. We can sort an array where elements are just $k$ positions away from their correct position using a heap with size $k+1$.

2. We can **convert BST into a special max-heap** (left subtree < right subtree < root) by using **inorder** traversal to store the elements in sorted order, then copying them into nodes while doing **postorder** traversal (left->right->root).

3. 