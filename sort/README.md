<h1>Sorting Algorithms</h1>

## Basics:
- **In-place**: use constant space, only modify the input array.
  
    (Selection Sort, Bubble Sort, Insertion Sort and Heap Sort).
- **Stable**: **same** items have the same order in sorted array as in orignal array.
  
    (Merge Sort, Insertion Sort, Bubble Sort).

## Comparison-based:

### Bubble sort: 

<a href="/sort/bubbleSort.cpp">BubbleSort</a>

Repeatedly **swap two adjancent items** if they are not in correct order.
- After the first pass, the largest item goes to the last position (its correct position in sorted array). 
- After $n-1$ passes, $n-1$ largest items are at their correct position. Thus, the remaining item is the smallest and stands at the front. This way, the entire the array is sorted.
  
```cpp
BUBBLE_SORT(int a, int n) 
1.    for i = 0 to n - 1
2.        for j = 0 to n - i - 1
3.            if a[j] > a[j+1]
4.                swap a[j] and a[j + 1]
```

> [!IMPORTANT] 
> - Time complexity:
>   - Normal version: $\Theta(n^2)$ for all cases.
>    - Optimized version: $\Theta(n)$ for best cases.
> - Space complexity: $\Theta(1)$.
>   
> Bubble sort is **stable**.

> [!NOTE]
> **Prove time complexity**
> 
> TC depends on the # of times the `for` loop in lines `2-4` runs, denoted by $C(n)$.
> 
> $$C(n) = (n-1) + (n-2) + \cdots + 1$$
> 
> This is an arithmetic series:
> 
> $$C(n) = \sum_{i=1}^{n-1}i = \dfrac{n(n-1)}{2} = \dfrac{n^2}{2} - \dfrac{n}{2}$$
> 
> Thus, the running time for bubble sort is $\Theta(n^2)$ for all cases.

> [!NOTE]
> **The correctness of Bubble Sort**
> 
> **1. The Inner Loop Invariant**: At the start of each iteration of the inner loop (indexed by `j`), `a[j]` is the largest element in the subarray `a[0...j]`.
> - **Initialization**: When `j=0`, `a[0..j]=a[0..0]` contains one element, which is the largest in its subarray.
> - **Maintanence**: In each step, we compare `a[j]` and `a[j+1]`. If `a[j] > a[j+1]`, we swap them. This ensures that after the comparison, the larger of the two is now at position `j+1`. As `j` increments, this "maximum" continues to move right.
> - **Termination**: The loop terminates when `j=n-i-1`. By the invariant, `a[n-i-1]` is now the largest in subarray `arr[0..n-i-1]`. Effectively, the `(i+1)`-th largest element has "bubbled up" to its correct sorted position.  
>
> **2. The Outer Loop Invariant**: At the start of each iteration of the outer loop (indexed by `i`), the subarray `a[n-i...n-1]` consists of the $i$ largest elements of the original array in their final sorted positions.
> - **Initialization**: Before the first iteration (`i = 0`), the subarray `a[n...n-1]` is empty. An empty subarray holds the property vacuously.  
> - **Maintenance**: During iteration `i`, the inner loop (proven above) finds the largest element in the unsorted part `a[0...n-i-1]` and places it at index `n-i-1`. Since `arr[n-i...n-1]` already contained the $i$ largest elements in order, the array now has the $i+1$ largest elements sorted at the end.
> - **Termination**:
>   - **Normal Case**: The loop terminates when `i = n - 1`. This means the $n-1$ largest elements are in their correct positions. By default, the remaining element at index `0` must also be in the correct position.  
>    - **Optimized Case**: If the swapped flag remains false after a pass, the loop breaks early (because it means every element is in its correct position and doens't need swapping).

### Selection Sort:
<a href="/sort/selectionSort.cpp">SelectionSort</a>

Repeatedly find the **smallest** (or largest) element from the unsorted part of the array, and swap it with the first unsorted element. This process continues until the full array is sorted.

```cpp
SELECTION_SORT(a, n)
1.    for i = 0 to n-1
2.        smallest = i
3.        for j = i + 1 to n
4.            if a[j] < a[smallest]
5.                smallest = j
6.        swap a[i] and a[smallest]
```

> [!IMPORTANT]
> - Time complexity: $\Theta(n^2)$ for all cases.
> - Space complexity: $\Theta(1)$.
>   
> Selection Sort is **unstable**.

> [!NOTE]
> **Prove Time Complexity**
> 
> _(Can be proved like Bubble Sort, here is just another way to infer the formula)_.
> 
> TC depends mostly on the # of times the comparisons in `4-5` are carried out, denoted by $C(n)$.
>
> ```math
> \begin{align*}
> C(n) &= \sum_{i=0}^{n-2}(n-i-1) \\
> &= (n-1)n - \dfrac{(n-2)(n-1)}{2} - (n-1) \\
> &= \dfrac{(n-1)n}{2} \\
> \end{align*} 
>```
> 
> Thus TC for **Selection Sort** is $\Theta(n^2)$.

> [!NOTE]
> **Correctness of Selection Sort**
> 
> **Loop invariant**: At the start of each iteration $i$ of the outer for loop, the subarray `a[0 .. i-1]` consists of the $i$ smallest elements of the original array, in sorted order.
> - **Initialization**: When `i=0`, `a[0..-1]` is empty, and contains $0$ smallest element. The ivariant holds.
> - **Maintenance**: After `i-1` iterations, `a[0..i-1]` consists of `i` smallest elements. At the start of `i`-th iteration, the algorithm finds the smallest element in `a[i...n-1]`, and replace `a[i]` with that element. Thus, `a[0...i]` consists of $i+1$ smallest sorted elements in the original array. When the loop increments $i$ for the next round, the invariant is maintained.
> - **Termination:** The loop terminates when `i=n-1`. According to the invariant, the subarray `a[0...n-2]` consists of $n-1$ smallest elements of the original array, in sorted order. The remaining element at position `n-1` is automatically the largest element in the array. Therefore, the entire array is sorted.

### Insertion Sort:
<a href="/sort/insertionSort.cpp">InsertionSort</a>

The array is divided into sorted and unsorted part.

Insertion Sort iteratively inserts the each element in the unsorted part into its correct position in the sorted part.

```cpp
INSERTION_SORT(a, n)
1.    for i = 1 to n
2.        key = a[i]
3.        j = i - 1
4.        // Insert key in a[0...i-1]
5.        while j >= 0 and a[j] > key
6.            a[j+1] = a[j]
7.            j = j - 1
8.        a[j+1] = key
```

> [!IMPORTANT] 
> - Time complexity:
>   - Best case (array is already sorted): $\Theta(n)$.
>   - Worst case (array is in reverse order): $\Theta(n^2)$.
>   - Average case: $\Theta(n^2)$.
> - Space complexity: $\Theta(1)$.
>   
> Insertion Sort is **stable**.

> [!NOTE]
> **Prove time complexity**
> 
> **Best case**: The array is sorted.
> 
> The outer loop's body runs $n-1$ times.
>
> The inner loop condition is checked **once** per outer iteration and never executes its body.
> 
> Thus the running time in the best case is $\Theta(n)$.
> 
> **Worst case**: The array is in reverse order.
> 
> Always find that `a[j] > key` in the while loop test.
> Have to compare `a[i]` with all elements in `a[0...i-1]` $\Rightarrow$ compare with $i$ elements, and one additional check to exit the loop $\Rightarrow t_i = i+1$ .
> 
> $$T(n) = \sum_{i=1}^{n-1}(i+1) = \sum_{i=2}^{n}i = \dfrac{n(n+1)}{2}-1 = \Theta(n^2)$$
> 
> **Average case**:
> 
> On average, the while loop has to look half way through the subarray to the left of `i` $\Rightarrow t_i = i/2$, and we still end up with a quadratic function $\Theta(n^2)$.

> [!NOTE]
> **The correctness of Insertion Sort**
> 
> **Loop invariant**: At the start of each iteration in lines `1-8`, the subarray `a[0...i-1]` contains $i$ elements originally in `a[0...i-1]` but in sorted order.
> - **Initialization**: When `i=1`, `a[0...0]` contains only one element `a[0]`, which is the original element in `a[0]`, and this subarray is sorted. Thus, the invariant holds.
> - **Maintenance**: Suppose the invariant is true prior to each iteration. Then, `a[0...i-1]` is sorted at the start of interation `i`. 
>     - The inner loop repeatedly move `a[i-1], a[i-2]...` by one position to the right until it finds a proper position for `a[i]`. The subarray `a[0...i]` then contains the original elements in `a[0...i]` but in sorted order.
>     - When the loop increments $i$ for the next round, the invariant is maintained.  
> - **Termination**: The loop terminates when `i=n`. Then, the subarray `a[0...n-1]` contains $n$ elements originally in `a[0...n-1]` but in sorted order. Thus, the entire array is sorted.

### Heap Sort:
<a href="/sort/heapSort.cpp">HeapSort</a>

#### Heap Data Structure:
- Heap DS is a nearly complete **binary tree**.
- A heap can be stored in an array (complete BT property):
    - Root of tree: $a[0]$.
    - Left child of $a[i]$: $a[2i+1]$.
    - Right child of $a[i]$: $a[2i+2]$.
    - Parent of $a[i]$: $a[\ \lfloor (i-1)/2 \rfloor\ ]$.

#### Heap Property:
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

#### Heap Operations:

##### Max-Heapify:
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

##### Build a heap:

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

#### Heapsort Algorithm:
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

### Merge Sort:
<a href="/sort/mergeSort.cpp">MergeSort</a>

Merge Sort follows **Divides and Conquer** approach. It recursively divides the array into two halves, recursively sorts each half, then merges them back together to obtain sorted array.

To sort `a[low...high]`:
- **Divide** by splitting into two subarrays `a[low...mid]` and `a[mid+1...high]` where `mid` is a halfway point of `a[low...high]`
- **Conquer** by recursively sorting the two subarrays `a[low...mid]` and `a[mid+1...high]`
- **Combine** by merging `a[low...mid]` and `a[mid+1...high]` to produce a single sorted array `a[low...high]`.

```cpp
MERGE(a, low, mid, high)
    n_l = mid - low + 1
    n_r = high - mid

    create arrays L[0...n_l-1] and R[0...n_r-1]

    // copy elements to L and R
    for i = 0 to n_l
        L[i] = a[low + i]
    for i = 0 to n_r
        R[i] = a[mid + 1 + i]
    
    set k = low
    set i, j = 0

    // Merge L and R into a
    while i < n_l and j < n_r
        if L[i] <= R[j]
            a[k++] = L[i++]
        else
            a[k++] = R[j++]
    
    // Copy the remaining elements of L, if there are any
    while i < n_l 
        a[k++] = L[i++]
    
    // Copy the remaining elements of R, if there are any
    while j < n_r
        a[k++] = R[j++]
```
```cpp
MERGE_SORT(a, low, high)
    if low >= high 
        return

    set mid = floor( (low + high)/2 )

    // Recursively sort two halves
    MERGE_SORT(a, low, mid)
    MERGE_SORT(a, mid + 1, high)

    // Merge two sorted halves
    MERGE(a, low, mid, high)
``` 

> [!IMPORTANT] 
> - Time complexity: $\Theta(n\log n)$ _for all cases_.
> - Auxiliary space: $O(n)$ _used to create temporary subarrays during merging_.
>   
> Merge Sort is **stable**.


> [!NOTE]
> **Prove time complexity**
> - **Divide**: only compute `mid` $\Rightarrow D(n) = \Theta(1)$.
> - **Conquer**: recursively solve $2$ subproblems, each of size $n/2$ $\Rightarrow 2T(n/2)$
> - **Combine**: `MERGE` on an $n$-element subarray takes $\Theta(n)$ time $\Rightarrow C(n) = \Theta(n)$
>   
> $D(n)$ and $C(n)$ summed together give a linear function $\Theta(n)$.
> 
> We have **recurrence** for Merge Sort:
>
> ```math
> T(n) = \begin{cases} \Theta(1) &\text{if } n = 1 \\ 2T(n/2) + \Theta(n) &\text{if } n > 1 \end{cases}
> ```
> 
> **By master theorem**, the solution is $T(n) = \Theta(n\log n)$.
> 
> **By substitution method**: Let $c_1$ be a constant describing the running time in base case, and $c_2$ be a constant describing the time per array element for the divide and conquer steps.
> 
> We rewrite the recurrence as:
>
> ```math
> T(n) = \begin{cases} c_1 &\text{if } n = 1 \\ 2T(n/2) + c_2n &\text{if } n > 1 \end{cases}
> ```
> 
> Solve using substitution: 
>
> ```math
> \begin{align*} T(n) &= 2T(n/2) + c_2n \\ 
> &= 2(\ 2T(n/4)+c_2(n/2)\ ) + c_2n \\
> &= 4T(n/4) + 2c_2n \\
> &=...\\
> &= 2^kT(n/2^k) + kc_2n \end{align*}.
> ```
> 
> $T(n/2^k)$ hits base case when $n/2^k = 1 \Rightarrow n = 2^k \Rightarrow k = \log_2n$.
> 
> Then $T(n) = c_1\cdot n + c_2\cdot n\log_2n = \Theta(n\log n)$.
> 
> **By drawing recursion tree**:
> 
> <img src="/sort/images/image-1.png" width=70%>

### Quicksort:
<a href="/sort/quickSort.cpp">QuickSort</a>

Quicksort is a sorting algorithm based on **Divide and Conquer** that picks an element as pivot and partitions the array into two subarrays around the pivot by placing the pivot in its correct position in the sorted array.

To sort `a[low...high]`
- **Divide**: Partition `a[low..high]` into two (possibly empty) subarrays `a[low..pi−1]` and `a[pi+1..high]`, such that each element in the first subarray `a[low... pi−1]` is $\le$ `a[pi]` and `a[pi]` is $\le$ each element in the second subarray `a[pi+1 ..high]`.
- **Conquer**: Sort the two subarrays recursively using `QUICKSORT`
- **Combine**: No work is needed to combine the subarrays, because they are sorted **in place**.

```cpp
PARTITION(a, low, high)
    set pivot = a[high]         // Choose pivot to be the rightmost element

    set i = low - 1             // Highest index into the low side

    for j = low to high         // Process each element other than the pivot
        if a[j] <= pivot        // Does this element belong to the low side
            i++                 // index of a new slot in the low side
            swap a[i] and a[j]  // put this element there
    
    swap a[i + 1] and a[high]   // pivot goes just to the right of the low side
    return i + 1                // new index of the pivot
```
```cpp
QUICK_SORT(a, low, high)
    if low >= high 
        return
    
    // Partition the subarray around the pivot, which ends up in a[pi].
    set pi = PARTITION(a, low, high)
    QUICKSORT(a, low, pi - 1)    // recursively sort the low side
    QUICKSORT(a, pi + 1, high)   // recursively sort the high side
``` 

> [!IMPORTANT]
> Time complexity:
>    - Worst case: $\Theta(n^2)$.
>    - Best/ average case: $\Theta(n\log n)$
>      
> Auxiliary Space:
>    - Worst case: $O(n)$ _unbalanced partitioning leading to skewed recursion tree_.
>    - Best/Average case: $O(\log n)$.
>
> Quicksort is **unstable**.

> [!NOTE]
> **Prove time complexity**
> 
> The running time of quicksort depends on the partitioning of the subarrays.
> - If the subarrays are balanced, quicksort is as fast as mergesort.
> - If they are unbalanced, quicksort is as slow as insertion sort.
> 
> **Worst case**:
> 
> Occur when the subarrays are completely unbalanced, one is empty and the other has $n-1$ elements.
> ```math
> \begin{align*} T(n) &= T(0) + T(n-1) + \Theta(n)\\
> &= T(n-1) + \Theta(n) \\
> &= \Theta(n^2)
> \end{align*}
> ```
> 
> **Balanced partitioning**:
> If the partitioning ratio is constant, the running time will always be $O(n\log n)$.
> 
> Supposed the ratio is $9 : 1$, we get the recurrence:
> ```math
> \begin{align*}
> T(n) &\le T(9n/10) + T(n/10) + \Theta(n) \\
> &= O(n\log n)\\ 
> \end{align*}
> ```
> 
> We can feel this looking at the recursion tree.
> 
> <img src="/sort/images/image-2.png" width=70%>
>
> As long as the split ratio is constant, the height of the recursion tree is always $O(\log n)$.
> 
> **Average case**:
> 
> <img src="/sort/images/image-3.png" width=70%>
>
> - Splits are not always constant.
> - There are usually a mix of good and bad splits.
> 
> **Intuition**: When there are alternating good and bad splits, the cost of bad splits can be absorbed into the cost of good splits, and only affect the constant hidden by $O$-notation.
>
> The average case analysis considers all possible proportions of the two subarrays, sums up the cost in each case, and divides by the # of cases.
> 
> We make a reasonable simplifying assumption that after each partition step, the pivot is equally likely to split the array into subarrays of size $0$ and $n-1$, $1$ and $n-2$, and so on. In other words, the pivot is equally likely to end in any position (in the sorted array). And since we have $n$ positions, the average cost of each recursion can be modeled as:
>
> ```math
> \dfrac{1}{n}  \sum_{k=0}^{n-1} \left[T(k) + T(n-1-k)\right]
> ```
> 
> And we also have to add the cost of partitioning and finding pivot, which is $\Theta(n)$.
> 
> Thus, we have the recurrence:
>
> ```math
> \begin{align*}T(n) &= \dfrac{1}{n}  \sum_{k=0}^{n-1} \left[T(k) + T(n-1-k)\right] + cn \\
> &= \dfrac{2}{n} \sum_{k=0}^{n-1}T(k) + cn \\
> \end{align*}
> ```
> 
> Multiply both sides by $n$:
> 
> $$nT(n) = 2 \sum_{k=0}^{n-1}T(k) + cn^2\quad (1)$$
> 
> Write the equation for $n-1$:
> 
> $$(n-1)T(n-1) = 2 \sum_{k=0}^{n-2}T(k) + c(n-1)^2\quad (2)$$
> 
> Take $(1)-(2)$:
> 
> $$nT(n) - (n-1)T(n-1) = 2T(n-1) + c(2n - 1)$$
> 
> $$\Rightarrow T(n) = (n+1)T(n-1) + c(2n - 1) = \Theta(n \log n)$$
> 
> <a href="https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-quick-sort/">More Detail</a>

> [!NOTE]
> **Correctness of Quicksort**
> 
> 1. `PARTITION` function:
> 
> **Loop invariant**:
> - All entries in `a[low..i]` are $\le$ `pivot`.
> - All entries in `a[i+1 .. j−1]` are $>$ `pivot`.
> - `a[high]=pivot`.  
>
> **Initialization**: Before the loop starts, `i = low-1` and `j = low`. The sets of elements $\le$ `pivot` and $>$ `pivot` are empty. The invariant is trivially true.
> 
> **Maintenance**:
>    - If `a[j]` $>$ `pivot`, we just increment `j`. The second condition of the invariant remains true for the new `a[j-1]`.
>   - If `a[j]` $\le$ `pivot`, we increment `i`, swap `a[i]` and `a[j]`, then increment `j`. Now `a[i]` is $\le$ pivot, and the invariant is maintained.
>
> **Termination**: The loop finishes when `j = high`. At this point, every element in the array (except the pivot at `a[high]`) has been sorted into one of the two partitions. We perform one final swap between `a[i+1]` and `a[high]` to put the pivot in its correct position.
>
> Now we prove the recursive algorithm using **Induction** on the number of elements $n$.
> 
> **Claim**: `QUICKSORT(A, low, high)` correctly sorts the subarray `a[low..high]`.
> 
> **Base Case** ($n \le 1$): If `low` $\ge$ `high`, the subarray has at most one element. A single element is already sorted by definition. The algorithm returns immediately.
> 
> **Inductive Step**: Assume `QUICKSORT` correctly sorts subarrays of any size $k < n$.
> 
> - **Partition**: The `PARTITION` procedure returns an index `pi`. As proven above, `a[pi]` is now in its final sorted position, with smaller elements to the left and larger to the right.
> - **Subproblems**: The algorithm calls `QUICKSORT(a, low, pi-1)` and `QUICKSORT(a, pi+1, high)`.
> - Since the pivot is at index `pi`, both sub-arrays must have sizes smaller than $n$. By our inductive hypothesis, these two recursive calls will correctly sort the left and right segments.
>   
> **Conclusion**: Since the left side is sorted, the pivot is in the correct middle spot, and the right side is sorted, the entire subarray `a[low..high]` is now sorted.

> [!NOTE]
> **Optimizing Quicksort**
> 
> We can avoid the worst case of Quicksort by choosing good pivots, mostly using Randomized algorithms to find a random pivot in each recursion.

## Non-comparison-based

### Lower bounds for sorting

A comparison sort only use comparisons to gain information about the relative order of elements in the input sequence.

We will prove that the lower bound of comparison sorts is $\Omega(n \log n)$ using **decision tree** model.
#### Decision Tree
Decision tree is a **full binary tree**, which represents the comparisons made by a specific sorting algorithm on input with a given size. 

We will abstract everything else: control, data movement and only **count comparisons**.

For insertion sort on 3 elements:

<img src="/sort/images/image-4.png" width=70%>

The decision tree will have $\ge n!$ leaves.
For any comparison sort:
- 1 tree for each $n$.
- View the tree as if the algorithm splits it into 2 at each node, based on the information it determined at that point.
- The tree models all possible execution trace.
- The worst-case number of comparisons for a given comparison sort algorithm equals the height of its decision tree. 

We can prove that: 
> [!IMPORTANT]
Any decision tree that sort $n$ elements has height $\Omega(n \log n)$

> [!NOTE]
> **Proof**
> 
> Let $l$ be # of leaves, then:
> 
> $$l \le 2^h$$
> 
> But
>
> $$l \ge n!$$
> 
> $$\Rightarrow n! \le l \le 2^h$$
> 
> or
>
> $$2^h \ge n!$$
> 
> Take $\log$
> 
> $$h \ge \log_2(n!)$$
> 
> According to Stirling's approximation: $n! > (n/e)^n$, so:
> 
> $$h \ge log_2[(n/e)^n] = n(\log_2n - log_2e) = \Omega(n\log n)$$

### Counting Sort

<a href="/sort/countingSort.cpp">CountingSort</a>

Depends on a key assumption: numbers to be sorted are integers in $\{0,1,... ,k\}$.

**Input**: `a[0.. n-1]`, where `a[j]` $\in \{0,1,... ,k\}$ for $j= 0,1,2,... ,n-1$. Array `a` and values `n` and `k` are given as parameters.

**Output**: `b[0.. n-1]`, sorted. `b` is assumed to be already allocated and is given as a parameter.

**Auxiliary storage**: `c[0.. k]`.

Counting sort works by counting the frequency of unique elements in `a`. The count is stored in an auxiliary array `c`. We compute the prefix sum of each element in `c`, and use that to map each `a[i]` element to its correct position in the sorted array `b`.

```cpp
COUNTING_SORT(a, b, n, k)
    Create array c[0..k]

    for i = 0 upto k
        c[i] = 0

    for i = 0 to n
        c[a[i]]++
    // c[i] now contains the number of elements equal to i

    for i = 1 upto k
        c[i] = c[i] + c[i - 1]
    // c[i] now contains the number of elements less than or equal to i .

    // Copy a to b, starting from the end of a.
    for i = n-1 downto 0
        b[c[a[i]] - 1] = a[i]   // Subtract 1 for 0-based index
        c[a[i]]--
```

> [!IMPORTANT]
> **Time complexity**: $\Theta(n+k)$, which is $\Theta(n)$ if $k=O(n)$.
> 
> **Auxiliary Space**: $\Theta(n + k)$, which is space taken by `b` and `c`.
> 
> Counting Sort is **stable**.
>
> _Counting Sort will be used in Radix Sort_.

### Radix Sort

<a href="/sort/radixSort.cpp">RadixSort</a>

Radix Sort processes numbers digit by digit, **from least to most significant digits**. On each level of digits with the same significance, perform a **stable** sorting algorithm (usually Counting Sort) to sort digits. Repeat this process  while preserving the order from the prior steps. 

<img src="/sort/images/image-5.png" width=70%>

```cpp
RADIX_SORT(a, d)
    for i = 1 upto d
        use a stable sort to sort array a[0..n] on digit i
```

> [!NOTE]
> **The correctness of Radix Sort**
> 
> Use **induction** on # of passes, which is `i`.
> 
> Assuming that digits $1, 2,...,i-1$ are sorted.
> 
> We prove that stable sort on digit `i` leaves digits $1, 2,..,$`i` sorted:
> - If $2$ digits in position `i` are different, then the ordering by position `i` is correct, and positions $1, 2,...,i-1$ are irrelevant.
> - If $2$ digits in position `i` are the same, then numbers are already in correct order (by inductive hypothesis). The stable sort on digit `i` leaves them in the right order.
>
> This is why using a **stable** sort algorithm is so important

> [!IMPORTANT]
> **Time complexity**: $\Theta(d(n+k))$ and $\Theta(dn)$ if $k=O(n)$.
> 
> **Auxiliary Space**: $O(n+k)$
> 
> Radix Sort is **stable**.

## Summary

| Algorithm | Worst Case | Best Case | Average Case | Memory | Stable |
| :---: | :---: | :---: | :---: | :---: | :---: |
| <a href="#bubble-sort">Bubble Sort</a></td> | $\Theta(n^2)$ | $\Theta(n)$  _(Optimized)_| $\Theta(n^2)$ | $\Theta(1)$ | :white_check_mark:|
| <a href="#selection-sort">Selection Sort</a> | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(1)$ | :x:|
| <a href="#insertion-sort">Insertion Sort</a> | $\Theta(n^2)$ | $\Theta(n)$ | $\Theta(n^2)$ | $\Theta(1)$ | :white_check_mark: |
| <a href="#merge-sort">Merge Sort</a> | $\Theta(n\log n)$ | $\Theta(n\log n)$ | $\Theta(n\log n)$ | $\Theta(n)$ | :white_check_mark: |
| <a href="#heap-sort">Heap Sort</a> | $\Theta(n\log n)$ | $\Theta(n\log n)$ | $\Theta(n\log n)$ | $\Theta(n)$ | :x: |
| <a href="#quicksort">Quick Sort</a> | $\Theta(n^2)$ | $\Theta(n\log n)$ | $\Theta(n\log n)$ | $\Theta(\log n)$ | :x: |
| <a href="#counting-sort">Counting Sort</a> | $\Theta(k + n)$ | $\Theta(n)$ | $\Theta(n + k)$ | $\Theta(n + k)$ | :white_check_mark: |
| <a href="#radix-sort">Radix Sort</a> | $\Theta(d(k + n))$ | $\Theta(dn)$ | $\Theta(d(n + k))$ | $\Theta(n + k)$ | :white_check_mark: |



