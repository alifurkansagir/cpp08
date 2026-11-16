# CPP Module 08

C++98 container, iterator and algorithm exercises, checked against subject version 10.1.

## Build and run

```sh
make
make test
make fclean
```

Each exercise also supports `all`, `test`, `clean`, `fclean` and `re` independently.
Compilation uses `c++ -Wall -Wextra -Werror -std=c++98`.
The tests use `assert`; compile without `-DNDEBUG` to keep the checks active.

## Implementation

- **ex00:** `easyfind` uses `std::find` and returns the first matching iterator.
  Mutable and const containers are supported. A missing value throws `std::runtime_error`.
- **ex01:** `Span` stores at most N integers. Span queries require at least two values.
  `shortestSpan` sorts a copy, preserving insertion order; `longestSpan` uses min/max algorithms.
  Distances use unsigned arithmetic to cover the complete `int` range without signed overflow,
  including systems with 32-bit `long`.
- **ex02:** `MutantStack` inherits the stack interface and exposes the protected container's
  forward, const and reverse iterators. The default container is `std::deque`.

## Range insertion

`Span::addRange(first, last)` reads the half-open iterator range once into a temporary vector.
This supports single-pass iterators such as `std::istream_iterator` as well as vector/list iterators.
An oversized range throws `Span::FullException` without changing the stored numbers.
Reading a stream still consumes its input, including when insertion fails; the stream cannot be rolled back.
Empty ranges are accepted, even when the Span is full or has zero capacity.
The range must be valid. Temporary storage is proportional to the number of accepted input values.
Copy assignment stages a new vector before changing the existing capacity and contents.

## Checks

- easyfind: first occurrence, negatives, const lookup, missing/empty containers, iterator mutation.
- Span: the subject's 2/14 example, zero capacity, empty/single-element query exceptions,
  stream insertion, range overflow without partial updates, empty ranges, duplicates,
  INT_MIN/INT_MAX, copy independence and assignment, deterministic 10,000-element checks,
  plus the original 100,000-element random demonstration.
- MutantStack: matching list traversal, empty ranges, mutable and const iteration,
  reverse traversal, copy independence, assignment, stack conversion and alternative containers.

