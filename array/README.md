# ARRAY RELATED ALGORITHMS

## Boyer-Moore Voting Algorithm
> [!IMPORTANT]
> **Problem**: Given a list of $n$ elements, finds the **majority element** (element that appears more than $n/2$ times in the list) in $O(n)$ time and $O(1)$ space.

**Algorithm**:
The algorithm is based on the idea that there is only one majority element in the list, and every other elements appear less than $n/2$ times.

The algorithm use two traversals.

- First traversal: we maintain a `candidate` and  `count`.

    - If the current element matches `candidate`, increment `count`.
    - If the current element is different from `candidate`, decrement `count`. This helps gradually cancelling out non-majority elements.
    - If `count` = 0, then `candidate` cannot be the majority element (because its frequency got cancelled out). Therefore, we choose another `candidate` and reset `count` to $1$.

    By the end of the traversal, the remaining `candidate` is the possible majority candidate. We traverse the list a second time to ensure its frequency is $ > n/2$.

- Second traversal: iterate over the list again and count the frequency of `candidate`. If frequency $> n/2$ then `cadidate` is the majority element, otherwise there doesn't exist a majority element in the list.

```cpp
MAJORITY(a, n)
    set count = 0
    set candidate = -1e9

    for i = 0 to n
        if count == 0
            candidate = a[i]
            count = 1
        else
            if a[i] == candidate
                count = count + 1
            else 
                count = count - 1

    set checkCount = 0
    for i = 0 to n
        if a[i] == candidate
            checkCount = checkCount + 1
    
    if checkCount > n/2
        return candidate
    return -1
```