
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdarg>

using namespace std;

void PrintVariance(std::size_t count, const char *fmt, ...) {
  double sum = 0;
  double sum_sq = 0;
  va_list args;
  va_start(args, fmt);
  for (std::size_t i = 0; i < count; ++i) {
    double d = va_arg(args, double);
    sum += d;
    sum_sq += d * d;
  }
  va_end(args);
  printf(fmt, sum_sq / count - (sum / count) * (sum / count));
}

void NanoPrintf(const char *fmt, ...) {
  std::va_list args;
  va_start(args, fmt);

  for (const char *p = fmt; *p != '\0'; ++p) {
    switch (*p) {
      case '%':
        switch (*++p) // read format symbol
        {
          case 'i':std::cout << va_arg(args, int);
            continue;
          case 'f':std::cout << va_arg(args, double);
            continue;
          case 's':std::cout << va_arg(args, const char*);
            continue;
          case 'c':std::cout << static_cast<char>(va_arg(args, int));
            continue;
          case '%':std::cout << '%';
            continue;
            /* ...more cases... */
        }
        break; // format error...
      case '\n':std::cout << '\n';
        continue;
      case '\t':std::cout << '\t';
        continue;
    }
    std::cout << *p;
  }

  va_end(args);
}

void TestVariadicParameter() {
  std::cout << "TestPrintVariance" << std::endl;
  PrintVariance(3, "variance = %f\n", 1.0, 2.0, 3.0);
  PrintVariance(4, "variance = %f\n", 1.0, 2.0, 3.0, 4.0);
  PrintVariance(5, "variance = %f\n", 1.0, 2.0, 3.0, 4.0, 5.0);
  std::cout << std::endl;

  std::cout << "TestNanoPrintf" << std::endl;
  NanoPrintf("Hello %s\n", "world");
  NanoPrintf("Hello %i %s\n", 10, "world");
  NanoPrintf("Hello %i %i %i\n", 1, 2, 3);
  NanoPrintf("Hello %i %i %i %i\n", 1, 2, 3, 4);
  NanoPrintf("Hello %i %i %i %i %i\n", 1, 2, 3, 4, 5);
  NanoPrintf("Hello %f\n", 1.1);
  NanoPrintf("Hello %f %f\n", 1.2, 2.3);
  NanoPrintf("Hello %f %f %f\n", 1.4, 2.5, 3.6);
  NanoPrintf("Hello %f %f %f %f\n", 1.11, 2.22, 3.33, 4.444);

  std::cout << std::endl;
}

int main() {
  TestVariadicParameter();
}