/**
* @file mp_pi.h
* @version 0.0
* @author Sebastiao Salvador de Miranda (ssm)
* @brief Compile-time metafunctions to compute pi. Part of the MetaPi library.
*        This uses the Bailey–Borwein–Plouffe formula to extract pi digits.
*        You must enable optimization on the target compiler (e.g. -O2) and
*        possibly increase the maximum constexpr recursion depth, depending
*        on which pi digit you seek.
*
* @code{.cpp}
* // This will compute the fourth hexadecimal fractional digit of pi
* // in compile-time.
* constexpr char digit{ meta_pi::PiHexDigit<3>::value };
* @endcode
*
* @copyright Copyright (c) 2016, Sebastiao Salvador de Miranda.
*            All rights reserved. See licence below.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* (1) Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*
* (2) Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in
* the documentation and/or other materials provided with the
* distribution.
*
* (3) The name of the author may not be used to
* endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>
#include <array>
#include <limits>
#include "mp_utils.h"

#ifndef _METAPI_PI_H_
#define _METAPI_PI_H_
namespace meta_pi {
/**
* @brief Get the nth hexadecimal fractional digit of pi.
*/
template<uint64_t N>
struct PiHexDigit {
  static constexpr char value{ HexCharacter<PiHexFraction<N>>::value };
};

/**
* @brief Compute pi faction digits from the Bailey–Borwein–Plouffe formula,
*        using base 16 math. TStartDigit is the index of the first fractional
*        digit of the pi to compute.
*/
template <uint64_t TStartDigit>
struct PiHexFraction {
  static constexpr double value {
    (PiHexFraction_<TStartDigit>::value -
     (int)PiHexFraction_<TStartDigit>::value + 1.0)
  };
};
template <uint64_t TStartDigit>
struct PiHexFraction_ {
  static constexpr double value{ (4.0 * PiHexSeries<1, TStartDigit>::value -
                                  2.0 * PiHexSeries<4, TStartDigit>::value -
                                  PiHexSeries<5, TStartDigit>::value -
                                  PiHexSeries<6, TStartDigit>::value) };
};
template <uint64_t M, uint64_t I, int64_t K> struct PiHexSeries_L0_;
template <uint64_t M, uint64_t I, int64_t K> struct PiHexSeries_L1_;

/**
* @brief Compute one instance of the series from Bailey–Borwein–Plouffe formula.
*        I is the index of the first fractional digit of the pi to compute.
*        M is to identify the summation instance, should be {1,4,5,6}.
*/
template <uint64_t M, uint64_t I>
struct PiHexSeries {
  static constexpr double value{ (PiHexSeries_L0_<M, I, I - 1>::value +
                                  PiHexSeries_L1_<M, I, 10>::value) };
};
template <uint64_t M, uint64_t I, int64_t K>
struct PiHexSeries_L0_ {
  static constexpr double value{
    (PiHexSeries_L0_<M, I, K - 1>::value +
    ((ModularExp<16, I - K, 8 * K + M>::value) / (8.0 * K + M)))
    -
    (int)(PiHexSeries_L0_<M, I, K - 1>::value +
          ((ModularExp<16, I - K, 8 * K + M>::value) / (8.0 * K + M)))
  };
};
template <uint64_t M, uint64_t I>
struct PiHexSeries_L0_ <M, I, -1> {
  static constexpr double value{ 0.0 };
};
template <uint64_t M, uint64_t I, int64_t K>
struct PiHexSeries_L1_ {
  static constexpr double value{
    (PiHexSeries_L1_<M, I, K - 1>::value +
    (Pow<16, K>::value > 0 ? 1.0 /
     (Pow<16, K>::value * (8.0 * (K + I) + M)) : 0.0))
    -
    (int)(PiHexSeries_L1_<M, I, K - 1>::value +
          (Pow<16, K>::value > 0 ? 1.0 / 
           (Pow<16, K>::value * (8.0 * (K + I) + M)) : 0.0))
  };
};
template <uint64_t M, uint64_t I>
struct PiHexSeries_L1_ <M, I, -1> {
  static constexpr double value{ 0.0 };
};
}
#endif
