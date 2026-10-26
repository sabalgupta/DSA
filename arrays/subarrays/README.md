# Subarrays

A **subarray** is a **contiguous** (unbroken) part of an array. Subarrays appear in many LeetCode and competitive programming problems, such as maximum sum, sum equal to `k`, longest or shortest valid segment, and counting segments. This README covers what subarrays are, how to enumerate them, and how to find the **maximum subarray sum** using three approaches of increasing efficiency, ending with **Kadane's Algorithm**.

---

## Table of Contents

- [Folder Structure](#folder-structure)
- [Core Concepts](#core-concepts)
- [Printing All Subarrays](#printing-all-subarrays)
- [Maximum Subarray Sum](#maximum-subarray-sum)
- [Operations and Complexity Summary](#operations-and-complexity-summary)
- [Problem-Solving Approach](#problem-solving-approach)
- [Edge Cases and Common Mistakes](#edge-cases-and-common-mistakes)
- [Key Takeaways](#key-takeaways)

---

## Folder Structure

```
print_sub_array.cpp
max_sub_arrays/
├── 1_bruteforce.cpp
├── 2_optimized.cpp
└── 3_kadanes_algo.cpp
```

| File | Purpose | Time Complexity |
|------|---------|-----------------|
| `print_sub_array.cpp` | Prints all subarrays using brute force | O(n³) |
| `max_sub_arrays/1_bruteforce.cpp` | Maximum subarray sum, brute force | O(n³) |
| `max_sub_arrays/2_optimized.cpp` | Maximum subarray sum, optimized | O(n²) |
| `max_sub_arrays/3_kadanes_algo.cpp` | Maximum subarray sum using Kadane's Algorithm | O(n) |

The files in `max_sub_arrays/` are numbered so you can read them in order and see how the solution improves from O(n³) to O(n²) to O(n).

---

## Core Concepts

### What Is a Subarray?

A subarray is a sequence of elements that:

- come from the original array,
- are **next to each other** (no gaps),
- keep the **original order**.

For the array `[1, 2, 3]`, the non-empty subarrays are:

```
[1]  [2]  [3]  [1, 2]  [2, 3]  [1, 2, 3]
```

`[1, 3]` is **not** a subarray because `2` is skipped.

### Subarray vs Subsequence vs Subset

| Term | Contiguous? | Order kept? | Count for array of size `n` |
|------|-------------|-------------|-----------------------------|
| **Subarray** | Yes | Yes | n(n + 1) / 2 (non-empty) |
| **Subsequence** | No | Yes | 2ⁿ (including empty) |
| **Subset** | No | Not required | 2ⁿ (including empty) |

Many beginners mix these up. If a problem says "subarray", **the elements must be adjacent**.

### Defining a Subarray

Every subarray is fully described by two indices:

- `start` (`i`): index of the first element
- `end` (`j`): index of the last element

with `0 ≤ i ≤ j ≤ n - 1`. Its **length** is `j - i + 1`.

### Counting Subarrays

- For each start index `i`, the end index `j` can be any of `i, i+1, ..., n-1`, which gives `n - i` choices.
- Total = n + (n−1) + ... + 1 = **n(n + 1) / 2**, which is O(n²).

This is the key fact behind all the complexities below: there are **O(n²) subarrays**, and doing O(n) work on each one costs O(n³).

### Subarray Sum

The **sum** of a subarray is the total of its elements. Most subarray problems ask you to compute, compare, or count sums over many subarrays efficiently.

---

## Printing All Subarrays

**File:** `print_sub_array.cpp` (brute force, O(n³))

### Approach

1. Pick every possible **start** index `i` from `0` to `n - 1`.
2. For each `i`, pick every possible **end** index `j` from `i` to `n - 1`.
3. For each pair `(i, j)`, print the elements from index `i` to index `j`.

### Why O(n³)?

- Two loops choose `(i, j)`, giving O(n²) subarrays.
- Printing one subarray takes up to O(n) time.
- Total: O(n²) × O(n) = **O(n³)**.

The exact total number of elements printed is n(n + 1)(n + 2) / 6, which grows as n³. Since the **output itself** has this size, printing all subarrays **cannot be done faster than O(n³)**. This is different from the maximum-sum problem below, where we only need one number and can do much better.

### Space Complexity

O(1) extra space (no additional data structures are needed beyond the loop variables).

---

## Maximum Subarray Sum

**Problem:** Given an array of integers (which may include negative numbers), find the **largest sum** among all non-empty subarrays.

**Example:** `[-2, 1, -3, 4, -1, 2, 1, -5, 4]` → answer is **6**, from the subarray `[4, -1, 2, 1]`.

The folder `max_sub_arrays/` contains three solutions of increasing efficiency.

### Approach 1: Brute Force

**File:** `max_sub_arrays/1_bruteforce.cpp`

**Idea:** Check every subarray, compute its sum from scratch, and keep the largest.

1. Loop over every start index `i`.
2. Loop over every end index `j ≥ i`.
3. Add up all elements from `i` to `j` (a third loop).
4. Update the answer if this sum is larger.

| Metric | Value |
|--------|-------|
| Time | **O(n³)** |
| Space | O(1) |

**Why it is slow:** The sum of `[i..j]` is recomputed from scratch each time, even though it overlaps heavily with the previous subarray's sum.

### Approach 2: Optimized (O(n²))

**File:** `max_sub_arrays/2_optimized.cpp`

**Idea:** Avoid recomputing the sum. The sum of `[i..j]` is the sum of `[i..j-1]` **plus** the element at `j`. So, for a fixed start `i`, keep a **running sum** as `j` moves right.

A common alternative that reaches the same O(n²) bound is **prefix sums**: precompute `prefix[k]` as the sum of the first `k` elements, then the sum of `[i..j]` is `prefix[j+1] - prefix[i]` in O(1).

Both methods remove the innermost loop.

| Metric | Running sum | Prefix sums |
|--------|-------------|-------------|
| Time | **O(n²)** | O(n²) (O(n) to build, O(n²) to check all pairs) |
| Space | O(1) | O(n) |

**Takeaway:** If a problem needs the sum of many subarrays, reuse previous work instead of recomputing.

### Approach 3: Kadane's Algorithm

**File:** `max_sub_arrays/3_kadanes_algo.cpp`

**Idea:** Scan the array once. At each index, decide the best subarray **ending exactly at that index**.

Define:

- `current` = the best (maximum) sum of a subarray that **ends at the current index**.
- `best` = the best sum seen so far across all indices.

At each element `x`:

- **Extend** the previous subarray: `current + x`, or
- **Start fresh** from this element: `x`.

So: **`current = max(x, current + x)`**, then **`best = max(best, current)`**.

Equivalent view: if `current` becomes negative, it can only hurt future sums, so **drop it and start a new subarray** at the next element.

#### Dry Run

Array: `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`

| Index | x | current = max(x, current + x) | best |
|-------|----|-------------------------------|------|
| 0 | -2 | -2 | -2 |
| 1 | 1 | 1 | 1 |
| 2 | -3 | -2 | 1 |
| 3 | 4 | 4 | 4 |
| 4 | -1 | 3 | 4 |
| 5 | 2 | 5 | 5 |
| 6 | 1 | 6 | **6** |
| 7 | -5 | 1 | 6 |
| 8 | 4 | 5 | 6 |

Answer: **6**.

| Metric | Value |
|--------|-------|
| Time | **O(n)** (one pass) |
| Space | **O(1)** |

#### Why Kadane's Algorithm Is Correct

Any maximum subarray ends at some index. For that index, the best subarray ending there either contains only the element itself or extends the best subarray ending at the previous index. Taking the maximum over all ending indices therefore covers every candidate.

#### Initialization (Important)

- Initialize `current` and `best` with the **first element**, **not** `0`.
- Initializing `best` to `0` is wrong when **all elements are negative** (it would wrongly return `0`, which corresponds to an empty subarray).
- If your problem allows an **empty subarray**, then `0` is a valid starting answer and the minimum result is `0`.

---

## Operations and Complexity Summary

Let `n` be the array size.

| Task | Method | Time | Extra Space |
|------|--------|------|-------------|
| Print all subarrays | Nested loops + print | O(n³) | O(1) |
| Count all non-empty subarrays | Formula n(n + 1) / 2 | O(1) | O(1) |
| Max subarray sum | Brute force | O(n³) | O(1) |
| Max subarray sum | Running sum / prefix sum | O(n²) | O(1) / O(n) |
| Max subarray sum | **Kadane's Algorithm** | **O(n)** | **O(1)** |

**Practical meaning:** For `n = 10⁵`, O(n²) means about 10¹⁰ operations (too slow for typical time limits), while O(n) means about 10⁵ operations (instant). Common contest limits allow roughly 10⁸ simple operations per second, so:

| Constraint on `n` | Feasible approach |
|-------------------|-------------------|
| n ≤ ~200 | O(n³) |
| n ≤ ~5,000 | O(n²) |
| n ≥ 10⁵ | O(n) or O(n log n) |

---

## Problem-Solving Approach

### How to Recognize a Subarray Problem

Look for keywords such as:

- "contiguous", "consecutive", "segment", "subarray", "window", "substring" (for strings)
- "maximum / minimum sum of a contiguous part"
- "longest / shortest segment such that ..."
- "number of subarrays with ..."

### Choosing a Technique

| Problem Type | Technique to Consider |
|--------------|-----------------------|
| Maximum / minimum subarray sum | **Kadane's Algorithm** |
| Many range-sum queries | **Prefix sums** (O(1) per query after O(n) setup) |
| Fixed-size subarray (e.g., size `k`) | **Sliding window** |
| Longest / shortest subarray with a condition, **all elements non-negative** | **Sliding window / two pointers** |
| Subarray sum equals `k`, **array may contain negatives** | **Prefix sums + hash map** |
| Maximum subarray product | Track both the maximum and minimum product ending at each index (a negative number can flip them) |
| Subarray on a circular array | Combine Kadane's (max) with total sum minus min subarray |
| Small `n` or need to list every subarray | Brute force with nested loops |

### Useful Observations

- A subarray is defined by `(start, end)`. Many solutions enumerate one endpoint and handle the other efficiently.
- **Reuse computations:** extending a subarray by one element changes its sum by exactly that element.
- **Prefix-sum identity:** sum of `[i..j]` = `prefix[j+1] - prefix[i]`.
- **Kadane's rule:** a negative running sum is never worth keeping when extending to the right.
- Sliding window works for sum conditions **only when elements are non-negative**. With negative numbers, shrinking or growing the window no longer changes the sum in a predictable direction.

### Getting the Subarray Itself (Not Just the Sum)

To also return the indices of the best subarray in Kadane's Algorithm:

- Track a temporary `start` index that resets to the current index whenever you start fresh (i.e., when the element alone is better than extending).
- Whenever `best` improves, record `start` as the answer's start and the current index as its end.

---

## Edge Cases and Common Mistakes

**Edge cases**

- **All negative numbers:** the answer is the **largest (least negative) single element**, not `0`.
- **Single element:** the only subarray is the element itself.
- **All positive numbers:** the whole array is the answer.
- **Array with zeros:** zeros are fine, but be careful if the problem asks for the longest or shortest subarray, since zeros can extend length without changing the sum.
- **Empty array:** check the problem statement for expected behavior.
- **Multiple subarrays with the same maximum sum:** check whether the problem wants the first, the longest, or any.

**Common mistakes**

- Initializing the maximum to `0` instead of the first element (or `INT_MIN`) when the empty subarray is not allowed.
- **Integer overflow:** sums of many large values can exceed the 32-bit range. Use a 64-bit type for sums when `n` or element values are large.
- Initializing the answer to a value that is not small enough (e.g., a too-small sentinel like `-1000`), when elements can be very negative.
- Confusing subarray (contiguous) with subsequence (not contiguous).
- Using sliding window when the array contains negative numbers.
- Off-by-one errors in loop bounds (`j` should run from `i` to `n - 1`) and in the prefix-sum formula (`prefix[j+1] - prefix[i]`).
- Forgetting that the total number of subarrays is O(n²), so printing all of them is inherently O(n³).

---

## Key Takeaways

- A subarray is **contiguous**; an array of size `n` has **n(n + 1) / 2** non-empty subarrays.
- Printing all subarrays is O(n³), and that cannot be improved because the output itself is that large.
- Max subarray sum has three levels of solution:
  1. **Brute force:** O(n³), recompute every sum.
  2. **Optimized:** O(n²), reuse the running sum or use prefix sums.
  3. **Kadane's Algorithm:** O(n) time, O(1) space.
- **Kadane's rule:** `current = max(x, current + x)`, `best = max(best, current)`.
- Always handle the **all-negative** case by initializing with the first element.
- Use a 64-bit integer type when sums can be large.

### Quick Reference

| Question | Answer |
|----------|--------|
| Number of non-empty subarrays? | n(n + 1) / 2 |
| Sum of `[i..j]` using prefix sums? | `prefix[j+1] - prefix[i]` |
| Fastest max subarray sum? | Kadane's Algorithm, O(n) |
| Max subarray sum, all elements negative? | The largest single element |
| Subarray sum equals `k` with negatives? | Prefix sums + hash map |
| Fixed-size window? | Sliding window |