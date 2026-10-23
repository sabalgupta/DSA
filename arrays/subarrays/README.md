# Subarrays

A **subarray** is a **contiguous** part of an array. It is one of the most common building blocks in DSA problems: sums, counts, longest or shortest windows, and maximum or minimum values are all questions about subarrays.

---

## Table of Contents

- [Topic Overview](#topic-overview)
- [Folder Structure](#folder-structure)
- [Core Concepts](#core-concepts)
- [Operations and Complexity](#operations-and-complexity)
- [Problem-Solving Approach](#problem-solving-approach)
- [Key Takeaways](#key-takeaways)

---

## Topic Overview

### What is a subarray?

A subarray is a sequence of elements that:

1. comes from the original array, and
2. sits in **consecutive positions**, with no gaps and the original order preserved.

A subarray is fully described by two indices: a **start index** `i` and an **end index** `j` where `0 <= i <= j < n`.

**Example:** for `arr = [1, 2, 3]`, the subarrays are:

| Start | End | Subarray    |
|:-----:|:---:|-------------|
| 0     | 0   | `[1]`       |
| 0     | 1   | `[1, 2]`    |
| 0     | 2   | `[1, 2, 3]` |
| 1     | 1   | `[2]`       |
| 1     | 2   | `[2, 3]`    |
| 2     | 2   | `[3]`       |

`[1, 3]` is **not** a subarray because index 1 is skipped.

### Why it matters

- Many problems ask for the "best" contiguous segment: maximum sum, longest with a property, shortest with a property, count of segments with a property.
- Understanding subarrays leads directly to **prefix sums**, **sliding window**, **two pointers**, and **Kadane's algorithm**.
- The brute-force-to-optimized progression here (`O(n^3)` to `O(n^2)` to better) is a pattern you will repeat in many other topics.

### Main problems it helps solve

- Generating or printing all subarrays.
- Finding the subarray with the maximum (or minimum) sum.
- Counting subarrays that satisfy a condition (for example, sum equals `k`).
- Finding the longest or shortest subarray satisfying a condition.

---

## Folder Structure

```text
print_sub_array.cpp
max_sub_arrays/
├── 1_bruteforce.cpp
└── 2_optimized.cpp
```

| Path                            | Purpose                                                      | Time Complexity |
|---------------------------------|--------------------------------------------------------------|:---------------:|
| `print_sub_array.cpp`           | Prints all subarrays using brute force                       | `O(n^3)`        |
| `max_sub_arrays/1_bruteforce.cpp` | Maximum subarray problem, brute-force approach             | `O(n^3)`        |
| `max_sub_arrays/2_optimized.cpp`  | Maximum subarray problem, optimized approach               | `O(n^2)`        |

The `max_sub_arrays/` folder is numbered to show the learning order: start with the simplest correct solution, then improve it.

---

## Core Concepts

### 1. Subarray vs. Subsequence vs. Subset

These three terms are often confused.

| Term            | Contiguous? | Order preserved? | Example from `[1, 2, 3]` |
|-----------------|:-----------:|:----------------:|--------------------------|
| **Subarray**    | Yes         | Yes              | `[2, 3]`                 |
| **Subsequence** | No          | Yes              | `[1, 3]`                 |
| **Subset**      | No          | Not required     | `{3, 1}`                 |

**Rule:** every subarray is a subsequence, but not every subsequence is a subarray.

### 2. How many subarrays does an array have?

For an array of size `n`:

- Subarrays of length 1: `n`
- Subarrays of length 2: `n - 1`
- ...
- Subarrays of length `n`: `1`

Total = `n + (n-1) + ... + 1` = **`n(n + 1) / 2`**, which is `O(n^2)`.

| `n` | Number of subarrays |
|:---:|:-------------------:|
| 3   | 6                   |
| 5   | 15                  |
| 10  | 55                  |
| 1000 | 500,500            |

**Why this matters:** any algorithm that looks at every subarray *individually* is at least `O(n^2)`. To go faster, you must avoid examining every subarray.

### 3. Identifying a subarray with two indices

Every subarray corresponds to one pair `(i, j)` with `i <= j`.

- Outer loop picks the **start** `i`.
- Inner loop picks the **end** `j`.
- The elements from `i` to `j` (inclusive) form the subarray.

This `(start, end)` view is the foundation of both files in this folder.

### 4. Length of a subarray

The length of the subarray from `i` to `j` (inclusive) is **`j - i + 1`**. Off-by-one mistakes here are very common.

### 5. Empty subarray

Some problems allow an empty subarray (sum `0`), others require at least one element. **Always check the problem statement.** This changes the answer when all elements are negative (see [Edge Cases](#edge-cases)).

---

## Operations and Complexity

### 1. Printing all subarrays (`print_sub_array.cpp`)

**Idea:** use three nested loops.

1. Outer loop: choose the start index `i`.
2. Middle loop: choose the end index `j`.
3. Inner loop: print every element from `i` to `j`.

**Complexity:**

| Measure | Value    | Reason                                                              |
|---------|----------|---------------------------------------------------------------------|
| Time    | `O(n^3)` | `O(n^2)` subarrays, and printing each one costs up to `O(n)`        |
| Space   | `O(1)`   | No extra storage beyond loop variables (output not counted)         |

**Important:** the total number of elements printed across all subarrays is `n(n+1)(n+2)/6`, which is `Θ(n^3)`. So **`O(n^3)` is unavoidable when you must print every subarray**. There is no faster way, because the output itself is that large. Optimization only helps when you need a *computed answer* (like a maximum) instead of the full output.

### 2. Maximum subarray sum

**Problem:** given an array of integers (possibly negative), find the largest sum of any non-empty subarray.

#### Approach 1: Brute force (`max_sub_arrays/1_bruteforce.cpp`)

**Idea:** for every pair `(i, j)`, compute the sum of elements from `i` to `j` with a separate loop, and keep the maximum.

| Measure | Value    | Reason                                                  |
|---------|----------|---------------------------------------------------------|
| Time    | `O(n^3)` | `O(n^2)` subarrays, each sum takes up to `O(n)`         |
| Space   | `O(1)`   |                                                         |

**Weakness:** the sum of `[i..j]` is recomputed from scratch every time, even though it overlaps heavily with the previous sum.

#### Approach 2: Optimized (`max_sub_arrays/2_optimized.cpp`)

**Key observation:** the sum of `[i..j]` equals the sum of `[i..j-1]` plus `arr[j]`. There is no need to re-add everything.

So for a fixed start `i`, extend the end `j` one step at a time and **update a running sum in `O(1)`**. (An equivalent way to get `O(1)` range sums is **prefix sums**.)

| Measure | Value    | Reason                                                  |
|---------|----------|---------------------------------------------------------|
| Time    | `O(n^2)` | `O(n^2)` subarrays, each sum obtained in `O(1)`         |
| Space   | `O(1)`   | Running sum only (prefix sums would use `O(n)`)         |

#### Beyond this folder: Kadane's algorithm

> Not part of the current files, but it is the standard next step.

**Kadane's algorithm** solves maximum subarray sum in **`O(n)` time and `O(1)` space**. The idea: at each index, decide whether the best subarray ending here **extends the previous one** or **starts fresh** at this element. Use it whenever `n` is too large for `O(n^2)`.

### 3. Comparison

| Approach                    | Time     | Space  | Practical limit for `n` (about 1 second) |
|-----------------------------|:--------:|:------:|------------------------------------------|
| Brute force                 | `O(n^3)` | `O(1)` | up to roughly 300 to 500                 |
| Running sum / prefix sum    | `O(n^2)` | `O(1)` or `O(n)` | up to roughly 10^4              |
| Kadane's algorithm          | `O(n)`   | `O(1)` | 10^5, 10^6 and beyond                    |

The limits are rough rules of thumb based on about `10^8` simple operations per second.

---

## Problem-Solving Approach

### How to recognize a subarray problem

Look for these phrases:

- "contiguous", "consecutive", "segment", "subarray", "substring" (same idea for strings)
- "maximum / minimum sum of a contiguous part"
- "longest / shortest segment such that..."
- "number of subarrays with..."

If the problem says **subsequence** or **subset**, the elements do *not* need to be adjacent, so it is a different problem (usually DP or backtracking).

### Standard progression

1. **Write the brute force.** Loop over all `(i, j)` pairs and compute the answer for each. Confirm correctness first.
2. **Find repeated work.** Usually the sum or property of `[i..j]` can be built from `[i..j-1]`.
3. **Remove the repeated work.** Use a running sum or prefix sums to get `O(n^2)`.
4. **Remove a whole loop.** Ask whether you really need to try every start index. Techniques that do this:

| Situation                                          | Technique                                |
|----------------------------------------------------|------------------------------------------|
| Maximum subarray sum, negatives allowed            | Kadane's algorithm                       |
| Many range-sum queries                             | Prefix sums                              |
| All elements non-negative, window with sum condition | Sliding window / two pointers          |
| Count subarrays with sum exactly `k` (negatives allowed) | Prefix sums with a hash map        |

### Choosing an approach

- **Small `n` (about 500 or less):** brute force is acceptable and good for verifying other solutions.
- **Medium `n` (about 10^4):** `O(n^2)` is usually fine.
- **Large `n` (10^5 or more):** you need `O(n)` or `O(n log n)`.

Always read the constraints **before** choosing an approach.

### Edge Cases

- **Single element array:** the only subarray is the element itself.
- **All negative numbers:** the maximum subarray sum is the **largest (least negative) single element**, not `0`, unless an empty subarray is allowed. Initializing the maximum to `0` is a classic bug.
- **All positive numbers:** the whole array is the maximum subarray.
- **Zeros in the array:** they never reduce a sum, so check that tie-breaking rules (longest, shortest, first) match the problem.
- **Empty array:** check whether the input can be empty.

### Common Mistakes

| Mistake                                              | Fix                                                                 |
|------------------------------------------------------|---------------------------------------------------------------------|
| Confusing subarray with subsequence                  | Subarrays must be contiguous                                        |
| Off-by-one in loop bounds or length (`j - i + 1`)    | Use inclusive `i..j` consistently                                   |
| Initializing max to `0` or `INT_MIN` carelessly      | Initialize with the first element, or a safe minimum value          |
| Integer overflow in sums                             | Use a 64-bit type when `n * max(value)` can exceed about `2 * 10^9` |
| Resetting the running sum in the wrong place         | Reset it when the start index changes                               |
| Assuming `O(n^3)` printing can be optimized          | The output size itself is `Θ(n^3)`                                  |
| Using sliding window when negatives are present      | Sliding window on sums needs non-negative values                    |

### Related Topics

- Prefix sums
- Sliding window
- Two pointers
- Kadane's algorithm
- Dynamic programming (for subsequence problems)

---

## Key Takeaways

- A subarray is **contiguous**; a subsequence is not.
- An array of size `n` has **`n(n+1)/2`** subarrays.
- Every subarray is defined by a **start and end index** `(i, j)`.
- Printing all subarrays is **`Θ(n^3)`** because of output size and cannot be improved.
- Brute-force maximum subarray sum is `O(n^3)`. Reusing the previous sum brings it to **`O(n^2)`**.
- Kadane's algorithm brings it to **`O(n)`** and is the standard solution.
- Check for **all-negative arrays**, **overflow**, and whether an **empty subarray** is allowed.

### Quick Reference

| Task                                  | Time     | Space  | File / Technique                     |
|---------------------------------------|:--------:|:------:|--------------------------------------|
| Print all subarrays                   | `O(n^3)` | `O(1)` | `print_sub_array.cpp`                |
| Max subarray sum, brute force         | `O(n^3)` | `O(1)` | `max_sub_arrays/1_bruteforce.cpp`    |
| Max subarray sum, optimized           | `O(n^2)` | `O(1)` | `max_sub_arrays/2_optimized.cpp`     |
| Max subarray sum, best known approach | `O(n)`   | `O(1)` | Kadane's algorithm (not in folder)   |

### Checklist Before Submitting

- [ ] Did I confirm the elements must be contiguous?
- [ ] Did I check whether an empty subarray is allowed?
- [ ] Did I handle the all-negative case?
- [ ] Is my sum type large enough to avoid overflow?
- [ ] Does my time complexity fit the constraints?