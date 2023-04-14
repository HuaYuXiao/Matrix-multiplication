# Matrix-multiplication
SUSTech CS205

implement matrix multiplication in C and try your best to improve its speed. The project is an
improvement of Project 3. You can reuse the source code in Project 3, but should present your
improvements and different parts in the report.

## Requirements

1. Implement a function `matmul_plain()` in a straightforward way using several loops as the
benchmark.

2. Implement a function `matmul_improved()` using SIMD, OpenMP and other technologies to
improve the speed. You can compare it with matmul_plain().

3. Test the performance using 16x16, 128x128, 1Kx1K, 8Kx8K and 64Kx64K matrices. You can
generate some matrics with random values to test your function.

不难发现，当数组⻓度超过⼀定限度之后，会发⽣segmentation fault的错误。查阅⼀番资料后，我决定在数组创建时候，加⼊static前缀，这样就能将数组存储在data segment中，⽽⾮stack中。这⼆者的区别就在于，data segment的空间⽐stack⼤得多，因此能存储下更⼤的数组。但同样会带来⼀个问题，nSize是由⽤户指定的，在创建可变⻓度数组时，不可以使⽤static，所以我不得不将数组的可变⻓改为定⻓。

### plain

```bash
(base) hyx13701490089@huayuxiaodeMacBook-Pro plain % gcc final.c
(base) hyx13701490089@huayuxiaodeMacBook-Pro plain % ./a.out
plain,nSize=16,time=0ms
plain,nSize=128,time=7ms
plain,nSize=1000,time=3s
plain,nSize=8000,time=53m4s
# nSize=64K时，计算时间超级超级⻓，就没有记录了
```

### unloop
```bash
(base) hyx13701490089@huayuxiaodeMacBook-Pro unloop % gcc final.c -o3
(base) hyx13701490089@huayuxiaodeMacBook-Pro unloop % ./3
unloop,nSize=16,time=0ms
unloop,nSize=128,time=25ms
unloop,nSize=1000,time=6s
unloop,nSize=8000,time=35m47s
```

### neon
```bash
(base) hyx13701490089@huayuxiaodeMacBook-Pro neon % gcc final.c -o3
(base) hyx13701490089@huayuxiaodeMacBook-Pro neon % ./3
neon,nSize=16,time=0ms
neon,nSize=128,time=0ms
neon,nSize=1000,time=0ms
neon,nSize=8000,time=0ms
```

我就实话和⽼师说吧，这个neon的程序是有问题的，按照程序的意思，是只算了矩阵数乘，所以结果会全0。它应该是这样的：A,B,C分别对应前矩阵的⼀⾏，后矩阵的⼀列，输出结果。这三者只是⼤矩阵的⼀个部分，但我把它写成了全部，这就导致了在计算时，只算了两个⼀维矩阵的乘法，⽽⾮⼆维矩阵的乘法。但我来不及写完了，所以有些遗憾。

### openmp
```bash
(base) hyx13701490089@huayuxiaodeMacBook-Pro openmp % gcc final.c -o3
(base) hyx13701490089@huayuxiaodeMacBook-Pro openmp % ./3
openmp,nSize=16,time=0ms
openmp,nSize=128,time=7ms
openmp,nSize=1000,time=3s
openmp,nSize=8000,time=53m4s
```

4. Compare your implementation with the matrix multiplication in OpenBLAS
(https://www.openblas.net/). The results by your implementation should be the same or very
similar with those by OpenBLAS. Can your implementation be as fast as OpenBLAS?

5. Test your program on X86 and ARM platforms, and describe the differences.
