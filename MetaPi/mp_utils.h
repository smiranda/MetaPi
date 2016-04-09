/**
* @file mp_utils.h
* @version 0.0
* @author Sebastiao Salvador de Miranda (ssm)
* @brief Utilities file for compile-time operations. Part of the MetaPi library.
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

#ifndef _METAPI_UTILS_H_
#define _METAPI_UTILS_H_
namespace meta_pi {
/**
* @brief Compute integer exponentiation in compile-time TBase ^ TExp.
*        In case of overflow, 0 is returned.
*/
template <uint64_t TBase, uint64_t TExp>
struct Pow {
  static constexpr uint64_t value{
    (TBase != 0 &&
    ((((std::numeric_limits<uint32_t>::max)() - 1) / TBase) <
     Pow<TBase, TExp - 1>::value)) ? 0 : TBase * Pow<TBase, TExp - 1>::value
  };
};
template <uint64_t TBase>
struct Pow<TBase, 0> {
  static constexpr uint64_t value{ 1 };
};

/**
* @brief Compute modular exponentiation in compile-time (TBase ^ TExp) % TMod.
*        This implements the right-to-left binary method.
*/
template <uint64_t TBase, uint64_t TExp, uint64_t TMod>
struct ModularExp {
  static constexpr uint64_t value{ ModularExp_<TBase%TMod, TMod, TExp>::value };
};
template <uint64_t TBaseMod, uint64_t TMod, uint64_t TExp>
struct ModularExp_ {
  static constexpr uint64_t value{ TExp & 1 ? (
    (ModularExp_<(TBaseMod * TBaseMod) % TMod, TMod, (TExp >> 1)>::value
     * TBaseMod) % TMod) :
    (ModularExp_<(TBaseMod * TBaseMod) % TMod, TMod, (TExp >> 1)>::value)
  };
};
template <uint64_t Base, uint64_t Mod>
struct ModularExp_<Base, Mod, 0> {
  static constexpr uint64_t value{ 1 };
};

/**
* @brief Compute floating point absolute value in compile-time |TValue|.
*/
template<typename TValue>
struct Abs {
  static constexpr double value{
    TValue::value >= 0.0 ? TValue::value : -TValue::value
  };
};

static constexpr std::array<char, 16> IntToHexChar{ {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8','9', 'A', 'B', 'C', 'D', 'E', 'F'
  } };

/**
* @brief Convert the first fractional digit of the input fractional value
*        to an hexadecimal character. The input type must supply a
*        floating-point value via ::value.
*/
template<typename THexFraction>
struct HexCharacter {
  static constexpr char value{
    IntToHexChar[(int)(16 * (Abs<THexFraction>::value
    - ((int)Abs<THexFraction>::value)))]
  };
};
}
#endif
