# Data Compression

## Introduction

**Why data compression?**
- storage efficiency
- efficient usage of transmission bandwidth
- reduction of transmission time
- most files have lots of redundancy

There are two major families of compression techniques in terms of the **possibility of reconstructing the original source**. 
1. **Lossless Compression:**
- It is possible to exactly reconstruct the original data from the compressed version. 
- No loss of any information during the compression process. 
- Mostly applied to symbolic data such as character text, numeric data, computer source code and executable graphics and icons.
- Used when the original data are so important that we cannot afford to lose any details. For example, medical images, text and images preserved for legal reasons; some computer executable files, etc.
- Some lossless algorithms: run-length, Huffman, delta, LZW...
- Common Formats: ZIP, PNG, FLAC, GZIP.
2. **Lossy Compression:**
- It is not possible to reconstruct the original exactly from the compressed version. 
- There are some insignificant details that may get lost during the process of compression.
- Achieve much higher compression ratios by permanently discarding data that human senses (sight and hearing) aren’t very good at perceiving.
- Data such as multimedia images, video and audio are more easily compressed by lossy compression techniques.
- Common Formats: JPEG, MP3, MP4, WebM.

## Run Length Encoding (RLE)
- A simple lossless data compression technique.
- Works by looking at data that has repeating elements (a "run") and replacing that repetition with a single value and a count of how many times it repeats.
- **Examples**
    - **Text**: A sequence like `acccbbaaabb` could be transformed into the pairs `(a,1)`, `(c,3)`, `(b,2)`, `(a,3)`, `(b,2)`
    - Another variation might encode `KKKKKKKKK` as `r9K`, where `r` is a control indicator specifying a repeating symbol, `9` is the count, and `K` is the symbol
    - **Images**: Instead of writing out "red pixel, red pixel, red pixel..." hundreds of times for a solid background, the algorithm simply records the data as "279 red pixels"
- **Cons**: performs poorly if the data **lacks these consecutive repeating patterns**, such as in standard English text or computer executable code. In cases with many single, isolated symbols, the overhead of adding counts and control flags can actually expand the file size rather than compress it
- **Pros**: efficient for images, especially icons, line drawings, or binary images (black and white) where large blocks of the same color appear consecutively.

**Real-World Variations**
Because different types of data have different structural patterns, RLE has been adapted into several unique implementations:

- **Binary and Black-and-White Data (Fax Machines)**: When data consists of only two possible values (like `0`s and `1`s, or black and white pixels), the algorithm doesn't even need to record the symbol; it can just record the alternating counts. For example, the `ITU-T T4` standard for fax machines assumes every line begins with a white pixel. Thus, a pixel sequence of `bbbbwwbbbbb` is transmitted simply as the counts `1, 4, 2, 5` (1 dummy white pixel, 4 black, 2 white, 5 black).
- **PackBits**: Created for early Macintosh computers, this scheme uses an added sign bit to indicate if a sequence is a run. To encode the consecutive run 2, 2, 2, 2, it outputs the character 2 followed by -3 (where the negative number dictates the run length - absolute of the number + 1).
- **Hardware Data Compression (HDC)**: Historically used in IBM tape drives, HDC employs specific control characters to navigate between repeating sequences (e.g., an r6 command tells the system to repeat the next character 6 times) and non-repeating sequences (e.g., an n6 command tells the system that the next 6 characters are unique and should be read exactly as-is).
- **Handling Max Counts:** If a run of symbols is longer than the maximum count the algorithm's memory allows (for instance, an 8-bit count caps at 255), the algorithm can simply intersperse runs of length zero to reset the count and keep the alternating sequence going.
For example: 
    - `500` white + `3` black in 8-bit system. 
    - Data tokens written: `[255, 245, 3]`. Wrong! 
    - The fix: `[255, 0, 245, 3]` (put the dummy 0 to keep the alternating color correct).

## Lempel-Ziv-Welch (LZW)
- Dictionary-based lossless data compression algorithm.
- Serves as the foundation for GIF and TIFF images, the UNIX compress utility, and hardware devices like modems.
- Works by dynamically building a "string table" that maps symbol sequences to $N$-bit indices as it processes a message.
- The string table has $2^N$ entries and the transmitted code can be used at the decoder as an index into the string table to retrieve the corresponding original symbol sequence. 
- The talbe is built dynamically on the fly. The compressed file doesn't need to bundle a string table with it; the decoder reconstructs the exact same table step-by-step as it decompresses the data.

#### Encode
- Before the algorithm starts, the table is pre-loaded with all standard single characters (e.g., the standard ASCII table from $0$ to $255$). The other entries will be filled in as the message byte stream is processed.
- The algorithm tracks a running sequence (`STRING`) and processes the current input character (`SYMBOL`). 
    - If the combined sequence `STRING + SYMBOL` is already in the table (`TABLE`), it updates the history by absorbing the character: `STRING = STRING + SYMBOL`.
    - If `STRING + SYMBOL` is not in the dictionary, it means a boundary has been hit. 
        - The algorithm outputs the integer code for the known history (`STRING`).
        - memorizes the new sequence by adding `STRING + SYMBOL` to the `TABLE`. 
        - Resets the history to start fresh with the current character: `STRING = SYMBOL`.
- This process repeats until all the message bytes are consumed, at which point the encoder makes a final transmission of the $N$-bit code for the current sequence S.
```
initialize TABLE[0 to 255] = code for individual bytes
STRING = get input symbol
while there are still input symbols:
    SYMBOL = get input symbol
    if STRING + SYMBOL is in TABLE:
        STRING = STRING + SYMBOL
    else:
        output the code for STRING
        add STRING + SYMBOL to TABLE
        STRING = SYMBOL
output the code for STRING
```
**LZW encoding of string “abcabcabcabcabcabcabcabcabcabcabcabc”**
<img src='/dataCompression/images/LZW-encoder.png' width=500 alt='LZW encoder for string“abcabcabcabcabcabcabcabcabcabcabcabc”"'>

- The encoder algorithm is **greedy**-it is designed to find the longest possible match in the string table before it makes a transmission.
- LZW operates strictly on the fly with no foresight. It routinely wastes dictionary slots on "one-hit wonders"—patterns that happen once but never repeat. While a look-ahead encoder would be tighter, LZW trades perfect mathematical efficiency for a fast, single-pass workflow.
- Compression accelerates the deeper we go into a file. It starts inefficiently, spending codes to learn simple 2-character pairs. But as entries stack on top of each other, the history window grows exponentially. By the end, a single integer code can swallow an entire long sentence at once.
- Real-world data often switches topics mid-file. If the dictionary stayed frozen with the vocabulary of the first half, the second half would compress terribly. Wiping the table clean once it fills up acts as an architectural reset, allowing LZW to discard obsolete data and learn the fresh patterns of the new stream.

#### Decode
- Before the algorithm starts, the table is pre-loaded with all standard single characters (e.g., the standard ASCII table from $0$ to $255$). The other entries will be filled in as the incoming code stream is processed.
- The algorithm tracks a running sequence history (`STRING`) and processes the current input code (`CODE`) to resolve the matching phrase (`ENTRY`).
    - Initialize: Read the very first code into `CODE`. Look up `CODE` in the table (`TABLE`) to resolve the sequence, assign it to `STRING`, and output `STRING`.
    - Loop: While there are still codes to receive, read the next integer into `CODE` and evaluate the following:
        - If `TABLE[CODE]` is not defined, it means the encoder outpaced the decoder. The algorithm reconstructs the missing phrase using history: `ENTRY = STRING + STRING[0]`.
        - If `TABLE[CODE]` is already in the dictionary, it resolves the active phrase normally: `ENTRY = TABLE[CODE]`.
    - Post-Evaluation: 
        - The algorithm outputs the resolved sequence (`ENTRY`).
        - Memorizes the new sequence by adding the combined sequence `STRING + ENTRY[0]` to the `TABLE`.
        - Updates the running sequence history to start fresh with the current phrase: `STRING = ENTRY`.This process repeats until all the input codes are consumed, at which point the decompression is complete.
- This process repeats until all the input codes are consumed, at which point the decompression is complete.
```
initialize TABLE[0 to 255] = code for individual bytes
CODE = read next code from encoder
STRING = TABLE[CODE]
output STRING
while there are still codes to receive:
    CODE = read next code from encoder
    if TABLE[CODE] is not defined: // needed because sometimes the
        ENTRY = STRING + STRING[0] // decoder may not yet have entry
    else:
        ENTRY = TABLE[CODE]
    output ENTRY
    add STRING+ENTRY[0] to TABLE
    STRING = ENTRY
```
**LZW decoding of the sequence _a, b, c, 256, 258, 257, 259, 262, 261, 264, 260, 266, 263,c_**
<img src='/dataCompression/images/LZW-decoder.png' width=300 alt=' LZW decoding of the sequence a, b, c, 256, 258, 257, 259, 262, 261, 264, 260, 266, 263,c'>

## Huffman Codes
- Traditional text encodings, like ASCII, allocate a uniform fixed length (typically eight bits) to every character, treating a rare letter like "Z" with the exact same data weight as a highly frequent letter like "E" **(fixed-length code)**
- A **variable-length** code can do considerably better than a fixed-length code: give frequent characters short codewords and infrequent characters long codewords.
- Usefull when we know symbols' probabilities of occurrence in the messages to be encoded. 
- The encoder creates the Huffman tree and sends the codes together with either the frequency table or the tree structure to the decoder.

### Prefix-free codes
- **Prefix-free code**: codes in which no codeword is also a prefix of some other codeword. 
- It can be decoded **instantaneously**. As you read a stream of bits from left to right, the moment we match a valid codeword, we can immediately decode it without needing to look ahead at future bits (no ambiguity).
-  A prefix-free code can always achieve the optimal data compression among
any character code.
- We use a binary tree (not a BST) to represent the prefix code.
- Interpret the binary codeword for a character as the simple path from the root to that character, where $0$ means "go to the left child" and $1$ means "go to the right child".

**Example**: Each leaf is labeled with a character and its frequency of occurrence. Each internal node is labeled with the sum of the frequencies of the leaves in its subtree. All frequencies are in thousands. 

(a) The tree corresponding to the fixed-length code $a = 000, b = 001, c = 010, d = 011, e = 100, f = 101$.

(b) The tree corresponding to the optimal prefix-free code $a = 0, b = 101, c = 100, d = 111, e = 1101, f = 1100$. Higher frequency $\Rightarrow$ shorter path and vice versa.

<img src='/dataCompression/images/huffmanTree.png' width = 700 alt=Huffman Tree>

- An optimal code: a **full binary tree**.

$\Rightarrow$ $C$ leaves (characters encoded) and $C-1$ internal nodes.

- Given a tree $T$ corresponding to a prefix-free code. For each character $c$ in the alphabet $C$, let the attribute $c.freq$ denote the frequency of $c$, and let $d_T(c)$ denote the depth of $c$’s leaf in the tree ($=$ the length of the codeword for
character $c$) . 
The cost of the tree $T$ = The number of bits required to encode a file:
$$B(T) = \sum_{c \in C} c.freq\cdot d_T(c)$$

### Constructing a Huffman code
- To construct an optimal prefix code, Huffman's Algorithm uses a greedy, bottom-up approach. It builds a binary tree by repeatedly combining the two lowest-probability symbols until only one tree remains.

**Core Logic:**
- Let $C$ be a set of $n$ characters, where each character $c \in C$ has a defined frequency (or probability) $f[c]$.
- The algorithm uses a Min-Priority Queue ($Q$) to track the nodes, keyed by their frequencies.
    - Leaves: Every character starts as a leaf node.
    - Internal Nodes: The algorithm pairs the two nodes with the lowest frequencies, creating a new parent node whose frequency is the sum of its children's frequencies.
    - Coding: Once the tree is complete, traversing left represents a $0$ bit, and traversing right represents a $1$ bit.

```
HUFFMAN(C)
    // Initialize a min-priority queue Q based on the frequency attribute
    Q = C
    BUILD_MIN_HEAP(Q)
    
    for each character c in C do
        allocate node z 
        z.freq = c.freq
        Insert(Q, z)
    
    // Iterate until only the root node remains
    while Size(Q) > 1 do
        // Extract the two nodes with the lowest frequencies
        x = ExtractMin(Q)
        y = ExtractMin(Q)
        
        // Create a new internal parent node
        allocate new node z
        z.left = z
        z.right = y
        z.freq = x.freq + y.freq
        
        // Insert the parent back into the queue
        Insert(Q, z)
    
    // The final remaining node is the root of the tree
    return ExtractMin(Q)
```
<img src='/dataCompression/images/buildingHuffmanTree.png' width= 800 alt='Building a Huffman Tree'>

> [!NOTE]
> **Time complexity**:
>
> Let $n$ be the size of $C$.
>
> Depends on how Min-queue $Q$ is implemented. If it is implemented as a min-heap, `BUILD_MIN_HEAP` takes $O(n)$ time.
>
> The `while` loop runs exactly $n-1$ times,  and since each heap operation runs in $O(\lg n)$ time, the loop contributes $O(n\lg n)$ to the running time.
>
> $\Rightarrow$ **Total running time** of `HUFFMAN` on a set of $n$ characters is $O(n\lg n)$.

### Correctness of Huffman’s algorithm

To prove that Huffman’s algorithm produces an optimal prefix code, we need to show that the tree it constructs minimizes the Weighted External Path Length (WEPL).

The WEPL represents the average number of bits per character and is defined as:

$$B(T) = \sum_{c \in C} f[c] \cdot d_T(c)$$

Where $f[c]$ is the frequency of character $c$, and $d_T(c)$ is its depth in the tree $T$ (the length of its code).

The proof relies on induction and is broken into two core parts: 
- **The Greedy Choice Property** (proving that combining the two lowest frequencies is a safe first move) 
- **Optimal Substructure** (proving that an optimal solution to the subproblem yields an optimal global solution).

#### Optimal prefix-free codes have the greedy-choice property

> [!IMPORTANT]
> **Lemma**: Let $C$ be an alphabet where every character $c \in C$ has a frequency $f[c]$. Let $x$ and $y$ be the two characters in $C$ with the absolute lowest frequencies. Then, there exists an optimal prefix tree $T$ for $C$ where $x$ and $y$ are sibling leaf nodes at the maximum depth of the tree ($x$ and $y$ have the same length and differ by one bit).

**Proof by Contradiction**
Suppose there is an optimal tree $T_{\text{opt}}$ where $x$ and $y$ are not sibling leaf nodes at the maximum depth.

Let $a$ and $b$ be two sibling leaf nodes that are at the maximum depth of $T_{\text{opt}}$.

Without loss of generality, assume the frequencies are ordered such that $f[x] \le f[y]$ and $f[a] \le f[b]$.

Since $x$ and $y$ are the two lowest frequencies in the entire alphabet, we know that $f[x] \le f[a]$ and $f[y] \le f[b]$.

Since $a$ and $b$ are at the deepest level, their depths are greater than or equal to the depths of $x$ and $y$:

$$d_{T_{\text{opt}}}(a) \ge d_{T_{\text{opt}}}(x) \quad \text{and} \quad d_{T_{\text{opt}}}(b) \ge d_{T_{\text{opt}}}(y)$$

Now, let's modify $T_{\text{opt}}$ by swapping $x$ with $a$ to create a new tree $T'$. Let's see how the cost changes:

$$B(T_{\text{opt}}) - B(T') = f[x]d(x) + f[a]d(a) - (f[x]d(a) + f[a]d(x))$$

$$B(T_{\text{opt}}) - B(T') = (f[a] - f[x])(d(a) - d(x))$$

Since $f[a] \ge f[x]$ and $d(a) \ge d(x)$, both terms are non-negative, meaning:

$$B(T_{\text{opt}}) - B(T') \ge 0 \implies B(T_{\text{opt}}) \ge B(T')$$

Next, swap $y$ with $b$ in $T'$ to create $T''$. By the same logic:

$$B(T') - B(T'') = (f[b] - f[y])(d(b) - d(y)) \ge 0 \implies B(T') \ge B(T'')$$

Combining these yields $B(T_{\text{opt}}) \ge B(T'')$. But $T_{\text{opt}}$ was already defined as optimal (the absolute minimum cost), so $B(T'')$ cannot be strictly less than $B(T_{\text{opt}})$. Therefore, $B(T_{\text{opt}}) = B(T'')$.

<img src='/dataCompression/images/greedyProof.png' width=700 alt='Proof of Greedy Property'>

This lemma implies that the process of building up an optimal tree by mergers can, without loss of generality, begin with the greedy choice of merging together those two characters of lowest frequency.  Of all possible mergers at each step, `HUFFMAN` chooses the one that incurs the least cost. $\blacksquare$

#### Optimal prefix-free codes have the optimal-substructure property

> [!IMPORTANT]
> **Lemma**: Let $C$ be an alphabet in which each character $c \in C$ has a frequency $f[c]$. Let $x$ and $y$ be the two characters in $C$ with the absolute lowest frequencies. Let $C'$ be the reduced alphabet obtained by removing $x$ and $y$ and replacing them with a new meta-character $z$, such that $C' = (C \setminus \{x, y\}) \cup \{z\}$, and assign it the frequency $f[z] = f[x] + f[y]$.If $T'$ is an optimal prefix tree representing an optimal prefix-free code for the alphabet $C'$, then the tree $T$ obtained by replacing the leaf node $z$ in $T'$ with an internal node having $x$ and $y$ as its child leaf nodes is an optimal prefix tree for the original alphabet $C$.

**The proof**
Let $T$ be a prefix tree for $C$ where $x$ and $y$ are sibling leaves sharing the parent node $z$. If we collapse $x$ and $y$ into $z$, we get a tree $T'$ for the reduced alphabet $C'$.

$$d_T(x) = d_T(y) = d_{T'}(z) + 1$$

Let's expand the cost equation for $B(T)$ by separating $x$ and $y$ from the rest of the alphabet:

```math
\begin{align*}
B(T) &= \sum_{c \in C \setminus \{x,y\}} f[c] \cdot d_T(c) + f[x]d_T(x) + f[y]d_T(y) \\

&= \sum_{c \in C \setminus \{x,y\}} f[c] \cdot d_{T'}(c) + f[x](d_{T'}(z) + 1) + f[y](d_{T'}(z) + 1) \\

&= \sum_{c \in C \setminus \{x,y\}} f[c] \cdot d_{T'}(c) + (f[x] + f[y])d_{T'}(z) + f[x] + f[y] \\

&= \left( \sum_{c \in C \setminus \{x,y\}} f[c] \cdot d_{T'}(c) + f[z]d_{T'}(z) \right) + f[x] + f[y] \\
&= B(T') + f[x] + f[y] \\
\end{align*}
```
Then, we have:
$$B(T)= B(T') + f[x] + f[y]$$
or, equivalently,
$$B(T')= B(T) - f[x] - f[y]$$

Now, we show that if $T'$ is optimal for $C'$, then $T$ must be optimal for $C$ by using contradiction.

Assume for contradiction that $T$ is not optimal for $C$. This implies there must exist some hypothetical alternative tree $W$ for the alphabet $C$ that achieves a strictly lower cost than $T$:

$$B(W) < B(T)$$

By the Greedy Choice Property, we can assume without loss of generality that $x$ and $y$ are sibling leaf nodes in $W$. 

Let's create a corresponding collapsed tree $W'$ for the alphabet $C'$ by replacing $x$ and $y$ with their parent node $z$.

The cost of $W'$ relates to $W$ by:

$$B(W') = B(W) - f[x] - f[y]$$

Now we manipulate our inequality. Start with our assumption:

$$B(W) < B(T)$$

Subtract the constant value $(f[x] + f[y])$ from both sides:

$$B(W) - f[x] - f[y] < B(T) - f[x] - f[y]$$

Substitute our structural identities ($B(W')$ for the left side, and $B(T')$ for the right side):$$B(W') < B(T')$$

This states that the tree $W'$ has a strictly lower cost for the alphabet $C'$ than the tree $T'$.

However, this contradicts our initial premise that $T'$ is an optimal prefix tree for $C'$. Because an optimal solution cannot be beaten, our assumption must be false.

Therefore, the tree $T$ constructed by expanding an optimal sub-tree $T'$ must be globally optimal for $C$. $\blacksquare$

#### Prove the correctness of `Huffman`
> [!IMPORTANT]
> Procedure `HUFFMAN` produces an optimal prefix-free code.

We prove that by mathematical induction on the alphabet size $n = |C|$, using two previously proved lemmas.

1. **Base Case** ($n = 2$)
An alphabet with two characters is structured as a root with two sibling leaves. Each character has a code length of $1$ bit. Since we cannot represent two unique symbols with fewer than $1$ bit each, this tree is trivially optimal.
2. **Inductive Hypothesis**
Assume the `HUFFMAN` procedure produces a completely optimal prefix tree for any alphabet of size $n - 1$.
- Inductive Step
    - Let $C$ be an alphabet of size $n$.
    - The algorithm greedily pairs the two lowest-frequency characters $x$ and $y$ under a parent node $z$, reducing the alphabet to $C'$ of size $n-1$.
    - By our Inductive Hypothesis, running the algorithm on $C'$ constructs a sub-tree $T'$ that is guaranteed to be optimal for $C'$.
    - The final tree $T$ is formed by expanding the leaf $z$ in $T'$ back out into leaves $x$ and $y$.

By the Optimal Substructure Lemma, because the sub-tree $T'$ is optimal, the resulting full tree $T$ is mathematically forced to be optimal for the global alphabet $C$.

By induction, Huffman's algorithm is globally correct for all finite alphabets. $\blacksquare$

> [!NOTE]
> - Huffman codes are optimal when restricted to instantaneous (prefix-free) codes and symbols are drawn independently from a fixed, known probability distribution. There are no other such codes with a shorter expected length.
> - Huffman coding can produce different encodings that all have the same expected length.

## Adaptive Huffman

