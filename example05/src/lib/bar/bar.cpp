
#include <iostream>
#include "bar.hpp"
#include "baz.hpp"

void bar() {
  std::cout << "bar\n";
  baz();

  return;
}


