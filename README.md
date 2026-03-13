# PulseField™

[![PulseField™](https://repository-images.githubusercontent.com/1141499400/0d3ae64a-3add-467b-9471-bc1a8ddea02b)](https://github.com/ghostproxies/pulsefield)

## Table of Contents

- [Introduction](README.md?tab=readme-ov-file#introduction)
- [Author](README.md?tab=readme-ov-file#author)
- [License](README.md?tab=readme-ov-file#license)
- [Reference](README.md?tab=readme-ov-file#reference)
- [Enterprise](README.md?tab=readme-ov-file#enterprise)

## Introduction

PulseField™ is the algorithm for parallel PRNG sequence segmentation.

It enables independent parallel sequences for efficient PRNGs (such as [BlastCircuit™](https://github.com/ghostproxies/blastcircuit) and [FlurryGate™](https://github.com/ghostproxies/flurrygate)).

Furthermore, it has reversibility, [simple implementation](README.md?tab=readme-ov-file#reference) and no vendor-specific SIMD.

## Author

PulseField™ was created by [William Stafford Parsons](https://github.com/williamstaffordparsons) as a product of [GhostProxies](https://ghostproxies.com).

## License

PulseField™ is licensed with the [BSD-3-Clause](LICENSE) license.

## Reference

The following pseudocode demonstrates PulseField™ with procedures that are simple to port to a majority of programming languages.

``` c
a = ROTATE_LEFT(a, CIRCULAR_SHIFT) ^ b;
b += INCREMENT;
```

Both `a` and `b` must have a matching bits length of `BITS_LENGTH` (or `ⁿ`) as a power of 2 that's a supported data type length greater than or equal to `8`.

Each instance within a set of parallel PRNG instances that use PulseField™ must seed `a` with a number that's unique among the set of parallel instances and must seed `b` with a number that's consistent among the set of parallel instances.

PulseField™ can generate up to 2ⁿ parallel instances that each avoid full state collisions (for at least 2ⁿ output results) among the set of parallel instances.

For example, the following PulseField™ seed values are valid for a set of 3 parallel PRNG instances.

```
a: 0
b: 0

a: 1
b: 0

a: 2
b: 0
```

`CIRCULAR_SHIFT` must be a number greater than `0` and less than `BITS_LENGTH`.

`INCREMENT` must be an odd number greater than `0` and less than `2ⁿ`.

Assigning either `a` or `b` a value (outside of PulseField™) may void the aforementioned parallelism properties.

Depending on the specific PRNG implementation requirements, `a` should either be output directly or mixed into additional state (excluding `b`) that affects the output.

`b` must be a Weyl sequence (or a counter) that wraps around `BITS_LENGTH` bits (as demonstrated in [pulsefield.c](pulsefield.c) when `BITS_LENGTH` is `8` and the `stdint.h` header defines an 8-bit, unsigned integral type for `uint8_t`).

## Enterprise

GhostProxies provides the following enterprise solutions for RNG system efficiency.

- [Nightmare℠](https://ghostproxies.com/nightmare) is the RNG system efficiency enhancement service.
- [Tome™](https://ghostproxies.com/tome) is a multi-level SLA for GhostProxies products.
- [Ectoplasm™](https://ghostproxies.com/ectoplasm) is the entropy schema that generates entropy bits efficiently.
