# ZoneSplit

[![ZoneSplit](https://repository-images.githubusercontent.com/1141499400/46eb6eba-e0ae-41b9-bb2e-0e24338d1ef1)](https://github.com/ghostproxies/zonesplit)

## Table of Contents

- [Introduction](README.md?tab=readme-ov-file#introduction)
- [Author](README.md?tab=readme-ov-file#author)
- [License](README.md?tab=readme-ov-file#license)
- [Period](README.md?tab=readme-ov-file#period)
- [Parallelism](README.md?tab=readme-ov-file#parallelism)
- [Reference](README.md?tab=readme-ov-file#reference)
- [Empirical Test Results](README.md?tab=readme-ov-file#empirical-test-results)
- [Speed](README.md?tab=readme-ov-file#speed)

## Introduction

ZoneSplit is an efficient algorithm for dividing parallel PRNG sequences.

It's intended to provide [parallelism guarantees](README.md?tab=readme-ov-file#parallelism) for PRNGs with the added benefit of a [minimum period](README.md?tab=readme-ov-file#period), the [fastest speed](README.md?tab=readme-ov-file#speed), [decent empirical test results](README.md?tab=readme-ov-file#empirical-test-results), reversibility, [simple implementation](README.md?tab=readme-ov-file#reference) and no vendor-specific SIMD.

It's implemented in [BlastCircuit](https://github.com/ghostproxies/blastcircuit), [StormDrop](https://github.com/ghostproxies/stormdrop) and [WaveDrift](https://github.com/ghostproxies/wavedrift).

## Author

ZoneSplit was created by [William Stafford Parsons](https://github.com/williamstaffordparsons) as a product of [GhostProxies](https://ghostproxies.com).

## License

ZoneSplit is licensed with the [BSD-3-Clause](LICENSE) license.

The default phrase `the copyright holder` in the 3rd clause is replaced with `GhostProxies`.

## Period

Instead of a full period that generates exactly 1 of each possible number predictably within a 2ⁿ space, ZoneSplit generates different seed-based deterministic sequences (of at least 2ⁿ numbers each) that have varying output number frequencies.

Varying number frequency distribution is a desirable property of a PRNG that deterministically mimics unpredictable true randomness where generating exactly 1 of each possible number within a 2ⁿ space is both anomalous and a predictability factor that increases as the remaining space within a full period sequence decreases.

The uniformity of output number frequency increases in the scope of every possible seeded ZoneSplit sequence, meaning it can eventually generate at least 1 of each possible number within a 2ⁿ space as an accumulation of multiple 2ⁿ sequences from different seeded states.

The 2ⁿ minimum period is proven by the mixed-in 2ⁿ equidistributed sequence.

ⁿ is defined as `BITS_LENGTH` in the [reference](README.md?tab=readme-ov-file#reference) section.

## Parallelism

ZoneSplit guarantees up to 2ⁿ parallel instances that each avoid collisions with other seeded states among the set of parallel instances for at least 2ⁿ output results.

ⁿ is defined as `BITS_LENGTH` in the [reference](README.md?tab=readme-ov-file#reference) section.

## Reference

The following code block demonstrates the ZoneSplit algorithm structure.

``` c
a = ROTATE_LEFT(a, SHIFT) ^ b;
b = (b + INCREMENT) % BITS_LENGTH;
```

Both `a` and `b` must have a matching bits length of `BITS_LENGTH` (or `ⁿ`) as a power of 2 that's a supported data type length greater than or equal to `8`.

Each instance within a set of parallel PRNG instances that use ZoneSplit must seed `a` with a number that's unique among the set of parallel instances and must seed `b` with a number that's consistent among the set of parallel instances.

`SHIFT` must be a number greater than `0` and less than `BITS_LENGTH`.

`INCREMENT` must be an odd number greater than `0` and less than `2ⁿ`.

`a` must either be mixed into additional state (excluding `b`) or returned.

Neither `a` nor `b` must be assigned a value outside of the aforementioned ZoneSplit algorithm.

[zonesplit.c](zonesplit.c) demonstrates the aforementioned [parallelism guarantee](README.md?tab=readme-ov-file#parallelism) when `BITS_LENGTH` is `8`.

Furthermore, small overlapping sequences of `a` escape quickly due to the [seed requirements](README.md?tab=readme-ov-file#reference) aligning to ensure occasional XOR rotation overlaps are XORed with the [2ⁿ equidistributed sequence](README.md?tab=readme-ov-file#period) at non-overlapping points.

## Empirical Test Results

ZoneSplit can add decent premixing in specific scenarios as proven by [StormDrop](https://github.com/ghostproxies/stormdrop), a non-cryptographic PRNG that's essentially a 64-bit ZoneSplit for 32-bit output.

## Speed

ZoneSplit is faster than `lcg` and `mcg` as proven by [StormDrop](https://github.com/ghostproxies/stormdrop).
