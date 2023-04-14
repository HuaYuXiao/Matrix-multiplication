# Matrix-multiplication
SUSTech CS205

implement matrix multiplication in C and try your best to improve its speed. The project is an
improvement of Project 3. You can reuse the source code in Project 3, but should present your
improvements and different parts in the report.

## Requirements

1. Implement a function matmul_plain() in a straightforward way using several loops as the
benchmark.

2. Implement a function matmul_improved() using SIMD, OpenMP and other technologies to
improve the speed. You can compare it with matmul_plain().

3. Test the performance using 16x16, 128x128, 1Kx1K, 8Kx8K and 64Kx64K matrices. You can
generate some matrics with random values to test your function.

4. Compare your implementation with the matrix multiplication in OpenBLAS
(https://www.openblas.net/). The results by your implementation should be the same or very
similar with those by OpenBLAS. Can your implementation be as fast as OpenBLAS?

5. Test your program on X86 and ARM platforms, and describe the differences.
