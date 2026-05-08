# String matching algorithms

> [!IMPORTANT]
> **Problem:**
> Given two strings - a **pattern** `P` and a **text** `T`, determine if the pattern appears in the text, and if it does, enumerate all its occurrences in $O(|P| + |T|)$ time.

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
> $\Rightarrow$ can be improved!

## Rabin-Karp Algorithm

### String hashing:

> [!IMPORTANT]
> A common hash function is **Rolling Hash**.
> We define the rolling hash function of a string `s` of length `n`:
> ```math
> \begin{align*} \text{hash}(s) &= s[0]\cdot p^{n-1} + s[1]\cdot p^{n-2} + \cdots + s[n-1]\cdot p^0 \quad &\text{mod}\ m \\
> &= \sum_{i=0}^{n-1}s[i]\cdot p^{n-1-i} \quad &\text{mod}\ m \\
> \end{align*}
> ```

Here:
- $s[i]$: ASCII values of characters.
- $p$: size of input alphabet (commonly $256$ for ASCII characters).
- $m$: a prime number used as modulus (commonly $101, 1e9+7,\ldots$) 
Using modulo helps prevent integer overflow and reduces hash collisions.

> [!IMPORTANT]
> **Compute next rolling hash**:
> 
> If we know hash value of $s[i-1..j-1]$, the hash value of $s[i..j]$ is as followed:
> ```math
> \text{hash}(i, j) = p \cdot (\ \text{hash}(i-1,j-1) -p^{n-1}\cdot s[i-1]\ ) + s[j]\quad \text{mod}\ m
> ```
> However, $\text{hash}(i-1,j-1) -p^{n-1}\cdot s[i-1]$ can be negative. 
> Therefore, we have a safer version:
> ```math
> \text{hash}(i, j) = p \cdot (\ \text{hash}(i-1,j-1) + m -p^{n-1}\cdot s[i-1] \text{ mod}\ m\ ) + s[j]\quad \text{mod}\ m
> ```

### Rabin-Karp Implementation:

Compare pattern with all subtrings using **rolling hash**.
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
15  set h_p = 0
16  set cur_h = 0
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

> [!IMPORTANT]
>  **Time complexity**:
> 
> Line `12-13`, `19-21`: Precomputing `p_pow` and computing hash value of pattern and first window in text each takes $O(P)$.
> 
> Line `23-38`:  
> - Best / Average Case: do $T-P$ shifts and each shift takes $O(1)$ on average (rare spurious hits thanks to good hash function and large $m$), summing up to $O(T-P)$ time or $O(T)$ if $P = O(T)$.
> - Worst Case: If the hash function is poorly designed, or the text and pattern are highly repetitive, we have to perform char-by-char check for every shift, taking $O(T\cdot P)$ time.
> 
> Overall:
> - Best / Average Case: $O(T + P)$.
> - Worst Case: $O(T\cdot P)$.

## Knuth-Morris-Pratt Algorithm (KMP)

### Prefix function (Longest Prefix Suffix - LPS)

Given a string $s$ of length $n$, the prefix function of $s$ is defined as an array $\pi$ of length $n$, where $\pi[i]$ is the length of the longest proper prefix of the substring $s[0..i]$ which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, $\pi[0] = 0$.

Mathematically, the definition can be rewritten as followed:

```math
\pi[i] = max_{k=0..i}\{k: s[0..k-1] = s[i-(k-1)..i]\}
```
For example, prefix function of string "abcabcd" is $\left[0, 0, 0, 1, 2, 3, 0\right]$ , and prefix function of string "aabaaab" is $\left[0, 1, 0, 1, 2, 2, 3\right]$.


> [!IMPORTANT]
> **Algorithm**:
>
> We compute the prefix values $\pi[i]$ in a loop by iterating from $i = 1$ to $i = n-1$ ($\pi[0]$  just gets assigned with $0$).
>
> To calculate the current value $\pi[i]$ we set the variable $j$ denoting the length of the best suffix for $i-1$. Initially $j = \pi[i-1]$.
> 
> Test if the suffix of length $j+1$ is also a prefix by comparing $s[j]$ and $s[i]$. If they are equal then we assign $\pi[i] = j + 1$.
>
> <img width="400" height="100" alt="image" src="https://github.com/user-attachments/assets/be0156fc-45c9-401c-bcec-011e5c7af2a8" />
>
> Otherwise we reduce $j$ to $\pi[j-1]$ and repeat this step.
>
> <img width="400" height="100" alt="image" src="https://github.com/user-attachments/assets/e876ceff-5cac-44c8-b684-48a4d81602ba" />
> <img width="400" height="100" alt="image" src="https://github.com/user-attachments/assets/b1f2cac1-3c49-4dff-a4d0-d303bd59b8cf" />
>
> If we have reached the length $j = 0$ and still don't have a match, then we assign $\pi[i] = 0$ and go to the next index $i + 1$ .

```cpp
PREFIX_FUNCTION(s, n)
    create array pi[0..n-1]
    pi[0] = 0

    for i = 1 to n
        set j = pi[i - 1]
        while j > 0 and s[i] != s[j]
            j = pi[j-1]

        if s[i] == s[j]
            ++j

        pi[i] = j
    
    return pi
```

### Finding pattern using KMP 

> [!IMPORTANT]
> **Algorithm**
> - We initialize two pointers, one for the text string and another for the pattern.
> - When the characters at both pointers match, we increment both pointers and continue the comparison.
> - If they do not match, we reset the pattern pointer to the last value from the LPS array, because that portion of the pattern has already been matched with the text string.
> - Similarly, if we have traversed the entire pattern string, we add the starting index of occurrence of pattern in text, to the result and continue the search from the LPS value of last element of the pattern.

```cpp
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

> [!IMPORTANT]
> **Time analysis**
> 
> `PREFIX_FUNCTION` takes $O(P)$ time.
> 
> - We track # loops by looking at the # of `j` updates.
>   - `j` increases together with `i`. 
>      Therefore,  # `j` increases $=$ # `i` increases $= P$.
>   - `j` can never be $< 0$. Supposed `j` decreases $k$ times, then `j` should have increased at least $k$ times (so that `j` $\ge 0$). But # `j` increases is bounded by $P$. Therefore, # `j` decreases is also $\le P$.
> 
> Summing up, running time $= \text{no. increases + no. decreases} \le 2P = O(P)$.
>
> `KMP` takes $O(T)$ time.
> - The same explanation can be applied, when we track the \# `j` updates. `j` and `i` increases at most `T` times, and `j` decreases at most the # times it increases over the entire function. Thus, running time is $\le T + T = O(T)$.
>
> Overall, KMP algorithm takes $O(T + P)$ time.

