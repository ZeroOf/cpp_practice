
#include <iostream>

long double operator ""_w(long double input) {
  std::cout << __FUNCTION__ << ":" << input << std::endl;
  return input;
}

std::string operator ""_w(const char16_t *input, size_t) {
  std::cout << __FUNCTION__ << ":" << input << std::endl;
  std::wcout << input << std::endl;
  wchar_t a;
  std::u16string ws(input);
  std::string test(ws.begin(), ws.end());
  return test;
}

void operator ""_w(unsigned long long input) {
  std::cout << __FUNCTION__ << ":" << input << std::endl;
}

unsigned operator ""_w(const char *input, size_t n) {
  std::cout << __FUNCTION__ << ":" << input << std::endl;
  return n;
}

int main() {
  1.2_w;    // calls operator ""_w(1.2L)
  std::cout << u"one"_w << std::endl;// calls operator ""_w(u"one", 3)
  12_w;     // calls operator ""_w("12")
  "two"_w;  // error: no applicable literal operator
}