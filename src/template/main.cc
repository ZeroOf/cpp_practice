//
// Created by Will Lee on 5/28/2024.
//


#include <iostream>

namespace TemplateFoldExpression {
// 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
template<typename... Args>
bool All(Args... args) {
  return (args && ...);
}

// 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
template<typename... Args>
bool Any(Args... args) {
  return (... || args);
}

// 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
template<typename ...Args>
int sum(Args &&... args) {
  return (args + ... + 0);
}

// 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)
template<typename ...Args>
int product(Args &&... args) {
  return (1 * ... * args);
}


void TestFoldExpression() {
  std::cout << "template_fold_expression::TestFoldExpression" << std::endl;
  std::cout << "All(true, true, false): " << All(true, true, false) << std::endl;
  std::cout << "All(true): " << All(true) << std::endl;
  std::cout << "All(): " << All() << std::endl;
  std::cout << "-----------------------------" << std::endl;

  std::cout << "Any(true, true, false): " << Any(true, true, false) << std::endl;
  std::cout << "Any(true): " << Any(true) << std::endl;
  std::cout << "Any(): " << Any() << std::endl;
  std::cout << "-----------------------------" << std::endl;

  std::cout << "sum(1, 2, 3, 4): " << sum(1, 2, 3, 4) << std::endl;
  std::cout << "sum(1, 2, 3, 4, 5): " << sum(1, 2, 3, 4, 5) << std::endl;
  std::cout << "sum(1, 2, 3, 4, 5, 6): " << sum(1, 2, 3, 4, 5, 6) << std::endl;
  std::cout << "sum(): " << sum() << std::endl;
  std::cout << "-----------------------------" << std::endl;

  std::cout << "product(1, 2, 3, 4): " << product(1, 2, 3, 4) << std::endl;
  std::cout << "product(): " << product() << std::endl;
  std::cout << "product(1, 2, 3, 4, 5): " << product(1, 2, 3, 4, 5) << std::endl;

  std::cout << "-----------------------------" << std::endl;
}

}

namespace NonTypeTemplatePackTest {
// A template class that takes a non-type template parameter pack
template<auto... Values>
struct NonTypeTemplatePack {
  // A method to print the values
  static void print() {
    ((std::cout << Values << " "), ...); // Fold expression to print all values
  }
};

template<auto... Values>
void print() {
  ((std::cout << Values << " "), ...); // Fold expression to print all values
}


void NonTypeTest() {
  std::cout << "NonTypeTemplatePackTest::Test" << std::endl;
  NonTypeTemplatePack<1, 2, 3>::print();      // Outputs: 1 2 3
  NonTypeTemplatePack<'a', 'b', 'c'>::print(); // Outputs: a b c
  NonTypeTemplatePack<true, false, true>::print(); // Outputs: 1 0 1

  constexpr int x = 42;
  constexpr int y = 7;
  NonTypeTemplatePack<x, y>::print(); // Outputs: 42 7
  std::cout << "-----------------------------" << std::endl;

  print<1, 2, 3>();
  print<'a', 'b', 'c'>();
  print<true, false, true>();
  print<x, y>();
  print<>();
  std::cout << "-----------------------------" << std::endl;
}

} // namespace NonTypeTemplatePackTest

namespace RecursiveVariadicTemplate {
void Print() {
  std::cout << "No arg Print" << std::endl;
}

template<typename T, typename ...Ts>
void Print(T v, Ts... args) {
  std::cout << v << std::endl;
  Print(args...);
}

void Test() {
  std::cout << "RecursiveVariadicTemplate::Test" << std::endl;
  Print(1, "10", 'a');
  std::cout << "-----------------------------" << std::endl;
}

}

namespace PatternExpansion {
// A function that takes a non-type template parameter pack
void PrintOneEachTime() {
  std::cout << "No more args" << std::endl;
}

template<typename T, typename ...Ts>
void PrintOneEachTime(T v, Ts... args) {
  std::cout << v << std::endl;
  PrintOneEachTime(args...);
}

template<typename T>
void PrintOneElement(T v) {
  std::cout << v << " ";
}

template<typename ...Ts>
void Print(Ts... args) {
  (PrintOneElement(args), ...);
}

// names of two parameter packs appear in the same pattern
template<class ...Args1>
struct zip {
  template<class ...Args2>
  struct with {
    using type = std::tuple<std::pair<Args1, Args2>...>;
  };
};

// pack expansion is nested within another pack expansion
template<class ...Args>
void g(Args... args) {
  Print(TemplateFoldExpression::All(args...) + args...);
  Print(TemplateFoldExpression::All(args)...);
}

void TestPatternExpansion() {
  std::cout << "PatternExpansion::TestPatternExpansion" << std::endl;
  Print(1, "10", 'a');
  std::cout << "-----------------------------" << std::endl;

  PrintOneEachTime(1, "10", 'a');
  std::cout << "-----------------------------" << std::endl;

  zip<int, float>::with<char, int>::type t{std::make_pair(1, 'a'), std::make_pair(2.1f, 'b')};
  std::apply([](const auto &... args) { ((std::cout << args.first << " " << args.second << std::endl), ...); }, t);
  std::cout << "-----------------------------" << std::endl;

  g(1, "10", 'a');
  std::cout << "-----------------------------" << std::endl;
}
}

int main() {
  TemplateFoldExpression::TestFoldExpression();
  NonTypeTemplatePackTest::NonTypeTest();
  RecursiveVariadicTemplate::Test();
  PatternExpansion::TestPatternExpansion();
  return 0;
}
