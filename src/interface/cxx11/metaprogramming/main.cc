
#include <util/util.h>

template<bool Condition, typename TrueType, typename FalseType>
using conditional_t = typename std::conditional<Condition, TrueType, FalseType>::type;

int main() {
  using TrueType = std::integral_constant<bool, true>;
  using FalseType = std::integral_constant<bool, false>;

  using SelectedType = conditional_t<TrueType::value, int, double>;

  if (std::is_same<SelectedType, int>::value) {
    std::cout << "SelectedType is int" << std::endl;
  } else if (std::is_same<SelectedType, double>::value) {
    std::cout << "SelectedType is double" << std::endl;
  } else {
    std::cout << "SelectedType is neither int nor double" << std::endl;
  }

  return 0;
}
