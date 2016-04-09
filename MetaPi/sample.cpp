#include "deps\microunit.h" // optional, just for unit testing
#include "mp_pi.h"

// This is all computed in compile-time !
constexpr std::array<char, 4> pi_4hex_digits {{
  meta_pi::PiHexDigit<0>::value,
  meta_pi::PiHexDigit<1>::value,
  meta_pi::PiHexDigit<2>::value,
  meta_pi::PiHexDigit<3>::value
}};

UNIT(Test4Digits) {
  std::string pi_string(pi_4hex_digits.begin(), pi_4hex_digits.end());
  std::cout << pi_string << std::endl;
  ASSERT_TRUE(pi_string == std::string("243F"));
};

int main() {
  microunit::UnitTester::Run();
}