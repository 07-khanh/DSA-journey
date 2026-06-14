# Hash Table
## Direct-Address Tables

Works well when the universe $U$ of keys is reasonably small. 

**Scenario**: 
- Suppose that an application needs a **dynamic set** in which each element has a distinct key drawn from the universe $U=\{0;1;...;m\}$, where $m$ is not too large.

- No two elements have the same key.

Represent by a direct-address table, or array, $T[0... m−1]$:
- Each slot, or position, corresponds to a key in $U$.
- If there is an element $x$ with key $k$, then $T[k]$ contains a pointer to $x$.
- Otherwise, $T[k]$ is empty, represented by NIL.

<img src='/hashTable/images/direct_address.png' alt='Direct-address table'>

Dictionary operations are trivial and take $O(1)$ time each:

```cpp
DIRECT-ADDRESS-SEARCH(T,k)
    return T[k]
DIRECT-ADDRESS-INSERT(T, x)
    T[key[x]] = x
DIRECT-ADDRESS-DELETE(T, x)
    T[key[x]] = NIL
```

## Hash tables

The problem with direct addressing is if the universe $U$ is large, storing a table of size $|U|$ may be impractical or impossible.

Often, the set $K$ of keys actually stored is small, compared to $U$, so that most of the space allocated for $T$ is wasted.

When $K$ is much smaller than $U$, a hash table:
-  Requires much less space than a direct-address table.
- Can reduce storage requirements to $\Theta(|K|)$.
- Can still get $O(1)$ search time, but in the average case, not the worst case.

Instead of storing an element with key $k$ in slot $k$, use a function $h$ and store the element in slot $h(k)$.
- We call $h$ a **hash function**.
- $h : U \rightarrow \{0,1,... ,m−1\}$, so that $h(k)$ is a legal slot number in $T$.
- We say that $k$ **hashes** to slot $h(k)$.

**Collisions**: When two or more keys hash to the same slot.
- Can happen when there are more possible keys than slots $(|U|> m)$.
- For a given set $K$ of keys with $|K | \le m$, may or may not happen. Definitely happens if $|K |> m$.
- Therefore, we must be prepared to handle collisions in all cases using two methods: chaining and open addressing.
- Chaining is usually better than open addressing.

<img src='/hashTable/images/hashTable.png' alt='Hash function'>

### Chaining
The idea is to put all elements that hash to the same slot into a linked list.

<img src='/hashTable/images/chaining.png' alt='Chaining with double linked lists'>

- Slot $j$ contains a pointer to the head of the list of all stored elements that hash to $j$ (or to the sentinel if using a circular, doubly linked list with a sentinel). 
- If there are no such elements, slot $j$ contains NIL.
- If we want to delete elements, it is better to use doubly linked lists.

**Dictionary operations with chaining:**
1. **Insertion**:
```cpp
CHAINED-HASH-INSERT(T, x)
    insert x at the head of list T[h(key[x])]
```
- Worst-case running time is $O(1)$.
- This assumes that the element being inserted isn't it already in the list. It would take an additional search to check if it was already inserted.
2. **Search:**
```cpp
CHAINED-HASH-SEARCH(T,k)
    search for an element with key k in list T[h(k)]
```
Running time is proportional to the length of the list of elements in slot $h(k)$.
3. **Deletion:**
```cpp
CHAINED-HASH-DELETE(T, x)
    delete x from the list T[h(key[x])]
```
- Given pointer $x$ to the element to delete, so no search is needed to find this element.
- Worst-case running time is $O(1)$ time if the lists are doubly linked.
- If the lists are singly linked, then deletion takes as long as searching, because we must find the predecessor in its list in order to correctly update next pointers.

#### Time Complexity Analysis:

> **Question**: Given a key, how long does it take to find an element with that key, or to determine that there is no element with that key?

Analysis is in terms of the **load factor** $\alpha =n/m$:
- $n =$ the number of elements in the table.
- $m =$ the number of slots in the table $=$ the number of (possibly empty) linked lists.
- Load factor is **average number of elements per linked list**.
- Can have $\alpha < 1, \alpha = 1, \alpha > 1$.
- Worst case is when all $n$ keys hash to the same slot $\Rightarrow$ get a single list of length $n$.
$\Rightarrow$ worst-case time to search is $O(n)$, plus time to compute hash function.
- Average case depends on how well the hash function distributes the keys among the slots.

We focus on average-case performance of hashing with chaining.

We rely on the **Simple Uniform Hashing Assumption (SUHA)**, which states that any given key is equally likely to hash into any of the $m$ slots in the table, independently of where any other key has hashed.

We consider two cases:
- If the hash table contains no element with key $k$, then the search is **unsuccessful**.
- If the hash table does contain an element with key $k$, then the search is **successful**.

1. **Unsuccessfull Search:**
- Hashing: Computing the hash function takes $\Theta(1)$ time to find the correct slot.
- Scanning: Under SUHA, the expected length of any single linked list is exactly the average number of elements per slot, which is the load factor $\alpha$. Since the key isn't there, the algorithm must search the entire list until it hits the end.

Total Expected Time: $$T_{\text{unsucc}} = \Theta(1) + \alpha = \Theta(1 + \alpha)$$

2. **Successfull Search:**
- Hashing: Finding the slot takes $\Theta(1)$ time.
- Scanning: The number of elements examined in the linked list is $1$ (for the element itself) plus the expected number of elements that were inserted into this specific list after our target element was already there.
- Derivation: Let $x_i$ be the $i$-th element inserted into the table, where $1 \le i \le n$. When $x_i$ is inserted, there are $i - 1$ elements already in the table. Under SUHA, the probability that any of those $i - 1$ elements are in the same slot as $x_i$ is $1/m$.
Therefore, the expected number of elements examined during a search for $x_i$ is:
$$E[\text{elements examined}] = 1 + \frac{i - 1}{m}$$
To find the average across all possible successful searches, we take the average of this expected value over all $n$ elements:
$$\frac{1}{n} \sum_{i=1}^{n} \left( 1 + \frac{i - 1}{m} \right) = 1 + \frac{1}{nm} \sum_{i=1}^{n} (i - 1)$$
Using the arithmetic progression summation formula $\sum_{i=1}^{n} (i-1) = \frac{n(n-1)}{2}$:
$$= 1 + \frac{1}{nm} \cdot \frac{n(n-1)}{2} = 1 + \frac{n-1}{2m} = 1 + \frac{\alpha}{2} - \frac{1}{2m}$$

Total Expected Time: Adding the initial $\Theta(1)$ hashing step yields:$$T_{\text{succ}} = \Theta\left(1 + 1 + \frac{\alpha}{2} - \frac{1}{2m}\right) = \Theta(1 + \alpha)$$

## Hash function
> **What makes a good hash function?**

- Ideally, the hash function satisfies the assumption of **simple uniform hashing**.
- In practice, it is not possible to satisfy this assumption, since we don't know in advance the probability distribution that keys are drawn from, and the keys may not be drawn independently.
- Often use **heuristics**, based on the domain of the keys, to create a hash function that performs well.

### Keys as natural numbers

Hash functions assume that the keys are natural numbers.
- When they are not, have to interpret them as natural numbers.
- Example: Interpret a character string as an integer expressed in some radix notation. 
'CLRS' $\rightarrow (67\cdot128^3) +(76\cdot128^2) +(82\cdot128^1) +(83\cdot128^0)=141,764,947$.

### Division method
> [!IMPORTANT]
> **Division Method:**
> $$h(k) = k \text{ mod } m$$

Example: $m =20$ and $k=91 \Rightarrow h(k)=11$.
- **Advantage**: Fast, since requires just one division operation.
- **Disadvantage**: Have to avoid certain values of $m$:
    - Powers of *2* are bad. If $m =2^p$ for integer $p$, then $h(k) $is just the least significant $p$ bits of $k$.
    - If $k$ is a character string interpreted in radix $2^p$ (as in CLRS example), then$ m = 2^p−1$ is bad.

Good choice for $m$: A prime not too close to an exact power of $2$.
> [!NOTE]
> _Why should we use a prime $m$?_
> 
> If the keys are random, then the value of $m$ doesn't really matter. 
> 
> However, in real-world data, keys are rarely completely random. They often share common increments, common factors, or end in similar digits (e.g., memory addresses ending in $0$ or $4$, or timestamps sharing the same prefix).
>
> If $m$ shares a common factor $d$ with the regular intervals in your keys, those keys will map to a **restricted subset of slots** in your hash table rather than spreading out evenly.
> 
> A prime number $m$ has no factors other than $1$ and itself. This minimizes the chance that patterns in your keys will align with the structure of the hash table size, forcing the hash function to utilize all available slots.
> 
> If we dive deeper into the math:
>
> Let $M$ be the size of the hash table, and let $S$ be a constant stride (interval) between a sequence of keys: $K_i = i \cdot S$ for $i = 0, 1, 2, \dots$. 
>
> The sequence of indices visited in the hash table is given by:
> $$x_i = (i \cdot S) \pmod M$$
>
> We prove that: The sequence of indices $x_i = (i \cdot S) \pmod M$ generates a subgroup of the additive group $\mathbb{Z}_M$ whose size (cardinality) is exactly $\frac{M}{d}$, where $d = \gcd(S, M)$.
> 
> **Proof**:
> Let $d = \gcd(S, M)$. By definition of the greatest common divisor, we can factor $d$ out of both $S$ and $M$:
> $$S = d \cdot s' \quad \text{and} \quad M = d \cdot m'$$
> where $s'$ and $m'$ are coprime integers ($\gcd(s', m') = 1$).
>
> Now, substitute these factored forms into our index equation:
> $$x_i = (i \cdot d \cdot s') \pmod{d \cdot m'}$$
> $$x_i = d \cdot \left[ (i \cdot s') \pmod{m'} \right]$$
> Look closely at this result. Because $d$ is multiplied by the entire term, every single index $x_i$ generated by this sequence must be a multiple of $d$.
> 
> Now, how many unique values can the term $(i \cdot s') \pmod{m'}$ produce?
> 
> Since $\gcd(s', m') = 1$, the multiplication by $s'$ permutes the elements of $\mathbb{Z}_{m'}$ perfectly. Therefore, as $i$ ranges from $0$ to $m'-1$, the term inside the brackets will produce exactly $m'$ unique integers: $\{0, 1, 2, \dots, m'-1\}$.
> 
> Multiplying these unique integers by our factor $d$, the set of all possible hash indices visited is:
> $$\text{Visited Slots} = \{0, d, 2d, 3d, \dots, (m'-1)d\}$$
> The total number of unique slots visited is exactly $m'$. Substituting $m' = \frac{M}{d}$ back in:
> $$\text{Total Unique Slots} = \frac{M}{\gcd(S, M)}$$.
> **Example**: If $M = 12$ and $S = 9$, then $d = \gcd(9, 12) = 3$.
> 
> The number of unique slots visited is $\frac{12}{3} = 4$. The slots are $\{0, 3, 6, 9\}$. The remaining $8$ slots are mathematically impossible to reach.
>
> Then, if $M$ and $S$ are coprime, we have:
> $$\text{Total Unique Slots} = \frac{M}{\gcd(S, M)} = \frac{M}{1} = M$$

### Multiplication Method
1. Choose constant $A$ in the range $0 < A < 1$.
2. Multiply key $k$ by $A$.
3. Extract the fractional part of $kA$.
4. Multiply the fractional part by $m$.
5. Take the floor of the result.
Put another way, $$h(k)= \lfloor m (kA \text{ mod } 1) \rfloor$$
where $kA \text{ mod } 1= kA − \lfloor kA \rfloor =$ fractional part of $kA$.

- **Disadvantage**: Slower than division method.
- **Advantage**: Value of $m$ is not critical.

> [!NOTE]
> **Knuth** suggested using $A = \frac{\sqrt{5}-1}{2} \approx 0.6180339887$ (reciprocal of the goldren ratio).
> When we multiply keys by A, we only keep the fractional part:
> $$kA \text{ mod } 1$$
>  If the sequence of $kA$ has fractional parts that are evenly spread throughout $[0,1)$, then the hash values will also be evenly spread instead of clustering. This really matters if there is some patterns in the keys $k$.
> 
> $A$ must be an irrational number. 
>
> Suppose $A=\frac{p}{q}$ is rational.
> 
> Then $kA \text{ mod } 1$ can take at most $q$ distinct values before repeating.
>
> Example: $A= \frac{1}{3}$ and the keys have sequential patterns ($k = 1, 2, 3, 4, \dots$)
> Then $kA \text{ mod } 1$ will be $\frac{1}{3}, \frac{2}{3}, 0, \frac{1}{3},\frac{2}{3}, 0,...$ which is terrible for hashing.
>
> Therefore $A$ should be irrational.
>
> However, not all irrational numbers are equally good. Some irrationals are very well approximated by rationals.
>
> Any real number can be expressed as a continued fraction, which looks like this:
> $$x = a_0 + \frac{1}{a_1 + \frac{1}{a_2 + \frac{1}{a_3 + \dots}}}$$
> If a number has large integers in its denominators ($a_1, a_2, \dots$), it can be closely approximated by a clean, rational fraction ($p/q$). For example, $\pi = 3.14159...$ has a continued fraction starting with $[3; 7, 15, 1, 292...]$. Because $7$ and $15$ are relatively large, the rational fraction $22/7$ is an incredibly close approximation to $\pi$.
>
> If our hash multiplier can be easily approximated by a simple rational fraction like $22/7$, then keys that step by a regular stride will quickly repeat patterns in our hash table, causing massive collisions.
> 
> The golden ratio's continued fraction expansion is famously composed entirely of ones:
>$$\phi = 1 + \frac{1}{1 + \frac{1}{1 + \frac{1}{1 + \dots}}}$$
> Because its denominators are the smallest possible integers ($1$), **the golden ratio is the hardest number to approximate with a rational fraction**. It resists falling into repeating fractional patterns better than any other number in existence.

### Multiply-Shift Method
This is the real-life application of the multiplication method, when $m$ is a power of $2$.
> [!IMPORTANT]
> $$h(k) = (ka \text{ mod } 2^w) \gg (w - \ell) $$
- Defining the Variables:
    - $w$ (Word Size): The number of bits your CPU processes at once (usually 32 or 64 bits).
    - $\ell$ (Index Bits): The number of bits needed for your hash table index. If your table size is $m = 2^\ell$, and you have 1024 slots, then $\ell = 10$ bits (since $2^{10} = 1024$).
    - $a$ (The Magic Multiplier): Instead of using a decimal fraction like $0.618$, we scale it up into a massive integer that fills a whole $w$-bit register: $a = A \cdot 2^w$. 

Multiply-shift method is usually used in universal hashing where $a$ is a **random odd integer**. This provides provable guarentees of $2/m$ collision probability.

**The process:**
- **Step 1**: Multiply your $w$-bit key $k$ by $a$ ($w$-bit).
The creates a product that is $2w$ bits,  $r_12^w +r_0$.
    - The High Word ($r_1$): The upper $w$ bits.
    - The Low Word ($r_0$): The lower $w$ bits.
    Because of how we scaled our multiplier, the High Word ($r_1$) represents the Integer Part of the multiplication, and the Low Word ($r_0$) represents the Fractional Part.
- **Step 2**: $ak\text{ mod } 2^w$
This extracts $r_0$ (the fractional part) by dropping $r_1$ (the integer part). 
On a real computer, the CPU automatically discards the High Word ($r_1$) due to integer overflow.

- **Step 3:** Right Shift( $\gg (w - \ell)$ )
We now have a $w$-bit Low Word ($r_0$), but our hash table only needs an $\ell$-bit index.
Because multiplication mixes digits from right to left, the leftmost bits of $r_0$ are the most thoroughly scrambled and random. We want to extract those $\ell$ highest bits.
To do this, we use a bitwise right-shift ($\gg$). We push the unwanted lower bits off the right edge of the register by shifting down by $w - \ell$ positions, which automatically slides our target bits cleanly into the rightmost slots.

This entire process perfectly aligns with the native hardware behavior of a CPU.

<img src='/hashTable/images/multiply-shift.png' alt='Mutiply-shift method for hash function'>

## Universal Hashing

Suppose that a malicious adversary, who gets to choose the keys to be hashed, has seen our hashing program and knows the hash function in advance. Then he could choose keys that all hash to the same slot, giving worst-case behavior.

Universal Hashing helps solve this exact problem.

**Idea:** Do not use a single, fixed hash function. Instead, pick a random hash function at runtime from a carefully designed family of functions.

Because the function is chosen at random when the program boots up, an attacker cannot predict how the keys will behave. Even if they feed us the exact same keys as yesterday, those keys will map to completely different, scattered slots today.

We can't just pick any random collection of hash functions. The collection must form a Universal Family (denoted as $\mathcal{H}$).

Let $M$ be the size of our hash table. A finite collection of hash functions $\mathcal{H}$ that maps a universe of keys $U$ into the range $\{0, 1, \dots, M-1\}$ is called universal if:

For any two distinct keys $x \neq y$, the number of hash functions $h \in \mathcal{H}$ for which $h(x) = h(y)$ is at most:

$$\frac{|\mathcal{H}|}{M}$$

In other words, if we pick a hash function $h$ completely at random from this family, the probability of a collision between any two distinct keys $x$ and $y$ is at most the chance $\frac{1}{m}$ of a collision if $h(x)$ and $h(y)$ were randomly and independently chosen from the set $\{0; 1; 2;...; m-1\}$.

$$P(h(x) = h(y)) \le \frac{1}{M}$$

This is a beautiful threshold. $\frac{1}{M}$ is the exact same collision probability we would get if we had a theoretically perfect, truly independent random hash function.

We also have $\epsilon$-universal: The family $\mathcal{H}$ of hash functions is $\epsilon$-universal if for any distinct keys $x$ and $y$ in $U$, the probability that $h(x) = h(y)$ is at most $\epsilon$. Therefore, a universal family of hash functions is also $\frac{1}{M}$-universal.

### Designing a universal family of hash functions
#### Based on number theory
1. Pick a prime number $p$ that is larger than the largest possible key in our universe ($p > |U|$).
2. Table size is $M$.
3. Define a family of functions $\mathcal{H}_{pm}$ where we choose two random integers, $a$ and $b$:
    - $a \in \{1, 2, \dots, p-1\}$ (Note: $a$ cannot be 0!)
    - $b \in \{0, 1, \dots, p-1\}$

>[!IMPORTANT]
> The universal hash function formula is:
> $$h_{a,b}(k) = ((a \cdot k + b) \pmod p) \pmod M$$
> Given $p$ and $m$, the family of all such hash functions is
> $$\mathcal{H}_{pm} = \{h_{a,b} : a \in \mathbb{Z^*}, b \in \mathbb{Z}\}$$

The size $m$ is arbitrary-it need not be prime. Since we can choose from among $p - 1$ values for $a$ and $p$ values for $b$, the family $\mathcal{H}_{pm}$ contains $p(p-1)$ hash functions.

> [!NOTE]
> Prove that for any two distinct keys $x \neq y$, picking a random function from the family $\mathcal{H}_{a,b}$ results in a collision probability of:
> $$P(h_{a,b}(x) = h_{a,b}(y)) \le \frac{1}{M}$$
> 1. **The Unique Mapping (Bijective Correspondence)**
> Let $r_x = (ax + b) \pmod p$ and $r_y = (ay + b) \pmod p$ be the intermediate values before the final modulo $M$ compression. 
> We can express this as a system of linear equations in the prime field $\mathbb{Z}_p$:
> $$\begin{pmatrix} x & 1 \\ y & 1 \end{pmatrix} \begin{pmatrix} a \\ b \end{pmatrix} \equiv \begin{pmatrix} r_x \\ r_y \end{pmatrix} \pmod p$$
> The determinant of the coefficient matrix is $D = x - y$. Since $x$ and $y$ are distinct keys strictly smaller than $p$, $D \not\equiv 0 \pmod p$. Because the determinant is non-zero, the matrix is **uniquely invertible**.
> This matrix invertibility yields two critical facts:
>  - Since $a \neq 0$, the outputs $r_x$ and $r_y$ can never be equal ($r_x \neq r_y$).
>  - There is a perfect one-to-one correspondence between every random parameter pair $(a, b)$ and every distinct remainder pair $(r_x, r_y)$.
>
> Therefore, picking a function from the family uniformly at random is combinatorially identical to picking a pair of distinct coordinates $(r_x, r_y)$ uniformly at random. The total number of possible pairs is:
> $$\text{Total Pairs} = p(p - 1)$$
> 2. **Counting the Collisions**
> A collision occurs if the compressed values match: $r_x \equiv r_y \pmod M$.
>
> For a fixed value of $r_x$, the value $r_y$ will cause a collision if it matches the pattern $r_y \in \{r_x \pm M, r_x \pm 2M, \dots\}$. 
>
> Within the bounded range $[0, p-1]$, the total number of multiples of $M$ is bounded by the ceiling of the total range divided by the step size, subtracted by $1$ because $r_y \neq r_x$: 
> ```math
> \begin{align*}
>  \text{Colliding values for } r_y &\le \left\lceil \frac{p}{M} \right\rceil - 1 \\
> & \le \frac{p + M - 1}{M} - 1\\
> & = \frac{p-1}{M}
> \end{align*}
> ```
> Because $r_x$ can be any of the $p$ elements in the field, the total number of colliding pairs across the entire system is:
> $$\text{Total Colliding Pairs} \le p \cdot \left(\frac{p - 1}{M}\right)$$
> 3. **Final Probability**
> $$P(\text{Collision}) = \frac{\text{Total Colliding Pairs}}{\text{Total Pairs}}$$$$P(\text{Collision}) \le \frac{p \cdot \left(\frac{p - 1}{M}\right)}{p(p - 1)} = \frac{1}{M}$$

#### A $2/m$-universal family of hash functions based on the multiply-shift method

Define $\mathcal{H}$ to be the family of multiply-shift hash functions with odd constants $a$:
$$\mathcal{H}_{a} = \{h_{a}: a \text{ is odd }, 1\le a < m\}$$
with 
$$h_a(k) = (ka \text{ mod } 2^w) \gg (w - \ell)$$

The probability that any two distinct keys collide is at most $2/m$.

In many practical situations, the speed of computing the hash function more than compensates for the higher upper bound on the probability that two distinct keys collide when compared with a universal hash function.

_(We do not give the proof for $2/m$ collision probability here)_

### Universal Hashing Time Complexity

> [!IMPORTANT]
> **Theorem**: Suppose we hash a set $S \subset U$ of $n$ keys into a table of size $m$ using a hash function $h$ chosen uniformly at random from a universal family $\mathcal{H}$. If collisions are resolved by chaining, the expected time to search for any key $x$ is $O(1 + \alpha)$, where $\alpha = n/m$ is the load factor.

**Proof**

Let's analyze the expected number of keys that hash to the same slot as our target key $x$.
- **Step 1:** Define Indicator Random Variables
For every key $y \in S$, define an indicator random variable $X_{xy}$ to represent whether $x$ and $y$ collide under the randomly chosen function $h$:
$$X_{xy} = \begin{cases} 
1 & \text{if } h(x) = h(y) \\
0 & \text{if } h(x) \neq h(y) 
\end{cases}$$
By the definition of expectation for indicator variables, the expected value $E[X_{xy}]$ is simply the probability that $h(x) = h(y)$.
    - If $x \neq y$: Because $\mathcal{H}$ is universal, $E[X_{xy}] = P(h(x) = h(y)) \le \frac{1}{m}$.
    - If $x = y$: The keys are identical, so they always hash to the same slot: $E[X_{xx}] = 1$.
- **Step 2:** Set up the Total Collision Count
Let $T$ be the random variable representing the total number of keys in the slot $h(x)$. This matches the length of the linked list at that slot. We can express $T$ as the sum of all indicators:
$$T = \sum_{y \in S} X_{xy}$$
To find the expected length of this list, we take the expectation of both sides and apply the linearity of expectation:
$$E[T] = E\left[ \sum_{y \in S} X_{xy} \right] = \sum_{y \in S} E[X_{xy}]$$
- **Step 3:** Analyze by Cases
We must split this analysis based on whether the target key $x$ is already in the hash table $S$ or not.
    - **Case A:** $x \notin S$ (Unsuccessful Search)
    Since $x$ is not in the set $S$, $x \neq y$ for all $y \in S$.
    $$E[T] = \sum_{y \in S} E[X_{xy}] \le \sum_{y \in S} \frac{1}{m} = \frac{n}{m} = \alpha$$
    - **Case B:** $x \in S$ (Successful Search)
    Since $x$ is in the set $S$, one of the elements in the summation is $y = x$ (where $X_{xx} = 1$). We separate this term from the rest:
    $$E[T] = E[X_{xx}] + \sum_{y \in S \setminus \{x\}} E[X_{xy}]$$
    $$E[T] \le 1 + \sum_{y \in S \setminus \{x\}} \frac{1}{m} = 1 + \frac{n - 1}{m} < 1 + \alpha$$


In both successful and unsuccessful searches, the expected number of elements examined during a search is bounded by $O(1 + \alpha)$.

The total time complexity of a search operation consists of two parts:
    - Computing the hash function: $O(1)$ time (assuming the functions in $\mathcal{H}$ can be evaluated in constant time).
    - Scanning the linked list: $O(E[T])$ time.

Therefore, the total expected time for a search operation is:
$$\text{Expected Time} = O(1) + O(1 + \alpha) = O(1 + \alpha)$$
If the size of the hash table $m$ is chosen to be proportional to the number of elements $n$ (i.e., $m = \Omega(n)$), then the load factor $\alpha = n/m = O(1)$. This brings the final expected computational complexity to a clean, constant $O(1)$.

## Open addressing

Open Addressing is a method for handling collisions in a hash table.

Unlike Chaining (where each slot in the table points to a linked list of colliding elements), open addressing keeps all elements directly inside the hash table array itself. 

Every slot contains either:
-  an element, 
- a NIL, 
- a special deletion flag.

Because everything is stored in the array, the load factor $\alpha = n/m$ can never exceed $1$. 

Collisions are handled as follows: 
- When a new element is to be inserted into the table, it is placed in its "first choice" location if possible. 
- If that location is already occupied, go to "second choice". 
- Continue until an empty slot is found in which to place the new element. 
- Different elements have different preference orders for the locations.

To **search** for an element:
- Systematically examine the preferred table slots for that element, in order of **decreasing preference**, until we either:
    - Find the desired element.
    - Find an empty slot $\Rightarrow$ the element is not in the table.

The memory freed by not storing pointers provides the hash table with a larger number of slots in the same amount of memory, potentially yielding fewer collisions and faster retrieval.

To perform **insertion** using open addressing, successively examine, or **probe**, the hash table until find an empty slot in which to put the key. 

Instead of being fixed in the order $0;1;...;m$ (which implies a $O(n)$ search time), the sequence of positions probed depends upon the key being inserted. 

To determine which slots to probe, the hash function includes the probe number (starting from $0$) as a second input. Thus, the hash function becomes 
$$h: U \times \{0;1...;m-1\} \rightarrow \{0;1;...;m-1\}$$ 

For every key $k$, the probe sequence $\langle h(k, 0), h(k, 1),...,h(k,m-1) \rangle$ be a **permutation** of $\langle 0, 1,...,m-1 \rangle$, so that every hash-table position is eventually considered as a slot for a new key as the table fills up.

**Deletion:**
Deletion is trickier.

Imagine we insert Key $A$, then Key $B$ collides with $A$ and lands in the next slot via linear probing. 

If we simply delete Key $A$ and clear its slot to NIL, then when the program searches for $B$:
- The program hashes Key $B$ and looks at Key $A$'s old slot.
- It sees NIL (empty).
- The program assumes, "If Key $B$ were in the table, it would have been placed here or continuously probed from here. Since this slot is empty, Key $B$ must not exist."

To fix this, when we remove an element from an open-addressed table, we cannot leave it blank. We must replace it with a special dummy token often called a Tombstone or `DELETED` flag.

- During **Search**: The algorithm treats the tombstone as "occupied" and continues probing past it.
- During **Insertion**: The algorithm treats the tombstone as "empty" and can overwrite it with a new key.

```cpp
INSERT(T, m, key, value):
    firstDeletedIndex = -1   // Tracks the first tombstone we hit
    
    for i from 0 to m - 1:
        index = getProbeIndex(key, i, m)
        slot = T[index]
        
        // Case 1: Key already exists, update its value
        if slot is not NULL and slot is not DELETED and slot.key == key:
            slot.value = value
            return true
            
        // Case 2: Hit a tombstone, remember it to reuse the space later
        if slot == DELETED:
            if firstDeletedIndex == -1:
                firstDeletedIndex = index
                
        // Case 3: Hit an empty slot
        if slot == NULL:
            // If we passed a tombstone earlier, optimize and insert there
            if firstDeletedIndex != -1:
                T[firstDeletedIndex] = NewElement(key, value)
            else:
                T[index] = NewElement(key, value)
            return true
            
    // If we looped m times and found no valid slot, or if we didn't hit a NULL
    if firstDeletedIndex != -1:
        T[firstDeletedIndex] = NewElement(key, value)
        return true
        
    error "Hash Table Overflow: Table is completely full!"
    return false
```

```cpp
SEARCH(T, m, key):
    for i from 0 to m - 1:
        index = getProbeIndex(key, i, m)
        slot = T[index]
        
        // Case 1: Slot is completely empty, key definitely does not exist
        if slot == NULL:
            return NOT_FOUND
            
        // Case 2: Slot contains a tombstone, skip it and keep probing
        if slot == DELETED:
            continue
            
        // Case 3: Slot contains an active element, check if it matches
        if slot.key == key:
            return slot.value
            
    // Checked all m slots without hitting a NULL or finding the key
    return NOT_FOUND
```
```cpp
DELETE(T, m, key):
    for i from 0 to m - 1:
        index = getProbeIndex(key, i, m)
        slot = table[index]
        
        // Case 1: Hit a completely empty slot.
        // This proves the key was never inserted, or any chain 
        // it belonged to has ended here.
        if slot == NULL:
            return NOT_FOUND
            
        // Case 2: Hit a tombstone. 
        // We must skip over it and keep searching, because the element
        // we want to delete might be further down the collision chain.
        if slot == DELETED:
            continue
            
        // Case 3: Found the active element matching our key.
        if slot.key == key:
            deletedValue = slot.value   // Save the value to return it
            T[index] = DELETED      // Place the tombstone
            return deletedValue         // Return the value of the deleted item
            
    // Checked all m slots without hitting a NULL or finding the key
    return NOT_FOUND
```

> [!NOTE]
> Using the special value `DELETED`, however, means that search times no longer depend on the load factor $\alpha$.
> 
> In open addressing, deleting an element requires leaving a tombstone (`DELETED` marker) to avoid breaking the search path of other collided elements down the chain. 
>
> However, because a search operation cannot stop at a tombstone and must keep probing past it, a lot of insertions and deletions will eventually clog the table with these markers. This means that even if the table currently holds very few active elements (a low load factor $\alpha$), a search must still probe a lot of tombstones before hitting a true NULL slot to terminate.
>
> $\Rightarrow$ Performance based on **historical churn** rather than current capacity. 
>
> Conversely, Chaining (using linked lists) avoids this completely. When we delete an item in chaining, we completely remove it from memory and the list instantly shrinks. Because there are no placeholders left behind, search speeds always stay fast and depend only on the actual amount of data inside the table right now.

### How to compute probe sequences

The ideal situation is **uniform hashing**: each key is equally likely to have any of the $m!$ permutations of $\langle 0, 1, ..., m−1 \rangle$ as its probe sequence. 

This generalizes **simple uniform hashing** for a hash function that produces a whole probe sequence rather than just a single number.
- First Probe ($i=0$): The key has a $\frac{1}{m}$ chance of checking any slot. (This is exactly identical to Simple Uniform Hashing).
- Second Probe ($i=1$): If the first slot is full, the algorithm doesn't just jump to the next physical slot (like Linear Probing does). Instead, it chooses completely randomly from the remaining $m-1$ empty slots. The probability of picking any specific remaining slot is $\frac{1}{m-1}$.
- Third Probe ($i=2$): If that is also full, it chooses completely randomly from the remaining $m-2$ slots with a probability of $\frac{1}{m-2}$...

It is hard to implement true uniform hashing, so we approximate it with techniques that at least guarantee that the probe sequence is a permutation of $\langle 0, 1, ..., m−1 \rangle$.

None of these techniques can produce all $m!$ probe sequences. They will make use of auxiliary hash functions $h':U \rightarrow \{0,1,... ,m−1\}$.
$$h(k, i) = (h'(k) + f(i)) \bmod m$$

#### Linear Probing ($f(i) = i$)
If a collision occurs at slot $x=h'(k)$, we simply check the next consecutive slots: $x+1, x+2, x+3, \dots$ wrapped around the array.

Given key $k$ and probe number $i$ $(0 \le i < m)$ 
$$h(k,i)=(h'(k) +i) \text{ mod } m$$

- **Pros**: Unmatched cache locality. Because the CPU fetches blocks of contiguous memory at once, scanning adjacent array indices is blindingly fast.
- **Cons**: 
    - **Primary Clustering**. Long, continuous blocks of occupied slots build up over time. Any new key that hashes to anywhere inside that block will drift all the way to the end of it, making the cluster grow even larger and degrading search times to $O(n)$.
    - Can only have $m$ possible sequences.

#### Quadractic Probing ($f(i) = c_1 \cdot i + c_2 \cdot i^2$)
Instead of checking consecutive slots, the distance between probes increases quadratically (e.g., $x+1, x+4, x+9, x+16\dots$).
$$h(k,i)=(h'(k) +c_1i +c_2i^2)  \text{ mod } m$$
Must constrain $c_1, c_2$, and $m$ in order to ensure that we get a full permutation of $\langle 0, 1, ..., m−1 \rangle$.
- **Pros**: It skips over the continuous blocks of data that ruin linear probing, eliminating primary clustering.
- **Cons**: 
    - **Secondary Clustering**. If two different keys happen to have the exact same initial hash value ($h'(k_1) = h'(k_2)$), they will still follow the exact same quadratic probe path, creating milder clusters. 
    - If not carefully designed, it might skip over empty slots entirely even if the table isn't full.

#### Double Hashing ($f(i) = i \cdot h_2(k)$)
Use two auxiliary hash functions, $h_1$ and $h_2$:
- $h_1$ gives the initial probe.
- $h_2$ gives the remaining probes.
 $$h(k,i)=(h_1(k) +ih_2(k)) \text{ mod } m$$

Must have $h_2(k)$ be coprime to $m$ in order to guarantee that the probe sequence is a full permutation of $\langle 0, 1, ..., m−1 \rangle$.
- Could choose $m$ to be a power of $2$ and $h_2$ to always produce an odd number $> 1$.
- Could let $m$ be prime and have $1 < h_2(k) < m$.

$\Theta(m^2)$ different probe sequences, since each possible combination of $h_1(k)$ and $h_2(k)$ gives a different probe sequence.

- **Pros**: This is the gold standard for open addressing. Because the step size depends directly on the key itself, two keys that share the same initial hash value will almost certainly have different step sizes, completely eliminating both primary and secondary clustering.
- **Cons**: It loses cache locality because it jumps wildly across the array, and computing a second hash function requires more CPU cycles.

### Analysis of open-address hashing

**Assumptions:**
- Analysis is in terms of load factor α. We will assume that the table never
completely fills, so we always have $0 \le n < m \Rightarrow 0 \le \alpha < 1$.
- Assume uniform hashing.
- No deletion.
- In a successful search, each key is equally likely to be searched for.
#### Unsuccessful Search (and Insertion)
An unsuccessful search occurs when you look for a key that is not in the table. To definitively prove the key is missing, the algorithm must keep probing until it encounters a completely empty (NIL) slot.

Similarly, inserting a new key requires probing until an empty slot is found. Therefore, the time complexity of an unsuccessful search is identical to the time complexity of an insertion.

> [!IMPORTANT]
> **Theorem:**
> In an open-address hash table with load factor $\alpha < 1$, the expected number of probes in an unsuccessful search is at most:
> $$\frac{1}{1 - \alpha}$$

#### Successful Search
A successful search is structurally different. The algorithm does not need to find an empty slot; it terminates the moment it encounters the target key.

> [!IMPORTANT]
> **Theorem**: 
> In an open-address hash table with load factor $\alpha < 1$, the expected number of probes in a successful search is at most:
> $$\frac{1}{\alpha} \ln \frac{1}{1 - \alpha}$$