# MetaPi
Compile-Time Pi via Template Meta-Programming.
This library offers a C++11 template meta-programming implementation of the Bailey–Borwein–Plouffe formula, used to extract hexadecimal fractional digits of pi.

The repository includes MSVS solution files, although it should be trival to compile this library in any other C++11 compliant compiler.
To enable compile-time constexpr evaluation, you must compile with optimizations enabled (e.g., -O2).
You might also need to increase the maximum constexpr recursion depth, depending on which pi digit you seek.

See LICENSE.txt for licensing details.
