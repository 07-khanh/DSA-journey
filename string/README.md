<center>
<h1>String matching algorithms</h1>
</center>

> [!IMPORTANT] Problem
Given two strings - a **pattern** `P` and a **text** `T`, determine if the pattern appears in the text, and if it does, enumerate all its occurrences in $O(|P| + |T|)$ time.

## Naive algorithm

The pattern moves over the text one position at a time, and characters are compared from left to right. If all characters match, the index is stored, else the next position is checked.

**Input**:
- Two strings `pattern`, `text`.
- `P` is length of `pattern`, `T` is length of `text`.
- `result` records all occurrences of `pattern` in `text`.
```cpp
SEARCH(pattern, text, P, T, result)
    for i = 0 upto T - P
        set j = 0
        for j = 0 to P
            if pattern[j] != text[i + j]
                break
            if j == P
                append i to result
```

> [!NOTE]
> **Time complexity**: $O(T \cdot P)$ :scream:
$\Rightarrow$ can be improved!

## Rabin-Karp Algorithm

### String hashing:

> [!IMPORTANT] Rolling Hash
A common hash function is **rolling hash**.
We define the rolling hash function of a string `s` of length `n`:
$$\begin{align*} \text{hash}(s) &= s[0]\cdot p^{n-1} + s[1]\cdot p^{n-2} + \cdots + s[n-1]\cdot p^0 \quad &\text{mod}\ m \\
&= \sum_{i=0}^{n-1}s[i]\cdot p^{n-1-i} \quad &\text{mod}\ m \\
\end{align*}$$

Here:
- $s[i]$: ASCII values of characters.
- $p$: size of input alphabet (commonly $256$ for ASCII characters).
- $m$: a prime number used as modulus (commonly $101, 1e9+7,\ldots$) 
Using modulo helps prevent integer overflow and reduces hash collisions.

> [!IMPORTANT] Compute next rolling hash
If we know hash value of $s[i-1..j-1]$, the hash value of $s[i..j]$ is as followed:
$$\text{hash}(i, j) = p \cdot (\ \text{hash}(i-1,j-1) -p^{n-1}\cdot s[i-1]\ ) + s[j]\quad \text{mod}\ m$$
However, $\text{hash}(i-1,j-1) -p^{n-1}\cdot s[i-1]$ can be negative. 
Therefore, we have a safer version:
$$\text{hash}(i, j) = p \cdot (\ \text{hash}(i-1,j-1) + m -p^{n-1}\cdot s[i-1] \text{ mod}\ m\ ) + s[j]\quad \text{mod}\ m$$

### Rabin-Karp Implementation:

Compare every pattern with all subtrings using **rolling hash**.
- Compute the hash of pattern.
- Compare pattern's hash with hash value of all substrings (of same length as pattern). If the hash values match, do character-by-character check to confirm (in case of hash collision).

```cpp
RABIN_KARP(text, pattern, occurrences)
1   set p = 256
2   set m = 1e9+7
3
4   set T = length of text
5   set P = length of pattern
6
7   if P > T 
8       return empty list
9   
10  set p_pow = 1
11  // Precompute the largest power p^{P-1}
12  for i = 1 to P
13      p_pow = (p_pow * p) % m
14
15  set h_p = 1
16  set cur_h = 1
17
18  // Compute hash value of pattern, and first window in text.
19  for i = 0 to P
20      h_p = ((h_p * p) % m + pattern[i]) % m  // Hash(pattern)
21      cur_h = ((cur_h * p) % m + text[i]) % m // Hash(text[0..P-1])
22  
23  for i = 0 upto T - P
24      // Hash values match
25      if cur_h == h_p
26          match = true
27
28          // Compare character-by-character
29          for j = 0 to P
30              if text[i+j] != pattern[j]
31                  match = false
32          
33          if match
34              append i to occurrences
35
36      // Compute hash value of next window
37      if i < T - P
38          cur_h = ( p * (cur_h + m - text[i] * p_pow % m) + text[i + P] ) % m

```

> [!IMPORTANT] Time complexity
Line `12-13`, `19-21`: Precomputing `p_pow` and computing hash value of pattern and first window in text each takes $O(P)$.
Line `23-38`:  
> - Best / Average Case: do $T-P$ shifts and each shift takes $O(1)$ on average (_rare spurious hits thanks to good hash function and large $m$_), summing up to $O(T-P)$ time or $O(T)$ if $P = O(T)$.
> - Worst Case: If the hash function is poorly designed, or the text and pattern are highly repetitive, we have to perform char-by-char check for every shift, taking $O(P)$ time.
> 
> Overall:
> - Best / Average Case: $O(T + P)$.
> - Worst Case: $O(T\cdot P)$.

## Knuth-Morris-Pratt Algorithm (KMP)

```cpp
PREFIX_FUNCTION(pattern, P)
    create array pi[0..P-1]
    pi[0] = 0

    for i = 1 to P
        set j = pi[i - 1]
        while j > 0 and pattern[i] != pattern[j]
            j = pi[j-1]

        if pattern[i] == pattern[j]
            ++j

        pi[i] = j
    
    return pi


KMP(pattern, text, P, T, occurrences)
    create pi = PREFIX_FUNCTION(pattern, P)

    set i = 0
    set j = 0

    while i < T
        // If characters match, move both pointers
        if text[i] == pattern[j]
            ++i
            ++j

            // If have found the pattern
            //  store the index and move pattern pointer to index = last LPS
            if j == P
                append (i - P) to occurrences
                j = pi[j - 1]

        // If there is a mismatch
        else
            // If there is still match in prior j characters, 
            // find smaller suffix by moving pattern pointer to index = last LPS
            if j != 0
                j = pi[j - 1]
            else
                // If the prior characters also don't match, 
                // text[i] cannot be part of pattern, so move text pointer to the next position.
                ++i
```

> [!IMPORTANT] Time analysis
> `PREFIX_FUNCTION` takes $O(P)$ time.
> - We track # loops by looking at the # of `j` updates.
>   - `j` increases together with `i`. 
>      Therefore,  # `j` increases $=$ # `i` increases $= P$.
>   - `j` can never be $< 0$. Supposed `j` decreases $k$ times, then `j` should have increased at least $k$ times (so that `j` $\ge 0$). But # `j` increases is bounded by $P$. Therefore, # `j` decreases is also $\le P$.
> 
> Summing up, running time $= \#\ increases + \#\ decreases \le 2P = O(P)$.
>
> `KMP` takes $O(T)$ time.
> - The same explanation can be applied, when we track the # `j` updates. `j` and `i` increases at most `T` times, and `j` decreases at most the # times it increases over the entire function. Thus, running time is $\le T + T = O(T)$.
>
> Overall, KMP algorithm takes $O(T + P)$ time.

